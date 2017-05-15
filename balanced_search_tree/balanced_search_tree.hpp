#pragma once

#include <cassert>
#include <memory>
#include <vector>

typedef char KeyType;

class BalancedSearchTree
{
	class Node
	{
	public:
		Node(KeyType key, unsigned long long nodeHeight = 1);
		~Node() = default;

		unsigned long long subtreeNodeCount() const;
		void incSubtreeNodeCount() { m_subtreeNodeCount++; };
		void decSubtreeNodeCount() { m_subtreeNodeCount--; };

		const KeyType& key() const { return m_key; }

		Node* left() const;
		void setLeftAsRed(std::unique_ptr<Node>&& node);
		
		void removeLeft()
		{ 
			std::unique_ptr<Node> node = std::move(m_left->m_right);
			m_left = std::move(node);
		}

		void removeLeftAndAttachLeft()
		{
			std::unique_ptr<Node> node = std::move(m_left->m_left);
			m_left = std::move(node);
		}

		Node* right() const;
		void setRightAsRed(std::unique_ptr<Node>&& node);
		void removeRight()
		{
			std::unique_ptr<Node> node = std::move(m_right->m_left);
			m_right = std::move(node);
		}

		std::unique_ptr<Node> detachRight()
		{
			return std::move(m_right);
		}

		void removeRightAndAttachRight()
		{
			std::unique_ptr<Node> node = std::move(m_right->m_right);
			m_right = std::move(node);
		}

		void removeLeftAndFixLinks();
		void removeRightAndFixLinks();
		
		unsigned long long getNodeHeight() const { return m_nodeHeight; }

		static unsigned long long getTreeHeight() { return s_treeHeight; }

		static bool isLinkRed(const Node* node)
		{
			if (node)
			{
				return node->m_color == LinkColor::RED;
			}
			else
			{
				return false;
			}
		}

		static void colorFlip(Node* node)
		{
			assert(!isLinkRed(node));
			assert(isLinkRed(node->left()));
			assert(isLinkRed(node->right()));

			node->m_color = LinkColor::RED;
			node->m_left->m_color = LinkColor::BLACK;
			node->m_right->m_color = LinkColor::BLACK;
		}

		std::unique_ptr<Node> roateRight(Node* oldParent)
		{
			assert(oldParent->m_color == LinkColor::RED);

			std::unique_ptr<Node> newParent = std::move(oldParent->m_left);
			newParent->m_color = LinkColor::BLACK;

			oldParent->m_left = std::move(newParent->m_right);
			oldParent->m_color = LinkColor::RED;

			return newParent;
		}

		std::unique_ptr<Node> roateLeft(Node* oldParent)
		{
			assert(oldParent->m_color == LinkColor::BLACK);

			std::unique_ptr<Node> newParent = std::move(oldParent->m_right);
			newParent->m_color = LinkColor::BLACK;

			oldParent->m_right = std::move(newParent->m_left);
			oldParent->m_color = LinkColor::RED;
			
			return newParent;
		}

	private:

		enum class LinkColor
		{
			RED,
			BLACK
		};

		static unsigned long long s_treeHeight;

		unsigned long long m_nodeHeight;
		unsigned long long m_subtreeNodeCount;

		const KeyType m_key;

		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;

		LinkColor m_color;
	};

public:
	BalancedSearchTree();
	~BalancedSearchTree() = default;

	unsigned long long size();
	unsigned long long height() const { return Node::getTreeHeight(); }
	void put(const KeyType& key);
	void putImpl(Node* current, const KeyType& key);

	Node* getRoot() { return m_root.get(); }

	std::vector<KeyType> keys(const KeyType& start, const KeyType& end); // return keys in a given range
	void keysImpl(Node* currentNode, std::vector<KeyType>& keys, const KeyType& start, const KeyType& end);

	KeyType min();
	KeyType max();

	KeyType floor(KeyType key, Node* currentNode = nullptr);
	KeyType ceiling(KeyType key, Node* currentNode = nullptr);

	unsigned int rank(KeyType key, Node* currentNode = nullptr, Node* parentNode = nullptr);
	
	KeyType select(unsigned int rankOfKey);
	KeyType selectImpl(unsigned int rankOfKey, Node* currentNode, unsigned int currentRank);

	void deleteMin();
	void deleteMax();
	void deleteKey(KeyType key);

private:
	//void removeRoot();

	std::unique_ptr<Node> m_root;
};