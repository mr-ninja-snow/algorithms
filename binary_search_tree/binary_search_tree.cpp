#include <iostream>

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

void BinarySearchTree::keysImpl(Node* currentNode, std::vector<KeyType>& keys, const KeyType& start, const KeyType& end)
{
	if (currentNode->key() > start)
	{
		if (currentNode->left())
		{
			keysImpl(currentNode->left(), keys, start, end);
		}
		if (currentNode->key() < end)
		{
			keys.push_back(currentNode->key());
		}
	}
	
	if (currentNode->key() == start || currentNode->key() == end)
	{
		keys.push_back(currentNode->key());
	}

	if (currentNode->key() < end && currentNode->right())
	{
		keysImpl(currentNode->right(), keys, start, end);
	}
}

std::vector<KeyType> BinarySearchTree::keys(const KeyType& start, const KeyType& end)
{
	if (start > end)
	{
		return std::vector<KeyType>();
	}

	std::vector<KeyType> keys;

	keysImpl(m_root.get(), keys, start, end);

	return keys;
}

KeyType BinarySearchTree::min()
{
	Node* parentNode;
	auto* currentNode = m_root.get();
	while (currentNode)
	{
		parentNode = currentNode;
		currentNode = currentNode->left();
	}

	return parentNode->key();
}

KeyType BinarySearchTree::max()
{
	Node* parentNode;
	auto* currentNode = m_root.get();
	while (currentNode)
	{
		parentNode = currentNode;
		currentNode = currentNode->right();
	}

	return parentNode->key();
}

KeyType BinarySearchTree::floor(KeyType key, Node* currentNode)
{
	if (currentNode == nullptr)
	{
		currentNode = m_root.get();
	}

	KeyType currentKey = currentNode->key();

	if (currentNode->key() > key)
	{
		currentNode = currentNode->left();
	}
	else
	{
		if (currentNode->key() < key)
		{
			currentNode = currentNode->right();
		}
		else
		{
			if (currentNode->key() == key)
			{
				currentNode = currentNode->left();
			}
		}
	}

	if (currentNode)
	{
		KeyType resultKey = floor(key, currentNode);
		if (currentKey > key && resultKey <= key)
		{
			return resultKey;
		}
		if (resultKey > currentKey && resultKey < key)
		{
			currentKey = resultKey;
		}
		if (currentKey == key && resultKey < key)
		{
			return resultKey;
		}
	}

	return currentKey;
}

/*KeyType BinarySearchTree::ceilingFind(KeyType key, Node* currentNode)
{
	if (currentNode->key() == key)
	{
		
	}
	else
	{
		if (currentNode->key() > key)
		{
			currentNode = currentNode->left();
		}
		else
		{

		}
	}
}*/

KeyType BinarySearchTree::ceiling(KeyType key, Node* currentNode)
{
	if (currentNode == nullptr)
	{
		currentNode = m_root.get();
	}

	KeyType currentKey = currentNode->key();
	KeyType resultKey = currentNode->key();

	if (currentNode->key() == key)
	{
		if (currentNode->right())
		{
			resultKey = ceiling(key, currentNode->right());
		}
	}
	else
	{
		if (currentNode->key() > key)
		{
			if (currentNode->left())
			{
				resultKey = ceiling(key, currentNode->left());
			}
		}
		else
		{
			if (currentNode->right())
			{
				resultKey = ceiling(key, currentNode->right());
			}
		}
	}

	if (currentKey < key && resultKey >= key)
	{
		return resultKey;
	}

	if (resultKey < currentKey && resultKey > key)
	{
		currentKey = resultKey;
	}

	if (currentKey == key && resultKey > key)
	{
		return resultKey;
	}
	return currentKey;
}

