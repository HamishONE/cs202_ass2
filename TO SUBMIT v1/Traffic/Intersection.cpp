#include "Intersection.hpp"
#include "Vehicle.hpp"
#include "Lane.hpp"

Intersection::Intersection() {

	// Loop through the four lanes and set the pointers to null
	for (unsigned int i=0; i<4; i++) {
		lanes[i] = 0;
	}
}


bool Intersection::valid() {

	// Loop through the four lanes and if any are null the intersection is not valid
	for (unsigned int i=0; i<4; i++) {
		if (lanes[i] == 0) {
			return false;
		}
	}

	// Otherwise the intersection is valid
	return true;
}

// Helper function to connect a lane to the intersection
Lane* Intersection::connector(Lane* lane, LaneDirection direction, CompassPoint compass) {

	// Store the previous lane in this location to return later
	Lane *toReturn = lanes[compass];

	// Copy the lane pointer and direction into the appropriate arrays
	lanes[compass] = lane;
	directions[compass] = direction;

	// Return the previous lane stored above, may be null
	return toReturn;
}

Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, NORTH);
}

Lane* Intersection::connectEast(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, EAST);
}

Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, SOUTH);
}

Lane* Intersection::connectWest(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, WEST);
}

void Intersection::simulate() {

	// Loop through the four lanes and find if any vehicles are turning left or going straight
	bool areLeft = false;
	bool areStraight = false;
	for (unsigned int i=0; i<4; i++) {

		// If the lane contains no vehicles or is an outgoing street skip to the next lane
		if(lanes[i]->front() == 0 || directions[i] == LD_OUTGOING) {
			continue;
		}

		// Set booleans as appropriate
		if (lanes[i]->front()->nextTurn() == Vehicle::TD_LEFT) {
			areLeft = true;
		}
		if (lanes[i]->front()->nextTurn() == Vehicle::TD_STRAIGHT) {
			areStraight = true;
		}
	}

	// Loop through the four lanes and process the vehicles
	for (unsigned int i=0; i<4; i++) {

		// If the lane contains no vehicles or is an outgoing street skip to the next lane
		if(lanes[i]->front() == 0 || directions[i] == LD_OUTGOING) {
			continue;
		}

		// If the vehicle wants to turn right and there are people going straight or turning
		// left skip to the next lane
		if (lanes[i]->front()->nextTurn() == Vehicle::TD_RIGHT) {
			if (areLeft || areStraight) {
				continue;
			}
		}

		// If the vehicle wants to turn left and there are people going straight skip to the next lane
		if (lanes[i]->front()->nextTurn() == Vehicle::TD_LEFT) {
			if (areStraight) {
				continue;
			}
		}

		// Otherwise remove the vehicle from the lane
		Vehicle *vehicle = lanes[i]->dequeue();

		// Find the lane the vehicle wants to turn into
		unsigned int newLane;
		switch (vehicle->nextTurn()) {
			case Vehicle::TD_RIGHT:
				newLane = i + 3;
				break;
			case Vehicle::TD_LEFT:
				newLane = i + 1;
				break;
			case Vehicle::TD_STRAIGHT:
				newLane = i + 2;
				break;
			default:
				return;
		}
		if (newLane > 3) {
			newLane = newLane - 4;
		}

		// Add the vehicle to this lane
		lanes[newLane]->enqueue(vehicle);
		vehicle->makeTurn();
	}
}
