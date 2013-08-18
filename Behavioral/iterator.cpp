/*
 * iterator.cpp
 *
 *  Created on: Jul 14, 2012
 *      Author: eatmuchpie
 */

#include <iostream>
using namespace std;

/*
 * An iterator can be dereferenced to give the value at its
 * position in a list.
 *
 * It can be '++itr' or '--itr' to go forwards or backwards in
 * the list.
 *
 * (Look at LinkedList::Iterator for what the iterator can do.)
 */

// --------------- Generic iterator -----------------
int LENGTH = 10;
int *array = new int[LENGTH];

int *itr = array;

int array_iterator(){
	for(int i=0; i<LENGTH; i++){
		*itr = i;
		itr++;
	}
	delete[] array;
}


// -------------------- Linked list :-D ---------------------
// NB. can't do 'list[2] = node', because I can't capture the
// behaviour to then change the preceeding and proceeding
// nodes.  Instead, use 'list.replace(2, node)'.

class Node {
private:
	Node *previous_, *next_;

public:
	const char* strng_;
	Node(const char* strng) : previous_(0) , next_(0), strng_(strng) {}

	Node* previous(){ return previous_; }
	Node* next(){ return next_; }

	void setPrevious(Node *obj){
		previous_ = obj;
		if (obj != 0)
			if (obj->next() != this)
				obj->setNext(this);
	}

	void setNext(Node *obj){
		next_ = obj;
		if (obj != 0)
			if (obj->previous() != this)
				obj->setPrevious(this);
	}
};


class LinkedList{
public:

	class Iterator{
	private:
			LinkedList *list_;
			Node *current_node;
			Iterator();

		public:
			Iterator(LinkedList *list) : list_(list), current_node(0) {}

			LinkedList::Iterator& operator++();
			LinkedList::Iterator operator++(int);
			LinkedList::Iterator& operator--();
			LinkedList::Iterator operator--(int);
			Node* operator*();

			void setCurrentNode(Node *node);
			void setIndex(int index);
			Node* operator[](int index);
	};

	LinkedList() : first_(0), last_(0), length_(0), internal_iterator(this) {}

	Node* first() { return first_; }
	Node* last() { return last_; }

	Node* operator[](int index){ return internal_iterator[index]; }

	Iterator* begin(){
		Iterator *iter = new Iterator(this);
		iter->setIndex(0);
		return iter;
	}

	Iterator* end(){
		Iterator *iter = new Iterator(this);
		iter->setIndex(-1);
		return iter;
	}

	void remove(Node *node){
		Node *next_node = node->next(), *previous_node = node->previous();
		if (previous_node != 0)
			previous_node->setNext(next_node);
		else
			first_ = next_node;

		if (next_node != 0)
			next_node->setPrevious(previous_node);
		else
			last_ = previous_node;

		--length_;
	}

	void remove(int index){
		Node *node = internal_iterator[index];
		if (node != 0)
			remove(node);
	}

	void replace(Node *old_node, Node *new_node){
		new_node->setNext( old_node->next() );
		new_node->setPrevious( old_node->previous() );

		if (first_ == old_node)
			first_ = new_node;
		if (last_ == old_node)
			last_ = new_node;

		old_node->setPrevious(0);
		old_node->setNext(0);
	}

	void replace(int position, Node *new_node){
		Node *old_node = internal_iterator[position];
		if (old_node != 0)
			replace(old_node, new_node);
	}

	void insert(int position, Node *new_node){
		if ( empty() )
			first_ = last_ = new_node;
		else if (position == length_)
		{
			last_->setNext(new_node);
			last_ = new_node;
		} else {
			Node *original_node = internal_iterator[position];

			if (original_node == 0)
				return;

			Node *before_node = original_node->previous();
			new_node->setNext(original_node);
			if (before_node == 0){
				first_ = new_node;
				new_node->setPrevious(0);
			} else {
				new_node->setPrevious(before_node);
			}
		}

		++length_;
	}

	void push_back(Node *new_node){ insert(length_, new_node); }
	void push_forward(Node *new_node){ insert(0, new_node); }

	bool contains(Node *node){
		internal_iterator.setIndex(0);
		while(*internal_iterator != 0){
			if ((*internal_iterator) == node)
				return true;
			++internal_iterator;
		}
		return false;
	}

	bool empty(){
		if (last_ == 0)
			return true;
		return false;
	}

	void print_list(){
		cout << "[" << first_->strng_ << "] ";
		internal_iterator.setIndex(0);
		while(*internal_iterator != 0){
			cout << (*internal_iterator)->strng_ << " ";
			++internal_iterator;
		}
		cout << " [" << last_->strng_ << "], length = " << length_;
	}

private:
	Node *first_, *last_;
	int length_;
	Iterator internal_iterator;

};


LinkedList::Iterator& LinkedList::Iterator::operator++(){
	if (current_node != 0)
		current_node = current_node->next();
	return *this;
}

LinkedList::Iterator LinkedList::Iterator::operator++(int){
	LinkedList::Iterator result(*this);
	++(*this);
	return result;
}

LinkedList::Iterator& LinkedList::Iterator::operator--(){
	if (current_node != 0)
		current_node = current_node->previous();
	return *this;
}

LinkedList::Iterator LinkedList::Iterator::operator--(int){
	LinkedList::Iterator result(*this);
	--(*this);
	return result;
}

Node* LinkedList::Iterator::operator*  (){
	return current_node;
}

void LinkedList::Iterator::setCurrentNode(Node *node) { current_node = node; }

void LinkedList::Iterator::setIndex(int index){
	int i;

	if (index>=0){
		current_node = list_->first();
		i=0;
		while (current_node!=0 and i!=index){
			++i;
			++(*this);
		}
	} else {
		current_node = list_->last();
		i=-1;
		while (current_node!=0 and i!=index){
			++i;
			--(*this);
		}
	}
}

Node* LinkedList::Iterator::operator[](int index){
	setIndex(index);
	return current_node;
}



int LinkedList_test(){
	Node n0("Zero"), n1("One"), n2("Two"), n3("Three"), n4("Four");
	LinkedList llist;
	llist.push_back(&n0);
	llist.push_back(&n1);
	llist.push_back(&n2);
	llist.push_back(&n3);

	llist.print_list();

	llist.remove(2);
	cout << endl << endl;
	llist.print_list();

	cout << "what is at 1?: " << llist[1]->strng_ << endl;

	llist.insert(1, &n4);
	cout << endl << endl;
	llist.print_list();

	llist.insert(0, &n2);
	cout << endl << endl;
	llist.print_list();

	cout << endl << endl;
	cout << "Is 'Two' in llist?  ";
	bool answer = llist.contains(&n2);
	if (answer)
		cout << "Yes!";
	else
		cout << "No.";

	llist.remove(&n2);
	llist.remove(&n3);
	llist.remove(&n4);
	cout << endl << endl;
	llist.print_list();

	llist.replace(0, &n2);
	llist.replace(&n1, &n3);
	cout << endl << endl;
	llist.print_list();

}
