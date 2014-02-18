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

	void adopt(TreeNode** dest, TreeNode** src) {
		deleteNode(*dest);
		*dest = *src;
		*src = NULL;
	}

	void copyNode(TreeNode** dest, TreeNode const * src)
	{
		if (src == NULL)
			*dest = NULL;
		else
		{
			*dest = new TreeNode;
			*dest->inf = src->inf;
			copyNode(*dest->left, src->left);
			copyNode(*dest->right, src->right);
		}
	}

	void deleteNode(TreeNode* node)
	{
		if (node != NULL)
		{
			if (node->pLeft)
			{
				deleteNode(node->pLeft);
				deleteNode(node->pRight);
			}
			delete node;
		}
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
            return BinTreeIter(ptr->pLeft);
        }
        BinTreeIter operator++(int)
        {
			return BinTreeIter(ptr->pRight);
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

	bool isEmpty()
	{
		return root == NULL;
	}

    BinTreeIter& GetIter()const
    {
        return BinTreeIter(root);
    }

    bool initRoot(const T& val)
    {
		deleteNode(root);
        if (!(root = createNode(val)))
        {
            return false;
        }
        return true;
    }

	void adoptLeft(BinaryTree& t)
	{
		if (root != NULL)
		{
			adopt(&(root->pLeft), &t.root);
		}
	}

	void adoptRight(BinaryTree& t)
	{
		if (root != NULL)
		{
			adopt(&(root->pRight), &t.root);
		}
	}

	T& GetRoot()
	{
		return *this->root;
	}
};

#endif //BINARY_TREE_HPP

