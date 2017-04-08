#include "binary_search_tree.hpp"


BinarySearchTree::Node::Node(KeyType key)
	: m_subtreeNodeCount(0),
	m_key(key),
	m_left(nullptr),
	m_right(nullptr)
{
}

inline unsigned long long BinarySearchTree::Node::subtreeNodeCount() const
{
	return m_subtreeNodeCount;
}

inline BinarySearchTree::Node* BinarySearchTree::Node::left() const
{
	return m_left.get();
}

inline void BinarySearchTree::Node::setLeft(std::unique_ptr<Node>&& node)
{
	m_left = std::move(node);
}

inline BinarySearchTree::Node* BinarySearchTree::Node::right() const
{
	return m_right.get();
}

inline void BinarySearchTree::Node::setRight(std::unique_ptr<Node>&& node)
{
	m_right = std::move(node);
}

BinarySearchTree::BinarySearchTree()
	: m_root(nullptr)
{
}

void BinarySearchTree::put(const KeyType& key)
{
	if (m_root.get())
	{
		Node* parentNode = nullptr;
		Node* currentNode = m_root.get();
		while (currentNode)
		{
			parentNode = currentNode;
			if (key > currentNode->key())
			{
				if (currentNode->right())
				{
					currentNode = currentNode->right();
				}
				else
				{
					parentNode->setRight(std::make_unique<Node>(key));
				}
			}
			else
			{
				if (currentNode->left())
				{
					currentNode = currentNode->left();
				}
				else
				{
					parentNode->setLeft(std::make_unique<Node>(key));
				}
			}
		}
	}
	else
	{
		m_root = std::make_unique<Node>(key);
	}
}