#pragma once
#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
  int data;
  Node* left;
  Node* right;
  NodeInterface* l;
  NodeInterface* r;

public:
  Node(int data);

  void setLeft(Node* newLeft);
  void setRight(Node* newRight);
  Node* getLeft() const;
  Node* getRight() const;

	int getData() const;
	NodeInterface* getLeftChild() const;
	NodeInterface* getRightChild() const;
};