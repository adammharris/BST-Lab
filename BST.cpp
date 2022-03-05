#include "BST.h"
#include "BSTInterface.h"
#include "Node.h"
#include "NodeInterface.h"
#include <iostream>

Node* BST::find(const int& data) {
  Node* nextNode;
  if (data > local_node->getData()) {
    nextNode = local_node->getRight();
  } else if (data < local_node->getData()) {
    nextNode = local_node->getLeft();
  } else {
    nextNode = NULL;
  }
  if (nextNode == NULL) {
    Node* toReturn = local_node;
    local_node = root; // reset local_node 
    return toReturn;
  }
  local_node = nextNode;
  return find(data);
}
Node* BST::findParent(const Node* child) {
  if (child == root)
    return NULL;
  if (local_node->getRight() == child || local_node->getLeft() == child) {
    Node* toReturn = local_node;
    local_node = root; // reset local_node 
    return toReturn;
  }
  if (local_node->getData() < child->getData()) {
    local_node = local_node->getRight();
  } else {
    local_node = local_node->getLeft();
  }
  findParent(child);
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
  Node* closestNode = find(data);
  if (closestNode == NULL || closestNode->getData() == data)
    return false;
  Node* newNode = new Node(data);
  if (data > closestNode->getData()) {
    closestNode->setRight(newNode);
  } else {
    closestNode->setLeft(newNode);
  }
  return true;
}
void BST::removeRoot(Node* old_root) {
  if (old_root == NULL)
    return;
  bool hasRightChild = (old_root->getRight() != NULL);
  bool hasLeftChild = (old_root->getLeft() != NULL);
  if (hasRightChild != hasLeftChild) {
    Node* onlyChild = (hasRightChild) ? old_root->getRight() : old_root->getLeft();
    Node* parent = findParent(old_root);
    if (parent != NULL) {
      if (parent->getLeft() == old_root) {
        parent->setLeft(onlyChild);
      } else {
        parent->setRight(onlyChild);
      }
    }
    if (old_root == root)
      root = onlyChild;
    delete old_root;
    return;
  }
  if (!hasRightChild && !hasLeftChild && old_root == root) {
    delete root;
    root = NULL;
    local_node = NULL;
    return;
  }
  // After here, know that both children are present
  /*60 is the old_root. 
Now find the rightmost local root that does not have a right child and call it local_root (57)
replace the data in node 60 with 57.  
Call erase(BTNode<int>*55, 57) This will go down the branch for 55 until it finds node 57 and will erase it by replacing it with 56.*/
  cout << "Hello " << old_root->getData();
  int hack = old_root->getData();
  hack--;
  local_node = old_root;
  Node* replacement = find(hack);
  cout << ' ' << replacement->getData() << endl;
  if (replacement->getData() == old_root->getData()) {
    cout << "SAME!!";
    replacement = old_root->getRight();
    return;
  }
  // recursive stuff here
  old_root->setData(replacement->getData());
  removeNode(replacement->getData(), old_root);
}
bool BST::remove(int data) {
  return removeNode(data, root);
}
bool BST::removeNode(int data, Node* local_root) {
  if (local_root == NULL)
    return false;
  if (local_root == root && root->getData() == data) {
    delete root;
    root = NULL;
    local_node = NULL;
    return true;
  }
  Node* child = find(data);
  if (child == NULL || child->getData() != data)
    return false;
  if (child->getLeft() != NULL || child->getRight() != NULL) {
    removeRoot(child); // Remove if have child
    return true;
  }
  // Remove if leaf
  Node* parent = findParent(child);
  if (parent == NULL) {
    delete local_root;
    local_root = NULL;
    local_node = NULL;
    return true;
  }
  if (child->getData() > parent->getData()) {
    parent->setRight(NULL);
  } else {
    parent->setLeft(NULL);
  }
  delete child;
  return true;
}
void BST::clear() {
  if (root == NULL)
    return;
  removeRoot(root);
  clear();
}