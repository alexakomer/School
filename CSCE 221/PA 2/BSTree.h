#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename U> struct BSNode
{
    // node members
    BSNode<U>* leftChild;
    BSNode<U>* rightChild;
    U data;

    BSNode(U data);
};

template <typename T> class BSTree
{
    private:
        //tree members
        BSNode<T>* root;
        int numberNodes;

        //private tree functions
        BSNode<T>* findMin(BSNode<T>* t); // finds minimum val
        BSNode<T>* findMax(BSNode<T>* t); // finds maximum val
        void insert(T value, BSNode<T>* &t); // inserts a node with the given value
        void remove(T value, BSNode<T>* & rm); // remove a node with the given value
        void display(BSNode<T>* &n, int padding); // prints the tree

    public:
        //public tree functions
        BSTree(); // constructor
        T findMin(); // finds minimum val
        T findMax(); // find maximum val
        bool contains(T value); // determines if a tree contains an element
        void insert(T value); // inserts a node with given value
        void remove(T value); // removes a node with given value
        int size(); // returns the number of nodes in the tree
        void display(); // prints the tree

};
