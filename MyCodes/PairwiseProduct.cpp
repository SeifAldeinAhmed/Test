#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

long long int maxPairwiseProduct(const vector<int> &numbers)
{
    long long int product=0;
    int n= numbers.size();
    for(int i=0; i<n; i++)
    {
        for(int j= i+1; j<n; j++)
        {
            if( ((long long int)numbers[i]*numbers[j]) > product)
            {
                product= ((long long int)numbers[i]*numbers[j]);
            }
        }
    }
    return product;
}

long long int maxPairwiseProductFast(const vector<int> &numbers)
{
    long long int product;
    int n= numbers.size();
    int maxindex1= -1;
    //check on indexes
    for(int i=0; i<n; i++)
    {
        if((maxindex1==-1) || (numbers[i]>numbers[maxindex1]))
        {
            maxindex1= i;
        }
    }
    int maxindex2= -1;
    for(int j=0; j<n; j++)
    {
        if((j!=maxindex1) && ((maxindex2==-1) || (numbers[j]>numbers[maxindex2])) )
        {
            maxindex2= j;
        }
    }
    product= ((long long int)(numbers[maxindex1]))*numbers[maxindex2];
    return product;
}

int main()
{
    /*
    //*Stress Test is a technique that applied on our main solution and another slow, not good enough solution to debug.
    //it consists of an infinite loop which we generated a random input tests  to check the results of 2 solutions.
    while(true)
    {
        int n= rand() % 1000 +2; //get number of numbers to be multiplied between 2 numbers to 5.
        cout<<n<<"\n";
        vector<int> a; //here we create a vector of n numbers.
        for(int i=0; i<n; i++)
        {
            a.push_back(rand()%100000); //numbers from 0 to 99,999 to be added to this vector.
        }
        for(int i=0; i<n; i++)
        {
            cout<<a[i]<<' ';  //printing them on screen separated by space.
        }
        cout<<"\n";
        //Launch our solutions to this input test
        long long int res1= maxPairwiseProduct(a);
        long long int res2= maxPairwiseProductFast(a);
        //here we are comparing them, if they are different that means that at least one of them is wrong.
        if(res1!=res2)
        {
            cout<<"Wrong Answer: "<<res1<<" "<<res2<<"\n";
            break;  //we will end infinite loop as soon as our solutions differ.
        }
        else{
            cout<<"OK"<<"\n"; //printing OK if they generate the same results.
        }
    }*/
    int n;
    cin>>n;
    vector<int> numbers(n);
    for(int i=0; i<n; i++)
    {
        cin>>numbers[i];
    }
    long long int result= maxPairwiseProductFast(numbers);
    cout<<result<<"\n";
    return 0;
}
