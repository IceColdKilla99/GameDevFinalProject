#include "DoublyLinkedList.h"

dLinkedList::dLinkedList() { //this is dLinkedList constructor which initialises the variables
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

void dLinkedList::deleteNode(node* deleteNode)
{
	/* base case */
	if (head == NULL || deleteNode == NULL)
		return;

	/* If node to be deleted is head node */
	if (head == deleteNode)
		head = deleteNode->next;

	/* Change next only if node to be
	deleted is NOT the last node */
	if (deleteNode->next != NULL)
		deleteNode->next->prev = deleteNode->prev;

	/* Change prev only if node to be
	deleted is NOT the first node */
	if (deleteNode->prev != NULL)
		deleteNode->prev->next = deleteNode->next;

	/* Finally, free the memory occupied by del*/
	delete deleteNode->data;
	delete deleteNode;
	return;
}

void dLinkedList::headInsert(GameObject* data) //insert at head constructor
{
	node* n = new node(data); //creating a new node which we have to insert

	if (head == nullptr) { //checks if the liost is empty
		head = n; //if empty, head becomes n
		tail = head; //since there is just one node, tail and head will be the same
	}
	else {
		head->prev = n; //otherwise, when list is not empty, head's previous will be n making n the had
		n->next = head; //and n's next will be head
		head = n; //n finally becomes head
	}

	size++; //increments the list's size
}

void dLinkedList::deleteTail() //function to delete at tail
{
	if (head == tail) { //checks if list contains just one node
		delete tail; //deletes that node
		head = nullptr; //list is now empty
		tail = nullptr;
	}
	else {
		node* temp2 = tail->prev; //otherwise tail's prev becomes temp
		delete tail; //delete tail
		tail = temp2; //reassign tail
		temp2 = nullptr; //discard temp
	}
	size--; //decrement list size
}

int dLinkedList::getSize() { //gets size of the linked list
	return size;
}

GameObject* dLinkedList::getGameObject(int index) //reads the cloud
{
	node* temp = head;
	int count = 0;

	while (temp != nullptr) {
		if (count == index) {
			return temp->data; //returns the address of the data
		}
		else {
			count++;
			temp = temp->next; //traverse the list further
		}
	}
}

dLinkedList::~dLinkedList() {

	while (size > 0)
		deleteTail();
}

