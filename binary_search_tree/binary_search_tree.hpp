#pragma once

#include <memory>

typedef char KeyType;

class BinarySearchTree
{
	class Node
	{
	public:
		Node(KeyType key);
		~Node() = default;

		unsigned long long subtreeNodeCount() const;

		const KeyType& key() const { return m_key; }

		Node* left() const;
		void setLeft(std::unique_ptr<Node>&& node);

		Node* right() const;
		void setRight(std::unique_ptr<Node>&& node);
		
	private:
		unsigned long long m_subtreeNodeCount;

		const KeyType m_key;

		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;
	};

public:
	BinarySearchTree();
	~BinarySearchTree() = default;

	void put(const KeyType& key);

private:
	std::unique_ptr<Node> m_root;
};