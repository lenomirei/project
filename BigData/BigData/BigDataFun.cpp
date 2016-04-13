#include"BigData.h"
#include<cassert>




#define MAXINT 0x7fffffffffffffff
#define MININT 0x8000000000000000

BigData::BigData()
	:m_strData("")
	,m_value(0)
{

}

BigData::BigData(INT64 num)
	:m_value(num)
{
	//执行数字转换成字符串的操作
	INT64toStr(num);
}

//12345,-12345,-0015586,+4564aa1321
BigData::BigData(const char* Data)
{
	INT64 iTemp = 0;
	char symbol;
	assert(Data);
	char *pData = (char *)Data;//不强转就无法赋值
	if ('+' == pData[0] || '-' == pData[0])
	{
		symbol = pData[0];
		pData++;
	}
	else if (*pData >= '0'&&*pData <= '9')
	{
		symbol = '+';
	}
	else
	{
		m_value = 0;
		m_strData = "0";
		return;
	}
	while (*pData == '0')
	{
		pData++;
	}
	m_strData.resize(strlen(pData) + 1);
	m_strData[0] = symbol;
	for (int i = 1; i < strlen(Data) + 1; i++)
	{
		if (*pData >= '0'&&*pData <= '9')
		{
			iTemp = iTemp * 10 + *pData - '0';
			m_strData[i] = *pData;
			pData++;
		}
		else
		{
			break;
		}
	}
	if ('-' == symbol)
	{
		iTemp = 0 - iTemp;
	}
	m_value = iTemp;
	//if (0 == strcmp(Data, "0"))
	//{
	//	m_strData.append(1, '0');
	//	return;
	//}
}

bool BigData::IsINT64OverFlow()
{
	string strtmp;
	if ('-' == m_strData[0])
	{
		strtmp = "-9223372036854775807";
	}
	else
	{
		strtmp = "+9223372036854775807";
	}
	if (m_strData.size() > strtmp.size())
	{
		return true;
	}
	if (m_strData.size() == strtmp.size() && m_strData>strtmp)
	{
		return true;
	}
	return false;
}


BigData BigData::operator+(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		if (m_strData[0] != b.m_strData[0])
		{
			return BigData(m_value + b.m_value);
		}
		else
		{
			if ('-' == m_strData[0] && MININT - m_value < b.m_value)
			{
				return BigData(m_value + b.m_value);
			}
			if ('+' == m_strData[0] && MAXINT - m_value > b.m_value)
			{
				return BigData(m_value + b.m_value);
			}
		}
	}
	else
	{
		string strret;
		if (m_strData[0] == b.m_strData[0])
		{
			strret = Add(m_strData, b.m_strData);
			return BigData(strret.c_str());
		}
		else
		{
			strret = Sub(m_strData, b.m_strData);
			return BigData(strret.c_str());
		}
	}
}


BigData BigData::operator-(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		if (m_strData[0] != b.m_strData[0])
		{
			if (('-' == m_strData[0] && MININT + b.m_value<m_value) || '+' == m_strData[0] && MAXINT + b.m_value>m_value)
			{
				return BigData(m_value - b.m_value);
			}
			else
			{
				string strret = Sub(m_strData, b.m_strData);
				return BigData(strret.c_str());
			}
		}
		else
		{
			return BigData(m_value - b.m_value);
		}
	}
	else
	{
		if (m_strData[0] != b.m_strData[0])
		{
			string strret = Add(m_strData, b.m_strData);
			return BigData(strret.c_str());
		}
		else
		{
			string strret = Sub(m_strData, b.m_strData);
			return BigData(strret.c_str());
		}
	}
}

BigData BigData::operator*(BigData b)
{
	if (0 == m_value || b.m_value == 0)
	{
		return BigData(INT64(0));
	}
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		if (m_strData[0] == b.m_strData[0])
		{
			if (('+' == m_strData[0] && MAXINT / m_value <= b.m_value) || ('-' == m_strData[0] && MAXINT / m_value <= b.m_value))
			{
				return BigData(m_value*b.m_value);
			}
		}
		else
		{
			if (('-' == m_strData[0] && MININT / m_value <= b.m_value) || ('+' == m_strData[0] && MININT / m_value >= b.m_value))
			{
				return BigData(m_value*b.m_value);
			}
		}
	}
	else
	{
		string strret;
		strret = Mul(m_strData, b.m_strData);
		return strret.c_str();
	}
	
}

