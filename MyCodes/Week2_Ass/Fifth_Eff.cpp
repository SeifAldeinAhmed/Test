#include "iostream"
#include "stdio.h"
using namespace std;

long long int pisano(long long int m)
{
    long long int prev = 0;
    long long int curr = 1;
    long long int res = 0;

    for(int i = 0; i < m * m; i++)
    {
        long long int temp = 0;
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;

        if (prev == 0 && curr == 1)
            res= i + 1;
    }
    return res;
}

long long int Fib_Again_Naive(long long int n, long long int m)
{
    long long int appreviated_num= 0, pisano_length= 0;
    pisano_length= pisano(m);           //pisano(3)= 8
    cout<<"pisano length= "<<pisano_length<<"\n";
    appreviated_num = n % pisano_length; // 2015%8= 7
    int arr[appreviated_num];           //arr[7]
    arr[0]= 0;
    arr[1]= 1;
    for(int i=2; i<=appreviated_num; i++)
    {
        arr[i]= (arr[i-1]+arr[i-2])%m;
    }
    return arr[appreviated_num];
}

int main()
{
    long long int n=0,m=0;
    long long int res=0;
    cout<<"Please Enter 2 integers\n";
    cin>>n>>m;
    res =Fib_Again_Naive(n,m);
    cout<<"res= "<<res;
    getchar();
    return 0;
}
