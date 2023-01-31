#ifndef BSTSET_H_
#define BSTSET_H_
#include <iostream>
#include "TNode.h"
#include <vector>

class BSTSet
{
private:
    // must contain only one private field
    TNode* root = NULL;
    int n = 0;
    int length;

public:
    // required constructors/destructor
    BSTSet();
    BSTSet(const std::vector<int>& input);
    ~BSTSet();

    // required methods
    bool isIn_rec(int v, TNode*& t);
    bool isIn(int v);
    void add_rec(int v, TNode*& t);
    void add(int v);
    bool remove(int v);
    void Union(const BSTSet& s);
    void intersection(const BSTSet& s);
    void difference(const BSTSet& s);
    int size_rec(TNode*& t);
    int size();
    int height_rec(TNode*& t);
    int height();
    void printNonRec(); // create and use class MyStack

    // provided recursive print method
    void printBSTSet();

    // Used for testing
    TNode* getRoot()
    {
        return root;
    }

private:
    // provided helper methods
    void printBSTSet(TNode* t);
};

#endif /* BSTSET_H_ */