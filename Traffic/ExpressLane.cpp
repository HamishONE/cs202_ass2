#include "ExpressLane.hpp"

void ExpressLane::enqueue(Vehicle* vehicle) {

	// Setup new node with its link set to null
	Node *newNode = new Node(vehicle, 0);

	// If the lane is currently empty point both the front and back pointers to this node
	if (frontQueue == 0) {
		frontQueue = newNode;
		backQueue = newNode;
		return;
	}

	// Check if the vehicle is a motorcycle
	if (vehicle->type() == Vehicle::VT_MOTORCYCLE) {

		// If there are no motorcycles already in the queue add the new node to the front of the queue
		if (frontQueue->getVehicle()->type() != Vehicle::VT_MOTORCYCLE) {
			newNode->changeLink(frontQueue);
			frontQueue = newNode;
			return;
		}

		// Otherwise loop until the new vehicle is not a motorcycle
		Node *node = frontQueue;
		while (node->getVehicle()->type() == Vehicle::VT_MOTORCYCLE) {
			node = node->getLink();
		}

		// Add the new node just after the last motorcycle
		Node *toLink = node->getLink();
		node->changeLink(newNode);
		newNode->changeLink(toLink);
	}

	// Otherwise link the node at the back of the queue to this new node
	else {
		backQueue->changeLink(newNode);
		backQueue = newNode;
	}
}
