#pragma once
#ifndef _ARRAYBST_H
#define _ARRAYBST_H
#include"ArrayBT.h"
#include "Enumeration.h"

template<class DT>
class PreOderEnumerator;


template<class DT>
class ArrayBST : virtual public ArrayBT<DT> {

	template<class DT> friend ostream& operator<<<DT>(ostream& os, ArrayBST<DT>& bst);
public:
	int outputStyle = 0; //0 for inoder, 1 for PreOder
	int _index; //idicate the index of object that found in the bst
	int _last; // idicate previously one position
	ArrayBST();
	ArrayBST(int k);//create the vector with k nodes
	ArrayBST(ArrayBTNode<DT>* data, int n);//initial the root value is data, and node into vector
	ArrayBTNode<DT>* find(DT& data);//find the data and return the pointer of the node
	bool contains(DT& data);//check if the binary search tree contain the data
	void insert(DT& data);//insert the data;
	Enumeration<DT>* preOderEnumerator();//pre oder Enumerator to print
	Enumeration<DT>* inOderEnumerator();//inorder enumerator to print
	void remove(DT& data);//remove the data
	void setOutputStyle(int i);//selete the print out mode
};

template<class DT>
ArrayBST<DT>::ArrayBST() : ArrayBT<DT>(){
}

template<class DT>
ArrayBST<DT>::ArrayBST(int k) : ArrayBT<DT>(k){
}

template<class DT>
ArrayBST<DT>::ArrayBST(ArrayBTNode<DT>* data, int n) : ArrayBT<DT>(data, n) {
}

/**
find the data
@paramater data DT&
@return ArrayBTNode<DT>*

*/
template<class DT>
ArrayBTNode<DT>* ArrayBST<DT>::find(DT& data) {
	ArrayBTNode<DT> node(data);
	ArrayBTNode<DT>* bst;
	int index = 0;
	if (this->_root >= 0) {//copare the value
		bst = (*this->myBinaryTree)[this->_root];//get the root node
		index = this->_root;
		while (true) {
			if (!bst->hasMoreSubtree()) {
				bst->found = false;//indicator that tell us if this bst is that we found it
				return bst; //check is have more subtree
			}
			
			if (node < *((*this->myBinaryTree)[index])) {
				_last = index;
				index = (*this->myBinaryTree)[index]->left();
				if (index == -1) {
					bst->found = false;
					return bst;
				}
				bst = (*this->myBinaryTree)[index];
				
			}

			else if (node > *((*this->myBinaryTree)[index])) {
				_last = index;//the last level of the node
				index = (*this->myBinaryTree)[index]->right();
				if (index == -1) {
					bst->found = false;
					return bst;
				}
				bst = (*this->myBinaryTree)[index];
			}
			else {
				//finally found the target node
				bst->found = true;
				_index = index;
				return bst;
			}
		}
	}
	else {
		//this is empty binary search tree, cannot find anything
		return NULL;
	}
}
/**
@paramater DT& data
@return bool check the tree contain the element
*/
template<class DT>
bool ArrayBST<DT>::contains(DT& data) {
	return(find(data)->found);
}

