//============================================================================
// Name        : A3.cpp
// Author      : Hazem Safwat
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include<string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
using namespace std;

template<class type>
class Stack {

public:

	Stack() {
		head = 0;
	}

	void push(type x) {
		Link addedNode = new Node;
		if (addedNode == 0)
			return;
		addedNode->data = x;
		addedNode->next = head;
		head = addedNode;
	}

	type pop() {
		if (head != 0) {

			type x = head->data;
			Link temp;
			temp = head;
			head = head->next;
			delete temp;
			return x;
		}
		return 0;
	}

	bool IsEmpty() {
		if (head == 0)
			return true;
		else
			return false;
	}

	type top() {
		return head->data;
	}
	bool search(char c) {
		Link p;
		p = head;
		while (p != 0) {
			if (c == '!' && p->data != '!') {
				return false;
			} else if ((c == 'x' || c == '/' || c == '%') && p->data != '!'
					&& p->data != 'x' && p->data != '/' && p->data != '%') {
				return false;
			} else if ((c == '+' || c == '-') && p->data != '!'
					&& p->data != 'x' && p->data != '/' && p->data != '%'
					&& p->data != '-' && p->data != '+') {
				return false;
			} else
				return true;
			p= p->next;
		}
	}
private:
	struct Node;
	typedef Node * Link;
	struct Node {
		type data;
		Link next;
	};
	Link head;

};
float fact(float num) {
	float result = 1;
	for (int i = num; i >= 1; i--) {
		result *= i;
	}
	return result;
}
float eval(char op, float op1, float op2) {
	float result;
	switch (op) {
	case '+':
		result = op1 + op2;
		break;

	case '-':
		result = op1 - op2;
		break;

	case 'x':
		result = op1 * op2;
		break;
	case '/':
		result = op1 / op2;
		break;
	case '%':
		result = int(op1) % int(op2);
		break;
	case '!':
		result = fact(op2);
		break;

	}

	return result;
}
bool oper(char ch) {

	if (ch == '+' || ch == '-' || ch == 'x' || ch == '/' || ch == '!'
			|| ch == '%')
		return true;
	else
		return false;
}

int main(int argc, char ** argv) {
	Stack<float> numbers;
	Stack<char> ch;
	float op1, op2, op;
	if (argc == 1) {
		printf("%.2 f", 0);
		return 0;
	}
	string f = argv[1];
	if (oper(f[0]) && f.length() == 1) {
		cout << "Invalid Expression";
		return 0;
	}

	for (int i = 1; i < (argc - 1); i++) {
		string s = argv[i], s1 = argv[i + 1];
		if (s.length() == 1) {
			if (!isdigit(s[0]) && !oper(s[0]) && s[0] != '(' && s[0] != ')'
					&& s[0] != '!') {
				cout << "Invalid Expression";
				return 0;
			} else if (s1.length() == 1 && oper(s1[0]) && oper(s[0])
					&& s[0] != '!') {
				cout << "Invalid Expression";
				return 0;
			} else {
				if (oper(s1[0]) && oper(s[0]) && s1[0] != '+' && s1[0] != '-'
						&& s1.length() != 1) {
					cout << "Invalid Expression";
					return 0;
				}

			}
			if (s1.length() > 1 && oper(s1[1])) {
				cout << "Invalid Expression";
				return 0;
			}

		} else if (s.length() > 1) {
			if (!isdigit(s[0]) && !oper(s[0]) && s[0] != '(' && s[0] != ')') {
				cout << "Invalid Expression";
				return 0;
			} else if (oper(s[1]) || oper(s[2])) {
				cout << "Invalid Expression";
				return 0;
			} else if (s1.length() > 1 && oper(s1[1])) {
				cout << "Invalid Expression";
				return 0;
			}
		}
	}
	int count = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '(') {
			ch.push(argv[i][0]);
			count++;
		} else if (isdigit(argv[i][0])
				|| (argv[i][0] == '-' && isdigit(argv[i][1]))
				|| (argv[i][0] == '+' && isdigit(argv[i][1]))) {
			float f = atof(argv[i]);
			numbers.push(f);
		} else if (oper(argv[i][0])) {
			char c = argv[i][0];
			if (ch.IsEmpty())
				ch.push(c);
			else if (c == '!' && ch.top() != '!'/* && ch.search(c)*/)
				ch.push(c);
			else if ((c == 'x' || c == '/' || c == '%')
					&& (ch.top() != '!' && ch.top() != 'x' && ch.top() != '/'
							&& ch.top() != '%') /*&& ch.search(c)*/)
				ch.push(c);
			else if ((c == '+' || c == '-') && (ch.top() != '!'
					&& ch.top() != 'x' && ch.top() != '/' && ch.top() != '%'
					&& ch.top() != '-' && ch.top() != '+')/*&& ch.search(c)*/) {
				ch.push(c);
			} else {
				op = ch.pop();
				if (op == '!') {
					op2 = numbers.pop();
					op1 = fact(op2);
					numbers.push(op1);
				} else {
					op2 = numbers.pop();
					op1 = numbers.pop();
					numbers.push(eval(op, op1, op2));
				}
				ch.push(c);
			}

		} else if (argv[i][0] == ')') {
			count--;
			while (!ch.IsEmpty() /*&& ch.top() != '('*/) {
				op = ch.pop();
				if (op != '(') {
					if (op == '!') {
						op2 = numbers.pop();
						op1 = fact(op2);
						numbers.push(op1);
					} else {
						op2 = numbers.pop();
						op1 = numbers.pop();
						numbers.push(eval(op, op1, op2));
					}
				}

			}

		}
	} //end of for loop
	if (count != 0) {
		cout << "Invalid Expression";
		return 0;
	}
	if (ch.IsEmpty())
		//cout <<setprecision(3) <<numbers.pop();
		printf("%.2 f", numbers.pop());

	else {
		while (!ch.IsEmpty()) {
			op = ch.pop();
			if (op == '!') {
				op2 = numbers.pop();
				op1 = fact(op2);
				numbers.push(op1);
			} else {
				op2 = numbers.pop();
				op1 = numbers.pop();
				numbers.push(eval(op, op1, op2));
			}
		}
		//cout <<setprecision(3) <<numbers.pop();
		printf("%.2 f", numbers.pop());
	}
	return 0;
}
