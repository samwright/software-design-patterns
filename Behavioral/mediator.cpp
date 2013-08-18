/*
 * mediator.cpp
 *
 *  Created on: Jul 15, 2012
 *      Author: eatmuchpie
 */


#include <iostream>
using namespace std;

/*
 * A single object that handles all the interconnections
 * of a group of object.
 *
 * eg. A parent window with some child widgets that talk with
 * each other.  When an even happens to a child, it delegates
 * to the parent window which then informs the relevant children.
 *
 * This is a static mediator example.  Qt's signal system uses
 * dynamic mediators.
 */

class Child;

class Parent{
private:
	Child *a_, *b_, *c_;
public:
	Parent() : a_(0), b_(0), c_(0) {}
	void valueChanged(Child*, int);
	void addChild(Child*);
};

class Child{
private:
	int val_;
	Parent *parent_;
public:
	Child(Parent *parent) : val_(0), parent_(parent) {
		parent->addChild(this);
	}
	int value() { return val_; }
	void setValue(int val) {
		val_ = val;
		parent_->valueChanged(this, val);
	}
};

void Parent::addChild(Child *new_child){
	if (a_==0)
		a_ = new_child;
	else if (b_==0)
		b_ = new_child;
	else if (c_==0)
		c_ = new_child;
}

void Parent::valueChanged(Child *child, int val){
	if (child == a_)
		b_->setValue(val*2);
	else if (child == b_)
		c_->setValue(val*2);
}

int mediator_test(){
	Parent *p;
	p = new Parent;

	Child *a, *b, *c;
	a = new Child(p);
	b = new Child(p);
	c = new Child(p);

	a->setValue(5);

	cout << "a = " << a->value() << endl;
	cout << "b = " << b->value() << endl;
	cout << "c = " << c->value() << endl;
}
