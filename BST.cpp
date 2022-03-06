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
    //cout << "Child: " << child->getData() << " Parent: " << toReturn->getData() << endl;
    return toReturn;
  }
  if (local_node->getData() < child->getData()) {
    local_node = local_node->getRight();
  } else {
    local_node = local_node->getLeft();
  }
  return findParent(child);
}

BST::BST() {
  root = NULL;
  local_node = NULL;
}
NodeInterface* BST::getRootNode() const {
  return root;
}
bool BST::add(int data) {
  cout << "Adding " << data;
  if (root == NULL) {
    root = new Node(data);
    local_node = root;
    cout << " succeeded (became root)" << endl;
    return true;
  }
  Node* closestNode = find(data);
  if (closestNode == NULL || closestNode->getData() == data) {
    cout << " failed (duplicate)" << endl;
   return false; 
  }
  Node* newNode = new Node(data);
  if (data > closestNode->getData()) {
    closestNode->setRight(newNode);
  } else {
    closestNode->setLeft(newNode);
  }
  cout << " succeeded" << endl;
  return true;
}
bool BST::remove(int data) {
  if (root->getRight() == NULL)
    cout << "No right node for root" << endl;
  if (root->getLeft() == NULL)
    cout << "No left node for root" << endl;
  //return removeNode(data, root);
  Node* representsRoot = root;
  if (data == root->getData()) {
    return removeFinalNode();
  }
  return erase(representsRoot, data);
}
bool BST::removeFinalNode() {
  if (root == NULL)
    return false;
  delete root;
  root = NULL;
  local_node = NULL;
  return true;
}

void BST::clear() {
  if (root == NULL)
    return;
  Node* representsRoot = root;
  remove(root->getData());
  clear();
}

bool BST::erase(Node*& local_root,const int& item) {
  if (local_root == NULL) {
    return false;
  } else {
    if (item < local_root->getData())
      return erase(local_root->recurseLeft(), item);
    else if (local_root->getData() < item)
      return erase(local_root->recurseRight(), item);
    else { // Found item
      Node* old_root = local_root;
      if (local_root->getLeft() == NULL) {
        local_root = local_root->getRight();
      } else if (local_root->getRight() == NULL) {
        local_root = local_root->getLeft();
      } else {
        //cout << "hello" << endl;
        replace_parent(old_root, old_root->recurseLeft());
        return true;
      }
      delete old_root;      
      return true;
    }
  }
}

void BST::replace_parent(Node*& old_root, Node*& local_root) {
  if (local_root->getRight() != NULL) {
    replace_parent(old_root, local_root->recurseRight());
  } else {
    int newData = local_root->getData();
    erase(local_root, local_root->getData());
    old_root->setData(newData);
  }
}