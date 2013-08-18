/*
 * Prototype.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * There's a catalogue of classes (derived from an abstract class)
 * and you're given an object from one of those classes.
 *
 * You want to clone this (prototypical) object.
 */


// ------------- Catalogue --------------

class CAbstractMonster{
	// All monsters derive from this class
public:
	virtual CAbstractMonster* Clone() const=0;
	virtual void print() {}
};



class CGreenMonster : public CAbstractMonster{
protected:
	int tail_length;

public:
	CGreenMonster() { tail_length = 0; }
	CGreenMonster( const CGreenMonster &copy )
		{ tail_length = copy.tail_length; }

	CAbstractMonster* Clone() const;
	/*
	 * Can't just put:
	 * 		{ return new CGreenMonster(*this); }
	 * 	here because, at the moment, CGreenMonster doesn't exist.
	 *
	 *	I could prototype the whole class, but that's silly.
	 */

	void setTailLength(int length)
			{ tail_length = length; }

	void print(){
		cout << "I am a green monster with a ";
		cout << tail_length << "m longer tail!" << endl;
	}
};


class CRedMonster : public CAbstractMonster{
protected:
	int spike_count;

public:
	CRedMonster() { spike_count = 0; }
	CRedMonster( const CRedMonster &copy )
		{ spike_count = copy.spike_count; }

	CAbstractMonster* Clone() const;

	void setSpikeCount(int count)
			{ spike_count = count; }

	void print(){
		cout << "I am a red monster with ";
		cout << spike_count << " counts!" << endl;
	}
};


CAbstractMonster* CRedMonster::Clone() const
	{ return new CRedMonster(*this); }

CAbstractMonster* CGreenMonster::Clone() const
	{ return new CGreenMonster(*this); }


// ---------------- Main ---------------
int prototype_test(){
	CGreenMonster *original_green = new CGreenMonster;
	original_green->setTailLength(30);

	CAbstractMonster *proto_monster;
	proto_monster = dynamic_cast<CAbstractMonster*> (original_green);
	proto_monster->print();

	CAbstractMonster *cloned_monster = proto_monster->Clone();
	cloned_monster->print();

	return 0;
}
