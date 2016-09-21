#include "Node.hpp"
#include "Vehicle.hpp"

Node::Node(Vehicle *v, Node *l) : vehicle(v), link(l) {}

void Node::deleteAll() {

	// Call on all other nodes recursively
	if (link != 0) {
		link->deleteAll();
	}

	// Delete this nodes link and associated vehicle
	delete link;
	delete vehicle;
}

Vehicle* Node::getVehicle() const {
	return vehicle;
}

Node* Node::getLink() const {
	return link;
}

void Node::changeLink(Node *newLink) {
	link = newLink;
}
