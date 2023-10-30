
#include <iostream>
using namespace std;

class BstNode
{
private:
    int data;
    BstNode *right;
    BstNode *left;

public:
    BstNode(int val) : data(val), right(NULL), left(NULL) {}
    friend class BST;
};

class BST
{
private:
    BstNode *root;
    BstNode *deleteRec(BstNode *root, int val)
    {
        if (!root)
        {
            cout << val << " Not Found" << endl;
            return root;
        }
        if (val > root->data)
            root->right = deleteRec(root->right, val);
        else if (val < root->data)
            root->left = deleteRec(root->left, val);
        else
        {
            // for No child and one child node
            if (root->left == NULL)
            {
                BstNode *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                BstNode *temp = root->left;
                delete root;
                return temp;
            }
            // for two children node
            else
            {
                BstNode *temp = minValueNode(root->right);
                root->data = temp->data;
                // to delete the minimum value node which is replaced by the deleted node
                root->right = deleteRec(root->right, temp->data);
            }
        }
        return root;
    }

    BstNode *minValueNode(BstNode *node)
    {
        BstNode *current = node;
        while (current && current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }
    BstNode *insertRec(BstNode *root, int val)
    {
        if (root == NULL)
            return new BstNode(val);
        if (val < root->data)
            root->left = insertRec(root->left, val);
        else if (val > root->data)
            root->right = insertRec(root->right, val);
        return root;
    }
    BstNode *findRec(BstNode *root, int val)
    {
        if (root == NULL)
            return root;
        if (root->data == val)
            return root;
        else if (val < root->data)
            return findRec(root->left, val);
        else
            return findRec(root->right, val);
    }

    void inOrderTraversal(BstNode *root)
    {
        if (root != NULL)
        {
            inOrderTraversal(root->left);
            cout << root->data << " ";
            inOrderTraversal(root->right);
        }
    }

    void preOrderTraversal(BstNode *root)
    {
        if (root != NULL)
        {
            cout << root->data << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }

    void postOrderTraversal(BstNode *root)
    {
        if (root != NULL)
        {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            cout << root->data << " ";
        }
    }

public:
    BST() : root(NULL) {}

    void insert(int val)
    {
        root = insertRec(root, val);
    }

    void find(int val)
    {
        BstNode *current = findRec(root, val);
        if (current != NULL)
        {
            cout << val << " Found" << endl;
            return;
        }
        cout << val << " Not Found" << endl;
    }

    void deleteNode(int val)
    {
        deleteRec(root, val);
    }

    void inOrder()
    {
        inOrderTraversal(root);
        cout << endl;
    }

    void preOrder()
    {
        preOrderTraversal(root);
        cout << endl;
    }

    void postOrder()
    {
        postOrderTraversal(root);
        cout << endl;
    }
};

int main()
{
    BST b;
    b.insert(82);
    b.insert(45);
    b.insert(92);
    b.insert(100);
    b.insert(2);
    b.insert(69);
    b.insert(56);
    b.insert(78);
    b.find(2);
    b.inOrder();
    b.deleteNode(100);
    b.inOrder();
    // b.preOrder();
    // b.postOrder();
    return 0;
}
