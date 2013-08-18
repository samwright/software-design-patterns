/*
 * proxy.cpp
 *
 *  Created on: Jul 11, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * The proxy class sits above the real class with the same interface,
 * but delegates all work to the real class.
 *
 * Can be used to control/add/prototype functionality.
 */

class Abstract{
public:
	virtual void print() = 0;
	virtual ~Abstract() {}
};

class Real : public Abstract{
public:
	void print() { cout << "hi!"; }
};

class Proxy : public Abstract{
private:
	Abstract *real;
public:
	Proxy() { real = new Real; }
	void print() { real->print(); }
};


int proxy_test(){
	Abstract *obj = new Proxy;
	obj->print();
}
