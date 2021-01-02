#include "iostream"
#include "stdio.h"
using namespace std;

int FibList(int n)
{
	int Fib_arr[n];
    Fib_arr[0]= 0;
    Fib_arr[1]= 0;
    for(int i=2; i<n; i++)
    {
        Fib_arr[i]= Fib_arr[i-1]+Fib_arr[i-2];
    }
    return Fib_arr[n];
}

int main(void)
{
    int num=0, res=0;
	cout<<"Please enter an integer\n";
	cin>>num;
	res = FibList(num);
	cout<<"the result is = "<<res;
    getchar();
	return 0;
}
