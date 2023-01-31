#include "integerVector.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
using namespace std;

integerVector::integerVector(const std::string& val) {
	// TODO
	int i = 0;
	if((val[0] >= '0') && (val[0] <= '9')){ //Looking for valid numbers within the string
		isNeg = false;
	}
	else if (val[0] == 45) //Checking if a -ve in the beginning of the string
	{
		isNeg = true;
	}
	else
	{
		throw("Error occurred."); //In case the string is empty
	}
	for (int i = 1; i < val.length(); i++) //For loop goes through val checking if there are only numbers
	{
		if (!(val[i] >= '0' && val[i] <= '9')) //if any elements arent a valid digit, throw error
		{
			throw("Error occurred");
		}
	}
	for(int y = 0; y < val.length(); y++)
	{
		if (!(y==0 && isNeg)) //Pushes the string values into the vector while skipping the negative sign at the start
		{
			int x = val[y] - '0';
			integerVector.push_back(x);
		}
	}
}

integerVector::integerVector(int n) {
	// TODO
	int i = 0;
	int digit;
	(srand(time(0))); //To make truly random digits, use srand
	int neg = (rand()%2);//randomly assigns negative int value
	if(n<=0){
		throw("N is less than 0. Error");
	}

	for(i=0;i < n;i++){//loops and inputs a random integer into each element of the vector
		digit = 1 + (rand() % 9);
		integerVector.push_back(digit);
	}
}

integerVector integerVector::add(const integerVector& h) {
	// TODO

	int carry = 0;
	int temp = 0;
	string sum = "";
	int i = 0;
	int j = 0;


	if (integerVector.size() >= h.integerVector.size()) {//Checks which vector is the biggest to use for addition
		i = integerVector.size() - 1;
		j = h.integerVector.size() - 1;
		while (j >= 0) { // reverse iterates from the back of the vector and adds elements from both vectors and saves them
			temp= integerVector[i] + h.integerVector[j] + carry;/
			sum = to_string((temp% 10)) + sum; //if the sum is greater than 9,use the modulus and input that into the sum
			carry = temp/ 10; //save the extra digit from the double digit value
			i--;
			j--;
		}
		while (i >= 0) {
			temp= integerVector[i] + carry; //reverse iterates and saves any leftover carries
			sum = to_string((temp% 10)) + sum;
			carry = temp/ 10;
			i--;
		}
	} else {
		i = h.integerVector.size() - 1;
		j = integerVector.size() - 1;

		while (j >= 0) {
			temp= h.integerVector[i] + integerVector[j] + carry;
			sum = to_string((temp% 10)) + sum;
			carry = temp/ 10;

			i--;
			j--;
		}
		while (i >= 0) {
			temp= h.integerVector[i] + carry;
			sum = to_string((temp% 10)) + sum;
			carry = temp/ 10;
			i--;
		}
	}
	if (carry){
		sum = "1" + sum;
	}
	return integerVector(sum);

}
integerVector integerVector::subtract(const integerVector& h) {
	// TODO

	int n = integerVector.size();
	int m = h.integerVector.size();


	int l = 0;
	int carry = 0;
	std::string sum = "";



	int diff = 0;
	int j = 0;
	int i = 0;


	if ((integerVector == h.integerVector) && (isNeg == h.isNeg)) {
		return integerVector("0");
	}

	if (integerVector[0] == 0 && h.isNeg == true) {  //0-4 = -4
		for (auto i = h.integerVector.begin(); i != h.integerVector.end(); i++) {
			sum += std::to_string(*i);
		}
		sum = "-" + sum;

		return integerVector(sum);
	}


	if (n >= m) {
		i = n - 1;
		j = m - 1;
		diff = n - m;

		while (j >= 0) { //locates the smallest array first
			l= integerVector[j + diff] - h.integerVector[j] - carry;
			if (l< 0) {
				l= l+ 10;
				carry = 1;
			}
			else
				carry = 0;
			sum = std::to_string((s)) + sum;
			j--;

		}

		for (int i = n- m - 1; i >= 0; i--) {
			if (integerVector[i] == 0 && carry) {
				l= 9;
				sum = std::to_string((s)) + sum;
				continue;
			}
			int l= (integerVector[i] - carry);
			if (i > 0 || l> 0)
				sum = std::to_string((s)) + sum;
			carry = 0;
		}
	}
	else {
		i = m - 1;
		j = n - 1;
		diff = m - n;
		while (j >= 0) {

			l= h.integerVector[j + diff] - integerVector[j] - carry;
			if (l< 0) {
				l= l+ 10;
				carry = 1;
			}
			else
				carry = 0;
			sum = std::to_string((s)) + sum;
			j--;

		}

		for (int i = m - n - 1; i >= 0; i--) {
			if (h.integerVector[i] == 0 && carry) {
				l= 9;
				sum = std::to_string((s)) + sum;
				continue;
			}
			int l= ((h.integerVector[i]) - carry);
			if (i > 0 || l> 0) { // remove  0's
				sum = std::to_string(s) + sum;
			}
			carry = 0;
		}
	}

	if (isNeg == true && h.isNeg == true) {
		if (compareTo(h) == -1) {
			sum = "-" + sum;
		}
	}

	if (isNeg == false && h.isNeg == true) {
		isNeg = true;
		integerVector output = add(h);
		output.isNeg = false;
		return output;
	}

	if (isNeg == false && h.isNeg == false) {
		//Used in situations where -5 - -2
		if (compareTo(h) == -1) {
			sum = "-" + sum;
		}
	}

	if (isNeg == true && h.isNeg == false) {
		integerVector h2 = h;
		h2.isNeg = true;
		integerVector output = add(h2);
		output.isNeg = true;
		return output;
	}
	if (sum[0] == '0') {
		sum.erase(0, sum.find_first_not_of('0'));
	}
	else if (sum[0] == '-') {
		sum.erase(0, 1);
		sum.erase(0, sum.find_first_not_of('0'));
		sum.insert(0, 1, '-');
	}


	return integerVector(sum);
}

