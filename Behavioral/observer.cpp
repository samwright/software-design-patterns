/*
 * observer.cpp
 *
 *  Created on: Jul 15, 2012
 *      Author: eatmuchpie
 */


#include <iostream>
#include <math.h> // for pow
#include <list> // This is the STL linked list. Insertion is easy,
				// random access is slow.
using namespace std;

/*
 * Observers are registered with subjects, so when a subject
 * changes state it can notify all registered observers.
 */

int round(int val, int to_exponent_of_ten){
	float scaled_val = (float) val / pow(10, to_exponent_of_ten);

	int rounded_val = (int) scaled_val;
	if ((scaled_val - rounded_val) >= 0.5)
		++rounded_val;

	return rounded_val * pow(10, to_exponent_of_ten);
}

class Observer{
public:
	virtual void shout(int) = 0;
	virtual ~Observer() {}
};

typedef list<Observer*> ObserverList;

class Subject{
private:
	int val_, val_neares10_, val_nearest100_;
	ObserverList val_list, val_nearest10_list, val_nearest100_list;


	void update(ObserverList& lst, int val){
		ObserverList::iterator itr = lst.begin();

		while (itr != lst.end()){
			(*itr)->shout(val);
			++itr;
		}
	}

	void registerForList(Observer *observer, ObserverList& lst){
		lst.push_back(observer);
	}

	void unregisterForList(Observer *observer, ObserverList& lst){
			lst.remove(observer);
		}
public:
	Subject(int val=0) : val_(val) {}

	bool registerObserver(Observer *observer, int to_nearest){
		if (to_nearest == 1)
			registerForList(observer, val_list);
		else if (to_nearest == 10)
			registerForList(observer, val_nearest10_list);
		else if (to_nearest == 100)
			registerForList(observer, val_nearest100_list);
		else
			return false;
		return true;
	}

	void unregisterObserver(Observer *observer, int to_nearest){
		if (to_nearest == 1)
			unregisterForList(observer, val_list);
		else if (to_nearest == 10)
			unregisterForList(observer, val_nearest10_list);
		else if (to_nearest == 100)
			unregisterForList(observer, val_nearest100_list);
	}

	void unregisterObserver(Observer *observer){
		unregisterForList(observer, val_list);
		unregisterForList(observer, val_nearest10_list);
		unregisterForList(observer, val_nearest100_list);
	}

	void setVal(int val){
		int old_val = val_;
		val_ = val;
		if (val_ != old_val)
			update(val_list, val_);
		if (round(val_, 1) != round(old_val, 1))
			update(val_nearest10_list, round(val_, 1));
		if (round(val_, 2) != round(old_val, 2))
			update(val_nearest100_list, round(val_, 2));
	}
};

class DigitsObserver : Observer{
public:
	void shout(int val) { cout << "Value changed to " << val << endl; }
	DigitsObserver(Subject *subject){ subject->registerObserver(this, 1); }
	~DigitsObserver() {}
};

class TensObserver : Observer{
public:
	void shout(int val) { cout << "Tens changed to " << val << endl; }
	TensObserver(Subject *subject){ subject->registerObserver(this, 10); }
	~TensObserver() {}
};

class HundredsObserver : Observer{
public:
	void shout(int val) { cout << "Hundreds changed to " << val << endl; }
	HundredsObserver(Subject *subject){ subject->registerObserver(this, 100); }
	~HundredsObserver() {}
};

int observer_test(){
	int val=1;
	Subject s(val);
	DigitsObserver d(&s);
	TensObserver t(&s);
	HundredsObserver h(&s);

	while(val!=0){
		cout << endl << "----- Setting value to " << val << " ------" << endl;
		cin >> val;
		s.setVal(val);
	}
}
