class Vehicle;

// Helper class to encapsulate a vehicle and a link to another node
class Node {
public:
	Node(Vehicle *v, Node *l);
	~Node() {};
	Vehicle* getVehicle() const;
	Node* getLink() const;
	void changeLink(Node *newLink);
	void deleteAll();
private:
	Vehicle *vehicle;
	Node *link;
};