string BigData::Add(string left, string right)
{
	int lSize = left.size();
	int rSize = right.size();
	if (lSize < rSize)
	{
		swap(lSize, rSize);
		swap(left, right);
	}
	string strret;
	strret.resize(left.size() + 1);
	strret[0] = left[0];
	int CS = 0;
	for (int i = 1; i < left.size(); i++)
	{
		int ctmp;
		ctmp= left[lSize - i] - '0' + CS;
		if (i < rSize)
		{
			ctmp += right[rSize - i] - '0';
		}
		//本位和进位的处理
		strret[lSize - i + 1] = ctmp % 10 + '0';
		CS = ctmp / 10;
	}
	strret[1] = CS='0';
	return strret;
}


string BigData::Sub(string left, string right)
{
	int iLsize = left.size();
	int iRsize = right.size();
	string strret;
	strret.resize(iLsize);
	if (iLsize < iRsize || (iLsize == iRsize && left < right))
	{
		swap(iLsize, iRsize);
		swap(left, right);
	}
	strret[0] = left[0];
	int CS = 0;
	for (int index = 1; index < iLsize; index++)
	{
		
		int cmp;
		cmp = (left[iLsize - index] - '0') - CS;
		if (index < iRsize)
		{
			cmp -= (right[iRsize - index] - '0');
			
		}
		if (cmp < 0)
		{
			CS = 1;
			cmp += 10;
		}
		else
		{
			CS = 0;
		}
		strret[iLsize - index] = cmp + '0';
	}
	strret[1] = '0' - CS;
	return strret;
}


string BigData::Mul(string left, string right)
{
	char symbol;
	int iLsize = left.size();
	int iRsize = right.size();
	if (iLsize > iRsize)
	{
		swap(iLsize, iRsize);
		swap(left, right);
	}
	if (left[0] == right[0])
	{
		symbol = '+';
	}
	else
	{
		symbol = '-';
	}
	string strret;
	strret.assign(iRsize + 1, '0');
	strret[0]= symbol;
	int offset = 0;//错位变量，在进行乘法的时候，每一位相乘的时候会有一个错位
	int iDataLen = iRsize + 1;
	for (int ildx = 1; ildx < iLsize; ++ildx)
	{
		int cleft = left[iLsize - ildx] - '0';
		int CS = 0;//进位变量，用来记录进位的数
		for (int irdx = 1; irdx < iRsize; ++irdx)
		{
			int retmp = cleft*(right[iRsize - irdx] - '0');
			retmp += CS;
			retmp += (strret[iDataLen - offset - irdx] - '0');
			strret[iDataLen - offset - irdx]= retmp % 10 + '0';
			CS = retmp / 10;
		}
		strret[iDataLen - offset - iRsize] += CS;
		offset++;
	}
	return strret;
}


void BigData::INT64toStr(INT64 num)
{
	INT64 temp = num;
	int count = 0;
	if (temp < 0)
	{
		temp = 0 - temp;
	}
	while (temp)
	{
		temp = temp / 10;
		count++;
	}
	m_strData.resize(count+1);
	if (num < 0)
	{
		m_strData[0] = '-';
	}
	else
	{
		m_strData[0] = '+';
	}
	for (int i = 1; i < count; i++)
	{
		m_strData[count - i] = '0' + num%10;
		num = num / 10;
	}
}

ostream& operator<<(ostream& ostr, BigData b)
{
	if (!b.IsINT64OverFlow())
	{
		ostr << b.m_value << "    ";
	}
	if (b.m_strData[0] == '+')
	{
		ostr << (char *)b.m_strData.c_str() + 1;
	}
	else
	{
		ostr << b.m_strData;
	}
	return ostr;
}
istream& operator>>(istream& istr, BigData b)
{
	istr >> b.m_value;
	istr >> b.m_strData;
	return istr;
}



