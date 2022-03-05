#pragma once

#include "BSTInterface.h"
#include "NodeInterface.h"
#include "Node.h"

using namespace std;
class BST : public BSTInterface {
protected:
  Node* root;
  Node* local_node;
public:
  bool find(NodeInterface*& local_root, int data);

  BST();
	NodeInterface* getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();
};