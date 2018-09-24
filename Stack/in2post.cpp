#include <iostream>
#include "stack.h"
#include <string>
#include <cctype>
using namespace std;
using namespace cop4530;

char determine(string &s1);

int main()
{
		cout << "Enter infix expression (type 'exit' to quit): " << endl;

	Stack<char> myStack;	//change to S
	Stack<float> evalStack; //change to S
	Stack<string> postFix;
	string input;
	bool foundLetter = false;
	string last;

	int varcount;
	int symbolcount;

	char next = cin.peek();
	while (!cin.eof())
	{
		varcount = 0;
		symbolcount = 0;
		foundLetter = false;
		myStack.clear(); // clears the stacks after coming from an alphabetical input for another line
		postFix.clear();
		while (cin.peek() != '\n' && !cin.eof()) //Begins a single line. Converts infix to postfix
		{
			next = cin.peek();
			if (cin.peek() == ' ')
			{
				cin.ignore(); // operands and operators separated by white space. Ignore.
			}
			else if (next == '(') // if ( push immediately into stack
			{
				cin >> next;
				myStack.push(next);
				last = next;
			}
			else if (isalnum(cin.peek()) || cin.peek() == '_' || cin.peek() == '.') // enter if alphanumerical, or _ for variables, or . for floats
			{
				string temp;
				while (isalnum(cin.peek()) || cin.peek() == '_' || cin.peek() == '.')
				{
					cin.get(next);
					if (isalpha(next) || cin.peek() == '_')
						foundLetter = true; // We set the flag as true to stop later evaluation of variables in postFix. We want to evaluate only digits
					temp += next;			//While reading one at a time, we append the character to the string it's connected to in the input. Until another operator or whitespace appears.
				}
				last = next;		//storing the input for balance checking
				if (temp == "exit")
				{
					exit(0);
				}
				postFix.push(temp); //pushes in the entire value
				varcount++;
			}
			else if (next == '+' || next == '-') //begin operator storing //((next == '+' || next == '-' || next == '*' || next == '/')) && (
			{
				cin >> next;
				symbolcount++;
				if (last[0] == '(' || last[0] == '+' || last[0] == '-' || last[0] == '*' || last[0] == '/')
				{
					cout << "Error: Operators cannot follow Operators. Exited" << endl;
					exit(1);
				}
				if (myStack.empty() || myStack.top() == '(') // if there's nothing higher precendence than + - then we store
				{
					myStack.push(next);
				}
				else
				{
					while (!myStack.empty()) // we have to pop until there's no equal or higher precendence operator
					{
						if (myStack.top() == '(')
							break;
						if ((myStack.top() == '*' || myStack.top() == '/') || (myStack.top() == '+') || (myStack.top() == '-'))
						{
							input = myStack.top(); // if higher precedence we
							postFix.push(input);   // 		add to postfix string
							myStack.pop();		   // and then pop it
						}
					}
					myStack.push(next); // finally adding the + or - to stack
				}
				last = next; // storing for later balance checking
			}
			else if (next == '*' || next == '/')	//store higher precedence operators
			{
				cin >> next;
				symbolcount++;
				if (last[0] == '(' || last[0] == '+' || last[0] == '-' || last[0] == '*' || last[0] == '/')
				{
					cout << "Error: OOperators cannot follow Operators. Exited" << endl;
					exit(1);
				}
				if (!myStack.empty() && (myStack.top() == '*' || myStack.top() == '/')) //if equal precedence
				{
					input = myStack.top();
					postFix.push(input); // adding the previous * or / to string

					myStack.pop();
				}
				myStack.push(next);
				last = next;
			}
			else if (cin.peek() == ')') // we don't push ) into stack. We pop until (
			{
				cin >> next;
				if (last[0] == '(' || last[0] == '+' || last[0] == '-' || last[0] == '*' || last[0] == '/')
				{
					cout << "Error: Operator missing operands. Exited" << endl;
					exit(1);
				}
				while (myStack.top() != '(') // pops until (
				{
					input = myStack.top();
					postFix.push(input);
					myStack.pop();
					if (myStack.empty())
					{
						cout << "Error: mismatched paranthesis. Exited." << endl;
						exit(1);
					}
				}
				myStack.pop(); //pops the (
				last = next;
			}
			else // deals with the new line.
			{
				cin.ignore();
				break;
			}
		}						 // ends the conversion loop
		while (!myStack.empty()) // Still some operators left in stack that we add to the postfix string
		{
			if (myStack.top() == '(')		//should not find a ( at end of input. Report error
			{
				cout << "Error: Mismatched paranthesis. Exited." << endl;
				exit(1);
			}
			input = myStack.top();
			postFix.push(input);
			myStack.pop();
		}						 // ______________________________________postFix is finally achieved. We check errors here before computation
		if (postFix.size() == 0) // if the line was blank we prevent computation
		{
			break;
		}
		if (last[0] == '(' || last[0] == '+' || last[0] == '-' || last[0] == '*' || last[0] == '/') //last input cannot be operand
		{
			cout << "Error: Last input is operator. Exited" << endl;
			break;
		}
		if (symbolcount < (varcount - 1))
		{
			cout << "Error: Missing operators in the expression." << endl;
			break;
		}
		if (symbolcount > (varcount - 1))
		{
			cout << "Error: Missing operands in the expression." << endl;
			break;
		}
		if (foundLetter == true) // A variable is in the string, we do not want to evaluate the postfix. Output now.	
		{
			cout << "Postfix Expression: " << postFix << endl;
			cout << "Postfix Evaluation: " << postFix << " = " << postFix << endl;
		}
		else					// if the postFix is all numbers and operators
		{
			Stack<string> keepPost; //We want the postfix expression to cout later
			keepPost = postFix;		// 			so we will store it as keepPost
			Stack<string> compute;
			while (!postFix.empty())		 //We want to read in the expression left from right.
			{								 //		It's stored as right to left.
				compute.push(postFix.top()); //So we correct it by pouring the postfix into another stack
				postFix.pop();
			}
			float a;				 //We want to compute float type. The variables are
			float b;				 // 		our operands.
			while (!compute.empty()) // we begin the evaluation
			{
				switch (determine(compute.top())) // determine() returns if operator or operand
				{
				case '*':
					b = evalStack.top(); // the "second" operand comes out first -> b
					evalStack.pop();
					a = evalStack.top(); // the "first" operand comes out second -> a
					evalStack.pop();
					evalStack.push(a * b);
					break;
				case '/':
					b = evalStack.top();
					evalStack.pop();
					a = evalStack.top();
					evalStack.pop();
					evalStack.push(a / b);
					break;
				case '+':
					b = evalStack.top();
					evalStack.pop();
					a = evalStack.top();
					evalStack.pop();
					evalStack.push(a + b);
					break;
				case '-':
					b = evalStack.top();
					evalStack.pop();
					a = evalStack.top();
					evalStack.pop();
					evalStack.push(a - b);
					break;
				case 'n': // if operand, we convert the string to float and push into stack. This case should be used twice at the start of loop
					float f = stof(compute.top());
					evalStack.push(f); // this stores the evaluation stack operands while waiting for the operators
					break;
				}
				compute.pop(); // keeps loop going forward
			}
			cout << "Postfix Expression: " << keepPost << endl; // following the format of the test driver
			cout << "Postfix Evaluation: " << keepPost << "= " << evalStack.top() << endl;
		}
		cin.ignore(); // deals with newline
		cout << "Enter infix expression (type 'exit' to quit): " << endl;
	}
	return 0;
}
char determine(string &s1) // used for evaluation.
{
	char temp = s1[0];											  // If it's an operator, we assume its only one character, so we take the first index of the string
	if (temp == '+' || temp == '-' || temp == '*' || temp == '/') 
	{
		return temp;
	}
	else
		return 'n';	// returns n if its an operand, a.k.a. a number
}
