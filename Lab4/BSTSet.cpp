#include "BSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

//create empty set
BSTSet::BSTSet()
{
    root = NULL;
    length = 0;
}

//set empty root, usses add to add in each element from string
BSTSet::BSTSet(const std::vector<int>& input)
{
    root = NULL;
    int length = (input.size());
    for (int i = 0; i < length; i++) {
        add(input[i]);
    }
}

//destroys tree
BSTSet::~BSTSet()
{
    //TNode* temp;
    //while (root) {
    //    temp = root;
    //    root = root->right;
    //    free(temp);
}


//compares v starting at root and comparing to children branches
bool BSTSet::isIn_rec(int v, TNode*& t) {
    if (t == NULL) {
        return false;
    }
    else if (v < t->element) {
        isIn_rec(v, t->left);
    }
    else if (v > t->element) {
        isIn_rec(v, t->right);
    }
    else if (t->element == v) {
        return true;
    }
}


//recursivly check if v is in set
bool BSTSet::isIn(int v)
{
    TNode* t = root;
    if (t == NULL) {
        return false;
    }
    else {
        return isIn_rec(v, t);
    }
}


//looking for empty slot using a similar method to isIn (checking children branches)
void BSTSet::add_rec(int v, TNode*& t) {
    if (t == NULL) {
        t = new TNode(v, NULL, NULL);
    }
    else if (v < t->element) {
        add_rec(v, t->left);
    }
    else if (v > t->element) {
        add_rec(v, t->right);
    }
}


//recursivly checking for a null spot
void BSTSet::add(int v)
{
    TNode* t = root;
    if (t == NULL) {
        root = new TNode(v, NULL, NULL);
    }
    else {
        add_rec(v, t);
    }
}


//
TNode* rec_remove(int v, TNode* t) {
    //if empty; put twice because of test case failure
    if (t == NULL) {
        return t;
    }
    //looking for element similar to add in isIn
    else if (v < t->element) {
        t->left = rec_remove(v, t->left);
    }
    else if (v > t->element) {
        t->right = rec_remove(v, t->right);
    }

    else {
        if (((t->left) == NULL) && ((t->right) == NULL)) { //no branches after root
            delete t;
            t = NULL;
            return t;
        }

        //to the right, if left is empty to look for element
        else if (t->left == NULL) {
            TNode* temp = t;
            t = t->right;
            delete temp;
            return t;
        }

        //the the left if right is empty to look for element
        else if (t->right == NULL) {
            TNode* temp = t;
            t = t->left;
            delete temp;
            return t;
        }

        //both branches; making sure the element after the enxt is not NULL (making sure u dont end up at Null)
        else {
            TNode* temp = t->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            t->element = temp->element;
            t->right = rec_remove(temp->element, t->right);
        }
    }
    return t;
}


//recursivly checking for element to remove
bool BSTSet::remove(int v)
{
    // TODO
    if (isIn(v) == false) {
        return false;
    }
    (root = rec_remove(v, root));
    return true;
}


//to interate through tree and save values into an array to be used in union, intersection, and difference 
vector<int> iterate(vector<int>& input, TNode* t) {
    if (t != NULL) {
        iterate(input, t->left);
        input.push_back(t->element);
        iterate(input, t->right);
    }
    return input;
}


// iterate through to save both trees and merging them together
void BSTSet::Union(const BSTSet& s)
{
    vector<int> vec;
    vec = iterate(vec, s.root);
    vec = iterate(vec, root);
    BSTSet temp = BSTSet(vec);
    root = temp.root;
}


//wosrt case is n^2 becaus eof nested for loop
void BSTSet::intersection(const BSTSet& s)
{
    vector<int> vecS;
    vector<int> vec;
    vector<int> same;
    vecS = iterate(vecS, s.root);
    vec = iterate(vec, root);
    //go through both arrays and if similar element exists, push it into the "same" array
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vecS.size(); j++) {
            if (vec[i] == vecS[j]) {
                same.push_back(vec[i]);
            }
        }
    }
    BSTSet temp = BSTSet(same);
    root = temp.root;
}


//worst case is n^2
//subtract all elements of s from original
void BSTSet::difference(const BSTSet& s)
{
    vector<int> vecS;
    vector<int> vec;
    vector<int> same;
    vecS = iterate(vecS, s.root);
    vec = iterate(vec, root);
    //go through both arrays and if similar element exists, push it into the "same" array
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vecS.size(); j++) {
            if (vec[i] == vecS[j]) {
                same.push_back(vec[i]);
            }
        }
    }

    //iterate through "same" to remove all similar elements from original
    BSTSet temp = BSTSet(vec);
    for (int i = 0; i < same.size(); i++) {
        temp.remove(same[i]);
    }
    root = temp.root;
}


//recursion to find size 
int BSTSet::size_rec(TNode*& t) {
    if (t == NULL) {
        return 0;
    }
    else {
        return(size_rec(t->left) + 1 + size_rec(t->right));
    }
}


//FIND SIZE
int BSTSet::size()
{
    TNode* t = root;
    if (t == NULL) {
        return NULL;
    }
    else {
        return size_rec(t);
    }
}

//recursivly find height
int BSTSet::height_rec(TNode*& t) {
    if (t == NULL) {
        return NULL;
    }
    else {
        int leftTreeHeight = height_rec(t->left);
        int rightTreeHeight = height_rec(t->right);

        //based on which side is greater
        if (leftTreeHeight > rightTreeHeight) {
            return(leftTreeHeight + 1);
        }
        else {
            return(rightTreeHeight + 1);
        }
    }
}

//keep going down
int BSTSet::height()
{
    TNode* t = root;
    if (t == NULL) {
        return -1;
    }
    else {
        return(height_rec(t) - 1);
    }
}


// create and use class MyStack
void BSTSet::printNonRec()
{
    ////initialize empty stack here
    //push(root);
    //currentNode = root->left;
    //while (size() != 0) {
    //	if (currentNode != NULL) {
    //		push(currentNode);
    //		currentNode = currentNode->left;
    //	}
    //	else if (currentNode == NULL && stack.size() != 0) {
    //		cout << (pop());
    //		currentNode = currentNode->right;
    //	}
    //	if (currentNode->left == NULL && currentNode->right == NULL) {
    //		cout << (pop());//prints root
    //		currentNode = root->right;
    //	}
    //}
}

//Do not modify 
void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}