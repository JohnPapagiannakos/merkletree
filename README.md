# Merkle tree (or Hash tree) implementation in C++

## What Is a Merkle Tree (or hash tree)?
A Merkle tree is a data structure used in computer science applications. For example, it is used in bitcoin and other cryptocurrencies​ to encode blockchain data more efficiently and securely.

More specifically, a Merkle tree is a tree (more often constructed as a binary tree but can also have many more child nodes under each node as well ) in which every "leaf" (node) is labelled with the cryptographic hash of a data block, and every node that is not a leaf is labelled with the cryptographic hash of the labels of its child nodes. 

A hash tree allows efficient and secure verification of the contents of a large data structure. A hash tree is a generalization of a hash list and a hash chain.

## A short example
Assume 8 data blocks, denoted as B(i) for i=1...8. 
Each block is hashed by a hashing function, denoted as H(·) (in this code we use SHA256 hash algorithm), and is stored as a leaf node in a binary tree as shown below.
Then, each hash of the left (L) and the right (R) child is concatenated (denoted here as {L,R}) and rehashed. This value is stored in their respective parent node.
This procedure is repeated until we reach the root node.

```bash
                      H({1234,5678})                           ---- root node
                        /         \
                      /             \
                    /                 \
                  /                     \
           H({12,34})                 H({56,78})
            /      \                     /    \            
           /        \                   /      \
          /          \                 /        \
    H({1,2})       H({3,4})       H({5,6})     H({7,8})
      /   \          /   \          /   \        /   \
     /     \        /     \        /     \      /     \
  H(1)     H(2)   H(3)   H(4)   H(5)   H(6)   H(7)   H(8)      ---- leaf-nodes
    |        |      |      |      |      |      |      |
  B(1)     B(2)   B(3)   B(4)   B(5)   B(6)   B(7)   B(8)      ---- data blocks
```


## Creator
* Yannis Marios Papagiannakos

## Requirements
* [openssl](https://github.com/openssl/openssl "openssl") library