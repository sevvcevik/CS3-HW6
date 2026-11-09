
#include "RedBlackTree.h"
#include <cassert> // used in PrivateTests()

using namespace std;


// default constructor
// an empty tree has no nodes so root is nullptr
RedBlackTree::RedBlackTree(){
    root = nullptr;
    numItems = 0;
}

// constructor with a starting value
// makes a tree with one node (the root)
// I added this because this is what Insert does on an empty tree
RedBlackTree::RedBlackTree(int newData){
    root = nullptr;
    numItems = 0;
    Insert(newData);
}

// copy constructor
// it is needed because the automatic copy constructor would only copy the root pointer
// so both trees would share the same nodes and changing one would change the other
RedBlackTree::RedBlackTree(const RedBlackTree &rbt){
    root = CopyOf(rbt.root, nullptr);
    numItems = rbt.numItems;
}


// recursively copies the subtree starting at n
RBTNode* RedBlackTree::CopyOf(const RBTNode *n, RBTNode *parent){
    if(n == nullptr)
    {
        return nullptr;
    }

    RBTNode *newNode = new RBTNode;
    newNode->data = n->data;
    newNode->color = n->color;
    newNode->parent = parent;

    newNode->left = CopyOf(n->left, newNode);
    newNode->right = CopyOf(n->right, newNode);

    return newNode;
}

// destructor
// C++ only frees the tree object itself
// so it is needed to free every node
RedBlackTree::~RedBlackTree(){
    DeleteSubtree(root);
    root = nullptr;
    numItems = 0;
}


// recursively deletes the subtree starting at n
// I used postfix order because after deleting n we can't use n->left or n->right anymore
void RedBlackTree::DeleteSubtree(RBTNode *n){
    if(n == nullptr)
    {
        return;
    }

    DeleteSubtree(n->left);
    DeleteSubtree(n->right);

    delete n;
}
 
// assignment operator
// needed because we have a destructor
// because the automatic version would only copy the root pointer, so both trees would delete the same nodes
// double free
RedBlackTree& RedBlackTree::operator=(const RedBlackTree &rbt){
    if(this == &rbt)
    {
        return *this;
    }

    DeleteSubtree(root);
    root = CopyOf(rbt.root, nullptr);
    numItems = rbt.numItems;
    return *this;
}
 

