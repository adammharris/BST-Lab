#include "BST.h"
#include "BSTInterface.h"
#include "Node.h"
#include "NodeInterface.h"

bool BST::find(NodeInterface*& local_root, int data) {
  if (local_root == NULL) {
    return false;
  }
  if (local_root->getData() < data) {
    local_root = local_root->getLeftChild();
  } else if (local_root->getData() > data) {
    local_root = local_root->getRightChild();
  } else if (local_root->getData() == data) {
    return true;
  }
  return find(local_root, data);
}

BST::BST() {
  root = NULL;
  local_node = NULL;
}
NodeInterface* BST::getRootNode() const {
  return root;
}
bool BST::add(int data) {
  if (root == NULL) {
    root = new Node(data);
    local_node = root;
    return true;
  }
  NodeInterface* local_root = root;
  bool isPresent = find(local_root, data);
  if (!isPresent) {
    local_root = new Node(data);
  }
  return isPresent;
}
bool BST::remove(int data) {
  if (root == NULL) {
    return false;
  }
  NodeInterface* local_root = root;
  bool isPresent = find(local_root, data);
  return false;
}
void BST::clear() {
  
}