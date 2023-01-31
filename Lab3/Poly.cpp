#include "Poly.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;


//big theta(n)
Poly::Poly()
{
	head = new PolyNode(-1, 0, NULL);
	size = 0;
}


//beg theta(n)
Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
    for (int j = deg.size(); j > 0; j--){
    	PolyNode *newNode = new	PolyNode (deg[j-1], coeff[j-1], head);
    	head = newNode;
    }
    size = deg.size();
    PolyNode *s = head;
    head = new PolyNode (-1, 0, s);
}



//big theta(n)
Poly::~Poly()
{
    PolyNode* temp;
    while (head -> next){
    	temp = head -> next;
    	head -> next = temp -> next;
    	free(temp);
	}
}

/*
//big theta(n)
void Poly::addMono(int i, double c)
{
    if (c == 0 || getTermsNo() == 0){ return; }

    PolyNode *newNodeHead = head;
    PolyNode *newNode = head->next;

    while(newNode){
    	if (newNode->deg == i){
    		if (newNode->coeff + c == 0){
    			newNodeHead->next = newNode->next;
    			size--;
    		}
    		else{
    			newNode->coeff += c;
    			size++;
    		}
    	}
    	else if (newNode->deg > i && newNode->next == NULL){
    		newNode->next = new PolyNode (i, c, NULL);
    		size++;
		}
    	else if (newNodeHead->deg > i && newNode->deg < i){
    		newNodeHead->next = new PolyNode(i ,c, newNode);
    		size++;
		}
    	newNode = newNode->next;
    }
}*/



//big theta(n)
void Poly::addPoly(const Poly& p)
{
	PolyNode *newNode = p.head->next;
    while(newNode){
    	addMono(newNode->deg, newNode->coeff);
    	newNode = newNode->next;
    }
}



void Poly::multiplyMono(int i, double c)
{
	if (c == 0){ head->next = NULL; }

	PolyNode *newNode = head->next;
	while (newNode){
		newNode->coeff *= c;
		newNode->deg += i;
		newNode = newNode->next;
	}
}



void Poly::multiplyPoly(const Poly& p)
{
    PolyNode *newNode = p.head->next;
    Poly tempMult = Poly();
    Poly tempAdd = Poly();

    while(newNode){
    	this->duplicate(tempMult);
    	tempMult.multiplyMono(newNode->deg, newNode->coeff);
    	tempAdd.addPoly(tempMult);
		newNode = newNode->next;
    }
    tempAdd.duplicate(*this);
}



void Poly::duplicate(Poly& outputPoly)
{
    if(head->next == NULL){outputPoly.head->next = NULL; }
    PolyNode *newNodeHead = outputPoly.head;
    PolyNode *newNode = head->next;
	while(newNode){
		newNodeHead->next = new PolyNode(newNode->deg, newNode->coeff, NULL);
		newNodeHead = newNodeHead->next;
    	newNode = newNode->next;
    }
}



int Poly::getDegree()
{
    if (head->next == NULL){
    	return -1;
    }
    int output = head->next->deg;
    return output;
}



int Poly::getTermsNo()
{
    if(head->next == NULL){
    	return 0;
    }
    int output = 0;
    PolyNode *newNode = head->next;
    while(newNode){
    	newNode = newNode->next;
    	output++;
    }
    return output;
}



double Poly::evaluate(double x)
{
    PolyNode* newNode = head->next;
    double output = 0;
    for(int i = 0; i < getTermsNo(); i++){
    	output += newNode->coeff*pow(x, newNode->deg);
    	newNode = newNode->next;
    }
    return output;
}



std::string Poly::toString()
{
	return "";
    /*string output = "";
    PolyNode* newNode = head->next;
    output = ("degree = ") + newNode->deg + ("; ");
    while (newNode){
    	output += ("a(") + newNode->deg + (") = ") + coeff + ("; ");
    	newNode = newNode->next;
    }
    return output;*/
}



















void Poly::addMono(int i, double c) { //big theta n
// TODO
    if(c==0){
        return;    //nothing happens
    }

    if(getTermsNo()==0){    //empty poly
        head->next = new PolyNode(i,c,NULL);
        return;
    }


    PolyNode *prev = head;

    for(PolyNode *thisnode = head->next; thisnode != NULL; thisnode = thisnode->next){

        if(i == thisnode->deg){ //when the input degree is the same as this term degree
            if (thisnode->coeff + c == 0){//case where coeffecients add to zero
                prev->next = thisnode->next;
                size--;
            }
            else{ //add
                thisnode->coeff = thisnode->coeff + c;
                size++;
            }
            return;
        }

        else if(i > thisnode->deg){
            prev->next = new PolyNode(i,c,thisnode);
            size++;
            return;
        }

        else if (thisnode->next == NULL && i < thisnode->deg){    //new smallest degree
            thisnode->next = new PolyNode(i,c,NULL);
            size++;
            return;
        }

        prev = thisnode;
    }

}
