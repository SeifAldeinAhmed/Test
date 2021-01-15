#include "iostream"
#include "stdio.h"
using namespace std;

int Fib_Rec(int num)
{
    if(num <= 1)
    {
        return num;
    }
    else{
        return Fib_Rec(num-1)+Fib_Rec(num-2);
    }
}

int main()
{
    int n=0, res=0;
    cout<<"Please Enter num\n";
    cin>>n;
    res =Fib_Rec(n);
    cout<<res;
    getchar();
    return 0;
}
