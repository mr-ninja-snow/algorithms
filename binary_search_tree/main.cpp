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
	bst.put('Y');
	bst.put('J');
	bst.put('D');
	bst.put('C');
	bst.put('X');
	bst.put('K');
	bst.put('H');
	bst.put('Z');

	std::cout <<"bst.size()" << bst.size() << "\n" ;
	std::cout <<"bst.treeHight()" << bst.height() << "\n" ;

	std::cout << "bst.min()" << bst.min() << "\n";
	std::cout << "bst.max()" << bst.max() << "\n";

	std::cout << "bst.floor(C)" << bst.floor('C') << " - A\n";
	std::cout << "bst.floor(B)" << bst.floor('B') << " - A\n";
	std::cout << "bst.floor(E)" << bst.floor('E') << " - D\n";
	std::cout << "bst.floor(J)" << bst.floor('J') << " - I\n";
	std::cout << "bst.floor(I)" << bst.floor('I') << " - H\n";
	std::cout << "bst.floor(Z)" << bst.floor('Z') << " - Y\n\n\n";

	std::cout << "bst.ceiling(C)" << bst.ceiling('C') << " - D\n";
	std::cout << "bst.ceiling(B)" << bst.ceiling('B') << " - C\n";
	std::cout << "bst.ceiling(E)" << bst.ceiling('E') << " - H\n";
	std::cout << "bst.ceiling(J)" << bst.ceiling('J') << " - K\n";
	std::cout << "bst.ceiling(I)" << bst.ceiling('I') << " - J\n";
	std::cout << "bst.ceiling(Z)" << bst.ceiling('Z') << " - Z\n";

	getRange(bst, 'C', 'K');

	getRange(bst, 'K', 'C');
	getRange(bst, 'A', 'A');

	std::cout << "bst.rank(I)" << bst.rank('I') << " - 5\n";
	std::cout << "bst.rank(A)" << bst.rank('A') << " - 1\n";
	std::cout << "bst.rank(C)" << bst.rank('C') << " - 2\n";
	std::cout << "bst.rank(H)" << bst.rank('H') << " - 4\n";
	std::cout << "bst.rank(D)" << bst.rank('D') << " - 3\n";
	std::cout << "bst.rank(K)" << bst.rank('K') << " - 7\n";
	std::cout << "bst.rank(Y)" << bst.rank('Y') << " - 9\n";
	std::cout << "bst.rank(Z)" << bst.rank('Z') << " - 10\n";
	std::cout << "bst.rank(X)" << bst.rank('X') << " - 0\n";
	
	std::cout << "bst.select(I[5])" << bst.select(5) << " - I\n";
	std::cout << "bst.select(A[1])" << bst.select(1) << " - A\n";
	std::cout << "bst.select(C[2])" << bst.select(2) << " - C\n";
	std::cout << "bst.select(H[4])" << bst.select(4) << " - H\n";
	std::cout << "bst.select(D[3])" << bst.select(3) << " - D\n";
	std::cout << "bst.select(K[7])" << bst.select(7) << " - K\n";
	std::cout << "bst.select(Y[9])" << bst.select(9) << " - Y\n";
	std::cout << "bst.select(Z[10])" << bst.select(10) << " - Z\n";
	std::cout << "bst.select(X[0])" << bst.select(0) << " - X\n";

	/*bst.deleteMin();
	std::cout << "bst.min()" << bst.min() << "\n";

	bst.deleteMax();
	std::cout << "bst.max()" << bst.max() << "\n";*/

	std::cout << "bst.select([1])" << bst.select(1) << "\n";
	std::cout << "bst.select([2])" << bst.select(2) << "\n";
	std::cout << "bst.select([3])" << bst.select(3) << "\n";
	std::cout << "bst.select([4])" << bst.select(4) << "\n";
	std::cout << "bst.select([5])" << bst.select(5) << "\n";
	std::cout << "bst.select([6])" << bst.select(6) << "\n";
	std::cout << "bst.select([7])" << bst.select(7) << "\n";
	std::cout << "bst.select([8])" << bst.select(8) << "\n";
	std::cout << "bst.select([9])" << bst.select(9) << "\n";
	std::cout << "bst.select([10])" << bst.select(10) << "\n";

	bst.deleteKey('D');

	std::cout << "bst.select([1])" << bst.select(1) << "\n";
	std::cout << "bst.select([2])" << bst.select(2) << "\n";
	std::cout << "bst.select([3])" << bst.select(3) << "\n";
	std::cout << "bst.select([4])" << bst.select(4) << "\n";
	std::cout << "bst.select([5])" << bst.select(5) << "\n";
	std::cout << "bst.select([6])" << bst.select(6) << "\n";
	std::cout << "bst.select([7])" << bst.select(7) << "\n";
	std::cout << "bst.select([8])" << bst.select(8) << "\n";
	std::cout << "bst.select([9])" << bst.select(9) << "\n";

	return 0;
}
