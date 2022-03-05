#include "NodeInterface.h"
#include "Node.h"

Node::Node(int data) {
  this->data = data;
  left = NULL;
  right = NULL;
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