#include <iostream>
#include <string>
#include<stack>
#include <sstream>
#include "bet.h"

using namespace std;


BET::BET(){

root = nullptr;

}



bool BET::buildFromPostfix(const string& postfix) {


       makeEmpty(root); // empty tree
        bool status = false;
        stack <BinaryNode*> S; // set stack
        istringstream tokens(postfix); // string stream for postfix string
        string token; // individual postifx tokens

        while(tokens >> token)
        {
                if (isOperand(token))  // if token is operand put on stack 
                {
                S.push(new BinaryNode(token));
                } 
                else if (isOperator(token))  // if token is operator make new tree to stack
                {
                BinaryNode* right = S.top(); S.pop();
                BinaryNode* left = S.top(); S.pop();

                S.push(new BinaryNode(token, left, right));
                }                       

         }
  if(!S.empty())  // if stack not empty root become top of stack
         {               
         root = S.top();
         }
         else
         {
         root = nullptr;
         }

        status = treeCheck(S);  // check is tree is correct
        if (status == false) 
        {
        cout << "Cannot build the tree based on " << postfix << endl;
        }

       if (status == true)
	cout << "Successfully built the tree given " << postfix << endl;

  return status;
}


bool BET::treeCheck(stack <BinaryNode*>&  S){

    if (!S.empty() && S.size() == 1)  // if tree has a single node then tree is correct
     {
        
        root = S.top(); S.pop();
        return true;
        } 
	else 
	{
        while (!S.empty())  // if tree doesnt have a single node then postfix expression was invalid 
	{                   // delete stack and sets root to nullptr
            delete S.top();
            S.pop();
        }
        root = nullptr; 
        return false;
    }


}

BET::BET(const string& postfix) : root(nullptr){

	bool status;

    status = buildFromPostfix(postfix); //builds tree from postfix expression


}


void BET::makeEmpty(BinaryNode* &t){


	if(t != nullptr) // if tree is not nullptr delte tree

	{
		makeEmpty (t->left); // goes down left side of tree

		makeEmpty (t -> right); // goes down right side of tree
		
		delete t; // deletes t


	}
	t = nullptr; // sets t to nullptr

}

void BET::makeEmpty(){

makeEmpty(root); //calls make empty on root

}



const BET& BET::operator=(const BET& rhs){
   

 if (this != &rhs) // checks for self assignment 
    {
	if (root != nullptr) // if root isnt nullptr empties tree
	{
		makeEmpty();
	
	}

	root = clone(rhs.root); // clones rhs.root 

  }
  return *this; // returns this 
}

BET::~BET(){

	makeEmpty(); // calls make empty

}

BET::BET(const BET& rhs) :root{nullptr} {

	root = clone(rhs.root); // calls clone

}

BET::BinaryNode* BET::clone(BinaryNode *t) const{

	// if tree is empty return nullptr
	if (t == nullptr)  
		return nullptr;

	else           
		return new BinaryNode{ t->element,
clone( t->left), clone( t-> right ) };
// returns tree with same values as passed in node
}


bool BET::empty() const {
    return root == nullptr; // checks if root is nullptr 
}

bool BET::isOperator(const string& t) const{

        bool status = false; // set status to false

	// if string is an operator sets status to true 
	if(t == "+")
	  status = true;

	if(t == "-")
	   status = true;

	if(t == "*")
          status = true;
		
        if(t == "/")
          status = true;

	return status;
}

bool BET::isOperand(const string& t){

	return !isOperator(t);// checks if operand by checking if it isnt a operator 
}


size_t BET::size() const{

return size(root); // calls size


}

size_t BET::size(BinaryNode *t) const{

	int nodes;
	
	if (t ==nullptr)  // if t is nullptr return 0 
	{
	return 0;
	}
	else
	{

	nodes = 1 + size(t -> left) + size(t->right); 
	return nodes; // adds 1 for every node found down the tree
	}

}

size_t BET::leaf_nodes(BinaryNode *t) const
{
  if (t == nullptr) // if t is nullptr returns 0
        {
        return 0;
        }
        else if (t->left == nullptr&& t->right == nullptr) // if t has nullptr children it is a leaf so return 1
          {         
          return 1;     
          }
          else  
        {       
        return leaf_nodes(t->left) + leaf_nodes(t->right); // if all leafs counted return val
        
 	}

}

size_t BET::leaf_nodes() const
{

	return leaf_nodes(root); // calls leaf nodes
}


void BET::printPostfixExpression(BinaryNode *n) const{

	if (n == nullptr) // if node is null ptr return
	{
	return;
	}


	// goes down down children of tree starting left 
	printPostfixExpression(n ->left);
	printPostfixExpression(n -> right);

	cout << n ->element << " "; // prints element

}


void BET:: printPostfixExpression() const{

	printPostfixExpression(root); // calls print function 

        cout << endl; // ends line

}

void BET::printInfixExpression(BinaryNode *n) const {
    if (n == nullptr) { // if nullptr return 
        return;
    }


	string val = n->element; // set string to element

    bool isAnOperator = isOperator(val); // check if val is an operator
    
    if (isAnOperator && n != root) { // if its not a root and its a operator start parenthesis 
        cout << "( ";
    }

    printInfixExpression(n->left);// goes down left of tree
    
     cout << n->element; // outputs value and space
     cout << " ";
    
    printInfixExpression(n->right); // goes down right of tree

    if (isAnOperator && n != root) {
        std::cout << ")"; // ends parenthesis 
    }
}

void BET::printInfixExpression() const{

printInfixExpression(root);// calls print
cout << endl; // ends line


}
