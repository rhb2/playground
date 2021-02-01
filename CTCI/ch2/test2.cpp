#include <iostream>
#include "../util/sll.h"

using namespace std;


int main(int argc, char **argv)
{
	int i;
	linkedlist<int> list1;

	for (i = 0; i < 10; i++)
		list1.ordered_insert(rand() % 40);
		//list1.push_front(rand() % 40);
		//list1.push_back(rand() % 40);

/*
	for (i = 0; i < 10; i++) {
		list1.pop_back();
		cout << list1 << endl;
	}
*/

	cout << list1 << endl;
	return (0);
}
