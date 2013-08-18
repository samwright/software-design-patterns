/*
 * state.cpp
 *
 *  Created on: Jul 15, 2012
 *      Author: eatmuchpie
 */


#include <iostream>
using namespace std;

/*
 * Functionality of an object depends on its state.
 *
 * The object contains a 'State' pointer, where 'State' contains
 * default (virtual) functionality.  The object delegates to the
 * State object.
 *
 * All that the state can do is replace the object's state with
 * another.  Eg. the On state has a 'turnOff' method which sets
 * 'object.state = new Off; delete this;'
 */

/*
 * Machine with states 'On' and 'Off', which determine the object's
 * turnOff and turnOn functionality.
 */

// Default functionality of each stateto be overriden.

class Object;

class State{
public:
	virtual void turnOff(Object *obj){ cout << "Already Off" << endl; }
	virtual void turnOn(Object *obj){ cout << "Already On" << endl; }

	virtual ~State() {}
};

class On : public State{
public:
	void turnOff(Object *obj);
};

class Off : public State{
public:
	void turnOn(Object *obj);
};

class Object{
private:
	State *state_;
public:
	Object() : state_(new Off) {} // Default state is Off.
	void setState(State *state) { state_ = state; }

	// turnOff and turnOn are delegated to state
	void turnOff() { state_->turnOff(this); }
	void turnOn() { state_->turnOn(this); }
};

void On::turnOff(Object *obj) {
	cout << "Turning Off..." << endl;
	obj->setState(new Off);
	delete this;
}

void Off::turnOn(Object *obj) {
	cout << "Turning On..." << endl;
	obj->setState(new On);
	delete this;
}

int state_test(){
	Object obj;
	cout << "----- Switching off ------" << endl;
	obj.turnOff();
	cout << "----- Switching on ------" << endl;
	obj.turnOn();
	cout << "----- Switching on ------" << endl;
	obj.turnOn();
	cout << "----- Switching off ------" << endl;
	obj.turnOff();
}
