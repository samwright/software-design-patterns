/*
 * Singleton.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * A class that always gives the same object when instantiated.
 *
 * Like a global variable, it is accessible globally.
 */


class Singleton{

	//  ----  Here's the class functionality ----
protected:
	int constant;

public:
	void setConst(int val) { constant = val; }
	int getConst() { return constant; }

	// ----- And here's the singleton-ness -------

	static Singleton* Instance(){
		/*
		 * This line only works when 'instance' is undefined,
		 * so only runs the first time.
		 *
		 * NB. static means you run "Singleton::Instance()"
		 * instead of instantiating then doing this.
		 */
		static Singleton *instance = new Singleton;

		return instance;
	}

	/*
	 * We only want to instantiate this class via 'Instance',
	 * not through the normal way, then only manipulate the object
	 * using the 'setConst' and 'getConst' functions.
	 *
	 * So we hide the following methods in 'private':
	 */
private:
	/*
	 * The constructor and destructor are already defined,
	 * so we need to reDEFINE them here to replace their
	 * public versions
	 */

	// Default Constructor
	Singleton(){}

	// Destruction
	~Singleton(){}

	/*
	 * The copy contructor an assignment operator aren't defined,
	 * so it is enough to simply declare them in private to hide them.
	 */

	// Copy Contructor
	Singleton(const Singleton &old);

	// Assignment operator
	const Singleton& operator=(const Singleton &old);

};


// ---------------- main -------------------
int singleton_test(){
	Singleton *s1 = Singleton::Instance();
	s1->setConst(45);

	Singleton *s2 = Singleton::Instance();
	cout << "Constant is " << s2->getConst();
}
