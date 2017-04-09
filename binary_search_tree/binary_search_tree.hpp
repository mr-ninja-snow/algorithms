#pragma once

#include <memory>
#include <vector>

typedef char KeyType;

class BinarySearchTree
{
	class Node
	{
	public:
		Node(KeyType key, unsigned long long nodeHeight = 0);
		~Node() = default;

		unsigned long long subtreeNodeCount() const;
		void incSubtreeNodeCount() { m_subtreeNodeCount++; };

		const KeyType& key() const { return m_key; }

		Node* left() const;
		void setLeft(std::unique_ptr<Node>&& node);

		Node* right() const;
		void setRight(std::unique_ptr<Node>&& node);
		
		unsigned long long getNodeHeight() const { return m_nodeHeight; }

		static unsigned long long getTreeHeight() { return s_treeHeight; }
	private: 
		static unsigned long long s_treeHeight;

		unsigned long long m_nodeHeight;
		unsigned long long m_subtreeNodeCount;

		const KeyType m_key;

		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;
	};

public:
	BinarySearchTree();
	~BinarySearchTree() = default;

	unsigned long long size();
	unsigned long long height() const { return Node::getTreeHeight(); }
	void put(const KeyType& key);

	std::vector<const KeyType&> keys(const KeyType& start, const KeyType& end); // return keys in a given range
	void keysImpl(Node* currentNode, std::vector<const KeyType&>& keys, const KeyType& start, const KeyType& end);
//
//	void min();
//	void max();
//	void floor();
//	void ceiling();
//	void select();
//	void rank();
//	void deleteMin();
//	void deleteMax();

private:
	std::unique_ptr<Node> m_root;
};