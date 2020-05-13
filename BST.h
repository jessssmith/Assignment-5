#include <iostream>
#include <string>
#include "TreeNode.h"

using namespace std;

template<class T>
class BST {
public:
  BST();
  virtual ~BST();

  T searchKey(int k); //to find student of faculty based on id
  void insert(T value);
  int search(T value);
  bool deleteNode(T key);

  bool isEmpty();
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();

  TreeNode<T>* getRoot();
  TreeNode<T>* getSuccessor(TreeNode<T> *d);
  void printTree(TreeNode<T> *node);
  TreeNode<T> *root;
private:
  //TreeNode<T> *root;
};

//bst implementation

template<class T>
BST<T>::BST() {
  root = NULL;
}

template<class T>
BST<T>::~BST() {
  //figure this one out
}

template<class T>
void BST<T>::printTree(TreeNode<T> *node) {
  if(node == NULL)
    return;
  printTree(node->left);
  node->value->printSorF();
  printTree(node->right);
}

template<class T>
TreeNode<T>* BST<T>::getMax() {
  TreeNode<T> *curr = root;
  if(root == NULL)
    return root;
  while(curr->right != NULL) {
    curr = curr->right;
  }
  return curr;
}

template<class T>
TreeNode<T>* BST<T>::getMin() {
  TreeNode<T> *curr = root;
  if(root == NULL)
    return root;
  while(curr->left != NULL) {
    curr = curr->left;
  }
  return curr;
}

template<class T>
bool BST<T>::isEmpty() {
  return (root == NULL);
}

template<class T>
void BST<T>::insert(T value) {
  TreeNode<T> *node = new TreeNode<T>(value, value->getID()); //value is also the key, inserts based on value which is the students id

  if(root == NULL)//isEmpty
    //we have an empty tree
    root = node;
  else {
    //tree not empty, we need to find the location
    TreeNode<T> *curr = root;
    TreeNode<T> *parent; //empty node

    while(true) {
      //lets find the insertion point
      parent = curr;

      //check if the value is less than or greater than curr (for left or right)
      if(value->getID() < curr->getKey()) {
        //go left
        curr = curr->left;
        if(curr == NULL) {
          parent->left = node;
          break;
        }
      }
      else {
        //go right
        curr = curr->right;
        if(curr == NULL) {
          parent->right = node;
          break;
        }
      }
    }
  }
}

template<class T>
int BST<T>::search(T value) {
  if(isEmpty())
    return false;
  else {
    TreeNode<T> *curr = root;

    while(curr->key != value->getID()) {
      if(value->getID() < curr->key)
        curr = curr->left;
      else
        curr = curr->right;
      if(curr == NULL) {
        return false;
      }
    }
    return curr->key;
  }
}

template<class T>
bool BST<T>::deleteNode(T ke) {
  if(isEmpty())
    return false;

  //tree is not empty
  TreeNode<T> *curr = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;

  int k = search(ke);
  //usual code to find node
  while(curr->key != k) { //_______________change here__________________
    parent = curr;
    if(k < curr->key) {
      isLeft = true;
      curr = curr->left;
    }
    else {
      isLeft = false;
      curr = curr->right;
    }
    if(curr == NULL)
      return false;
  }
  //if we made it to here then we found the node and need to delete

  if(curr->left == NULL && curr->right == NULL) {
    //leaf
    if(curr == root)
      root = NULL;
    else if(isLeft)
      parent->left = NULL;
    else
      parent->right = NULL;
  }
  //one child case, and child is is left
  else if(curr->right == NULL) {
    if(curr == root)
      root = curr->left;
    else if(isLeft)
      parent->left = curr->left;
    else
      parent->left = curr->left;
  }
  else if(curr->left == NULL) {
    if(curr == root)
      root = curr->right;
    else if(isLeft)
      parent->right = curr->right;
    else
      parent->right = curr->right;
  }
  else {
    //node has two children
    TreeNode<T> *successor = getSuccessor(curr);

    if(curr == root)
      root = successor;
    else if(isLeft)
      parent->left = successor;
    else
      parent->right = successor;

    successor->left = curr->left;

    return true;
  }
}

template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
  //d is the node to be deleted
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *curr = d->right;

  while(curr != NULL) {
    sp = successor;
    successor = curr;
    curr = curr->left;
  }
  //found successor
  if(successor != d->right) {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template<class T>
T BST<T>::searchKey(int k) {
  if(isEmpty())
    return NULL;
  else {
    TreeNode<T> *curr = root;
    int temp = curr->getKey();

    while(temp != k) {
      if(k < temp)
        curr = curr->left;
      else
        curr = curr->right;

      if(curr == NULL)
        return NULL;
      temp = curr->getKey();
    }
    return curr->getValue();
  }
}

template <class T>
TreeNode<T>* BST<T>::getRoot() {
  return root;
}
