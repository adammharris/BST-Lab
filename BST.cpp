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
bool BST::remove(int data) {
  if (root == NULL) {
    return false;
  }
  Node* closestNode = find(data);
  cout << data;
  if (closestNode == NULL || closestNode->getData() != data) {
    cout << " not found" << endl;
    return false;
  }
  cout << " found!!" << endl;
  //delete closestNode;
  return true;
}
void BST::clear() {
  
}