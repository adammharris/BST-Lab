#pragma once

#include "BSTInterface.h"

using namespace std;

class BST {
protected:
  Node *root;
public:
	NodeInterface * getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();
};