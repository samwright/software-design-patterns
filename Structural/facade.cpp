/*
 * facade.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * This summarises a number of low-level classes into one high-level interface
 */


// -------------- Low-level components -----------------
class Wheels{
public:
	void spin(){
		cout << "Wheels spinning,,," << endl;
	}
};

class Drivetrain{
private:
	Wheels *wheels_;
public:
	Drivetrain() : wheels_(NULL) {}
	void setWheels(Wheels *wheels) { wheels_ = wheels; }
	void drive(){
		cout << "Drivetrain driving..." << endl;
		if (wheels_ != NULL)
			wheels_->spin();
	}
};

class Frame{};


// ---------------- Facade class ------------------
class Bike{
private:
	Wheels *wheels_;
	Frame *frame_;
	Drivetrain *drivetrain_;
public:
	Bike(){
		wheels_ = new Wheels;

		drivetrain_ = new Drivetrain;
		drivetrain_->setWheels(wheels_);

		frame_ = new Frame;
	}

	void cycle(){
		cout << "Start cycling..." << endl;
		drivetrain_->drive();
	}
};


// ----------------- main -------------------
int facade_test(){
	(new Bike)->cycle();
}
