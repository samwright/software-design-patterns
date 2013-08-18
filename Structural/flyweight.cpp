/*
 * flyweight.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

typedef map< int, vector<int>* > KeyTable;

/*
 * Reduces the number of instantiations required by reusing objects
 * that contain shared and unchanged data.
 *
 * The flywheel is a class containing these reusable objects, and
 * is in charge of deciding whether to create a new object or reuse
 * an old one.
 */


/*
 * eg. You want an object for each hour of the day,
 * and each hour is divided by a number set on instantiation, eg:
 * 		Hour one(6);  // one.minutes = {0, 10, 20, 30, 40, 50}
 * 		Hour two(2);  // two.minutes = {0, 30}
 *
 * This can be done by each object creating the 'minutes' list on
 * instantiation, but some hours will be divided the same way.
 *
 * We want a flyweight to create and reuse these 'minutes' lists.
 */


class MinutesFlyweight{
private:
	static KeyTable minutesTable;

	static vector<int>* createMinutesVector(int divisor){
		int minute = 0;
		vector<int> *minutes = new vector<int>;

		while( minute < 60 ){
			minutes->push_back(minute);
			minute += 60/divisor;
		}

		return minutes;
	}

public:
	static vector<int>* getMinutes(int divisor){
		vector<int> *minutes;
		KeyTable::iterator iter;
		iter = minutesTable.find(divisor);


		if (iter == minutesTable.end()){
			minutes = createMinutesVector(divisor);
			minutesTable[divisor] = minutes;
		}
		else
			minutes = iter->second;

		return minutes;
	}

	static void printStoredDivisors(){
		cout << "Divisors stored in flyweight:  ";
		KeyTable::iterator iter;

		for (iter = minutesTable.begin();
				iter != minutesTable.end();
				iter++){
			cout << iter->first << ", ";
		}
		cout << endl;
	}
};
KeyTable MinutesFlyweight::minutesTable;


class Hour{
private:
	vector<int> *minutes;
	int hour_;
public:
	Hour(int hour, int divisor) : hour_(hour) {
		minutes = MinutesFlyweight::getMinutes(divisor);
	}

	void const print(){
		vector<int>::iterator iter;

		for(iter = minutes->begin(); iter < minutes->end(); iter++){
			cout << hour_ << ":" << setw(2) << setfill('0') << *iter << ", ";
		}
		cout << endl;
	}
};



int flyweight_test(){
	Hour h1(1, 4), h2(2, 3), h3(5, 10), h4(9, 4);
	h1.print();
	h2.print();
	h3.print();
	h4.print();

	cout << endl;
	MinutesFlyweight::printStoredDivisors();
}
