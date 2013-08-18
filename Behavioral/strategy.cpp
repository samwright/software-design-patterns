/*
 * strategy.cpp
 *
 *  Created on: Jul 16, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * Algorithms derive from a single abstract class / interface.
 * Each solver object can choose which algorithm to use.
 */


class AbstractAlgorithm{
public:
	virtual void execute() = 0;
	virtual ~AbstractAlgorithm() {}
};

class Algor1 : public AbstractAlgorithm{
public:
	void execute() { cout << "Ran algorithm 1" << endl; }
};

class Algor2 : public AbstractAlgorithm{
public:
	void execute() { cout << "Ran algorithm 2" << endl; }
};


class Solver{
private:
	AbstractAlgorithm *algorithm_;

public:
	Solver(AbstractAlgorithm *algorithm) : algorithm_(algorithm) {}
	void setAlgorithm(AbstractAlgorithm *algorithm) { algorithm_ = algorithm; }
	void execute() { algorithm_->execute(); }
};



int strategy_test(){
	Solver s(new Algor1);
	s.execute();

	s.setAlgorithm(new Algor2);
	s.execute();
}
