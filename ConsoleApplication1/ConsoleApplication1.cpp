#include "pch.h"
#include <iostream>
using namespace std;

struct Stack {
	char s;
	Stack* next;
};

struct stackForNumbers {
	double info;
	stackForNumbers* next;
};

struct keyAndValue {
	double value;
	char key;
};


int prior(char);
Stack* OUT(Stack*, char*);
Stack* IN(Stack*, char);
double calculate(char*);



int main()
{
	Stack *a, *operation = NULL;
	char c, in[81], out[81];
	int k = 0, l = 0;
	cout << "Enter your formula" << endl;
	cin >> in;

	while (in[k] != '\0') {
		if (in[k] >= 'a' && in[k] <= 'z')
			out[l++] = in[k];
		if (in[k] == '(')
			operation = IN(operation, in[k]);
		if (in[k] == ')') {
			while ((operation->s) != '(') {
				operation = OUT(operation, &c);
				if (!operation)
					c = '\0';
				out[l++] = c;
			}
			a = operation;
			operation = operation->next;
			delete a;
		}
		if (in[k] == '+' || in[k] == '-' || in[k] == '*' || in[k] == '/') {
			while (operation != NULL && prior(operation->s) >= prior(in[k])) {
				operation = OUT(operation, &c);
				out[l++] = c;
			}
			operation = IN(operation, in[k]);
		}
		k++;
	}
	while (operation != NULL) {
		operation = OUT(operation, &c);
		out[l++] = c;
	}
	out[l] = '\0';
	cout << "Polish version: " << out << endl;
	double result = calculate(out);
	cout << result;
}

int prior(char a) {
	switch (a) {
	case '*': 	case '/': 	return 3;
	case '–': 	case '+': 	return 2;
	case '(':   return 1;
	}
	return 0;
}
Stack* IN(Stack* p, char st)
{
	Stack* t = new Stack;
	t->s = st;
	t->next = p;
	return t;
}
Stack* OUT(Stack* p, char* st)
{
	Stack* t = p;
	*st = p->s;
	p = p->next;
	delete t;
	return p;
}

stackForNumbers* push(stackForNumbers* begin, double info) {
	if (info == -52) {
		return begin;
	}
	stackForNumbers* temp = new stackForNumbers;
	temp->info = info;
	temp->next = begin;
	return temp;
}

stackForNumbers* pop(stackForNumbers* begin, double* info) {
	stackForNumbers* temp = begin;
	*info = temp->info;
	begin = begin->next;
	delete temp;
	return begin;
}

double findValue(keyAndValue mas[], char temp) {
	for (int i = 0; i < 10; i++) {
		if (mas[i].key == temp) {
			return mas[i].value;
		}
	}
}

double calculate(char str[]) {
	stackForNumbers* begin = NULL;
	int  i;
	char ss;
	double ss1, ss2;
	double res;
	keyAndValue mas[10];
	cout << " Input data" << endl;
	int iterator = 0;
	for (i = 0; str[i] != '\0'; i++) {
		ss = str[i];
		if (ss >= 'a' && ss <= 'z') {
			cout << ss << " = ";
			cin >> mas[iterator].value;
			mas[iterator].key = ss;
			iterator += 1;
		}
	}
	
	for (i = 0; str[i] != '\0'; i++) {
		char temp = str[i];
		if (!(temp == '+' || temp == '-' || temp == '*' ||
			temp == '/')) {
			double valueToPush = findValue(mas, temp);
			begin = push(begin, valueToPush);
		}
		else {
			begin = pop(begin, &ss2);
			begin = pop(begin, &ss1);

			switch (temp) 
			{
			case '+': 	res = ss1 + ss2;  	  break;
			case '-': 	res = ss1 - ss2;  	  break;
			case '*': 	res = ss1 * ss2;  	  break;
			case '/': 	res = ss1 / ss2;  	  break;
			}
			begin = push(begin, res);
		}
	}
	return begin->info;
}


