//Kevin Durr
#include "bet.h"
#include <stack>
#include <cctype>
BET::BET() : root{nullptr} {}  // default zero-parameter constructor. Initialize root to nullptr
BET::BET(const string postfix) // call bool buildFromPostfix(const string postfix)
{
    buildFromPostfix(postfix);
}
BET::BET(const BET &rhs) : root{nullptr} // Based off textbook page 142 figure 4.28
{
    root = clone(rhs.root);
}
BET::~BET() // Based off textbook page 141 figure 4.27.
{
    makeEmpty(root); //Based off textbook = makeEmpty( );, but no zero parameter makempty member function
}
bool BET::buildFromPostfix(const string postfix) //follows similar format to proj3
{
    root = nullptr; // If the tree contains nodes before the function is called, you need to first delete the existing nodes

    stack<BinaryNode *> myStack;
    string input;
    int varcount = 0;

    for (size_t i = 0; i < postfix.size(); i++)
    {

        input.clear(); //clear string for next operand or operator
        if (isspace(postfix[i]))
        {
            continue; // cin.ignore(); Begins next iterations
        }
        /* else if (isalnum(postfix[i]))
        {
            while(isalnum(postfix[i]) && i < postfix.size())
            {
                input += postfix[i];
                i++;
            }
            varcount++;
            BinaryNode * temp = new BinaryNode{input, nullptr, nullptr};
            myStack.push(temp); //must push type binarynode into stack, not string.
        }*/
        else if (postfix[i] == '(' || postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
        {
            if (varcount < 2) //myStack.size() < 2 wont work. Needs internal operand counter for this error check
            {
                makeEmpty(root);
                cout << "Wrong postfix expression." << endl;
                return false;
            }
            varcount--;         //accounting that the two operands turn into one operand
            input = postfix[i]; //store operator on string
            BinaryNode *right = myStack.top();
            myStack.pop();
            BinaryNode *left = myStack.top();
            myStack.pop();
            BinaryNode *temp = new BinaryNode{input, left, right};
            myStack.push(temp); //must push type binarynode into stack, not string.
        }
        else //Different from proj3 where only isalnum() allowed. Now accepting anything other than operators as a variable including '? "" |'
        {
            //grab the entire operand
            while (!isspace(postfix[i]) && (i < postfix.size() && !(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')))
            {
                input += postfix[i];
                i++;
            }
            varcount++;
            BinaryNode *temp = new BinaryNode{input, nullptr, nullptr};     //creates leaf node
            myStack.push(temp); //must push type binarynode into stack, not string.
        }
    }
    root = myStack.top(); //the binary node stack is
    return true;
}
const BET &BET::operator=(const BET &rhs) //assignment operator
{
    root = clone(rhs.root);
    return *this;
}
void BET::printInfixExpression() // call private void printInfixExpression(BinaryNode *n) recursive function
{
    printInfixExpression(root);
    cout << endl; //formatting
}
void BET::printPostfixExpression() // call private void printPostfixExpression(BinaryNode *n) recursive function
{
    printPostfixExpression(root);
    cout << endl; //formatting
}
size_t BET::size() // call private size(BinaryNode *t) recursive function
{
    return size(root);
}
size_t BET::leaf_nodes() // call private leaf_nodes(BinaryNode *t) recursive function
{
    return leaf_nodes(root);
}
bool BET::empty() // call private size(BinaryNode *t) recursive function
{
    return (size(root) == 0);
}
//*************** PRIVATE ***************
void BET::printInfixExpression(BinaryNode *n) //Based off textbook example of inorder tree traversal printTree
{                                             //Lecture Note 11: Definition: left child, vertex, right child (recursive)
    if (n != nullptr)
    {
        if ((n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/") && (n != root))
            cout << "( ";
        //Lecture Note 11: Algorithm: depth-first search (visit between children)
        printInfixExpression(n->left);
        cout << n->element << " ";
        printInfixExpression(n->right);

        if ((n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/") && (n != root))
            cout << ") ";
    }
}
/*
void printTree( BinaryNode *t, ostream & out ) const       // Textbook inorder traversal example
    if ( t != nullptr )
    {
        printTree( t->left, out );
        out << t->element << endl;
        printTree( t->right, out );
    }
}
*/
void BET::printPostfixExpression(BinaryNode *n)     //based off postorder traversal
{
    if (n != nullptr)
    {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode *t)
{
    if (t == nullptr)       //exit condition
    {
        return 0;
    }
    else
        return (size(t->left) + 1 + size(t->right));
}
size_t BET::leaf_nodes(BinaryNode *t)
{
    if (t->left == nullptr)             //leaf nodes have no children, if it doesnt have a left it does not have a right
        return 1;
    else
        return leaf_nodes(t->left) + leaf_nodes(t->right);
}
void BET::makeEmpty(BinaryNode *&t) //Based off textbook page 141 figure 4.27.
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}
BinaryNode *BET::clone(BinaryNode *t) const //Based off textbook page 142 figure 4.28.
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}