// insert a new value into the tree
// following video lecture's insert steps
void RedBlackTree::Insert(int k){
 
    if(root == nullptr)
    {
        RBTNode *newNode = new RBTNode;
        newNode->data = k;
        newNode->color = COLOR_BLACK;
        root = newNode;
        numItems++;
        return;
    }
 
    RBTNode *curr = root;
    RBTNode *parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;

        if(k < curr->data)
        {
            curr = curr->left;
        } 
        else if(k > curr->data)
        {
            curr = curr->right;
        } 
        else 
        {
            // equal means duplicate -> not allowed
            throw invalid_argument("Insert: duplicate value " + to_string(k));
        }
    }
 
    RBTNode *newNode = new RBTNode;
    newNode->data = k;
    newNode->color = COLOR_RED;
    newNode->parent = parent;
 
    if(k < parent->data)
    {
        parent->left = newNode;
    } 
    else 
    {
        parent->right = newNode;
    }
    numItems++;
 
    InsertFixUp(newNode);
}
 
 
// InsertFixUp
// called after a new red node is inserted
void RedBlackTree::InsertFixUp(RBTNode *node){
 
    while(node != root && node->parent->color == COLOR_RED)
    {
        RBTNode *parent = node->parent;
        RBTNode *grandparent = parent->parent;
 
        RBTNode *uncle;
        if(parent == grandparent->left)
        {
            uncle = grandparent->right;
        } 
        else 
        {
            uncle = grandparent->left;
        }
 

        if(uncle != nullptr && uncle->color == COLOR_RED)
        {
            parent->color = COLOR_BLACK;
            uncle->color = COLOR_BLACK;
            grandparent->color = COLOR_RED;
            node = grandparent;
        }
        else 
        {
            if(parent == grandparent->left)
            {
                // LR case (zig-zag)
                // straighten it into LL first
                if(node == parent->right)
                {
                    RotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                // LL case
                // one right rotation at the grandparent
                RotateRight(grandparent);
            } 
            else 
            {
                // RL case (zig-zag, mirror of LR)
                // straighten it into RR first
                if(node == parent->left)
                {
                    RotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                // RR case
                // one left rotation at the grandparent
                RotateLeft(grandparent);
            }
 

            parent->color = COLOR_BLACK;
            grandparent->color = COLOR_RED;
            break;
        }
    }
 
    // recoloring may have turned the root red
    // the root must be black
    root->color = COLOR_BLACK;
}
 
 
// RotateLeft
// x's right child (y) moves up into x's spot and x moves down to become y's left child
void RedBlackTree::RotateLeft(RBTNode *x){
    RBTNode *y = x->right;
 
    x->right = y->left;
    if(y->left != nullptr)
    {
        y->left->parent = x;
    }
 
    y->parent = x->parent;
    if(x->parent == nullptr)
    {
        root = y;
    } 
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    } 
    else 
    {
        x->parent->right = y;
    }
 
    y->left = x;
    x->parent = y;
}
 
 
// RotateRight
// mirror image of RotateLeft
// x's left child (y) moves up, and x becomes y's right child
void RedBlackTree::RotateRight(RBTNode *x){
    RBTNode *y = x->left;
 
    x->left = y->right;

    if(y->right != nullptr)
    {
        y->right->parent = x;
    }
 
    y->parent = x->parent;

    if(x->parent == nullptr)
    {
        root = y;
    } 
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    } 
    else 
    {
        x->parent->right = y;
    }
 
    y->right = x;
    x->parent = y;
}
 
 
bool RedBlackTree::Contains(int k) const{
    RBTNode *curr = root;

    while(curr != nullptr)
    {
        if(k == curr->data)
        {
            return true;
        } 
        else if(k < curr->data)
        {
            curr = curr->left;
        } 
        else 
        {
            curr = curr->right;
        }
    }
    return false;
}
 
 
int RedBlackTree::GetMin() const{
    if(root == nullptr)
    {
        throw invalid_argument("GetMin: tree is empty");
    }
    
    RBTNode *curr = root;

    while(curr->left != nullptr)
    {
        curr = curr->left;
    }

    return curr->data;
}
 
 
int RedBlackTree::GetMax() const{
    if(root == nullptr)
    {
        throw invalid_argument("GetMax: tree is empty");
    }

    RBTNode *curr = root;

    while(curr->right != nullptr)
    {
        curr = curr->right;
    }

    return curr->data;
}
 
 
unsigned long long int RedBlackTree::Size() const{
    return numItems;
}
 
 
// turns one node into its printed form
// R or B followed by the value
string RedBlackTree::GetNodeString(RBTNode *n) const{
    if(n->color == COLOR_RED)
    {
        return "R" + to_string(n->data);
    }

    return "B" + to_string(n->data);
}
 
 
// Infix (left subtree, then this node, then right subtree)
// an empty subtree (nullptr) prints nothing, which stops the recursion
string RedBlackTree::ToInfixString(RBTNode *n) const{
    if(n == nullptr)
    {
        return "";
    }

    return ToInfixString(n->left) + " " + GetNodeString(n) + " " + ToInfixString(n->right);
}
 
 
// Prefix (this node first, then left subtree, then right subtree)
string RedBlackTree::ToPrefixString(RBTNode *n) const{
    if(n == nullptr)
    {
        return "";
    }

    return " " + GetNodeString(n) + " " + ToPrefixString(n->left) + ToPrefixString(n->right);
}
 
 
// Postfix (left subtree, then right subtree, then this node last)
string RedBlackTree::ToPostfixString(RBTNode *n) const{
    if(n == nullptr)
    {
        return "";
    }

    return ToPostfixString(n->left) + ToPostfixString(n->right) + " " + GetNodeString(n) + " ";
}
 
 
// helper for PrivateTests
// checks the red black properties of a subtree
// (two reds in a row, wrong parent pointer, or unequal black-heights)
static int CheckRBT(RBTNode *n){
    if(n == nullptr)
    {
        return 1;
    }

    if(n->color == COLOR_RED)
    {
        if((n->left != nullptr && n->left->color == COLOR_RED) || (n->right != nullptr && n->right->color == COLOR_RED))
        {
            return -1;
        }
    }

    if(n->left != nullptr && n->left->parent != n)
    {
        return -1;
    }
    if(n->right != nullptr && n->right->parent != n)
    {
        return -1;
    }
 
    int leftHeight = CheckRBT(n->left);
    int rightHeight = CheckRBT(n->right);

    if(leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
    {
        return -1;
    }
    if(n->color == COLOR_BLACK)
    {
        return leftHeight + 1;
    }

    return leftHeight;
}
 
 
// tests for private methods 
// put them here as the assignment suggests
// because the test file can't call private methods directly
void RedBlackTree::PrivateTests(){
    cout << "Testing Private Methods..." << endl;
 
    // GetNodeString
    RBTNode redNode;
    redNode.data = 5;
    redNode.color = COLOR_RED;
    assert(GetNodeString(&redNode) == "R5");
    RBTNode blackNode;
    blackNode.data = 7;
    blackNode.color = COLOR_BLACK;
    assert(GetNodeString(&blackNode) == "B7");
 
    // RotateLeft / RotateRight on their own tree
    // because rotating can break the red black rules, so we use a separate tree
    RedBlackTree t = RedBlackTree();
    t.Insert(10);
    t.Insert(5);
    t.Insert(20);
    t.Insert(15);
    t.Insert(30);
    assert(t.ToPrefixString() == " B10  B5  B20  R15  R30 ");
 
    t.RotateLeft(t.root);
    assert(t.ToPrefixString() == " B20  B10  B5  R15  R30 ");
    assert(t.root->data == 20);
    assert(t.root->parent == nullptr);
    assert(t.root->left->parent == t.root);
    assert(t.root->left->right->data == 15);
    assert(t.root->left->right->parent == t.root->left);
 
    t.RotateRight(t.root);
    assert(t.ToPrefixString() == " B10  B5  B20  R15  R30 ");
    assert(t.root->data == 10);
    assert(t.root->parent == nullptr);
    assert(t.root->right->left->parent == t.root->right);
 
    // InsertFixUp
    RedBlackTree big = RedBlackTree();
    for(int i = 1; i <= 1000; i++)
    {
        big.Insert(i);
    }
    assert(big.root->color == COLOR_BLACK);
    assert(big.root->parent == nullptr);
    assert(CheckRBT(big.root) != -1);
 
    RedBlackTree mixed = RedBlackTree();
    for(int i = 0; i < 500; i++)
    {
        mixed.Insert((i * 37) % 500);  // every number 0-499 once, in a scrambled order (Source: ChatGPT)
    }
    assert(CheckRBT(mixed.root) != -1);
 
    // copy constructor
    RedBlackTree copy = RedBlackTree(mixed);
    assert(copy.root != mixed.root);
    assert(CheckRBT(copy.root) != -1);
 
    cout << "PASSED!" << endl << endl;
}
 
// Sources:
// ChatGPT was used the logic of insert and insert fixup, private tests, and error texts
// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html visualizer was used to understand insert steps and rotations and for checking the test cases
// http://btechsmartclass.com/data_structures/red-black-trees.html used before writing the header and .cpp file
// https://www.tutorialspoint.com/data_structures_algorithms/red_black_trees.htm used before writing the insert and insert fixup methods
// https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/
// Video lecture (the whole video) and worksheet