integerVector integerVector::multiply(const integerVector& h) {
	// TODO

	int l= 0;
	int carry = 0;
	std::string sum = "";


	int n = integerVector.size();
	int m = h.integerVector.size();

	int i_hugeInt = 0;
	int i_h = 0;

	std::vector<int> output(n + m, 0);

	if (integerVector[0] == 0 || h.integerVector[0] == 0) {
		return integerVector("0");
	}

	//iterates from right to left
	for (int i = n - 1; i >= 0; i--){
		carry = 0;
		i_h = 0;

		for (int j = m - 1; j >= 0; j--){

			//Multiples by the first digit in vector and adds result
			l= integerVector[i] * h.integerVector[j] + output[i_hugeInt + i_h] + carry;

			//Carry
			carry = l/ 10;


			output[i_hugeInt + i_h] = l% 10;

			i_h++;
		}

		if (carry > 0) {
			output[i_hugeInt + i_h] += carry;
		}
		i_hugeInt++;
	}


	int k = output.size() - 1;
	while (k >= 0 && output[k] == 0) {
			k--;
	}
	//situations where vector is empty
	if (k == -1) {
		return 0;
	}

	//Outputs the final string

	while (k >= 0) {
		sum += std::to_string(output[k--]);
	}

	if (isNeg == false && h.isNeg == true) { //if num is + and h is -
		sum = "-" + sum;
	}
	else if (h.isNeg == false && isNeg == true) {
		sum = "-" + sum;
	}


	return integerVector(sum);
}

int integerVector::compareTo(const integerVector& h) {
	// TODO

	int result = 0;

	if (this->isNeg == true && h.isNeg == false) {
		return 1;
	}
	else if (this->isNeg == false && h.isNeg == true) {
		return -1;
	}

	if (h.integerVector.size() > integerVector.size()) {
		result = -1;
		//if both neg
		if (this->isNeg == false && h.isNeg == false) {
			result = 1;
		}
		return result;
	}
	else if (h.integerVector.size() < integerVector.size()) {
		result = 1;
		if (this->isNeg == false && h.isNeg == false) {
			result = -1;
		}
		return result;
	}
	if (h.integerVector.size() == integerVector.size()) {
		int result = 0;
		//if both positive
		if (integerVector[0] > h.integerVector[0]) {
			result = 1;
			//if both negative while also being the same size
			if (this->isNeg == false && h.isNeg == false) {
				result = -1;
			}
			return result;
		}
		else if (integerVector[0] < h.integerVector[0]) {
			result = -1;
			if (this->isNeg == false && h.isNeg == false) {
				result = 1;
			}
			return result;
		}

		if (integerVector[0] == h.integerVector[0]) {

			for (int i = 1; i < h.integerVector.size(); i++) {
				if (integerVector[i] > h.integerVector[i]) {
					result = 1;
					if (this->isNeg == false && h.isNeg == false) {
						result = -1;
					}
					return result;
				}
				else if (integerVector[i] < h.integerVector[i]) {
					result = -1;
					if (this->isNeg == false && h.isNeg == false) {
						result = 1;
					}
					return result;
				}
				else if (integerVector[i] == h.integerVector[i]) {
					continue;
				}
			}
		}
	}
	return result;
}


std::string integerVector::toString() {
	// TODO
	string Output = ""; //creates an empty string
	if(isNeg){ //if the boolean from earlier returns true add '-' value at the front of the string
		Output += ("-");
	}
	for(auto z = integerVector.begin(); z != integerVector.end(); z++){
		Output += to_string(*z); //Inputs the rest of the vector into the string
	}
	return Output;
}