unsigned int BinarySearchTree::rank(KeyType key, Node* currentNode, Node* parentNode)
{
	if (currentNode == nullptr)
	{
		currentNode = m_root.get();
	}

	unsigned int res = 0;

	if (currentNode->key() == key)
	{
		res = 1;
		if (currentNode->left())
		{
			res += currentNode->left()->subtreeNodeCount() + 1;
		}
		return res;
	}
	else
	{
		if (currentNode->key() > key)
		{
			if (currentNode->left())
			{
				return rank(key, currentNode->left(), nullptr);
			}
		}
		else
		{
			if (currentNode->right())
			{
				if (currentNode->left())
				{
					return currentNode->left()->subtreeNodeCount() + 2 + rank(key, currentNode->right(), currentNode);
				}
				else
				{
					return 1 + rank(key, currentNode->right(), currentNode);
				}
			}
		}
	}
	return 0;
}

KeyType BinarySearchTree::select(unsigned int rankOfKey)
{
	Node* currentNode = m_root.get();

	if (m_root->subtreeNodeCount() + 1 < rankOfKey || rankOfKey < 1)
	{
		return '?';
	}

	unsigned int currentRank = 0;

	if (currentNode->left())
	{
		currentRank = currentNode->left()->subtreeNodeCount() + 1 + 1;
	}
	else
	{
		currentRank = 1;
	}

	if (currentRank == rankOfKey)
	{
		return currentNode->key();
	}

	if (currentRank > rankOfKey)
	{
		unsigned int newRank = currentRank;

		if (currentNode->left()->right())
		{
			newRank -= currentNode->left()->right()->subtreeNodeCount() + 1;
		}

		newRank -= 1; // for the cur node

		return selectImpl(rankOfKey, currentNode->left(), newRank);
	}
	else
	{
		unsigned int newRank = currentRank;


		if (currentNode->right())
		{
			if (currentNode->right()->left())
			{
				newRank += currentNode->right()->left()->subtreeNodeCount() + 1;
			}

			newRank += 1; // for the next node

			return selectImpl(rankOfKey, currentNode->right(), newRank);
		}
	}

	return '?';
}

KeyType BinarySearchTree::selectImpl(unsigned int rankOfKey, Node* currentNode, unsigned int currentRank)
{
	if (currentRank == rankOfKey)
	{
		return currentNode->key();
	}

	if (currentRank > rankOfKey)
	{
		unsigned int newRank = currentRank;

		if (currentNode->left())
		{
			if (currentNode->left()->right())
			{
				newRank -= currentNode->left()->right()->subtreeNodeCount() + 1;
			}
		}

		newRank -= 1; // for the cur node

		return selectImpl(rankOfKey, currentNode->left(), newRank);
	}
	else
	{
		unsigned int newRank = currentRank;


		if (currentNode->right())
		{
			if (currentNode->right()->left())
			{
				newRank += currentNode->right()->left()->subtreeNodeCount() + 1;
			}

			newRank += 1; // for the next node

			return selectImpl(rankOfKey, currentNode->right(), newRank);
		}
	}

	return '?';
}

// won't work in an empty BST
// won't work in a BST with one element
void BinarySearchTree::deleteMin()
{
	Node* parentNode;
	auto* currentNode = m_root.get();

	while (true)
	{	
		if (currentNode->left())
		{
			parentNode = currentNode;
			parentNode->decSubtreeNodeCount();
			currentNode = currentNode->left();
			continue;
		}
		break;
	}

	parentNode->removeLeft();
}

// won't work in an empty BST
// won't work in a BST with one element
void BinarySearchTree::deleteMax()
{
	Node* parentNode;
	auto* currentNode = m_root.get();
	while (true)
	{
		if (currentNode->right())
		{
			parentNode = currentNode;
			parentNode->decSubtreeNodeCount();
			currentNode = currentNode->right();
			continue;
		}
		break;
	}

	parentNode->removeRight();
}

