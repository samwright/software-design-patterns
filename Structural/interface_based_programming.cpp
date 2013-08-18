/*
 * interface_based_programming.cpp
 *
 *  Created on: Jul 11, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * Classes contain interfaces for other classes to use.  Increased
 * modularity makes for happy developers.
 */

/*
 *  For better readability, we can define something like this:
 */

#ifndef DeclareInterface

#define implements public virtual

#define DeclareInterface(name) class name {\
	public:\
		virtual ~name() {}

#define DeclareDerivedInterface(name, base) class name : implements base {\
	public:\
		virtual ~name() {}

#define EndInterface };


#endif

// (I)nterface for (Car) class = ICar
DeclareInterface(ICar)
	virtual const char* getMake() = 0;
	virtual void print() = 0;
EndInterface


// The implementation class of this is then
class CCar : implements ICar{
protected:
	// Define functionality for subclasses to use
	const char* commonHiddenCarFunctionality(){ return "car"; }
public:
	// Impliment ICar.  Print can be implemented, but it only
	// makes sense for a subclass to implement getMake, so
	// keep getMake virtual pure.
	void print(){ cout << "I am a " << commonHiddenCarFunctionality(); }
	virtual const char* getMake() = 0;
};

// Finally we can fully implement ICar.  print() is already implemented,
// so just need to do getMake().
class CBMW : public CCar{
public:
	const char* getMake(){ return "BMW"; }
};

class CFord : public CCar{
public:
	const char* getMake(){ return "Ford"; }
};


int simple_interface_test(){
	CBMW bmw;
	bmw.print();
	cout << " and a " << bmw.getMake();
}



/*
 * What if a Ferrari should have some different functionality
 * to a Hyundi?
 *
 * We would need to subclass ICar into IFerrari and IHyundi...
 */

DeclareDerivedInterface(IFerrari, ICar)
	virtual void vroom() = 0;
EndInterface

DeclareDerivedInterface(IHyundi, ICar)
	virtual void setPowerSaver(bool) = 0;
EndInterface

/*
 * Now to implement IFerrari, we want to inherit CCar's functionality
 * AND IFerrari.
 */
class CFerrari : public CCar, implements IFerrari{
protected:
	const char* getCarSound() { return "vroom"; }

public:
	const char* getMake() { return "Ferrari"; }
	void vroom(){ cout << "I go " << getCarSound(); }
};
/*
 * There's a potential pitfall here because I inherit CCar -> ICar,
 * and IFerrari -> ICar.  Had ICar been subclassed the normal way,
 * the IFerrari -> ICar class would have complained about ICar::print
 * not being implemented, regardless of the face that CCar does.
 *
 * To get around this, 'implements' is actually 'public virtual'.  This
 * virtual inheritance means a few things.
 * 		Firstly (and important here) because IFerrari virtually inherits
	 * 		from ICar, the fact that IFerrari::print is virtual is
	 * 		swept under the carpet until the rest of CFerrari is imported,
	 * 		at which point CFerrari::print is already set to CCar::print.
 *		Secondly (unimportant here) we could do sister-delegation,
	 *		whereby CCar could implement some IFerrari-functionality without
	 *		the same functionality being explicitly in CFerrari.  This is a
	 *		little odd, since CCar shouldn't really know anything about
	 *		what specifically a Ferrari can do...
 *
 * So that we can further subclass IFerrari and CFerrari, we need to
 * follow the convention that any interface-class inheritance is done
 * with 'implements' (ie. virtual inheritance).
 */

// Annoyingly, while everything compiles and runs as expect, we still
// get an error in eclipse saying CFerrari::print is virtual!

class IWidget{
public:
	virtual void foo() = 0;
	virtual ~IWidget() {}
};

class IButton : virtual public IWidget{
public:
	virtual void bar() = 0;
	virtual ~IButton() {}
};

class CWidget : virtual public IWidget{
public:
	void foo(){ cout << "foo"; }
};

class CButton : public CWidget, public IButton{
public:
	void bar() { cout << "bar"; }
};

class CButton_inheritable : public CWidget, public virtual IButton{
public:
	void bar() { cout << "bar"; }
};

class IBigButton : public virtual IButton{
	virtual void bam() = 0;
};

class CBigButton : public CButton_inheritable, public virtual IBigButton{
	void bam() {}
};


int diamond_test(){
	CButton button;
	button.foo();
	button.bar();
}

int ferrari_test(){
	CFerrari ferrari;
	ferrari.print();
	cout << " and a " << ferrari.getMake();
	cout << ", and "; ferrari.vroom();
	cout << endl;
}
