#include "binary_search_tree.hpp"


BinarySearchTree::Node::Node(KeyType key, unsigned long long nodeHeight)
	:
	m_nodeHeight(nodeHeight),
	m_subtreeNodeCount(0),
	m_key(key),
	m_left(nullptr),
	m_right(nullptr)
{
	if (nodeHeight > s_treeHeight)
	{
		s_treeHeight = nodeHeight;
	}
}

unsigned long long BinarySearchTree::Node::s_treeHeight = 0;

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

unsigned long long BinarySearchTree::size()
{
	if (m_root)
	{
		return m_root->subtreeNodeCount() + 1;
	}
	else
	{
		return 0;
	}
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
			parentNode->incSubtreeNodeCount();
			if (key > currentNode->key())
			{
				currentNode = currentNode->right();
				if (!currentNode)
				{
					parentNode->setRight(std::make_unique<Node>(key, parentNode->getNodeHeight() + 1));
				}
			}
			else
			{
				currentNode = currentNode->left();
				if (!currentNode)
				{
					parentNode->setLeft(std::make_unique<Node>(key, parentNode->getNodeHeight() + 1));
				}
			}
		}
	}
	else
	{
		m_root = std::make_unique<Node>(key);
	}
}

void BinarySearchTree::keysImpl(Node* currentNode, std::vector<const KeyType&>& keys, const KeyType& start, const KeyType& end)
{
	if (currentNode->key() > start)
	{
		keysImpl(currentNode->left(), keys, start, end);
	}
	if (currentNode->key() < end)
	{
		keysImpl(currentNode->right(), keys, start, end);
	}
}

std::vector<const KeyType&> BinarySearchTree::keys(const KeyType& start, const KeyType& end)
{
	if (start > end)
	{
		return std::vector<const KeyType&>();
	}

	std::vector<const KeyType&> keys;

	keysImpl(m_root.get(), keys, start, end);

	return keys;
}
