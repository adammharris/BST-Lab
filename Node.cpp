#include "NodeInterface.h"
#include "Node.h"

Node::Node(int data) {
  this->data = data;
  left = NULL;
  right = NULL;
}

void Node::setData(int data) {
  this->data = data;
}
void Node::setLeft(Node* newLeft) {
  left = newLeft;
}
void Node::setRight(Node* newRight) {
  right = newRight;
}
Node* Node::getLeft() const {
  return left;
}
Node* Node::getRight() const {
  return right;
}
Node*& Node::recurseRight() {
  return right;
}

int Node::getData() const {
  return data;
}
NodeInterface* Node::getLeftChild() const {
  return left;
}
NodeInterface* Node::getRightChild() const {
  return right;
}