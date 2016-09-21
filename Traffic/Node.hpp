class Vehicle;

// Helper class to encapsulate a vehicle and a link to another Node
class Node {
public:

	// Constructor to initialise vehicles and linked Node
	Node(Vehicle *v, Node *l);

	// Retrieve the vehicle this object links to
	Vehicle* getVehicle() const;

	// Retrieve what Node this object is liked to
	Node* getLink() const;

	// Change the Node this object is linked to to the input argument
	void changeLink(Node *newLink);

	// Deletes all linked Nodes and their vehicles
	void deleteAll();

private:

	// Store pointers to a Vehicle and linked Node
	Vehicle *vehicle;
	Node *link;
};
