#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

template <class T>
class BinaryTree
{
    struct TreeNode
    {
        TreeNode(const T& _val, TreeNode* _pLeft = NULL, TreeNode* _pRight = NULL)
        {
            val = _val;
            pLeft = _pLeft;
            pRight = _pRight;
        }
        T val;
        TreeNode* pLeft;
        TreeNode* pRight;
    };

	TreeNode* createNode(const T& _val)
	{
		TreeNode* tmp = new TreeNode(_val);
		if (!tmp)
		{
			return NULL;
		}
		return tmp;
	}

	TreeNode* root;

public:
    class BinTreeIter
    {
		friend class BinaryTree;
        TreeNode* ptr;
    public:
        BinTreeIter(TreeNode* node)
        {
            this->ptr = node;
        }

        BinTreeIter operator++()
        {
            return this->ptr = this->ptr->pLeft;
        }
        BinTreeIter operator++(int)
        {
            return this->ptr = this->ptr->pRight;
        }
        T& operator*() const
        {
            return this->ptr->val;
        }
        operator bool() const
        {
            return this->ptr != NULL;
        }
        bool operator== (BinTreeIter& right) const
        {
            return this == *right;
        }
        bool operator!= (BinTreeIter& right) const
        {
            return this != *right;
        }
    };

    BinaryTree()
    {
        this->root = NULL;
    }

    ~BinaryTree()
    {
        deleteNode(root);
    }

    BinTreeIter& GetIter()const
    {
        return BinTreeIter(root);
    }

    void deleteNode(TreeNode* node)
    {
        if (node->pLeft)
        {
            deleteNode(node->pLeft);
        }
        if (node->pRight)
        {
            deleteNode(node->pRight);
        }
        delete node;
    }

    bool initRoot(const T& val)
    {
        if (!(root = createNode(val)))
        {
            return false;
        }
        return true;
    }

	void adoptLeftNode(BinTreeIter& iter, TreeNode& node)
	{
		if (iter.ptr->pLeft)
		{
			deleteNode(iter.ptr->pLeft);
		}
		iter.ptr->pLeft = &node;
	}

	void adoptRightNode(BinTreeIter& iter, TreeNode& node)
	{
		if (iter.ptr->pRight)
		{
			deleteNode(iter.ptr->pRight);
		}
		iter.ptr->pRight = &node;
	}

    bool adoptLeftVal(BinTreeIter& iter, const T& val)
    {
		TreeNode* tmp;
        if (!(tmp = createNode(val)))
        {
            return false;
        }
		adoptLeftNode(iter, *tmp);
        return true;
    }

	bool adoptRightVal(BinTreeIter& iter, const T& val)
	{
		TreeNode* tmp;
		if (!(tmp = createNode(val)))
		{
			return false;
		}
		adoptRightNode(iter, *tmp);
		return true;
	}
};

#endif //BINARY_TREE_HPP

