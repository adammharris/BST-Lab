#pragma once

#include "BSTInterface.h"
#include "NodeInterface.h"
#include "Node.h"

using namespace std;
class BST : public BSTInterface {
protected:
  Node* root;
  Node* local_node; // used for `find`
public:
	/*
	* `find` helps find data via recursion
  * @return pointer of node next to or equal to data
  * @return NULL if BST is empty
	*/
  Node* find(const int& data);

  BST();
	NodeInterface* getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();
};