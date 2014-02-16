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

    class BinTreeIter
    {
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

    TreeNode* createNode(const T& _val)
    {
        TreeNode* tmp = new TreeNode();
        if (!tmp)
        {
            return NULL;
        }
        tmp->val = _val;
        return tmp;
    }

    TreeNode* root;
public:
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
        if (!root = createNode(val))
        {
            return false;
        }
        return true;
    }

    bool adoptLeft(BinTreeIter* iter, const T& val)
    {
        if ((*iter)->pLeft)
        {
            deleteNode((*iter)->pLeft);
        }
        if (!(*iter)->pLeft = createNode(val))
        {
            return false;
        }
        return true;
    }
    bool adoptRight(BinTreeIter* iter, const T& val)
    {
        if ((*iter)->pRight)
        {
            deleteNode((*iter)->pRight);
        }
        if (!(*iter)->pRight = createNode(val))
        {
            return false;
        }
        return true;
    }
};

#endif //BINARY_TREE_HPP

