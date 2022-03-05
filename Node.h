#pragma once
#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
  int data;
  NodeInterface* left;
  NodeInterface* right;

public:
  Node(int data);
	int getData() const;
	NodeInterface* getLeftChild() const;
	NodeInterface* getRightChild() const;
};