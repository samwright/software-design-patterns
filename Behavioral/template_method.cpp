/*
 * template_method.cpp
 *
 *  Created on: Jul 16, 2012
 *      Author: eatmuchpie
 */

#include <list>
#include <vector>
#include <iostream>
using namespace std;

/*
 * An algorithm is defined skeletally in a base class, referring
 * to virtual methods which will be overriden when subclassed.
 */

template <class T>
class RandomAccessQueue{
private:
	int max_length_, current_index;
	vector<T> vect_;

	RandomAccessQueue();

	int translateToLocalIndex(int ext_index){
		if (ext_index >= max_length_)
			return -2;
		int int_index = current_index - ext_index;
		if (int_index < 0)
			int_index += max_length_;
		return int_index;
	}

public:
	RandomAccessQueue(int max_length) :
		max_length_(max_length), current_index(-1) {}

	void push_front(T new_val){
		++current_index;
		if (current_index >= max_length_)
			current_index -= max_length_;
		if (vect_.size() == current_index)
			vect_.push_back(new_val);
		else
			vect_[current_index] = new_val;
	}

	T operator[](int ext_index){
		return vect_[ translateToLocalIndex(ext_index) ];
	}

	void clear(){
		current_index = -1;
		vect_.resize(0);
	}

	void print(){
		for (int i=0; i<vect_.size(); ++i)
			cout << i << " : as queue = " << (*this)[i]
			<< ", as raw list = "<< vect_[i] << endl;
		cout << "current = " << current_index << endl;
	}
};


// eg. next_value = some_function(old_value[0], old_value[2])
template <class T>
class AbstractMemoryAlgorithm{
protected:
	RandomAccessQueue<T> values;
	AbstractMemoryAlgorithm();

	virtual T next() = 0;
	virtual void fillInitialValues(vector<T> *initial_values) {};

public:
	AbstractMemoryAlgorithm(int max_history) : values(max_history) {}
	virtual ~AbstractMemoryAlgorithm() {}

	vector<T>* execute(int number_of_times){
		values.clear();

		vector<T> *results = new vector<T>;
		fillInitialValues(results);

		typename vector<T>::const_iterator itr;
		itr = results->begin();

		while(itr != results->end()){
			values.push_front(*itr);
			++itr;
		}

		for (int i=0; i<number_of_times; ++i){
			T new_value = next();
			values.push_front( new_value );
			results->push_back(new_value);
		}

		return results;
	}

};


class Fibonnaci : public AbstractMemoryAlgorithm<float>{
protected:
	float next(){
		return values[0] + values[1];
	}

	void fillInitialValues(vector<float> *initial_values){
		initial_values->push_back(0);
		initial_values->push_back(1);
	}

public:
	Fibonnaci() : AbstractMemoryAlgorithm<float>(3) {}
};


int fibonnaci_test(){
	Fibonnaci f;
	vector<float> *results = f.execute(12);
	vector<float>::const_iterator itr = results->begin();
	while(itr != results->end()){
		cout << *itr << ", ";
		++itr;
	}
}