void BinarySearchTree::deleteKey(KeyType key)
{
	std::vector<Node*> nodeToDec;
	Node* parentNode = nullptr;
	auto* currentNode = m_root.get();
	bool wentLeft = true;
	while (true)
	{
		if (currentNode->key() == key)
		{
			if (parentNode)
			{
				if(!currentNode->left() && !currentNode->right())
				{
					if (wentLeft)
					{
						parentNode->removeLeft();
					}
					else
					{
						parentNode->removeRight();
					}
					std::cout << "Deleted key\n";
					break;
				}

				if (!currentNode->left() && currentNode->right())
				{
					if (wentLeft)
					{
						parentNode->removeLeft();
					}
					else
					{
						parentNode->removeRightAndAttachRight();
					}
					std::cout << "Deleted key\n";
					break;
				}

				if (currentNode->left() && !currentNode->right())
				{
					if (wentLeft)
					{
						parentNode->removeLeftAndAttachLeft();
					}
					else
					{
						parentNode->removeRight();
					}
					std::cout << "Deleted key\n";
					break;
				}

				if (wentLeft)
				{
					parentNode->removeLeftAndFixLinks();
				}
				else
				{
					parentNode->removeRightAndFixLinks();
				}
				std::cout << "Deleted key\n";
				break;
			}
			else
			{
				removeRoot();
			}
		}
		else
		{
			if (currentNode->key() > key)
			{
				if (currentNode->left())
				{
					nodeToDec.push_back(currentNode);
					parentNode = currentNode;
					wentLeft = true;
					currentNode = currentNode->left();
					continue;
				}
				else
				{
					std::cout << "Couldn't find this key\n";
					return;
				}
			}
			else
			{
				if (currentNode->right())
				{
					nodeToDec.push_back(currentNode);
					parentNode = currentNode;
					wentLeft = false;
					currentNode = currentNode->right();
					continue;
				}
				else
				{
					std::cout << "Couldn't find this key\n";
					return;
				}
			}
		}
		break;
	}


	//
	for (auto& node : nodeToDec)
	{
		node->decSubtreeNodeCount();
	}
}

void BinarySearchTree::Node::removeLeftAndFixLinks()
{

	Node* parentNode = nullptr;
	auto* currentNode = this->left()->right();
	
	if (!currentNode)
	{
		auto node = std::move(this->m_left->m_left);
		this->m_left = std::move(node);
		return;
	}

	while (true)
	{
		if (currentNode->left())
		{
			parentNode = currentNode;
			currentNode = currentNode->left();
			continue;
		}
		break;
	}

	if (!parentNode)
	{
		this->removeLeftAndAttachLeft();
		return;
	}

	auto nodeToRM = std::move(this->m_left);

	auto newSubRoot = std::move(parentNode->m_left);

	auto newSubRootTail = std::move(newSubRoot->m_right);

	parentNode->m_left = std::move(newSubRootTail);

	newSubRoot->m_right = std::move(nodeToRM->m_right);
	newSubRoot->m_left = std::move(nodeToRM->m_left);

	this->m_left = std::move(newSubRoot);
}

void BinarySearchTree::Node::removeRightAndFixLinks()
{
	Node* parentNode = nullptr;
	auto* currentNode = this->right()->right();

	if (!currentNode)
	{
		auto node = std::move(this->m_right->m_left);
		this->m_right = std::move(node);
		return;
	}

	while (true)
	{
		if (currentNode->left())
		{
			parentNode = currentNode;
			currentNode = currentNode->left();
			continue;
		}
		break;
	}

	if (!parentNode)
	{
		std::unique_ptr<Node> node = std::move(m_right->m_right);
		std::unique_ptr<Node> subLeft = std::move(m_right->m_left);

		node->m_left = std::move(subLeft);

		for (int i = 0; i < node->m_left->subtreeNodeCount() + 1; i++)
		{
			node->incSubtreeNodeCount();
		}

		m_right = std::move(node);
		return;
	}

	auto nodeToRM = std::move(this->m_right);

	auto newSubRoot = std::move(parentNode->m_left);

	auto newSubRootTail = std::move(newSubRoot->m_right);

	parentNode->m_left = std::move(newSubRootTail);

	newSubRoot->m_right = std::move(nodeToRM->m_right);
	newSubRoot->m_left = std::move(nodeToRM->m_left);

	this->m_right = std::move(newSubRoot);
}

void BinarySearchTree::removeRoot()
{
	throw 1;
}