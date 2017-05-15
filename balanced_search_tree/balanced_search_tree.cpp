#include <iostream>

#include "balanced_search_tree.hpp"


BalancedSearchTree::Node::Node(KeyType key, unsigned long long nodeHeight)
	:
	m_nodeHeight(nodeHeight),
	m_subtreeNodeCount(0),
	m_key(key),
	m_left(nullptr),
	m_right(nullptr),
	m_color(LinkColor::BLACK)
{
	if (nodeHeight > s_treeHeight)
	{
		s_treeHeight = nodeHeight;
	}
}

unsigned long long BalancedSearchTree::Node::s_treeHeight = 0;

inline unsigned long long BalancedSearchTree::Node::subtreeNodeCount() const
{
	return m_subtreeNodeCount;
}

inline BalancedSearchTree::Node* BalancedSearchTree::Node::left() const
{
	return m_left.get();
}

inline void BalancedSearchTree::Node::setLeftAsRed(std::unique_ptr<Node>&& node)
{
	m_left = std::move(node);
	m_left->m_color = LinkColor::RED;
}

inline BalancedSearchTree::Node* BalancedSearchTree::Node::right() const
{
	return m_right.get();
}

inline void BalancedSearchTree::Node::setRightAsRed(std::unique_ptr<Node>&& node)
{
	m_right = std::move(node);
	m_right->m_color = LinkColor::RED;
}

BalancedSearchTree::BalancedSearchTree()
	: m_root(nullptr)
{
}

unsigned long long BalancedSearchTree::size()
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

void BalancedSearchTree::putImpl(Node* currentNode, const KeyType& key)
{
	if (key > currentNode->key())
	{
		if (!currentNode->right())
		{
			currentNode->setRightAsRed(std::make_unique<Node>(key, currentNode->getNodeHeight()));
		}
		else
		{
			putImpl(currentNode->right(), key);
		}
	}
	else
	{
		if (!currentNode->left())
		{
			currentNode->setLeftAsRed(std::make_unique<Node>(key, currentNode->getNodeHeight()));
		}
		else
		{
			putImpl(currentNode->left(), key);
		}
	}

	bool currentIsRed = Node::isLinkRed(currentNode);
	bool leftIsRed = Node::isLinkRed(currentNode->left());
	bool rightIsRed = Node::isLinkRed(currentNode->left());

	if (currentIsRed)
	{
		
	}
	else
	{
		if (leftIsRed && rightIsRed)
		{
			Node::colorFlip(currentNode);
		}
		else
		{
			if (rightIsRed)
		}
	}
}

void BalancedSearchTree::put(const KeyType& key)
{
	if (m_root.get())
	{
		putImpl(m_root.get(), key);
	}
	else
	{
		m_root = std::make_unique<Node>(key);
	}
}

void BalancedSearchTree::keysImpl(Node* currentNode, std::vector<KeyType>& keys, const KeyType& start, const KeyType& end)
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

std::vector<KeyType> BalancedSearchTree::keys(const KeyType& start, const KeyType& end)
{
	if (start > end)
	{
		return std::vector<KeyType>();
	}

	std::vector<KeyType> keys;

	keysImpl(m_root.get(), keys, start, end);

	return keys;
}

KeyType BalancedSearchTree::min()
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

KeyType BalancedSearchTree::max()
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

KeyType BalancedSearchTree::floor(KeyType key, Node* currentNode)
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

/*KeyType BalancedSearchTree::ceilingFind(KeyType key, Node* currentNode)
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

KeyType BalancedSearchTree::ceiling(KeyType key, Node* currentNode)
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

unsigned int BalancedSearchTree::rank(KeyType key, Node* currentNode, Node* parentNode)
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

KeyType BalancedSearchTree::select(unsigned int rankOfKey)
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

KeyType BalancedSearchTree::selectImpl(unsigned int rankOfKey, Node* currentNode, unsigned int currentRank)
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
void BalancedSearchTree::deleteMin()
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
void BalancedSearchTree::deleteMax()
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

void BalancedSearchTree::deleteKey(KeyType key)
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
				//removeRoot();
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

void BalancedSearchTree::Node::removeLeftAndFixLinks()
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

void BalancedSearchTree::Node::removeRightAndFixLinks()
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

/*void BalancedSearchTree::removeRoot()
{
	std::unique_ptr<Node> tmpParentNode = std::make_unique<Node>('?');

	tmpParentNode->setRight(std::move(m_root));
	tmpParentNode->removeRightAndFixLinks();

	m_root = std::move(tmpParentNode->detachRight());
}*/