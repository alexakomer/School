#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

using namespace std;

// helps with coloring nodes
enum {RED, BLACK};

template <class T>
struct RBNode
{
  // node members
  RBNode<T>* leftChild;
  RBNode<T>* rightChild;
  RBNode<T>* parent;
  bool color;
  T data;

  RBNode(T data); // constructor
};

template <class T>
class RBTree
{
  private:
        // tree members
        RBNode<T>* root;
        int numberNodes;

        //private tree functions
        RBNode<T>* findMin(RBNode<T>* &t); // finds minimum val
        RBNode<T>* findMax(RBNode<T>* &t); // finds maximum val
        void rotateLeft(RBNode<T>  *&t); // rotates subtree left
        void rotateRight(RBNode<T>* &t); // rotates subtree right
        void reorient(RBNode<T>* &t); // fixes coloring and order violations
        RBNode<T>* basicInsert(RBNode<T>* value, RBNode<T>* t); // node insertion with no violations
        void display(RBNode<T>* n, int padding); // prints the tree

    public:
        //public tree functions
        RBTree(); // constructor
        T findMin(); // finds minimum val
        T findMax(); // finds maximum val
        bool contains(T value); // determines if an element is within the tree
        void insert(T value); // inserts a node and accounts for violations
        int size(); // returns the number of nodes in the tree
        void display(); // prints the tree
};
