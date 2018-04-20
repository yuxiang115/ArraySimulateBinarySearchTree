#pragma once
#ifndef _ARRAYBT_H
#define _ARRAYBT_H
#include "ArrayBTNode.h"
#include <vector>
#include<stack>
#include<queue>
#include<cstdlib>

class Exception{};
class ArrayBTException : Exception{};
class ArrayBTEmptyTree : ArrayBTException {};

template<class DT>
class ArrayBT {
public:
	vector<ArrayBTNode<DT>*>* myBinaryTree;
	int _root; //index position of the root the binary tree in the vector 
	int _numNodes; //the number of nodes in the binary tree 
	int _size; //max size of vector
	stack<int> freeLocations; //STL stack
	ArrayBT();//empty constructor
	ArrayBT(ArrayBTNode<DT>* data, int n);//create the tree with root value of data and n node of vector
	ArrayBT(int n);//create empty tree with vector that with n nodes
	bool isEmpty();//check if the tree empty
	int size();//size of the tree
	int height();//height of the tree
};

/**
default constructor
*/
template<class DT>
ArrayBT<DT>::ArrayBT() {
	_root = -1;
	_numNodes = 1;
	_size = 1;
	myBinaryTree = new vector<ArrayBTNode<DT>*>();
	myBinaryTree->push_back(new ArrayBTNode<DT>());
	freeLocations.push(0);
}
/**constructor
@paramater int n of node into vector
@ArrayBTNode<DT>* data initial the root
*/
template<class DT>
ArrayBT<DT>::ArrayBT(ArrayBTNode<DT>* data, int n) {
	_root = 0;
	_numNodes = n;
	_size = n; 
	myBinaryTree = new vector<ArrayBTNode<DT>*>();
	myBinaryTree->push_back(data);

	for (int i = 1; i < n; i++) {
		myBinaryTree->push_back(new ArrayBTNode<DT>());
		freeLocations.push(i);
	}
}
/**constructor
@paramater int n of node into vector
*/
template<class DT>
ArrayBT<DT>::ArrayBT(int n) {
	_root = -1;
	_numNodes = n;
	_size = n;
	myBinaryTree = new vector<ArrayBTNode<DT>*>();
	for (int i = 0; i < n; i++) {
		myBinaryTree->push_back(new ArrayBTNode<DT>());
		freeLocations.push(i);
	}
}
/**
@return bool check if empty tree
*/
template<class DT>
bool ArrayBT<DT>::isEmpty() {
	return (_root == -1);
}
/**
@return int size of tree
*/
template<class DT>
int ArrayBT<DT>::size() {
	int size = 0;
	for (int i = 0; i < _size; i++) {//just track the tree
		if (!(*myBinaryTree)[i]->isEmpty()) {
			size = size + 1;
		}
	}
	return size;
}
/**
@return int height of tree
*/
template<class DT>
int ArrayBT<DT>::height() {
	int height = 0;
	if(isEmpty()){		
		return 0; //if empty tree  0
	}
	queue<ArrayBTNode<DT>*> q;
	q.push((*myBinaryTree)[_root]);
	while (true) {
		int nodesNum = q.size();
		if (nodesNum == 0)
			return height;//no more lower subtree

		height++; //means there is some lowever subtree so height + 1
		while (nodesNum > 0) {
			ArrayBTNode<DT>* node = q.front();
			q.pop();
			if (node->_left != -1)//use queue (first in first out) to cout the height
				q.push((*myBinaryTree)[node->_left]);
			if (node->_right != -1)
				q.push((*myBinaryTree)[node->_right]);
			nodesNum--;
		}
	
	}
} 


#endif // !_ARRAYBT_H
