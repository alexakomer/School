#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

using namespace std;

// RBNode constructor
template <class T>
RBNode<T>::RBNode(T data) : leftChild(nullptr), rightChild(nullptr), data(data), color(RED) {}

// finds minimum val
template <class T>
RBNode<T>* RBTree<T>::findMin(RBNode<T>* &t)
{
    while(t->leftChild != nullptr)
        t = t->leftChild;
    return t;
}

// finds maximum val
template <class T>
RBNode<T>* RBTree<T>::findMax(RBNode<T>* &t)
{
    while(t->rightChild != nullptr) {
        t = t->rightChild;
    }
    return t;
}

// rotates subtree left
template <class T>
void RBTree<T>::rotateLeft(RBNode<T>  *&t)
{
    RBNode<T>* t_right = t->rightChild;
    t->rightChild = t_right->leftChild;

    if (t->rightChild != nullptr)
        t->rightChild->parent = t;

    t_right->parent = t->parent;

    if (t->parent == nullptr)
        root = t_right;
    else if (t == t->parent->leftChild)
        t->parent->leftChild = t_right;
    else
        t->parent->rightChild = t_right;

    t_right->leftChild = t;
    t->parent = t_right;
}

// rotates subtree right
template <class T>
void RBTree<T>::rotateRight(RBNode<T>* &t)
{
    RBNode<T>* t_left = t->leftChild;
    t->leftChild = t_left->rightChild;

    if (t->leftChild != nullptr)
        t->leftChild->parent = t;


    t_left->parent = t->parent;

    if (t->parent == NULL)
        root = t_left;
    else if (t == t->parent->leftChild)
        t->parent->leftChild = t_left;
    else
        t->parent->rightChild = t_left;

    t_left->rightChild = t;
    t->parent = t_left;
}

// fixes coloring and order violations
template <class T>
void RBTree<T>::reorient(RBNode<T>* &t)
{
    RBNode<T>* t_parent = nullptr;
    RBNode<T>* t_grand = nullptr;

    while ((t != root) && (t->color != BLACK) && (t->parent->color == RED))
    {
        t_parent = t->parent;
        t_grand = t->parent->parent;
        RBNode<T>* t_uncle = (t_parent == t_grand->leftChild) ? (t_grand->rightChild) : (t_grand->rightChild);

        if (t_uncle != nullptr && t_uncle->color ==  RED)
        { //Case 1: uncle is red
                t_grand->color = RED;
                t_parent->color = BLACK;
                t_uncle->color = BLACK;
                t = t_grand;
            }
        else
        { //Case 2: uncle is black
            if (t_parent == t_grand->leftChild)
            {
                if (t == t_parent->rightChild)
                { //Case 2.2: left-right
                    rotateLeft(t_parent);
                    t = t_parent;
                    t_parent = t->parent;
                }
                rotateRight(t_grand);  //Case 2.1: left-left
                std::swap(t_parent->color, t_grand->color);
                t = t_parent;
            }
            else
            {
                if (t == t_parent->leftChild)
                {  //Case 2.4: right-right
                    rotateRight(t_parent);
                    t = t_parent;
                    t_parent = t->parent;
                }
                rotateLeft(t_grand); //Case 2.3: right-left
                std::swap(t_parent->color, t_grand->color);
                t = t_parent;
            }
        }
    }
    root->color = BLACK; //root is always black
}

// recursively handle node insertion with no violations
template <class T>
RBNode<T>* RBTree<T>::basicInsert(RBNode<T>* value, RBNode<T>* t)
{
    if (t == nullptr) {
        numberNodes++;
        return value;
    }
    if (value->data < t->data) {
        t->leftChild = basicInsert(value, t->leftChild);
        t->leftChild->parent = t;
    }
    else if (value->data > t->data) {
        t->rightChild = basicInsert(value, t->rightChild);
        t->rightChild->parent = t;
    }
    return t;
}

// prints the tree
template <class T>
void RBTree<T>::display(RBNode<T>* n, int padding)
{
    if (n == nullptr) { return; }
    padding += 10;

    display(n->rightChild, padding);

    std::cout << std::endl << std::setw(padding) << n->data;
    (n->color==BLACK) ? (std::cout<<" (BLK)") : (std::cout<<" (RED)");
    std::cout << std::endl;

    display(n->leftChild, padding);
}

//constructor
template <class T>
RBTree<T>::RBTree() : root(nullptr), numberNodes(0) {}

// finds minimum val
template <class T>
T RBTree<T>::findMin()
{
  return findMin(root)->data;
}

// finds maximum val
template <class T>
T RBTree<T>::findMax()
{
  return findMax(root)->data;
}

// determines if an element is within the tree
template <class T>
bool RBTree<T>::contains(T value)
{
    RBNode<T>* t = root;
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

// inserts a node with the given value and accounts for violations
template <class T>
void RBTree<T>::insert(T value)
{
    RBNode<T>* v = new RBNode<T>(value);
    root = basicInsert(v, root);
    if (v == root || v->parent != nullptr) // if violation exists
      reorient(v); // fix it
}

// returns number of nodes in the tree
template <class T>
int RBTree<T>::size()
{
    return numberNodes;
}

//prints the tree
template <class T>
void RBTree<T>::display()
{
    display(root,0);
}

#include <chrono>

int main()
{
    int iterations = 100000;

    // insert increasing order code

    // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    // for (int i = 1; i <= iterations / 10; i *= 10)
    // {
    //     for (int c = i; c <= i * 10; c++)
    //         rbTree.insert(c);
    //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
    //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
    // }

    // insert decreasing order code

    // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    // for (int i = 1; i <= iterations / 10; i *= 10)
    // {
    //     for (int c = i; c <= i * 10; c++)
    //         rbTree.insert(iterations - c);
    //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
    //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
    // }

    // insert random order code

    // int nums[iterations];
    // for (int i = 1; i <= iterations; i++)
    //   nums[i] = i;
    // std::random_shuffle(nums, nums + iterations);
    //
    // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    // for (int i = 1; i <= iterations / 10; i *= 10)
    // {
    //     for (int c = i; c <= i * 10; c++)
    //         rbTree.insert(nums[i]);
    //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
    //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
    // }

    // Testing functions

    RBTree<int> rbTree;

    rbTree.insert(1);
    rbTree.display();
    rbTree.insert(1);
    rbTree.display();
    // rbTree.remove(1);
    // rbTree.display();
    // rbTree.remove(1);
    // rbTree.display();
    rbTree.insert(1);
    rbTree.insert(2);
    rbTree.insert(3);
    rbTree.insert(0);
    rbTree.display();
    cout << "Max is: " << rbTree.findMax() << endl;
    cout << "Min is: " << rbTree.findMin() << endl;
    cout << "Size is: " << rbTree.size() << endl;
    cout << "Contains 2?: " << rbTree.contains(2) << endl;
    cout << "Contains 4?: " << rbTree.contains(4) << endl;

}
