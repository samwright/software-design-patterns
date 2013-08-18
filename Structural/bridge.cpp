/*
 * bridge.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * Decouples interface and implementation, so both can vary independently.
 */


// ------------- Implementations -----------------

class AbstractImplementor{
public:
	virtual void setConst(float) = 0;
	virtual float getConst()	= 0;

	virtual ~AbstractImplementor() {}
};

// Implements setting/getting a constant.
class Implementor1 : public AbstractImplementor{
protected:
	float const1;
public:
	void setConst(float val) { const1 = val; }
	float getConst() { return const1; }
};

// Implements setting a constant with 10% added, then getting.
class Implementor2 : public AbstractImplementor{
protected:
	float const2;
public:
	void setConst(float val) { const2 = val*1.1; }
	float getConst() { return const2; }
};



// --------------- Interface -----------------

class AbstractInterface{
public:
	virtual void setValue(float, float) = 0;
	virtual float getValue() = 0;

	virtual ~AbstractInterface() {}
};

class ConcreteInterface : public AbstractInterface{
private:
	float offset;
	AbstractImplementor *implementor;
public:
	void setValue(float new_const, float new_offset){
		implementor->setConst(new_const);
		offset = new_offset;
	}
	float getValue(){
		return implementor->getConst() + offset;
	}
	ConcreteInterface(AbstractImplementor *new_implementor){
		implementor = new_implementor;
		implementor->setConst(0);
		offset = 0;
	}
};


// ------------------- main --------------

int bridge_test(){
	ConcreteInterface obj1( new Implementor1 );
	ConcreteInterface obj2( new Implementor2 );
	obj1.setValue(5, 1);
	obj2.setValue(5, 1);

	cout << "Without 10% extra: " << obj1.getValue() << endl;
	cout << "With 10% extra: " << obj2.getValue() << endl;
}
