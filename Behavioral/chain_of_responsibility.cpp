/*
 * chain_of_responsibility.cpp
 *
 *  Created on: Jul 11, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;


/*
 * Chain of objects - if the first can't `handle` it, the `next` will try.
 */

class ChainElement{
private:
	ChainElement *next;

public:
	ChainElement() { setNext(0); }

	ChainElement(ChainElement *previous) {
		setNext(0);
		previous->setNext(this);
	}

	void setNext(ChainElement *new_next) { next = new_next; }

	virtual void handle(int number) {
		cout << "can't handle it ... ";
		if (next != 0){
			cout << "passing to next." << endl;
			next->handle(number);
		} else
			cout << "no more in chain to handle it. Sorry!" << endl;

	}
};


class Handler1 : public ChainElement{
public:
	Handler1() {}
	Handler1(ChainElement *previous) : ChainElement(previous) {}

	void handle(int number) {
		if (number<5)
			cout << "Handled by Handler1" << endl;
		else {
			cout << "Not handled by Handler1..." << endl;
			ChainElement::handle(number);
		}
	}
};


class Handler2 : public ChainElement{
public:
	Handler2() {}
	Handler2(ChainElement *previous) : ChainElement(previous) {}

	void handle(int number) {
		if (number<10)
			cout << "Handled by Handler2" << endl;
		else {
			ChainElement::handle(number);
			cout << "Not handled by Handler2..." << endl;
		}
	}
};

int chain_of_responsibility_test(){
	ChainElement *h1 = new Handler1;
	ChainElement *h2 = new Handler2(h1);
	ChainElement *h3 = new Handler2(h2);

	cout << "Throwing 3..." << endl;
	h1->handle(3);
	cout << endl;

	cout << "Throwing 7..." << endl;
	h1->handle(7);
	cout << endl;

	cout << "Throwing 12..." << endl;
	h1->handle(12);
	cout << endl;
}
