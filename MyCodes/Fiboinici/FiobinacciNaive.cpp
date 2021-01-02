#include "iostream"
#include "stdio.h"
using namespace std;

int FibRecurs(int n)
{
	if(n<=1)
	{
		return n;
	}
	else
	{
		return FibRecurs(n-1)+FibRecurs(n-2);
	}
}

int main(void)
{
	int num=0, res=0;
	cout<<"Please enter an integer\n";
	cin>>num;
	res = FibRecurs(num);
	cout<<"the result is = "<<res;
	getchar();
	return 0;
}

