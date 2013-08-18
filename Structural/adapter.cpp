/*
 * adapter.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * Converts the interface of one class to look like the interface
 * of another.
 */

// First, the interface that we want (with pure abstract members)
class DesiredInterface{
public:
	virtual void foo(int arg) = 0;
	virtual int bar() = 0;
};

// This is the class that needs wrapping
class LegacyClass{
private:
	int constant;
public:
	LegacyClass(){
		constant = 0;
	}

	void FOO(int arg){
		constant = arg;
	}

	int BAR(){
		return constant;
	}
};

// And this is the adapter that inherits from both the above classes
class Adapter : public DesiredInterface, private LegacyClass{
public:
	virtual void foo(int arg){
		FOO(arg);
	}

	virtual int bar(){
		return BAR();
	}
};


//---------------------- main ------------------
int adapter_test(){
	/*
	 * We don't want any of LegacyClass' members in
	 * our final object, so create a new adapter
	 * object but point to it with a DesiredInterface
	 * pointer, so only the members defined in the
	 * DesiredInterface are accessible.
	 */
	DesiredInterface *a = new Adapter;
	a->foo(5);
	cout << "adapter->bar() gives " << a->bar() << endl;
}
