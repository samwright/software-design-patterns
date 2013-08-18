/*
 * Factory.cpp
 *
 *  Created on: Jul 6, 2012
 *      Author: eatmuchpie
 */



/*
 * There's a catalogue of classes, and I want to instantiate one
 * of them based on eg. the user typing the class name.
 */

#include <string>
#include <iostream>

using namespace std;


// --------------------- Catalogue ----------------------

class Enemy{
	/*
	 * All enemies in a game derive from this class.
	 */
protected:
	int strength;
	int health;
public:
	virtual void shout() = 0;
};


class C_Minion : public Enemy {
public:
	void stab() {}
	void shout()
		{ cout << "eep!" << endl; }
};

class C_BigBoss : public Enemy {
public:
	void stomp() {}
	void shout()
		{ cout << "RAAWR!" << endl; }
};


// ----------------------- Factory ---------------------

class EnemyFactory{
	// static means I don't have to instantiate EnemyFactory
public:
	enum Type{
		Minion,
		BigBoss
	};
	static Enemy* create(Type enemyType){
		switch (enemyType){
		case Minion:
			return (new C_Minion);
		case BigBoss:
			return (new C_BigBoss);
		}
		throw "Not an enemy";
	}
};


// ----------------------- Main --------------------------

int factory_test(){
	Enemy *Bowser = EnemyFactory::create( EnemyFactory::BigBoss );
	Enemy *worm = EnemyFactory::create( EnemyFactory::Minion );

	cout << "Bowser says: "; Bowser->shout();
	cout << "Worm says: "; worm->shout();
}
