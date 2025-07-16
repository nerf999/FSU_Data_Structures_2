#include <iostream>
#include <string>
#include<stack>
#include <sstream>

using namespace std;

class BET{

private:

struct BinaryNode {
        string element; 
        BinaryNode* left;    
        BinaryNode* right; 



	 BinaryNode(const std::string& theElement, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
            : element(theElement), left(lt), right(rt) {}

        BinaryNode(std::string&& theElement, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
            : element(std::move(theElement)), left(lt), right(rt) {}
        
    };

BinaryNode* root;  //start of the tree


void makeEmpty(BinaryNode* &t); // deletes tree values 
BinaryNode* clone(BinaryNode *t) const; // makes another tree
bool isOperator(const string& t)const; // checks if string is a single operator
bool isOperand(const string& t);     // checks if string is a single operand
size_t size(BinaryNode *t) const; // checks size of tree
size_t leaf_nodes(BinaryNode *t) const; // checks amount of leaf nodes 
bool treeCheck(stack <BinaryNode*>&  S); // checks postfix expression was correct by checking the tree
void printPostfixExpression(BinaryNode *n) const; // prints postfix expression from tree
void printInfixExpression(BinaryNode *n) const; // prints infix expression from tree



public:

BET(); // default constructor
BET(const string& postfix); // constructor with parameter
~BET(); // destructor
BET(const BET&); // copy constructor 
const BET& operator=(const BET&); // assignment operator
bool empty() const;// checks if tree is empty 
size_t size() const; // returns amount of nodes
size_t leaf_nodes() const; // returns amount of leaf nodes 
bool buildFromPostfix(const string& postfix);// builds tree from postfix expression
void printPostfixExpression() const; // prints postfix expression from tree
void printInfixExpression() const; // prints infix expression from tree
void makeEmpty();

};
