#include "iostream"
#include "stdio.h"
using namespace std;

int GCD_Eff(long long int a, long long int b)
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


//a=4 , b=8 then d= 24
long long int LCM_Eff(long long int a,long long int b)
{
    return (a*b)/GCD_Eff(a,b);
}

int main()
{
    int n1=0, n2=0;
    long long int res=0;
    cout<<"Please Enter two integers\n";
    cin>>n1>>n2;
    res =LCM_Eff(n1, n2);
    cout<<res;
    getchar();
    return 0;
}
