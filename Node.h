#pragma once
#include <iostream>

template<typename T>
class Node {
private:
  T data;
  Node* left;
  Node* right;

public:
  Node();
	int getData() const;
	NodeInterface * getLeftChild() const;
	NodeInterface * getRightChild() const;
};