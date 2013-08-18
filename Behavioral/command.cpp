/*
 * command.cpp
 *
 *  Created on: Jul 13, 2012
 *      Author: eatmuchpie
 */


#include <iostream>
using namespace std;

/*
 * A command object is instantiated by (and stored within) a commander object.
 * The command object is then pointed to the object to be commanded.
 */

// Light is the object to be commanded (ie. turned off or on).
class Light{
public:
	void turnOn() { cout << "Light turned on" << endl; }
	void turnOff() { cout << "Light turned off" << endl; }
};

// The command objects, TurnOn and TurnOff.
class Command{
public:
	virtual void execute() = 0;
	virtual ~Command() {}
};

class TurnOn : public Command{
private:
	Light *light_;
	TurnOn();

public:
	TurnOn(Light *light) : light_(light) {}
	void execute() { light_->turnOn(); }
};

class TurnOff : public Command{
private:
	Light *light_;
	TurnOff();

public:
	TurnOff(Light *light) : light_(light) {}
	void execute() { light_->turnOff(); }
};


// The commander object (the switch)
class Switch{
private:
	Command *turn_on, *turn_off;
	Switch();

public:
	Switch(Light *light){
		turn_on = new TurnOn(light);
		turn_off = new TurnOff(light);
	}

	void turnOn() { turn_on->execute(); }
	void turnOff() { turn_off->execute(); }
};


int command_test(){
	Light *light = new Light;
	Switch *swtch = new Switch(light);

	swtch->turnOn();
	swtch->turnOff();
}
