#pragma once
#include<string>
using namespace std;


typedef long long INT64;
class BigData
{
public:
	BigData();
	BigData(INT64 num);
	BigData(const char *Data);
	bool IsINT64OverFlow();
	friend ostream& operator<<(ostream& ostr, BigData b);
	friend istream& operator>>(istream& istr, BigData b);
	BigData operator+(BigData b);
	BigData operator-(BigData b);
	BigData operator*(BigData b);
	BigData operator/(BigData b);
	BigData operator%(BigData b);
private:
	string   Add(string left, string right);
	string   Sub(string left, string right);
	string   Mul(string left, string right);
	string   Div(string left, string right);
	string   Mol(string left, string right);
	bool IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize);
	char SubLoop(char * pLeft, int  LSize, char * pRight, int RSize);
	void INT64toStr(INT64 num);
private:
	INT64 m_value;
	string m_strData;
};