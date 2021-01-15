#include "iostream"
#include "stdio.h"
using namespace std;

int GCD_Naive(int num1, int num2)
{
    int Greatest_div=0;                                   //Initialize the variable to be returned with zeros
    for(int div=1; div <= num1 && div <= num2; div++)    //The condition is that the div. must be less than or equal both numbers
    {
        if( (num1 % div ==0) && (num2 % div==0) )               //Check the ability of division on it
        {
            if(div >= Greatest_div)                             //Comparing it with the greatest one
            {
                Greatest_div= div;                             //Assigning it to the greatest one
            }
        }
    }
    return Greatest_div;                                       //Returning it
}

int main()
{
    int n1=0, n2=0, res=0;
    cout<<"Please Enter two integers\n";
    cin>>n1>>n2;
    res =GCD_Naive(n1, n2);
    cout<<res;
    getchar();
    return 0;
}
