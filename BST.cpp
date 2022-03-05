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
  bool hasRightChild = (old_root->getRight() != NULL);
  bool hasLeftChild = (old_root->getLeft() != NULL);
  if (hasRightChild != hasLeftChild) {
    Node* onlyChild = (hasRightChild) ? old_root->getRight() : old_root->getLeft();
    Node* parent = findParent(old_root);
    if (parent->getLeft() == old_root) {
      parent->setLeft(onlyChild);
    } else {
      parent->setRight(onlyChild);
    }
    delete old_root;
    return;
  }
  // After here, know that both children are present
  
}
bool BST::remove(int data) {
  if (root == NULL)
    return false;
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
    delete root;
    root = NULL;
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
  
}