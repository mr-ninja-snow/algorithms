#include <iostream>
#include "binary_search_tree.hpp"

int main(int argc, char *argv[])
{
	BinarySearchTree bst;

	bst.put('B');
	bst.put('A');
	bst.put('C');
	bst.put('D');

	std::cout <<"bst.size()" << bst.size() << "\n" ;
	std::cout <<"bst.treeHight()" << bst.height() << "\n" ;

	return 0;
}
