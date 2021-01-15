#include "iostream"
#include "stdio.h"
using namespace std;

long long int GCD_Eff(long long int a, long long int b)
{
    //Here We will use Euclidean Algorithm to Calculate it
    if(a == 0)
    {
        return b;
    }
    else{
        return GCD_Eff(b % a, a);
    }
}

int main()
{
    int n1=0, n2=0;
    long long int res=0;
    cout<<"Please Enter two integers\n";
    cin>>n1>>n2;
    res =GCD_Eff(n1, n2);
    cout<<res;
    getchar();
    return 0;
}
