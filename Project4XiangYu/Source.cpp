#include<iostream>
#include "ArrayBST.h"
using namespace std;
void main() {

	char command;
	int data;
	int max_size = 400;
	cin >> data;
	ArrayBST<int>* bst = new ArrayBST<int>(new ArrayBTNode<int>(data), max_size);
	while (!cin.eof()) {
		cin >> command;
		if (command != 'O')
			cin >> data;

		if (command == 'O') {
			
			cout << endl << endl << "Height of the Binary Search Tree: " << bst->height() << "   ";
			cout << "Size of the Binary Search Tree: " << bst->size() << endl;
			cout << "Output Binary Search Tree InOrder: " << endl;
			bst->setOutputStyle(0);
			cout << *bst;
			cout << endl <<"Output Binary Search Tree PreOrder: " << endl;
			bst->setOutputStyle(1);
			cout << *bst;
			cout << endl << endl << "Print the vector" << endl;
			ArrayBTNode<int>* temp;
			for (int i = 0; i < bst->_size; i++) {
				temp = (*bst->myBinaryTree)[i];
				if (temp->_info == NULL)
					cout << i << "     " << "NULL" << "     " << temp->left() << "     " << temp->right() << "     " << endl;
				else
					cout << i << "     " << *temp << "     " << temp->left() << "     " << temp->right() << "     " << endl;
			}
			
		}
		else if (command == 'I') {
			bst->insert(data);
		}
		else if(command == 'F'){
			ArrayBTNode<int>* temp = bst->find(data);
			if (temp != NULL) {
				if (temp->found) {
					cout << "Number: " << temp << "found in the index of vector: " << bst->_index << endl;
				}
			}
		}
		else if (command == 'R') {
			//bst->remove(data);
		}
	}

}