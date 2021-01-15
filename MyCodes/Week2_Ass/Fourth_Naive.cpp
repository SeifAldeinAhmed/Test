#include "iostream"
#include "stdio.h"
using namespace std;

//a=4 , b=8 then d= 24
int LCM_Naive(int a, int b)
{
    int LCM = a*b;
    for(int d=1; d < LCM; d++)
    {
        if((d%a==0) && (d%b==0))
        {
                LCM = d;
        }
    }
    return LCM;
}

int main()
{
    int n1=0, n2=0, res=0;
    cout<<"Please Enter two integers\n";
    cin>>n1>>n2;
    res = LCM_Naive(n1, n2);
    cout<<res;
    getchar();
    return 0;
}
