#include "ExpressLane.hpp"

void ExpressLane::enqueue(Vehicle* vehicle) {

	Node *newNode = new Node(vehicle, 0);

	if (frontQueue == 0) {
		frontQueue = newNode;
		backQueue = newNode;
		return;
	}

	if (vehicle->type() == Vehicle::VT_MOTORCYCLE) {

		if (frontQueue->vehicle->type() != Vehicle::VT_MOTORCYCLE) {
			newNode->link = frontQueue;
			frontQueue = newNode;
			return;
		}

		Node *node = frontQueue;

		while(true) {
			if (node->vehicle->type() != Vehicle::VT_MOTORCYCLE) break;
			else node = node->link;
		}

		Node *toLink = node->link;
		node->link = newNode;
		newNode->link = toLink;
	}

	else {
		backQueue->link = newNode;
		backQueue = newNode;
	}
}
