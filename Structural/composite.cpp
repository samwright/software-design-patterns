/*
 * composite.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: eatmuchpie
 */

#include <vector>
#include <iostream> // std::cout
#include <memory> // std::auto_ptr
#include <algorithm> // std::for_each
#include <functional> // std::mem_fun
using namespace std;

/*
 * A composite class has the same functionality of the atomic classes,
 * but the functions are applied to a list of atomic class objects stored
 * in a list (or vector)
 */

class Atomic{
private:
	int constant;
public:
	void setConst(int val) { constant = val; }
	int getConst() { return constant; }
	void print() { cout << "My value is " << constant << endl; }

	Atomic(int val=0) { setConst(val); }
};


class Composite{
private:
	vector<Atomic*> components;
public:
	void add(Atomic *extra_atom){
		components.push_back(extra_atom);
	}
	void print(){
		for_each(components.begin(), components.end(), mem_fun(&Atomic::print));
	}
};


// ------------------ main ------------------

int composite_test(){
	Atomic *a1 = new Atomic(3);
	Atomic *a2 = new Atomic(6);
	Atomic *a3 = new Atomic(9);

	Composite *molecule = new Composite;

	molecule->add(a1);
	molecule->add(a2);
	molecule->add(a3);

	cout << "These are the values of the atoms in molecule:" << endl;
	molecule->print();
}
