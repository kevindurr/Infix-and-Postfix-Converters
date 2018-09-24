//Kevin Durr
#ifndef BET_H
#define BET_H
#include <iostream>
#include <string>

using namespace std;

struct BinaryNode       //Based off Textbook page 133 figure 4.16
{
    string element;     
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode( const string & theElement, BinaryNode *lt, BinaryNode *rt ) : element{ theElement }, left{ lt }, right{ rt } { }
    BinaryNode( string && theElement, BinaryNode *lt, BinaryNode *rt ): element{move( theElement ) }, left{ lt }, right{ rt } { }
};
class BET
{
public:
    BET();                                           //D: default zero-parameter constructor.
    BET(const string postfix);                           //T: one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space.
    BET(const BET &);                                //D: copy constructor.
    ~BET();                                          //D: destructor.
    bool buildFromPostfix(const string postfix); //T: parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
    
    const BET &operator=(const BET &);        //D: assignment operator.
    void printInfixExpression();   //D: call the private version of the printInfixExpression function to print out the infix expression.
    void printPostfixExpression(); //D: call the private version of the printPostfixExpression function to print out the postfix expression.
    size_t size();                 //D: call the  private version of the size function to return the number of nodes in the tree.
    size_t leaf_nodes();           //D: call the private version of the leaf_nodes function to return the number of leaf nodes in the tree.
    bool empty();                  //D: return true if the tree is empty. Return false otherwise.

//:Private interfaces (all the required private member functions must be implemented recursively)
private: 
    void printInfixExpression(BinaryNode *n);   //T: print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
    void makeEmpty(BinaryNode *&t);             //: delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
    BinaryNode *clone(BinaryNode *t) const;     //: clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.
    void printPostfixExpression(BinaryNode *n); //: print to the standard output the corresponding postfix expression.
    size_t size(BinaryNode *t);                 //: return the number of nodes in the subtree pointed to by t.
    size_t leaf_nodes(BinaryNode *t);           //: return the number of leaf nodes in the subtree pointed to by t.
    BinaryNode* root;                           //member data
};
#endif