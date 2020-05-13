#include <iostream>

template<class T>
class TreeNode {
public:
  TreeNode();
//  TreeNode(T key);
  TreeNode(T v, int k);
  virtual ~TreeNode();
  T getValue();
  int getKey();

  int key;
  T value;
  TreeNode *left;
  TreeNode *right;
};

//TreeNode implementation
//tree implementation
template<class T>
TreeNode<T>::TreeNode() {
  key = 0;
  left = NULL;
  right = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T v, int k) {
  key = k;
  value = v;
  left = NULL;
  right = NULL;
}

template<class T>
TreeNode<T>::~TreeNode() {
  //figure this one out
}

template<class T>
int TreeNode<T>::getKey() {
  return key;
}

template<class T>
T TreeNode<T>::getValue() {
  return value;
}
