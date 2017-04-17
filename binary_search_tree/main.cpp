#include <iostream>
#include "binary_search_tree.hpp"

void getRange(BinarySearchTree& bst, const KeyType& start, const KeyType& end)
{
	std::cout << "Key in range\n";
	auto res = bst.keys(start, end);
	for (const auto key : bst.keys(start, end))
	{
		std::cout << "key - " << key << "\n";
	}
}

int main(int argc, char *argv[])
{
	BinarySearchTree bst;

	bst.put('I');
	bst.put('A');
	bst.put('J');
	bst.put('D');
	bst.put('C');
	bst.put('K');
	bst.put('H');

	std::cout <<"bst.size()" << bst.size() << "\n" ;
	std::cout <<"bst.treeHight()" << bst.height() << "\n" ;

	std::cout << "bst.min()" << bst.min() << "\n";
	std::cout << "bst.max()" << bst.max() << "\n";

	std::cout << "bst.floor(C)" << bst.floor('C') << " - A\n";
	std::cout << "bst.floor(B)" << bst.floor('B') << " - A\n";
	std::cout << "bst.floor(E)" << bst.floor('E') << " - D\n";
	std::cout << "bst.floor(J)" << bst.floor('J') << " - K\n";
	std::cout << "bst.floor(I)" << bst.floor('I') << " - H\n";

	getRange(bst, 'C', 'K');

	getRange(bst, 'K', 'C');
	getRange(bst, 'A', 'A');


	return 0;
}
