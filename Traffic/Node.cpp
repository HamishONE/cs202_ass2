#include "Node.hpp"
#include "Vehicle.hpp"

Node::Node(Vehicle *v, Node *l) : vehicle(v), link(l) {}

void Node::deleteAll() {
	if (link != 0) link->deleteAll(); // will delete nodes recursively
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
