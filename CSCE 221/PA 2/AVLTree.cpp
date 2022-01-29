#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

using namespace std;

// AVLNode constructor
template <typename S>
AVLNode<S>::AVLNode(S data) : leftChild(nullptr), rightChild(nullptr), data(data), height(0) {}

// finds minimum val
template <typename S>
AVLNode<S>* AVLTree<S>::findMin(AVLNode<S>* &t)
{
    while(t->leftChild != nullptr)
        t = t->leftChild;
    return t;
}

// finds maximum val
template <typename S>
AVLNode<S>* AVLTree<S>::findMax(AVLNode<S>* &t)
{
    while(t->rightChild != nullptr)
        t = t->rightChild;
    return t;
}

// returns height of tree
template <typename S>
int AVLTree<S>::height(const AVLNode<S>* t)
{
   return (t != nullptr) ? (t->height) : (0);
}

// rotate subtree left once
template <typename S>
void AVLTree<S>::leftSingleRotation(AVLNode<S>* &B)
{
    AVLNode<S>* A = B->leftChild; //where A is K1 and B is K2
    B->leftChild = A->rightChild;
    A->rightChild = B;
    B->height = std::max(height(B->leftChild), height(B->rightChild))+1;
    A->height = std::max(height(A->leftChild), height(B))+1;
    B = A;
}

// rotates subtree right once
template <typename S>
void AVLTree<S>::rightSingleRotation(AVLNode<S>* &B)
{
    AVLNode<S>* A = B->rightChild; //where A is K1 and B is K2
    B->rightChild = A->leftChild;
    A->leftChild = B;
    B->height = std::max(height(B->rightChild), height(B->leftChild))+1;
    A->height = std::max(height(A->rightChild), height(B))+1;
    B = A;
}

// rotates subtree left twice
template <typename S>
void AVLTree<S>::leftDoubleRotation(AVLNode<S>* &C)
{
    rightSingleRotation(C->leftChild);
    leftSingleRotation(C);
}

// rotates subtree right twice
template <typename S>
void AVLTree<S>::rightDoubleRotation(AVLNode<S>* &C)
{
    leftSingleRotation(C->rightChild);
    rightSingleRotation(C);
}

// fixes order violations
template <typename S>
void AVLTree<S>::balanceTree(AVLNode<S>* &t)
{
    if (t==nullptr) { return;}

    if (height(t->leftChild) - height(t->rightChild) > TOL)
    { // left subtree bigger than right
        (height(t->leftChild->leftChild) >= height(t->leftChild->rightChild)) ? (leftSingleRotation(t)) : (leftDoubleRotation(t));
    }
    else if (height(t->rightChild) - height(t->leftChild) > TOL)
    { // right subtree bigger than left
        (height(t->rightChild->rightChild) >= height(t->rightChild->leftChild)) ? (rightSingleRotation(t)) : (rightDoubleRotation(t));
    }
    t->height = std::max(height(t->leftChild), height(t->rightChild))+1;
}

// inserts a node with the given value
template <typename S>
void AVLTree<S>::insert(S value, AVLNode<S>* &t)
{
    if (t==nullptr) { // similar to BST
        t = new AVLNode<S>(value);
        numberNodes++;
    }
    else if (value < t->data) {
        insert(value, t->leftChild);
    }
    else if (value > t->data) {
        insert(value, t->rightChild);
    }

    balanceTree(t); //recursive balancing for every node
}

// removes a node with the given value
template <typename S>
void AVLTree<S>::remove(S value, AVLNode<S>* & rm)
{
    if (rm==nullptr) { return;}

    if(value<rm->data)
        remove(value,rm->leftChild);
    else if(value>rm->data)
        remove(value,rm->rightChild);
    else if (rm->leftChild != nullptr && rm->rightChild != nullptr)
    { //case 3
        rm->data = findMin(rm->rightChild)->data; //switch smallest right leaf with node to delete
        remove(rm->data, rm->rightChild); //delete swapped leaf
    }
    else { //case 1/2
        AVLNode<S>* t = rm;
        rm = ((t->leftChild != nullptr) ? rm->leftChild : rm->rightChild);
        delete t;
        numberNodes--;
    }
    balanceTree(rm);
}

// prints the tree
template <typename S>
void AVLTree<S>::display(AVLNode<S>* &n, int padding)
{
    if (n == nullptr)
        return;
    padding += 10;

    display(n->rightChild, padding);
    std::cout << std::endl << std::setw(padding) << n->data << std::endl;

    display(n->leftChild, padding);
}

// constructor
template <typename S>
AVLTree<S>::AVLTree() : root(nullptr), numberNodes(0) {}

// finds minimum val
template <typename S>
S AVLTree<S>::findMin()
{
  return findMin(root)->data;
}

// finds maximum val
template <typename S>
S AVLTree<S>::findMax()
{
  return findMax(root)->data;
}

// determines if an element exists within the tree
template <typename S>
bool AVLTree<S>::contains(S value)
{
    AVLNode<S>* t = root;
    while(t!=nullptr)
    {
        if(value < t->data)
            t=t->leftChild;

        else if(value > t->data)
            t=t->rightChild;

        else //already in tree
            return true;
    }
    return false;
}

// inserts a node with the given value
template <typename S>
void AVLTree<S>::insert(S value)
{
    insert(value,root);
}

// removes a node with the given value
template <typename S>
void AVLTree<S>::remove(S value)
{
    remove(value, root);
}

// returns the number of nodes in the tree
template <typename S>
int AVLTree<S>::size()
{
    return numberNodes;
}

// prints the tree
template <typename S>
void AVLTree<S>::display()
{
    display(root,0);
}


#include <chrono>

int main()
{

  int iterations = 100000;

  // AVLTree<int> avlTree;

  // insert increasing order code

  // cout <<"Inserting in increasing order: " << endl;

  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.insert(c);
  //     // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     // cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // remove increasing order code

  // cout <<"Removing in increasing order: " << endl;
  //
  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.remove(c);
  //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // insert decreasing order code

  // cout <<"Inserting in decreasing order: " << endl;
  //
  // // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.insert(iterations - c);
  //     // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     // cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // remove dereasing order code

  // cout <<"Removing in decreasing order: " << endl;
  //
  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.remove(iterations - c);
  //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // insert random order code

  // int nums[iterations];
  // for (int i = 1; i <= iterations; i++)
  //   nums[i] = i;
  // std::random_shuffle(nums, nums + iterations);
  //
  // // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.insert(nums[i]);
  //     // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     // cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // remove random order code

  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         avlTree.remove(nums[i]);
  //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // Testing functions

  AVLTree<int> avlTree;

  avlTree.insert(1);
  avlTree.display();
  avlTree.insert(1);
  avlTree.display();
  avlTree.remove(1);
  avlTree.display();
  avlTree.remove(1);
  avlTree.display();
  avlTree.insert(1);
  avlTree.insert(2);
  avlTree.insert(3);
  avlTree.insert(0);
  avlTree.display();
  cout << "Max is: " << avlTree.findMax() << endl;
  cout << "Min is: " << avlTree.findMin() << endl;
  cout << "Size is: " << avlTree.size() << endl;
  cout << "Contains 2?: " << avlTree.contains(2) << endl;
  cout << "Contains 4?: " << avlTree.contains(4) << endl;

    return 0;
}
