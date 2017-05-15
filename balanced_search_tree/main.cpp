#include <iostream>
#include "balanced_search_tree.hpp"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Empty Balanced Searcg Tree Test")
{
	BalancedSearchTree bst;

	SECTION("check size of empty tree")
	{
		REQUIRE(bst.size() == 0);
	}

	SECTION("push element check size of tree")
	{
		bst.put('Z');
		REQUIRE(bst.size() == 1);
	}

	SECTION("push 2 element check size of tree")
	{
		bst.put('Z');
		bst.put('A');
		REQUIRE(bst.size() == 2);
	}

	SECTION("push 2 element check height of tree")
	{
		bst.put('Z');
		bst.put('A');
		REQUIRE(bst.height() == 1);
	}

	SECTION("push 2 element check height of tree")
	{
		bst.put('A');
		bst.put('Z');
		REQUIRE(bst.height() == 1);
	}
}


/*TEST_CASE("Empty Grid size 2 by 2 Test")
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

	SECTION("push 10 key on to bst and get size 10")
	{
		REQUIRE(bst.size() == 10);
	}

	SECTION("push 10 key on to bst and get hight")
	{
		REQUIRE(bst.height() == 4);
	}

	SECTION("push 10 key on to bst and get max key")
	{
		REQUIRE(bst.max() == 'Z');
	}

	SECTION("push 10 key on to bst and get min")
	{
		REQUIRE(bst.min() == 'A');
	}

	SECTION("bst.floor(C) = A")
	{
		REQUIRE(bst.floor('C') == 'A');
	}

	SECTION("bst.floor(B) = A")
	{
		REQUIRE(bst.floor('B') == 'A');
	}

	SECTION("bst.floor(E) = D")
	{
		REQUIRE(bst.floor('E') == 'D');
	}

	SECTION("bst.floor(J) = I")
	{
		REQUIRE(bst.floor('J') == 'I');
	}

	SECTION("bst.floor(I) = H")
	{
		REQUIRE(bst.floor('I') == 'H');
	}

	SECTION("bst.floor(Z) = Y")
	{
		REQUIRE(bst.floor('Z') == 'Y');
	}

	SECTION("bst.ceiling('C') == 'D'")
	{
		REQUIRE(bst.ceiling('C') == 'D');
	}

	SECTION("bst.ceiling('B') == 'C'")
	{
		REQUIRE(bst.ceiling('B') == 'C');
	}

	SECTION("bst.ceiling('E') == 'H'")
	{
		REQUIRE(bst.ceiling('E') == 'H');
	}

	SECTION("bst.ceiling('J') == 'K'")
	{
		REQUIRE(bst.ceiling('J') == 'K');
	}

	SECTION("bst.ceiling('I') == 'J'")
	{
		REQUIRE(bst.ceiling('I') == 'J');
	}

	SECTION("bst.ceiling('Z') == 'Z'")
	{
		REQUIRE(bst.ceiling('Z') == 'Z');
	}

	SECTION("bst.keys('C', 'K') == {'C', 'D', 'H', 'I', 'J', 'K'}")
	{
		std::vector<KeyType> ans = { 'C', 'D', 'H', 'I', 'J', 'K' };
		REQUIRE(bst.keys('C', 'K') == ans);
	}

	SECTION("delMin and get min == C")
	{
		bst.deleteMin();
		REQUIRE(bst.min() == 'C');
	}

	SECTION("get subNode count of root")
	{
		REQUIRE(bst.getRoot()->subtreeNodeCount() == 9);
	}

	SECTION("rm min and get subNode count of root")
	{
		bst.deleteMin();
		REQUIRE(bst.getRoot()->subtreeNodeCount() == 8);
	}

	SECTION("rm 'A' get bst.keys('C', 'Z') == {'C', 'D', 'H', 'I', 'J', 'K', 'X', 'Y', 'Z'}")
	{
		std::vector<KeyType> ans = { 'C', 'D', 'H', 'I', 'J', 'K', 'X', 'Y', 'Z' };
		bst.deleteKey('A');
		REQUIRE(bst.keys('C', 'Z') == ans);
	}

	SECTION("rm 'D' get bst.keys('A', 'Z') == {'A', 'C', 'H', 'I', 'J', 'K', 'X', 'Y', 'Z'}")
	{
		std::vector<KeyType> ans = { 'A', 'C', 'H', 'I', 'J', 'K', 'X', 'Y', 'Z' };
		bst.deleteKey('D');
		REQUIRE(bst.keys('A', 'Z') == ans);
	}

	SECTION("rm 'D' and H get bst.keys('A', 'Z') == {'A', 'C', 'I', 'J', 'K', 'X', 'Y', 'Z'}")
	{
		std::vector<KeyType> ans = { 'A', 'C', 'I', 'J', 'K', 'X', 'Y', 'Z' };
		bst.deleteKey('D');
		bst.deleteKey('H');
		REQUIRE(bst.keys('A', 'Z') == ans);
	}

	SECTION("rm 'Z' get bst.keys('A', 'Y') == {'A', 'C', 'D', 'H', 'I', 'J', 'K', 'X', 'Y'}")
	{
		std::vector<KeyType> ans = { 'A', 'C', 'D', 'H', 'I', 'J', 'K', 'X', 'Y' };
		bst.deleteKey('Z');
		REQUIRE(bst.keys('A', 'Y') == ans);
	}

	SECTION("rm 'K' get bst.keys('A', 'Z') == {'A', 'C', 'D', 'H', 'I', 'J', 'X', 'Y', 'Z'}")
	{
		std::vector<KeyType> ans = { 'A', 'C', 'D', 'H', 'I', 'J', 'X', 'Y', 'Z' };
		bst.deleteKey('K');
		REQUIRE(bst.keys('A', 'Z') == ans);
	}

	SECTION("rm 'I' get bst.keys('A', 'Z') == {'A', 'C', 'D', 'H', 'J', 'K', 'X', 'Y', 'Z'}")
	{
		std::vector<KeyType> ans = { 'A', 'C', 'D', 'H', 'J', 'K', 'X', 'Y', 'Z' };
		bst.deleteKey('I');
		REQUIRE(bst.keys('A', 'Z') == ans);
	}
}*/