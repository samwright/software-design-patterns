/*
 * curiously_recurring_template.cpp
 *
 *  Created on: Jul 11, 2012
 *      Author: eatmuchpie
 */

/*
 * AKA mixin.
 *
 * The base class controls delegation with real functions instead of
 * virtual functions.  The base class is given the derived class as a
 * template, so can static_cast itself into it, allowing access to the
 * derived class' members.
 *
 *
 * The normal system of a virtual base class being subclassed and its
 * virtual members overriden with real members allows a base class pointer
 * to point to any base-subclassed object and access its members at runtime.
 * This requires a framework to work out which members to access and call them,
 * which has a memory overhead.
 *
 * The mixin pattern removes this overhead by specifying at compile-time
 * which member from which class is to be run, but in doing so removes
 * the "dynamic polymorphism".
 */

#include <iostream>
using namespace std;

template <class Derived>
class Base {
public:
	void print(){
		cout << "Printing in base class..." << endl;

		// This is how the derived class' members are accessed.
		static_cast<Derived*>(this)->realPrint();
	}
};

// This is the curiously-recurring template bit:
class DerivedClass : public Base<DerivedClass>{
public:
	void realPrint(){
		cout << "Printing for real..." << endl;
	}
};

int mixin_test1(){
	DerivedClass obj;
	obj.print();
}


/*
 * This can be useful when you want a number of classes to derive
 * static functionality from a base class, but not share the
 * functionality between these subclasses.
 *
 * eg. object counters in classes
 */

template <class T>
class Counter{
public:
	static int objs_created, objs_alive;

	Counter(){
		objs_created++;
		objs_alive++;
	}

protected:
	// This is protected so a counter object can't be deleted,
	// but a counter-derived object can be.
	~Counter(){
		objs_alive--;
	}
};
template <class T> int Counter<T>::objs_alive = 0;
template <class T> int Counter<T>::objs_created = 0;


class A : public Counter<A>{};
class B : public Counter<B>{};

int mixin_test2(){
	A objA1, objA2, objA3;
	B objB1, objB2;

	cout << "There are " << A::objs_alive << " 'A' objects," << endl;
	cout << "      and " << B::objs_alive << " 'B' objects." << endl;
}
