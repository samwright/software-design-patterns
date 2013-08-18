/*
 * builder.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: eatmuchpie
 */


#include <string>
#include <iostream>

using namespace std;

/*
 * Builder
 *
 * I want to instantiate a class with lots of private member variables,
 * but without a really long constructor.
 */


class Bike{
	// This is the class I want to instantiate
private:
	int front_suspension;
	int rear_suspension;
	int wheels;

public:
	void setFrontSus(int val)
		{ front_suspension = val;}
	void setRearSus(int val)
		{ rear_suspension = val;}
	void setWheels(int val)
		{ wheels = val;}

	void describe(){
		cout << "Bike has " << front_suspension << "mm up front, ";
		cout << rear_suspension << "mm round the back, ";
		cout << "and a wheel size of " << wheels << endl;
	}
};


/*
 * --------------------- Builders ------------------------
 * These define functions to set the bike parameters
 */

class BikeBuilder{
	// This is the base (parent) class of all builders
protected:
	Bike *bike_pntr;

public:
	void createNewBike(){
		bike_pntr = new Bike;

		buildFrontSus();
		buildRearSus();
		buildWheels();
	}

	virtual void buildFrontSus() = 0;
	virtual void buildRearSus() = 0;
	virtual void buildWheels() = 0;

	Bike* getBike()
		{ return bike_pntr; }
};


class C_DownhillBikeBuilder : public BikeBuilder{
public:
	void buildFrontSus()
		{ bike_pntr->setFrontSus( 180 ); }
	void buildRearSus()
		{ bike_pntr->setRearSus( 6*2.54 ); }
	void buildWheels()
		{ bike_pntr->setWheels( 26 ); }
};

class C_RoadBikeBuilder : public BikeBuilder{
public:
	void buildFrontSus()
		{ bike_pntr->setFrontSus( 0 ); }
	void buildRearSus()
		{ bike_pntr->setRearSus( 0 ); }
	void buildWheels()
		{ bike_pntr->setWheels( 700 ); }
};

/*
 * -------------------- Bike mechanic ---------------
 * The bike mechanic operates the bike builders
 */
class BikeMechanic{
private:
	BikeBuilder *builder;
public:
	void setBikeBuilder(BikeBuilder* new_builder)
		{ builder = new_builder; }

	Bike* buildBike(){
		builder->createNewBike();
		return builder->getBike();
	}
};


// ------------------ Main ---------------------
int builder_test(){
	BikeMechanic *mechanic = new BikeMechanic;
	BikeBuilder *downhillBikeBuilder = new C_DownhillBikeBuilder;
	BikeBuilder *roadBikeBuilder = new C_RoadBikeBuilder;

	mechanic->setBikeBuilder(downhillBikeBuilder);
	Bike *dhBike = mechanic->buildBike();

	mechanic->setBikeBuilder(roadBikeBuilder);
	Bike *roadBike = mechanic->buildBike();

	dhBike->describe();
	roadBike->describe();

	delete dhBike;
	delete roadBike;
	delete mechanic;
	delete downhillBikeBuilder;
	delete roadBikeBuilder;

	return 0;
}
