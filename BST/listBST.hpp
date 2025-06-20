#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    Node *insertBST(Node *root, Key key, Value value)
    {
        if (root == NULL)
            return new Node(key, value);
        if (key < root->key)
        {
            root->left = insertBST(root->left, key, value);
        }
        else
        {
            root->right = insertBST(root->right, key, value);
        }
        return root;
    };

    Node *searchBST(Node *root, Key k) const
    {
        if (root == nullptr)
            return nullptr;
        if (root->key == k)
            return root;

        if (k < root->key)
        {
            return searchBST(root->left, k);
        }
        else
        {
            return searchBST(root->right, k);
        }
    };

    Node *deleteBST(Node *root, Key k)
    {
        if (root == nullptr)
            return nullptr;

        if (k < root->key)
        {
            root->left = deleteBST(root->left, k);
        }
        else if (k > root->key)
        {
            root->right = deleteBST(root->right, k);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            // both child
            Node *succ = findMinNode(root->right);
            root->key = succ->key;
            root->value = succ->value;
            root->right = deleteBST(root->right, succ->key);
        }
        return root;
    }

    Node *findMinNode(Node *node) const
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node *findMaxNode(Node *node) const
    {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    void clearBST(Node *node) const
    {
        if (node)
        {
            clearBST(node->left);
            clearBST(node->right);
            delete node;
        }
    };

    void inorderTraversal(Node *node) const
    {
        if (node)
        {
            inorderTraversal(node->left);
            std::cout << "(" << node->key << ":" << node->value << ") ";
            inorderTraversal(node->right);
        }
    }
    void preorderTraversal(Node *node) const
    {
        if (node)
        {
            std::cout << "(" << node->key << ":" << node->value << ") ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    void postorderTraversal(Node *node) const
    {
        if (node)
        {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << "(" << node->key << ":" << node->value << ") ";
        }
    }
    void printBST(Node *node) const
    {
        if (!node)
            return;
        std::cout << "(" << node->key << ":" << node->value;
        if (node->left || node->right)
        {
            std::cout << " ";
            if (node->left)
                printBST(node->left);
            else
                std::cout << "()";

            if (node->right)
            {
                std::cout << " ";
                printBST(node->right);
            }
        }
        std::cout << ")";
    }

    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clearBST(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        if (find(key))
        {
            return false;
        }
        // Node *new_node=new Node(key, value);
        root = insertBST(root, key, value);
        node_count++;
        return true;
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        if (!find(key))
        {
            return false;
        }
        root = deleteBST(root, key);
        node_count--;
        return true;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic
        if (searchBST(root, key) == NULL)
            return false;
        else
            return true;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Node *node = searchBST(root, key);
        if (node)
        {
            return node->value;
        }
        else
        {
            throw std::runtime_error("Key not found");
        }
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        Node *node = searchBST(root, key);
        if (node)
        {
            node->value = value;
        }
        else
        {
            throw std::runtime_error("Key not found");
        }
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        clearBST(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        if (empty())
        {
            throw std::runtime_error("BST is empty");
        }
        Node *min_node = findMinNode(root);
        return min_node->key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        if (empty())
        {
            throw std::runtime_error("BST is empty");
        }
        Node *max_node = findMaxNode(root);
        return max_node->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (traversal_type == 'I')
        {
            inorderTraversal(root);
        }
        else if (traversal_type == 'P')
        {
            preorderTraversal(root);
        }
        else if (traversal_type == 'O')
        {
            postorderTraversal(root);
        }
        else if (traversal_type == 'D')
        {
            // BST (Default): (9:9 (1:1 () (7:7 (4:4))) (10:10 () (14:14 (13:13))))
            printBST(root);
        }
        else
        {
            std::cout << "Invalid traversal type. Use 'In', 'Pre', or 'Post'." << std::endl;
        }
    }
};

#endif // LISTBST_H