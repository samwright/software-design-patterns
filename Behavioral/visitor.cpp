/*
 * visitor.cpp
 *
 *  Created on: Jul 16, 2012
 *      Author: eatmuchpie
 */

/*
 * TODO!
 */
#include <iostream>
using namespace std;


class Base{
public:
	virtual void print_virt(){ cout << " Base_virt " << endl; }
	void print_real(){ cout << " Base_real " << endl; }
	virtual ~Base() {}
};

class Derived_overwrite : public Base{
public:
	void print_virt(){ cout << " Derived_virt " << endl; }
	void print_real(){ cout << " Derived_real " << endl; }
};

class Derived_not_overwritten : public Base{
	void print_virt(int i) { cout << i << endl; }
	void print_real1(int i) { cout << i << endl; }
};

int main(){
	Base b;
	b.print_virt();
	b.print_real();

	cout << endl;
	Derived_overwrite d;
	d.print_virt();
	d.print_real();

	cout << endl;
	Derived_not_overwritten d_not;
	//d_not.print_virt();
	d_not.print_real();

}
