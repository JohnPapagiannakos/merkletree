#ifndef HTREE_HPP
#define HTREE_HPP

#include <math.h>
#include <utility>
#include <queue>

#include "Node.hpp"
#include "Types.hpp"
#include "Hash/HashingFunctions.hpp"

template <typename T>
class HTree
{
    public:
    HTree() : _root(NULL) {};

    void construct_tree(std::vector<std::pair<T,HASHTYPE>> &datablocks)
    {
        int size = datablocks.size();
        if(size < 1) return;

        int height = static_cast<int>(std::ceil(std::log2(size)) + 1);

        // sort blocks first
        std::sort(datablocks.begin(), datablocks.end());

        int non_leafs_num = std::pow(2, height-1) - 1;

        // Create non-leaf nodes & initialize their values to 0.
        for (int n = datablocks[size - 1].first + 1; n < datablocks[size - 1].first + 1 + non_leafs_num; n++)
        {
            HASHTYPE hash = ""; // empty string
            if (_root != NULL)
            {
                insert(n, hash, _root);
            }
            else
            {
                _root = new Node2<T, HASHTYPE>(n, hash);
                _root->left  = NULL;
                _root->right = NULL;
            }
        }

        // Insert leafs
        for (int n = 0; n < size; n++)
        {
            HASHTYPE hash = sha256(datablocks[n].second);

            if (_root != NULL)
            {
                insert(n, hash, _root);
            }
            else
            {
                _root = new Node2<T, HASHTYPE>(datablocks[n].first, hash);
                // std::cout << "<" << _root->key << "," << _root->value << ">" << std::endl;
                _root->left = NULL;
                _root->right = NULL;
            }
        }
    }

    HASHTYPE compute_hash(void)
    {
        compute_hash(_root);
        return _root->value;
    }

    void topview(void)
    {
        topView(_root);
        std::cout << std::endl;
    }

    void destroy_tree(void)
    {
        destroy_tree(_root);
    }

    /*
        Compute the number of nodes in a tree.
    */
    size_t size(void)
    {
        return size(_root);
    }

    /*
        Compute the maxDepth of a BST.
    */
    size_t maxDepth(void)
    {
        return maxDepth(_root);
    }

    ~HTree() {destroy_tree();};

    private:
    Node2<T,HASHTYPE> *_root;

    void insert(T key, HASHTYPE value, Node2<T,HASHTYPE> *leaf)
    {
        std::queue<Node2<T,HASHTYPE>*> waitingNodes;

        waitingNodes.push(leaf);

        while (!waitingNodes.empty())
        {
            Node2<T,HASHTYPE> *firstNode = waitingNodes.front();
            waitingNodes.pop();

            if (firstNode->left != NULL)
            {
                waitingNodes.push(firstNode->left);
            }
            else
            {
                firstNode->left = new Node2<T,HASHTYPE>(key, value);
                firstNode->left->left = NULL;
                firstNode->left->right = NULL;
                return;
            }

            if (firstNode->right != NULL)
            {
                waitingNodes.push(firstNode->right);
            }
            else
            {
                firstNode->right = new Node2<T,HASHTYPE>(key, value);
                firstNode->right->left = NULL;
                firstNode->right->right = NULL;
                return;
            }
        }
    }

    HASHTYPE compute_hash(Node2<T, HASHTYPE> *node)
    {
        // Compute hashes recursively
        if (node == NULL)
        {
            return "";
        }
        else
        {
            HASHTYPE l_hash = compute_hash(node->left);
            HASHTYPE r_hash = compute_hash(node->right);
            if (!(l_hash.empty() && r_hash.empty())) // if node is not a leaf-node
            {
                node->value = sha256(concat(l_hash, r_hash));
            }
            // std::cout << "<" << node->key << "," << node->value << ">" << std::endl;
            return node->value;
        }
    }

    void topView(Node2<T, HASHTYPE> *leaf)
    {
        if (leaf != NULL)
        {
            topView(leaf->left);
            topView(leaf->right);
            std::cout << "<" << leaf->key << "," << leaf->value << ">\t";
        }
    }

    void destroy_tree(Node2<T,HASHTYPE> *leaf)
    {
        if (leaf != NULL)
        {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
        }
    }

    size_t size(Node2<T,HASHTYPE> *leaf)
    {
        if (leaf == NULL)
        {
            return 0;
        }
        else
        {
            return (size(leaf->left) + 1 + size(leaf->right));
        }
    }

    size_t maxDepth(Node2<T,HASHTYPE> *leaf)
    {
        if (leaf == NULL)
        {
            return 0;
        }
        else
        {
            size_t lMaxDepth = maxDepth(leaf->left);
            size_t rMaxDepth = maxDepth(leaf->right);

            return std::max(lMaxDepth, rMaxDepth) + 1;
        }
    }
};

#endif