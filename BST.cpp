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
void BST::removeRoot(Node*& old_root) {
  if (old_root == NULL)
    return;
  cout << 'R';
  cout << " (removeRoot " << old_root->getData() << ")";
  bool hasRightChild = (old_root->getRight() != NULL);
  bool hasLeftChild = (old_root->getLeft() != NULL);
  if (hasRightChild != hasLeftChild) {
    Node* onlyChild;
    if (hasRightChild)
      onlyChild = old_root->getRight();
    else
      onlyChild = old_root->getLeft();
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
    cout << " succeeded (one: " << onlyChild->getData() << ")" << endl;
    return;
  }
  if (!hasRightChild && !hasLeftChild) {
    cout << " succeeded (was final)" << endl;
    delete root;
    root = NULL;
    local_node = NULL;
    return;
  }
  cout << " (two: " << old_root->getLeft()->getData() << ' ' << old_root->getRight()->getData() << ") ";
  // After here, know that both children are present
  Node* replacement = old_root->getLeft();
  //cout << replacement->getLeft() << endl;
  replaceParent(old_root, replacement);
  // recursive stuff here
  if (old_root == root) {
    cout << "first!";
  }
  cout << endl;
}
void BST::replaceParent(Node*& old_root,Node*& local_root) {
  cout << "RP";
  cout << old_root->getData() << ' ' << local_root->getData();
  if (local_root->getRight() != NULL) {
    replaceParent(old_root, local_root->recurseRight());
  } else {
    int newData = local_root->getData();
    removeNode(local_root->getData(), root);
    cout << 'L';
    old_root->setData(newData);
  }
}
bool BST::remove(int data) {
  return removeNode(data, root);
}
bool BST::removeNode(int data, Node* local_root) {
  cout << "Removing " << data;
  if (local_root == NULL) {
    cout << " failed (BST empty)" << endl;
    return false;
  }
  if (local_root == root && root->getData() == data) {
    local_node = NULL;
    delete root;
    root = NULL;
    //removeRoot(local_root);
    cout << " succeeded (was root first)" << endl;
    return true;
  }
  Node* child = find(data);
  if (child == NULL || child->getData() != data) {
    cout << " failed" << endl;
    return false;
  }
  if (child->getLeft() != NULL || child->getRight() != NULL) {
    removeRoot(child); // Remove if have child
    //cout << " succeeded (had at least one child)" << endl;
    return true;
  }
  // Remove if leaf
  Node* parent = findParent(child);
  if (parent == NULL) {
    delete local_root;
    local_root = NULL;
    local_node = NULL;
    cout << " succeeded (was root)" << endl;
    return true;
  }
  if (child->getData() > parent->getData()) {
    parent->setRight(NULL);
  } else {
    parent->setLeft(NULL);
  }
  delete child;
  cout << " succeeded (was leaf)" << endl;
  cout << "root = " << root->getData() << endl;
  return true;
}
void BST::clear() {
  if (root == NULL) {
    cout << "finished clear";
    return;
  }
  cout << "non finished clear…";
  cout << root->getLeft() << root->getRight();
  remove(root->getData());
  clear();
}