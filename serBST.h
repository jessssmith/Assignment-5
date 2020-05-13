#include <iostream>

using namespace std;

template <class T>
class serBST : public BST<T> {
public:
  serBST();

  void serTree(ostream& o);
  void recSer(TreeNode<T>* node, ostream& o);
};

template <class T>
serBST<T>::serBST() : BST<T>() {}

template <class T>
void serBST<T>::serTree(ostream& o) {
  recSer(this->getRoot(), o);
}

template <class T>
void serBST<T>::recSer(TreeNode<T>* node, ostream& o) {
  if(node == NULL)
    return;
    node->getValue()->serialize(o);
    recSer(node->left, o);
    recSer(node->right, o);
}
