#include "Intersection.hpp"
#include "Vehicle.hpp"
#include "Lane.hpp"

Intersection::Intersection() {
	northLane = 0;
	eastLane = 0;
	southLane = 0;
	westLane = 0;
}


bool Intersection::valid() {
	if (northLane && eastLane && southLane && westLane) return true;
	else return false;
}

Lane* Intersection::connector(Lane* lane, LaneDirection direction, LaneWrapper*& wrapper) {
	Lane *toReturn = 0;
	if (wrapper != 0) toReturn = wrapper->lane;

	wrapper = new LaneWrapper(lane, direction);

	return toReturn;
}

Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, northLane);
}

Lane* Intersection::connectEast(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, eastLane);
}

Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, southLane);
}

Lane* Intersection::connectWest(Lane* lane, LaneDirection direction) {
	return connector(lane, direction, westLane);
}

void Intersection::findTurns(LaneWrapper*& wrapper) {
	if(wrapper->lane->front() == 0 || wrapper->direction == LD_OUTGOING) return;

	if (wrapper->lane->front()->nextTurn() == Vehicle::TD_LEFT) areLeft = true;
	if (wrapper->lane->front()->nextTurn() == Vehicle::TD_STRAIGHT) areStraight = true;
}

void Intersection::moveVehicle(LaneWrapper*& wrapper) {
	if(wrapper->lane->front() == 0 || wrapper->direction == LD_OUTGOING) return;

	if (wrapper->lane->front()->nextTurn() == Vehicle::TD_RIGHT) {
		if (areLeft || areStraight) return;
	}

	if (wrapper->lane->front()->nextTurn() == Vehicle::TD_LEFT) {
		if (areStraight) return;
	}

	Vehicle *vehicle = wrapper->lane->dequeue();

	//move to appropiate lane

	vehicle->makeTurn();
}

void Intersection::simulate() {

	areLeft = false;
	areStraight = false;
	findTurns(northLane);
	findTurns(eastLane);
	findTurns(southLane);
	findTurns(westLane);

	moveVehicle(northLane);
	moveVehicle(eastLane);
	moveVehicle(southLane);
	moveVehicle(westLane);
}