BigData BigData::operator/(BigData b)
{
	if (b.m_value == 0)
	{
		assert("除数不能为0！");
	}
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		
			return BigData(m_value / b.m_value);
		
	}
	else
	{
		if (b.m_value == 0)
		{
			assert("除数不能为0！");
		}
		return BigData(Div(m_strData, b.m_strData).c_str());
	}
	
}
string BigData::Div(string left, string right)
{
	string strret;
	char symbol = '+';
	if (left[0] != right[0])
	{
		symbol = '-';
	}
	if ("-1" == right || right == "+1")
	{
		return left;
	}
	int iLSize = left.size();
	int iRSize = right.size();
	if (iLSize < iRSize || (iLSize == iRSize && left < right))
	{
		swap(left, right);
		swap(iLSize, iRSize);
	}
	char *pLeft = (char *)left.c_str() + 1;
	char *pRight = (char *)right.c_str() + 1;
	int DataLen = 1;
	strret.append(1, symbol);
	for (int ildx = 0; ildx < iLSize-1;)
	{
		if ('0' == *pLeft)
		{
			pLeft ++;
			strret.append(1, '0');
			ildx++;
			continue;
		}//排除被除数自身本身携带的‘0’
		if (!IsLeftStrBig(pLeft, DataLen, pRight, iRSize - 1))
		{
			DataLen++;
			if (ildx + DataLen > iLSize)
			{
				break;
			}
			strret.append(1, '0');
			continue;
		}
		else
		{
			strret.append(1, SubLoop(pLeft, DataLen, pRight, iRSize-1));
		}
		while ('0' == *pLeft && DataLen>0)
		{
			pLeft++;
			ildx++;
			DataLen--;
			/*strret.append(1, '0');*/
		}//删除掉因为进行减法而出现的0
	}
	return strret;
}
bool BigData::IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize)
{
	assert(NULL != pLeft && NULL != pRight);
	if (LSize > RSize || (LSize == RSize && strncmp(pLeft, pRight, LSize) >= 0))//为什么不使用strcmp因为我们传进来的不是以\0结尾的，只传进来一部分字串
	{
		return true;
	}
	return false;
}
char BigData::SubLoop(char *pLeft, int LSize, char *pRight, int RSize)
{
	assert(NULL != pLeft && NULL != pRight);
	char cret = '0';
	while (true)
	{
		if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
		{
			break;
		}
		else
		{
			int LDataLen = LSize;
			int RDataLen = RSize;

			while (LDataLen >= 0 && RDataLen >= 0)
			{
				if (pLeft[LDataLen] < pRight[RDataLen])
				{
					pLeft[LDataLen - 1] -= 1;
					pLeft[LDataLen] += 10;
				}
				pLeft[LDataLen] = pLeft[LDataLen] - (pRight[RDataLen] - '0');
				LDataLen--;
				RDataLen--;
			}
			while (*pLeft == '0' && LSize > 0)
			{
				pLeft++;
				LSize--;
			}
		}
		cret++;
	}
	return cret;
}

BigData BigData::operator%(BigData b)
{
	if (b.m_value == 0)
	{
		assert("除数不能为0！");
	}

	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		return BigData(m_value%b.m_value);
	}
	else
	{
		return BigData(Mol(m_strData, b.m_strData).c_str());
	}
}string BigData::Mol(string left, string right)
{
	string strret;
	char symbol = '+';
	if (left[0] == '-')
	{
		symbol = '-';
	}
	if ("-1" == right || right == "+1")
	{
		return left;
	}
	int iLSize = left.size();
	int iRSize = right.size();
	if (iLSize < iRSize || (iLSize == iRSize && left < right))
	{
		swap(left, right);
		swap(iLSize, iRSize);
	}
	char *pLeft = (char *)left.c_str() + 1;
	char *pRight = (char *)right.c_str() + 1;
	int DataLen = 1;
	strret.append(1, symbol);
	for (int ildx = 1; ildx < iLSize - 1;)
	{
		if ('0' == *pLeft)
		{
			pLeft++;
			strret.append(1, '0');
			ildx++;
			continue;
		}
		if (!IsLeftStrBig(pLeft, DataLen, pRight, iRSize - 1))
		{
			DataLen++;
			if (ildx + DataLen > iLSize)
			{
				break;
			}
			strret.append(1, '0');
			continue;
		}
		else
		{
			strret.append(1, SubLoop(pLeft, DataLen, pRight, iRSize - 1));
		}
		while ('0' == *pLeft && DataLen>0)
		{
			pLeft++;
			ildx++;
			DataLen--;
			/*strret.append(1, '0');*/
		}
	}
	return string(left);
}


