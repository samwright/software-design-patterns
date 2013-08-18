/*
 * memento.cpp
 *
 *  Created on: Jul 15, 2012
 *      Author: eatmuchpie
 */

#include <stack>
#include <iostream>
using namespace std;

/*
 * A snapshot object of an object's variables.
 */

class Number;

class Mememto{
private:
	int state_;

public:
	Mememto(int state) : state_(state) {}
	int getState() { return state_; }
};


class Caretaker{
private:
	stack<Mememto*> undo, redo;
	Mememto *current_state;

public:
	Caretaker() : current_state(0) {}

	void saveState(int state){
		if (current_state != 0)
			undo.push(current_state);
		current_state = new Mememto(state);
		while( !redo.empty() )
			redo.pop();
	}

	Mememto* getUndoneMememto(){
		if (undo.empty())
			return 0;
		redo.push(current_state);
		current_state = undo.top();
		undo.pop();
		return current_state;
	}

	Mememto* getRedoneMememto(){
		if (redo.empty())
			return 0;
		undo.push(current_state);
		current_state = redo.top();
		redo.pop();
		return current_state;
	}
};


class Number{
private:
	int val_;
	Caretaker *caretaker_;

public:
	Number(Caretaker *caretaker, int val=0) : caretaker_(caretaker) {
		setVal(val);
	}

	void setVal(int val){
		val_ = val;
		caretaker_->saveState(val);
	}

	int getVal() { return val_; }

	void undo(){
		Mememto *mememto = caretaker_->getUndoneMememto();
		if (mememto != 0)
			val_ = mememto->getState();
	}

	void redo(){
		Mememto *mememto = caretaker_->getRedoneMememto();
		if (mememto != 0)
			val_ = mememto->getState();
	}
};

int mememto_test(){
	Caretaker c;
	Number n(&c);
	n.setVal(2);
	n.setVal(4);
	n.setVal(6);
	n.setVal(8);

	cout << "0 -> 2 -> 4 -> 6 -> 8" << endl;
	cout << "Current val = 8" << endl;
	n.undo();
	cout << "undo: val = " << n.getVal() << endl;
	n.undo();
	cout << "undo: val = " << n.getVal() << endl;
	n.undo();
	cout << "undo: val = " << n.getVal() << endl;
	n.redo();
	cout << "redo: val = " << n.getVal() << endl;
	n.setVal(15);
	cout << "setVal(15): val = " << n.getVal() << endl;
	n.redo();
	cout << "redo: val = " << n.getVal() << endl;
	n.undo();
	cout << "undo: val = " << n.getVal() << endl;
	n.undo();
	cout << "undo: val = " << n.getVal() << endl;



}
