/*
 * decorator.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * Decorator adds functionality to an object.
 *
 * Specifically, it shallow-copies an existing object to a nephew-class with
 * extra functionality, but all the original functionality.
 */

// ---------------- Thing to be decorated --------------------
class AbstractThing{
public:
	virtual void print() = 0;
	virtual void setNumber(int) = 0;
	virtual int getNumber() const = 0;
	virtual ~AbstractThing() {}
};

class ConcreteThing : public AbstractThing{
private:
	int number;

public:
	void print(){
		cout << "thing is " << number << endl;
	}

	int getNumber() const {
		return number;
	}

	void setNumber(int number) {
		this->number = number;
	}

};

// -------------------- Decorators ------------------------

// This is the base decorator class that wraps 'thing_' (without modification)
class Decorator : public AbstractThing{
protected:
	AbstractThing *thing_;
	Decorator();
public:
	Decorator(AbstractThing *thing) : thing_(thing) {}
	void print() { thing_->print(); }
	void setNumber(int number) { thing_->setNumber(number); }
	int getNumber() const { return thing_->getNumber(); }
};

// This inherits from Decorator, but modifies the 'setNumber' method.
class AddFive : public Decorator{
public:
	AddFive(AbstractThing *thing) : Decorator(thing){
		thing->setNumber( thing->getNumber() + 5 );
	}
	void setNumber(int number) { thing_->setNumber(number+5); }
};

// This modifies the 'print' method.
class AddGreeting : public Decorator{
public:
	AddGreeting(AbstractThing *thing) : Decorator(thing) {}
	void print(){
		cout << "Greetings! This ";
		thing_->print();
	}
};



int decorator_test(){
	AbstractThing *thing = new ConcreteThing;

	thing->setNumber(10);
	cout << "Without decoration:" << endl;
	thing->print();

	AbstractThing *thing_AddFive = new AddFive(thing);
	cout << endl << "With 'AddFive'" << endl;
	thing_AddFive->print();

	AbstractThing *thing_AddGreeting = new AddGreeting(new ConcreteThing);
	thing_AddGreeting->setNumber(10);
	cout << endl << "With 'AddGreeting'" << endl;
	thing_AddGreeting->print();

	AbstractThing *thing_AddFiveAndGreeting = new AddFive(thing_AddGreeting);
	cout << endl << "With 'AddFive' and 'AddGreeting" << endl;
	thing_AddFiveAndGreeting->print();

}
