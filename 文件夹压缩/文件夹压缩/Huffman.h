#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;

template<class T>
struct HuffmanNode
{
	T _value;
	HuffmanNode* _left;
	HuffmanNode* _right;
	HuffmanNode(T x)
		:_value(x)
		, _left(NULL)
		, _right(NULL)
	{

	}
};

template<class T>
class HuffmanTree
{
public:
	HuffmanTree()
		:_root(NULL)
	{
		
	}
	HuffmanNode<T> *ReturnRootNode()
	{
		return _root;
	}
	//vector<string> HuffmanCode(T* a,size_t size)
	//{
	//	vector<string> test;
	//	test.resize(size);
	//	for (int i = 0; i < size; ++i)
	//	{
	//		_Find(_root, test[i], a[i]);
	//	}
	//	return test;
	//}
	void CreateHuffmanTree(T *a, size_t size,T& invalid)
	{
		vector<HuffmanNode<T> *> v;
		for (int i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
			{
				v.push_back(new HuffmanNode<T>(a[i]));
			}	
		}
		for (int i = (v.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(v, i, v.size());
		}
		while (v.size() > 1)
		{
			HuffmanNode<T> *left = v[0];
			swap(v[0], v[v.size() - 1]);
			v.pop_back();
			AdjustDown(v, 0, v.size());
			HuffmanNode<T> *right = v[0];
			swap(v[0], v[v.size() - 1]);
			v.pop_back();
			AdjustDown(v, 0, v.size());
			HuffmanNode<T> *parent = new HuffmanNode<T>(left->_value + right->_value);
			parent->_left = left;
			parent->_right = right;
			v.push_back(parent);
			AdjustDown(v, 0, v.size());
		}
		_root = v[0];
		v.pop_back();
	}
protected:
	void AdjustDown(vector<HuffmanNode<T> *> &a, int root, size_t size)
	{
		int child = root * 2 + 1;
		while (child < size)
		{
			if (child + 1 < size && a[child + 1]->_value < a[child]->_value)
			{
				child++;
			}
			if (a[child]->_value < a[root]->_value)
			{
				swap(a[child], a[root]);
				root = child;
				child = root * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	/*HuffmanNode<T> *_Find(HuffmanNode<T> *root,string &str, const T &x)
	{
		if (root == NULL)
		{
			str.pop_back();
			return NULL;
		}
		if (root->_value == x && root->_left==NULL && root->_right==NULL)
		{
			return root;
		}
		else
		{
			str.push_back('0');
			HuffmanNode<T> *tmp = _Find(root->_left,str, x);
			if (root->_left && tmp)
			{
				return tmp;
			}
			else
			{
				str.push_back('1');
				HuffmanNode<T> *tmp2 = _Find(root->_right, str, x);
				if (tmp == NULL && tmp2 == NULL)
				{
					str.pop_back();
				}
				return tmp2;
			}
		}
		return NULL;
	}*/
	
protected:
	HuffmanNode<T> *_root;
};