#include <iostream>
#include <algorithm>

class AVLNode
{
public:
    int data;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class AVLTree
{
private:
    AVLNode *root;

    int getBalanceFactor(AVLNode *node)
    {
        if (node == nullptr)
            return 0;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return leftHeight - rightHeight;
    }

    int getHeight(AVLNode *node)
    {
        if (node == nullptr)
            return 0;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }

    AVLNode *rightRotate(AVLNode *y)
    {
        AVLNode *x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }

    AVLNode *leftRotate(AVLNode *x)
    {
        AVLNode *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    AVLNode *minValueNode(AVLNode *node)
    {
        AVLNode *current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    AVLNode *insertNode(AVLNode *node, int value)
    {
        if (node == nullptr)
            return new AVLNode(value);

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
        {
            // Duplicate values not allowed
            return node;
        }

        int balance = getBalanceFactor(node);

        if (balance > 1)
        {
            if (value < node->left->data)
            {
                // Left-Left case
                return rightRotate(node);
            }
            else
            {
                // Left-Right case
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        if (balance < -1)
        {
            if (value > node->right->data)
            {
                // Right-Right case
                return leftRotate(node);
            }
            else
            {
                // Right-Left case
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    AVLNode *deleteNode(AVLNode *node, int value)
    {
        if (node == nullptr)
            return nullptr;

        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }
        else
        {
            // Node with the key to be deleted found
            if (node->left == nullptr || node->right == nullptr)
            {
                AVLNode *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    // Node with one child or no child
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    // Node with one child (promote the child)
                    *node = *temp;
                }

                delete temp;
            }
            else
            {
                // Node with two children
                AVLNode *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        int balance = getBalanceFactor(node);

        if (balance > 1)
        {
            if (value < node->left->data)
            {
                // Left-Left case
                return rightRotate(node);
            }
            else
            {
                // Left-Right case
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        if (balance < -1)
        {
            if (value > node->right->data)
            {
                // Right-Right case
                return leftRotate(node);
            }
            else
            {
                // Right-Left case
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void remove(int value)
    {
        root = deleteNode(root, value);
    }

    void inorderTraversal(AVLNode *node)
    {
        if (node != nullptr)
        {
            std::cout << node->data << " ";
            inorderTraversal(node->left);
            inorderTraversal(node->right);
        }
    }

    void inorder()
    {
        inorderTraversal(root);
    }
};

int main()
{
    AVLTree avl;

    // Insert some nodes into the AVL tree
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);

    // Perform an inorder traversal to display the sorted values
    std::cout << "Inorder Traversal: ";
    avl.inorder();
    std::cout << std::endl;

    // Delete a node (e.g., 20) and display the updated tree
    avl.remove(20);
    std::cout << "Inorder Traversal after deleting 20: ";
    avl.inorder();
    std::cout << std::endl;

    return 0;
}
