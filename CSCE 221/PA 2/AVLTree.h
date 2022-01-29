#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename U> struct AVLNode
{
  // node members
    AVLNode<U>* leftChild;
    AVLNode<U>* rightChild;
    U data;
    int height;

    AVLNode(U data);
};

template <typename T> class AVLTree
{
    private:

        //tree members
        AVLNode<T>* root;
        int numberNodes;
        static const int TOL = 1;

        //private tree functions
        AVLNode<T>* findMin(AVLNode<T>* &t); // finds minimum val
        AVLNode<T>* findMax(AVLNode<T>* &t); // finds maximum val
        int height(const AVLNode<T>* t); // returns height of tree
        void leftSingleRotation(AVLNode<T>* &B); // rotates subtree left once
        void rightSingleRotation(AVLNode<T>* &B); // rotates subtree right once
        void leftDoubleRotation(AVLNode<T>* &C); // rotates subtree left twice
        void rightDoubleRotation(AVLNode<T>* &C); // rotates subtree right twice
        void balanceTree(AVLNode<T>* &t); // fixes order violations
        void insert(T value, AVLNode<T>* &t); // inserts a node with given value
        void remove(T value, AVLNode<T>* & rm); // deletes a node with given value
        void display(AVLNode<T>* &n, int padding); // prints the tree

    public:
        //public tree functions
        AVLTree(); // constructor
        T findMin(); // finds minimum val
        T findMax(); // finds maximum val
        bool contains(T value); // determine if an element exists within the tree
        void insert(T value); // inserts a node with the given value
        void remove(T value); // removes a node with the given value
        int size(); // returns the number of nodes in the tree
        void display(); // prints the tree
};
