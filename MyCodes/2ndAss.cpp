#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
//using std::max;

long long int maxPairwiseProudct(const vector<int>& numbers)
{
	long long int product=0;
	int n= numbers.size();
	for(int i=0; i< n; i++)
	{
		for(int j= i+1; j< n; j++)
		{
			//product= max(product,(long long int)numbers[i]*numbers[j]);
			if((long long int)numbers[i]*numbers[j] > product)
			{
				product= (long long int)numbers[i]*numbers[j];
			}
		}
	}	
	return product;
}

long long int maxPairwiseProudctFast(const vector<int>& numbers)
{
	long long int product=0;
	int maxint1=-1;
	int maxint2=-1;
	
	for(int i=0; i< numbers.size(); i++)
	{
		if((maxint1== -1)||(numbers[i]> numbers[maxint1]))
		{
			maxint1 = i;
		}
	}	
	for(int j=0; j< numbers.size(); j++)
	{
		if((numbers[j] != numbers[maxint1])&&(maxint2 == -1)||(numbers[j]> numbers[maxint2]))
		{
			maxint2 = j;
		}
	}
	product= ((long long int)(numbers[maxint1]) * (numbers[maxint1]));
	return product;
}

int main()
{
	//Taking number of array elements
	int n;
	cin >> n;
	//Array Initialization
	vector<int> numbers(n);
	for(int i=0; i<n; i++)
	{
		cin >> numbers[i];
	}
	long long int result = maxPairwiseProudctFast(numbers);
	cout<<result<<"\n";
	return 0;
}