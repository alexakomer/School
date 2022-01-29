#include "BSTree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// BSNode constructor
template <typename S>
BSNode<S>::BSNode(S data) : leftChild(nullptr), rightChild(nullptr), data(data) {}

// finds minimum val
template <typename S>
BSNode<S>* BSTree<S>::findMin(BSNode<S>* t)
{
    while(t->leftChild != nullptr)
        t = t->leftChild;
    return t;
}

// finds maximum val
template <typename S>
BSNode<S>* BSTree<S>::findMax(BSNode<S>* t)
{
    while(t->rightChild != nullptr)
        t = t->rightChild;
    return t;

}

// inserts a node with the given value
template <typename S>
void BSTree<S>::insert(S value, BSNode<S>* &t)
{
    if (t==nullptr)
    {
        t = new BSNode<S>(value);
        numberNodes++;
    }
    else if (value < t->data)
        insert(value, t->leftChild);
    else if (value > t->data)
        insert(value, t->rightChild);
}

// removes a node with the given value
template <typename S>
void BSTree<S>::remove(S value, BSNode<S>* & rm)
{
    if(rm==nullptr)
        return;
    if(value<rm->data)
        remove(value,rm->leftChild);
    else if(value>rm->data)
        remove(value,rm->rightChild);
    else if (rm->leftChild != nullptr && rm->rightChild != nullptr)
    { //case 3
        rm->data = findMin(rm->rightChild)->data; //switch smallest right leaf with node to delete
        remove(rm->data, rm->rightChild); //delete swapped leaf
    }
    else
    { //case 1/2
        BSNode<S>* t = rm;
        rm = ((t->leftChild != nullptr) ? rm->leftChild : rm->rightChild);
        delete t;
        numberNodes--;
    }
}

// prints the tree
template <typename S>
void BSTree<S>::display(BSNode<S>* &n, int padding)
{
    if (n == nullptr)
    {
        return;
    }
    padding += 10;

    display(n->rightChild, padding);
    std::cout << std::endl << std::setw(padding) << n->data << std::endl;

    display(n->leftChild, padding);
}

// constructor
template <typename S>
BSTree<S>::BSTree() : root(nullptr), numberNodes(0) {}

// finds minimum val
template <typename S>
S BSTree<S>::findMin()
{
  return findMin(root)->data;
}

// finds maximum val
template <typename S>
S BSTree<S>::findMax()
{
  return findMax(root)->data;
}

// determines if a tree contains a given value
template <typename S>
bool BSTree<S>::contains(S value)
{
    BSNode<S>* t = root;
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
void BSTree<S>::insert(S value)
{
    insert(value,root);
}

// removes a node with the given value
template <typename S>
void BSTree<S>::remove(S value)
{
    remove(value, root);
}

// returns the number of nodes in the tree
template <typename S>
int BSTree<S>::size()
{
    return numberNodes;
}

// prints the tree
template <typename S>
void BSTree<S>::display()
{
    display(root,0);
}

#include <chrono>

int main()
{

  int iterations = 100000;

  // insert increasing order code

  // cout <<"Inserting in increasing order: " << endl;
  //
  // // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         bsTree.insert(c);
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
  //         bsTree.remove(c);
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
  //         bsTree.insert(iterations - c);
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
  //         bsTree.remove(iterations - c);
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
  //         bsTree.insert(nums[i]);
  //     // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     // cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }

  // remove random order code

  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // for (int i = 1; i <= iterations / 10; i *= 10)
  // {
  //     for (int c = i; c <= i * 10; c++)
  //         bsTree.remove(nums[i]);
  //     chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  //     cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  // }


  // Testing functions

  BSTree<int> bsTree;

  bsTree.insert(1);
  bsTree.display();
  bsTree.insert(1);
  bsTree.display();
  bsTree.remove(1);
  bsTree.display();
  bsTree.remove(1);
  bsTree.display();
  bsTree.insert(1);
  bsTree.insert(2);
  bsTree.insert(3);
  bsTree.insert(0);
  bsTree.display();
  cout << "Max is: " << bsTree.findMax() << endl;
  cout << "Min is: " << bsTree.findMin() << endl;
  cout << "Size is: " << bsTree.size() << endl;
  cout << "Contains 2?: " << bsTree.contains(2) << endl;
  cout << "Contains 4?: " << bsTree.contains(4) << endl;
    return 0;
}
