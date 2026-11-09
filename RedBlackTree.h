#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>
#include <stdexcept> // for invalid_argument

using namespace std;

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2  //  will be used in the remove algorithm(s) only. (Part 2)


struct RBTNode {
    int data;
    unsigned short int color;
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr; 
    // not in the lecture's struct
    // added to make methods easier to write
};


class RedBlackTree {
public:
    RedBlackTree(); // makes an empty tree
    RedBlackTree(int newData); // makes a tree with one node (the root)
    RedBlackTree(const RedBlackTree &rbt); // copy constructor
    ~RedBlackTree(); // destructor
    RedBlackTree& operator=(const RedBlackTree &rbt); // assignment operator

    void Insert(int k);
    bool Contains(int k) const;

    int GetMin() const;
    int GetMax() const;
    unsigned long long int Size() const;

    // given by the assignment
    string ToInfixString() const {return ToInfixString(root);};
    string ToPrefixString() const { return ToPrefixString(root);};
    string ToPostfixString() const { return ToPostfixString(root);};

    // tests for the private methods (suggested by the assignment)
    void PrivateTests();

private:
    // given by the assignment
    unsigned long long int numItems = 0;
    RBTNode *root = nullptr;

    // recursive helpers for the public ToString methods
    string ToInfixString(RBTNode *n) const;
    string ToPrefixString(RBTNode *n) const;
    string ToPostfixString(RBTNode *n) const;

    // turns one node into its printed form
    // helper so we don't have to repeat this code in the three ToString methods
    string GetNodeString(RBTNode *n) const;

    void RotateLeft(RBTNode *x);
    void RotateRight(RBTNode *x);

    void InsertFixUp(RBTNode *node);

    // recursively copies a subtree 
    // used by the copy constructor
    RBTNode* CopyOf(const RBTNode *n, RBTNode *parent);

    // recursively deletes a subtree 
    // used by the destructor
    void DeleteSubtree(RBTNode *n);
};

#endif