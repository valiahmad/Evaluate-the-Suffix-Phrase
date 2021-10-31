#include <iostream>
#include <conio.h>
#include <vector>
#include <stack>
using namespace std;
#define pos 43
#define neg 45
#define mul 42
#define div 47
#define pr_op 40
#define pr_c 41

struct post_fix {
	stack<char>ch;
	vector<char>postfix;
	float make_postfix(vector<char>input) {
		int i = 0;
		while (input[i] != '\r') {
			if (isDigit(input[i])) {
				postfix.push_back(input[i]);
				i++;
			}
			else if (isSign(input[i])) {
				if (ch.empty()) {
					ch.push(input[i]);
					i++;
				}
				else if (!ch.empty() && check(input[i])) {
					ch.push(input[i]);
					i++;
				}
				else if (input[i] != pr_c) {
					while (!ch.empty() && !check(input[i])) {
						postfix.push_back(ch.top());
						ch.pop();
					}
				}
				else if (input[i] == pr_c) {
					while (ch.top() != pr_op) {
						postfix.push_back(ch.top());
						ch.pop();
					}
					ch.pop();
					i++;
				}
			}
		}
		while (!ch.empty()) {
			postfix.push_back(ch.top());
			ch.pop();
		}
		i = 0;
		cout << "\n\npostfix is : ";
		while (i < postfix.size()) {
			if (postfix[i] >= 48 && postfix[i] <= 57) {
				cout << (int)postfix[i] - 48;
			}
			else { cout << postfix[i]; }
			i++;
		}
		return evaluate(postfix);
	}
	int isDigit(char num) {
		if (num >= 48 && num <= 57)
			return 1;
		else return 0;
	}
	int isSign(char sign) {
		if (sign >= 40 && sign <= 47 && sign != 44 && sign != 46)
			return 1;
		else return 0;
	}
	int check(char word) {
		int in, out;
		if (word == pos || word == neg) {
			out = 1;
		}
		else if (word == mul || word == div) {
			out = 2;
		}
		else if (word == pr_op) { return 1; }
		else if (word == pr_c) { return 0; }
		if (ch.top() == pos || ch.top() == neg) {
			in = 1;
		}
		else if (ch.top() == mul || ch.top() == div) {
			in = 2;
		}
		else if (ch.top() == pr_op) { in = 0; }
		////////////////////////
		if (out >= in) { return 1; }
		else return 0;
	}
	float evaluate(vector<char>post) {
		stack<int>s;
		float value, operand1, operand2;
		char symbol;
		for (int i = 0; i < post.size(); i++) {
			symbol = post[i];
			if (isDigit(symbol))
				s.push((float)(symbol - 48));
			else {
				operand2 = s.top();
				s.pop();
				operand1 = s.top();
				s.pop();
				value = operate(symbol, operand1, operand2);
				s.push(value);
			}
		}
		value = s.top();
		s.pop();
		return value;
	}
	float operate(char symbol, float operand1, float operand2) {
		switch (symbol) {
		case '+':
			return operand1 + operand2;
		case '-':
			return operand1 - operand2;
		case '*':
			return operand1 * operand2;
		case '/':
			return operand1 / operand2;
		}
	}
};

int main()
{
	post_fix ob;
	vector<char>g;
	cout << "enter the sentence : ";
	while (true) {
		g.push_back(_getche());
		if (g.back() == '\r') {
			break;
		}
	}
	cout << "\n\nthe valu is : " << ob.make_postfix(g) << endl;

	return 0;
}