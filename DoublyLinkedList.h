#pragma once
#pragma once
#include <iostream>
#include <stdlib.h> 
#include "GameObject.h"


using namespace std;

class node {

public:
	GameObject* data; //data of type GameObject because that is what we have to store in node as it is the parent of Cloud and Rabbit
	node* next; //pointer that point to the next node
	node* prev; //pointer that points to the previous node

	node(GameObject* value) {
		data = value;
		next = nullptr;  //both of these pointers will be null in the beginning because the there is no node and linked list is empty
		prev = nullptr;
	}
};

class dLinkedList {
public:

	node* head;
	node* tail;
	int size;

	dLinkedList();

	void deleteNode(node* deleteNode);

	void headInsert(GameObject* data);
	void deleteTail();
	int getSize();
	GameObject* getGameObject(int index); //previously Cloud but now GameObject
	~dLinkedList();

};
