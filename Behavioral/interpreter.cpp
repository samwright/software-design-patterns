/*
 * interpreter.cpp
 *
 *  Created on: Jul 13, 2012
 *      Author: eatmuchpie
 */

#include <string.h>
#include <iostream>
using namespace std;

/*
 * This doesn't work yet, and I think I might have to rethink the
 * algorithm for decoding roman numerals.  Also, I should change from
 * using char* to string, and use string's inbuilt find and replace
 * functionality.
 */

/*
 * Roman numerals: Any number can be made in range 1->10 with:
 * 	 1=I, IV=4, V=5, IX=9, X=10.
 * Multiplying this up to 10->100:
 * 	 10=X, 40=XL, 50=L, 90=XC, 100=C
 * Again, for 100->1000:
 *   100=C, 400=CD, 500=D, 900=CM, 1000=M
 *
 * So we could create a class for each range, and methods for
 * one, four, five, nine, ten, and have a multiplier too.
 *
 * The process should be:
 * 		Try hundreds:
 * 			Try 9 and 4 first
 * 			then try the rest
 * 		Try tens:
 * 			Try 9 and 4 first
 * 			then try the rest
 * 		Try digits:
 * 			Try 9 and 4 first
 * 			then try the rest
 *
 * 	The 'try 9 and 4, then the rest' is common to all ranges,
 * 	so it should be derived from a base class
 *
 * Then
 */

class RomanRange{
protected:
	virtual const char* one() = 0;
	virtual const char* four() = 0;
	virtual const char* five() = 0;
	virtual const char* nine() = 0;
	virtual const char* ten() = 0;

	virtual int multiplier() = 0;

	void fourAndNine(char *input, int &total){
		cout << "FOURANDNINE";
		while(input[0] != '\0' and input[1] != '\0'){
			if (!strncmp(input, nine(), 2)){
				input[0] = input[1] = ' ';
				total += 9;
			} else if (!strncmp(input, four(), 2)) {
				input[0] = input[1] = ' ';
				total += 4;
			}
			input++;
		}
	}

	void theRest(char *input, int &total){
		while(*input){
			/*
			if (!strncmp(input, one(), 1)){
				input[0] = ' ';
				total += 1;
			} else if (!strncmp(input, five(), 1)) {
				input[0] = ' ';
				total += 5;
			} else if (!strncmp(input, ten(), 1)) {
				input[0] = ' ';
				total += 10;
			}
			input++;
			*/
			cout << "input is: " << *input << endl;
			if (!strncmp(input, one(), 1)){
				cout << "it is one!" << endl;
				//input[0] = ' ';
				total += 1;
			}

			input++;
		}
	}

public:
	void interpret(char *input, int &total){
		int local_total = 0;
		cout << endl << "--- starting " << multiplier() << endl;


		//fourAndNine(input, local_total);

		theRest(input, local_total);

		total += local_total * multiplier();
	}
	virtual ~RomanRange() {}
};


class Digits : public RomanRange{
	const char* one() { return "I"; }
	const char* four() { return "IV"; }
	const char* five() { return "V"; }
	const char* nine() { return "IX"; }
	const char* ten() { return "X"; }

	int multiplier() { return 1; }
};

class Tens : public RomanRange{
	const char* one() { return "X"; }
	const char* four() { return "XL"; }
	const char* five() { return "L"; }
	const char* nine() { return "XC"; }
	const char* ten() { return "C"; }

	int multiplier() { return 10; }
};

class Hundreds : public RomanRange{
	const char* one() { return "C"; }
	const char* four() { return "CD"; }
	const char* five() { return "D"; }
	const char* nine() { return "CM"; }
	const char* ten() { return "M"; }

	int multiplier() { return 100; }
};


class RomanInterpreter{
private:
	Hundreds* hundreds;
	Tens* tens;
	Digits* digits;

public:
	RomanInterpreter() : hundreds(new Hundreds),
						tens(new Tens),
						digits(new Digits) {}

	int interpret(char* input){
		int total = 0;

		hundreds->interpret(input, total);
		tens->interpret(input, total);
		digits->interpret(input, total);

		return total;
	}

	~RomanInterpreter() {
		delete hundreds;
		delete tens;
		delete digits;
	}

};


int interpreter_test(){
	RomanInterpreter* r = new RomanInterpreter;
	char *eg1 = "XI";
	cout << "hi?" << endl;
	cout << eg1+1;
	const char* I = "I";
	char *eg2 = eg1 + 1;
	if (!strncmp(eg2, I, 1))
		cout << "yay!";
	int number = r->interpret(eg1);
	cout << "XI is " << number << endl;

	string s;
}
