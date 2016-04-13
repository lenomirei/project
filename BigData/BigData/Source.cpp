#include"BigData.h"
#include<iostream>
void test()
{
	BigData b1("-1235489");

	BigData b2("-123adsda5489");
	BigData b3("-00001235489");
	BigData b4("+1235489");
	BigData b5("1235489");

	BigData b6("-123");
	BigData b7("1000000000000000000000000000000000");
	BigData b8("8242481989159128295");
	//cout << b1 << endl;
	//cout << b2 << endl;
	//cout << b3 << endl;
	//cout << b4 << endl;
	//cout << b5 << endl;
	//cout << b6 << endl;
	cout << b7/b8 << endl;
}


int main()
{
	test();
	return 0;
}