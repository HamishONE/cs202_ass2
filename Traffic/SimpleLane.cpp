#include "SimpleLane.hpp"

SimpleLane::SimpleLane() {

	frontQueue = 0;
	backQueue = 0;
}

SimpleLane::~SimpleLane() {

	Node *node, *nextNode = frontQueue;

	while(true) {

		node = nextNode;
		if (node == 0) break;

		nextNode = node->link;
		delete node->vehicle;
		delete node;
	}
}

const Vehicle* SimpleLane::front() const {

	if (frontQueue == 0) return 0;
	else return frontQueue->vehicle;
}

void SimpleLane::enqueue(Vehicle* vehicle) {

	Node *newNode = new Node(vehicle, 0);

	if (frontQueue == 0) {
		frontQueue = newNode;
		backQueue = newNode;
	}
	else {
		backQueue->link = newNode;
		backQueue = newNode;
	}
}

Vehicle* SimpleLane::dequeue() {
	if (frontQueue == 0) return 0;

	Vehicle *toReturn = frontQueue->vehicle;
	frontQueue = frontQueue->link;
	return toReturn;
}

bool SimpleLane::empty() const {
	if (frontQueue == 0) return true;
	else return false;
}

unsigned int SimpleLane::count() const {

	int counter = 0;
	Node *node = frontQueue;

	while(true) {

		if (node == 0) break;

		node = node->link;
		counter++;
	}

	return counter;
}

const Vehicle* SimpleLane::back() const {

	if (backQueue == 0) return 0;
	else return backQueue->vehicle;
}
