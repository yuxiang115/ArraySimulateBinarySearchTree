#pragma once
#ifndef _ARRAYBTNODE_H
#define _ARRAYBTNODE_H
#include <ostream>
using namespace std;

template<class DT>
class ArrayBTNode {
	template<class DT> friend ostream& operator<< (ostream& os, ArrayBTNode<DT>& node);
public:
	DT* _info;
	int _left;
	int _right;
	bool found;//check if find this tree

	ArrayBTNode();
	ArrayBTNode(DT& data);
	DT& info();
	bool isEmpty();
	int left();
	int right();
	void setInfo(DT& data);
	void setLeft(int left);
	void setRight(int right);
	bool operator> (ArrayBTNode<DT>& node);
	bool operator< (ArrayBTNode<DT>& node);
	bool operator == (ArrayBTNode<DT>& node);
	bool operator >= (ArrayBTNode<DT>& node);
	bool operator <= (ArrayBTNode<DT>& node);
	bool operator != (ArrayBTNode<DT>& node);
	bool hasMoreSubtree();
	void makeEmpty();
};

template<class DT>
ArrayBTNode<DT>::ArrayBTNode() {
	_info = NULL;
	_left = -1;
	_right = -1;
	bool found = false;
}

template<class DT>
ArrayBTNode<DT>::ArrayBTNode(DT& data) {
	_info = new DT(data);
	_left = -1;
	_right = -1;
	bool found = false;
}

template<class DT>
DT& ArrayBTNode<DT>::info() {
	return *_info;
}

template<class DT>
bool ArrayBTNode<DT>::operator> (ArrayBTNode<DT>& node) {
	return (*_info > node.info());
}

template<class DT>
bool ArrayBTNode<DT>::operator<=(ArrayBTNode<DT>& node) {
	return (*_info <= node.info());
}

template<class DT>
bool ArrayBTNode<DT>::operator<(ArrayBTNode<DT>& node) {
	return (*_info < node.info());
}

template<class DT>
bool ArrayBTNode<DT>::operator>=(ArrayBTNode<DT>& node) {
	return(*_info >= node.info());
}

template<class DT>
bool ArrayBTNode<DT>::operator==(ArrayBTNode<DT>& node) {
	return(*_info == node.info());
}

template<class DT>
bool ArrayBTNode<DT>::operator!=(ArrayBTNode<DT>& node) {
	return(*_info != node.info());
}

template<class DT>
ostream& operator<<(ostream& os, ArrayBTNode<DT>& node) {
	os << node.info();
	return os;
}

template<class DT>
bool ArrayBTNode<DT>::isEmpty() {
	return(_info == NULL);
}

template<class DT>
void ArrayBTNode<DT>::setLeft(int left) {
	_left = left;
}

template<class DT>
void ArrayBTNode<DT>::setRight(int right) {
	_right = right;
}

template<class DT>
int ArrayBTNode<DT>::left() {
	return _left;
}

template<class DT>
int ArrayBTNode<DT>::right() {
	return _right;
}
/**
@paramater set info
@return void
*/
template<class DT>
void ArrayBTNode<DT>::setInfo(DT& data) {
	if (_info == NULL)
		_info = new DT(data);
	else {
		delete _info;
		_info = new DT(data);
	}
}
/**
@return bool check if more subtree
*/
template<class DT>
bool ArrayBTNode<DT>::hasMoreSubtree() {
	return ((_left != -1) || (_right != -1));
}

template<class DT>
void ArrayBTNode<DT>::makeEmpty() {
	if (_info != NULL)
		delete _info;
	_info = NULL;
}

#endif // !_ARRAYBTNODE_H
