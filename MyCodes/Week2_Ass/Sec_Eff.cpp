#include "iostream"
#include "stdio.h"
using namespace std;

int Fib_LastDigit_Eff(int num)
{
    int arr[num];
    arr[0]= 0;
    arr[1]= 1;
    for(int i=2; i<=num; i++)
    {
        arr[i]= (arr[i-1]+arr[i-2])%10;
    }
    return arr[num];
}

int main()
{
    int n=0, res=0;
    cout<<"Please Enter an integer\n";
    cin>>n;
    res =Fib_LastDigit_Eff(n);
    cout<<res;
    getchar();
    return 0;
}
