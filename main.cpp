#include <iostream>
using namespace std;
#include "SortedSet.h"

int main()
{
	SortedSet<int> a, b;
	a.insert(0);
	a.insert(1);
	a.insert(3);
	a.insert(5);
	a.insert(7);
	a.insert(10);

	b.insert(0);
	b.insert(2);
	b.insert(4);
	b.insert(6);
	b.insert(8);
	b.insert(9);
	b.insert(1);
	b.insert(3);
	
	a.union_(b);
	a.print();
	cout << "______________________" << endl;

	a.intersection(b);
	a.print();

}