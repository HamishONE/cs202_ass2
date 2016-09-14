#include "SimpleLane.hpp"
#include "Vehicle.hpp"

SimpleLane::SimpleLane() {

	// Initialise the front and back pointers to null
	frontQueue = 0;
	backQueue = 0;
}

SimpleLane::~SimpleLane() {

	// Will delete nodes recursively
	if (frontQueue != 0) frontQueue->deleteAll();
}

const Vehicle* SimpleLane::front() const {

	// If no vehicles in lane return null
	if (frontQueue == 0) return 0;

	// Otherwise return the front vehicle
	else return frontQueue->getVehicle();
}

const Vehicle* SimpleLane::back() const {

	// If no vehicles in lane return null
	if (backQueue == 0) return 0;

	// Otherwise return the back vehicle
	else return backQueue->getVehicle();
}

void SimpleLane::enqueue(Vehicle* vehicle) {

	// Setup new node with its link set to null
	Node *newNode = new Node(vehicle, 0);

	// If the lane is currently empty point both the front and back pointers to this node
	if (frontQueue == 0) {
		frontQueue = newNode;
		backQueue = newNode;
	}

	// Otherwise link the node at the back of the queue to this new node
	else {
		backQueue->changeLink(newNode);
		backQueue = newNode;
	}
}

Vehicle* SimpleLane::dequeue() {

	// If no vehicles in lane return null
	if (frontQueue == 0) return 0;

	// Otherwise store the vehicle at the start of the queue to return later
	Vehicle *toReturn = frontQueue->getVehicle();

	SimpleLane::Node *oldFrontNode = frontQueue;

	// Set the front of the queue to the second vehicle in the queue
	frontQueue = frontQueue->getLink();

	// Delete the Node object
	//oldFrontNode->changeLink(0);
	delete oldFrontNode;


	// If the queue is now empty set the back queue pointer to null
	if (frontQueue == 0) backQueue = 0;

	// Return the previous front of the queue stored earlier
	return toReturn;
}

bool SimpleLane::empty() const {
	if (frontQueue == 0) return true;
	else return false;
}

unsigned int SimpleLane::count() const {

	// Start at the front of the queue
	Node *node = frontQueue;

	// Loop while the current node is not null
	int counter = 0;
	while (node != 0) {

		// Get the next node via the link and increment the counter
		node = node->getLink();
		counter++;
	}

	// Once the loop breaks return the counter
	return counter;
}

/* Implementation of the Node class follows */

SimpleLane::Node::Node(Vehicle *v, Node *l) : vehicle(v), link(l) {}

void SimpleLane::Node::deleteAll() {
	if (link != 0) link->deleteAll(); // will delete nodes recursively
	delete link;
	delete vehicle;
}

Vehicle* SimpleLane::Node::getVehicle() const {
	return vehicle;
}

SimpleLane::Node* SimpleLane::Node::getLink() const {
	return link;
}

void SimpleLane::Node::changeLink(Node *newLink) {
	link = newLink;
}
