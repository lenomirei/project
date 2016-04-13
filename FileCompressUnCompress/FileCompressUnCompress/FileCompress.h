#pragma once
#include<iostream>
#include<string>
#include<cassert>
#include"Huffman.h"
using namespace std;


typedef long LongType;
struct CharInfo
{
	unsigned char _ch;
	LongType _count;
	string _code;
	CharInfo(unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
	{
	}
	bool operator!=(CharInfo &c)
	{
		return this->_count != c._count;
	}
	CharInfo operator+(CharInfo &c)
	{
		CharInfo tmp;
		tmp._count = this->_count + c._count;
		return tmp;
	}
	bool operator<(CharInfo &c)
	{
		return this->_count < c._count;
	}
	bool operator>(CharInfo &c)
	{
		return this->_count>c._count;
	}
};


class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}
public:
	bool Compress(const char *filename)
	{
		assert(filename);
		FILE *fIn;
		string path = filename;
		path += ".txt";
		fIn = fopen(path.c_str(), "r");
		assert(fIn);
		char ch = fgetc(fIn);
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fIn);
		}
		HuffmanTree<CharInfo> ht;
		ht.CreateHuffmanTree(_infos, 256, CharInfo());
		string tmp;
		GetHuffmanCode(ht.ReturnRootNode(), tmp);
		string CompressFilename = filename;
		CompressFilename += ".Huffman";
		FILE *fInCompress;
		fInCompress = fopen(CompressFilename.c_str(), "w");
		assert(fInCompress);
		fseek(fIn, 0, SEEK_SET);
		ch = fgetc(fIn);
		unsigned char InCh = 0;
		int index = 0;
		int count = 0;
		while (ch != EOF)
		{
			string Code = _infos[(unsigned char)ch]._code;
			for (int i = 0; i < Code.size(); ++i)
			{

				InCh = InCh << 1;

				if (Code[i] == '1')
				{
					InCh |= 1;
				}
				if (++index == 8)
				{
					fputc(InCh, fInCompress);
					index = 0;
					InCh = 0;
				}
				count++;
			}
			ch = fgetc(fIn);
		}//当index!=0时证明没写完需要进行处理
		if (index != 0)
		{
			InCh = InCh << (8 - index);
			fputc(InCh, fInCompress);
		}
		FILE *fconfig;
		string ConfigFilename = filename;
		ConfigFilename += ".config";
		fconfig = fopen(ConfigFilename.c_str(), "w+");
		assert(fconfig);

		fputc(count + '0', fconfig);

		for (int i = 0; i < 256; ++i)
		{
			if (_infos[i] != CharInfo())
			{
				fputc(_infos[i]._ch, fconfig);
				fputc(_infos[i]._count + '0', fconfig);
				fputc('\n', fconfig);
			}
		}
		fclose(fIn);
		fclose(fInCompress);
		fclose(fconfig);
		return true;
	}
	void UnCompress(const char *huffmanfilename, const char *configfilename)
	{
		FILE *configfile;
		configfile = fopen(configfilename, "r");
		assert(configfile);
		int count = fgetc(configfile) - '0';
		char ch = fgetc(configfile);
		while (ch != EOF)
		{
			unsigned char index = (unsigned char)ch;
			ch = fgetc(configfile);
			_infos[index]._count = ch - '0';
			ch = fgetc(configfile);
			ch = fgetc(configfile);
		}
		HuffmanTree<CharInfo> ht;
		ht.CreateHuffmanTree(_infos, 256, CharInfo());
		string tmp;
		GetHuffmanCode(ht.ReturnRootNode(), tmp);
		FILE *huffmanfile;
		huffmanfile = fopen(huffmanfilename, "r");
		assert(huffmanfile);
		FILE *fOut;
		fOut = fopen("outputfile.txt", "w");
		assert(fOut);
		//跟1与，向右移

		ch = fgetc(huffmanfile);
		HuffmanNode<CharInfo> *root = ht.ReturnRootNode();
		if (root->_left == NULL && root->_right == NULL)
		{
			//只有一个节点的情况
			fputc(root->_value._ch, fOut);
		}
		int index = 0;

		int i = 0;//进行计数

		while (ch != EOF && i < count)
		{
			if (((unsigned char)ch & (unsigned char)128) == 0)
			{
				root = root->_left;
				if (root->_left == NULL && root->_right == NULL)
				{
					fputc(root->_value._ch, fOut);
					root = ht.ReturnRootNode();
				}
			}
			else
			{
				root = root->_right;
				if (root->_left == NULL && root->_right == NULL)
				{
					fputc(root->_value._ch, fOut);
					root = ht.ReturnRootNode();
				}
			}
			i++;
			ch = ch << 1;
			if (++index == 8)
			{
				ch = fgetc(huffmanfile);
				index = 0;
			}
		}
	}
	void GetHuffmanCode(HuffmanNode<CharInfo> *root, string & str)
	{
		if (root == NULL)
		{
			return;
		}//采用后序遍历的方式
		str += '0';
		GetHuffmanCode(root->_left, str);
		str.pop_back();
		str += '1';
		GetHuffmanCode(root->_right, str);
		str.pop_back();
		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_value._ch]._code = str;
		}
	}
protected:
	CharInfo _infos[256];
};



void TestFileCompress()
{
	FileCompress f;
	f.Compress("test");
	f.UnCompress("test.Huffman", "test.config");
}