/**
insert the new data in to tree
@paramater DT& data
@return void
*/
template<class DT>
void ArrayBST<DT>::insert(DT& data) {
	int location;
	ArrayBTNode<DT> key(data); //create the node of the data insert
	ArrayBTNode<DT>* node;
		node = find(data);//check if this data have exist in the tree
		if (node == NULL) {//this means this Binary Search treee is empty, so just put the new data in to root
			location = this->freeLocations.top();
			this->freeLocations.pop();//free lacation out
			_root = location;
			(*this->myBinaryTree)[_root]->setInfo(data);//copty the data
		}
		else if (!node->found) {//this is not empty BST
			location = this->freeLocations.top();//get the free location 
			this->freeLocations.pop();//put out of free location

			(*this->myBinaryTree)[location]->setInfo(data);//copt the data into vector(bst)

			if (*node > key) {
				node->setLeft(location); //for order
			}
			else {
				node->setRight(location);
			}
		}
}
/**
@return Enumeration<DT>* PreOder
*/
template<class DT>
Enumeration<DT>* ArrayBST<DT>::preOderEnumerator() {
	return new PreOderEnumerator<DT>(this);
}
/**
@return Enumeration<DT>* InreOder
*/
template<class DT>
Enumeration<DT>* ArrayBST<DT>::inOderEnumerator() {
	return new InOderEnumerator<DT>(this);
}
/**
set the selete with order Enumerator for print
@return void 
*/
template<class DT>
void ArrayBST<DT>::setOutputStyle(int i) {
	outputStyle = i;
}
/**
remove data
there are 3 cases
@paramater DT& data for remove
@return void
*/
template<class DT>
void ArrayBST<DT>::remove(DT& data) {
	ArrayBTNode<DT> node = *find(data);
	ArrayBTNode<DT>* temp;
	ArrayBTNode<DT>* temp2;
	
	if (!node.found) {
		cout << "Data which need to be removed cannot be found, remove fail." << endl;
		return;
	}
	if (node.left() == -1) {//left subtree empty
		if (node.right() != -1) {
			int i = node.right();//i for hold track for tree
			int l;//the last level node postion
			temp = (*this->myBinaryTree)[i];
			while (temp->left() != -1) {
				l = i;
				i = temp->left();
				temp = (*this->myBinaryTree)[i];
			}
			node.setInfo(temp->info());
			temp->makeEmpty();
			temp = (*this->myBinaryTree)[l];
			temp->setLeft(-1);
			this->freeLocations.push(i);
		}
		else {
			temp2 = (*this->myBinaryTree)[_last];
			if (node > *temp2) {
				temp2->setRight(-1);
			}
			else temp2->setLeft(-1);
			node.makeEmpty();
			this->freeLocations.push(_index);
		}
	}

	else if (node.right() == -1) {
		if (node.left() != -1) {
			int i = node.left();
			int l;
			temp = (*this->myBinaryTree)[i];
			while (temp->right() != -1) {
				l = i;
				i = temp->right();
				temp = (*this->myBinaryTree)[i];
			}
			node.setInfo(temp->info());
			temp->makeEmpty();
			temp = (*this->myBinaryTree)[l];
			temp->setLeft(-1);
			this->freeLocations.push(i);
		}
		else {

			temp2 = (*this->myBinaryTree)[_last];
			if (node > *temp2) {
				temp2->setRight(-1);
			}
			else temp2->setLeft(-1);
			node.makeEmpty();
			this->freeLocations.push(_index);
		}
	}
	
	else{
		int l2;
		int i2 = node.right();
		temp = (*this->myBinaryTree)[i2];
		while (temp->left() != -1) {
			l2 = i2;
			i2 = temp->left();
			temp = (*this->myBinaryTree)[i2];
		}
		temp2 = temp;
		node.setInfo(temp->info());
		
		//========================//
		if (temp->right() != -1) {
			int i = temp->right();
			int l = i;
			temp = (*this->myBinaryTree)[i];
			while (temp->left() != -1) {
				l = i;
				i = temp->left();
				temp = (*this->myBinaryTree)[i];
			}
			temp2->setInfo(temp->info());
			temp->makeEmpty();
			temp = (*this->myBinaryTree)[l]; //previous level node
			temp->setLeft(-1);
			this->freeLocations.push(i);
			
		}
		else {
			temp2 = (*this->myBinaryTree)[l2];
			if (*temp > *temp2) {
				temp2->setRight(-1);
			}
			else temp2->setLeft(-1);
			temp->makeEmpty();
			this->freeLocations.push(i2);
		}
	}
	
	cout << "Removed Element: " << data << endl;
}
/**
@paramater ostream& os
@paramater ArrayBST<DT>& bst for print
@return ostream& os
*/
template<class DT>
ostream& operator << (ostream& os, ArrayBST<DT>& bst) {
	
	if (bst.outputStyle == 1) {
		Enumeration<int>* preOder = bst.preOderEnumerator();
		while (preOder->hasMoreElements()) {
			os << preOder->nextElement() << ", ";
		}
	}
	else {
		Enumeration<int>* inOder = bst.inOderEnumerator();
		while (inOder->hasMoreElements()) {
			os << inOder->nextElement() << ", ";
		}
	}
	os << endl;
	return os;
}


//================================================PreOder==========================//
template<class DT>
class PreOderEnumerator : public Enumeration<DT> {
protected:
	ArrayBST<DT>* _bst;
	stack<int> _stack;
public:
	PreOderEnumerator(ArrayBST<DT>* bst);
	bool hasMoreElements();
	DT& nextElement();
};

template<class DT>
PreOderEnumerator<DT>::PreOderEnumerator(ArrayBST<DT>* bst) {
	_bst = bst;
	_stack.push(_bst->_root);
}

template<class DT>
bool PreOderEnumerator<DT>::hasMoreElements() {
	return (!_stack.empty());
}

template<class DT>
DT& PreOderEnumerator<DT>::nextElement() {
	int i = _stack.top();
	_stack.pop();
	ArrayBTNode<DT>* temp;
	temp = (*_bst->myBinaryTree)[i];
	if(temp->right() >= 0)
		_stack.push(temp->right());
	if(temp->left() >= 0)
		_stack.push(temp->left());
	return temp->info();
}
//=======================================Inoder=======================================================//
template<class DT>
class InOderEnumerator : public Enumeration<DT> {
protected:
	ArrayBST<DT>* _bst;
	stack<int> _stack;
public:
	InOderEnumerator(ArrayBST<DT>* bst);
	bool hasMoreElements();
	DT& nextElement();
	void pushToBtmLeft(int i);
};

template<class DT>
InOderEnumerator<DT>::InOderEnumerator(ArrayBST<DT>* bst) {
	_bst = bst;
	pushToBtmLeft(bst->_root);
}

template<class DT>
bool InOderEnumerator<DT>::hasMoreElements() {
	return (!_stack.empty());
}

template<class DT>
void InOderEnumerator<DT>::pushToBtmLeft(int i) {
	ArrayBTNode<DT>* temp;
	do {
		if (i == -1) return;
		_stack.push(i);
		temp = (*_bst->myBinaryTree)[i];
		if (temp->left() == -1) return;
		i = temp->left();
	} while (true);
}

template<class DT>
DT& InOderEnumerator<DT>::nextElement() {
	int i = _stack.top();
	_stack.pop();
	ArrayBTNode<DT>* temp;
	temp = (*_bst->myBinaryTree)[i];
	pushToBtmLeft(temp->right());
	return temp->info();
}

#endif // !_ARRAYBST_H
