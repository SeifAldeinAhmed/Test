#include <stdio.h>
#include <iostream>
#include <vector>

/*Vectors are dynamic, array are static size, if we don't put & before vector's name, func. will take action on a copy of that vector not the original one*/

using std::vector;
using std::cin;
using std::cout;
using std::max;

void func(const vector<int> &vect)
{
	vect.push_back(30);
}

int main()
{
	vector<int> vect;
	vect.push_back(5);
	vect.push_back(10);
    vect.push_back(20);

	func(vect);

	for(int i=0; i< vect.size(); i++)
		cout<<vect[i]<<"\n";

	return 0;
}
