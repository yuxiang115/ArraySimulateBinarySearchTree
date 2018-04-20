#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include<iostream>
#include<cstdlib>

using namespace std;

template<class DT>
struct node {
	DT* _info;
	struct node<DT> *_next;
};

template<class DT>
class Queue {
private:
	node<DT> *_rear;
	node<DT> *_front;

public:
	Queue();
	void enQueue(DT& data);

};

template<class DT>
Queue<DT>::Queue() {
	_rear = NULL;
	_front = NULL;
}

template<class DT>
void Queue<DT>::enQueue(DT& data) {
	node<DT>* temp = new node<DT>();
	temp->_info = data;
	if (_front = NULL) {
		_front = temp;
	}
	else {
		_rear->_next = temp;
		_rear = temp;
	}
}
#endif // !_QUEUE_H
