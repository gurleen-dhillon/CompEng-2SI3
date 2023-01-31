#include "HugeInteger.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;



HugeInteger::HugeInteger(const std::string& val) {
    if (val[0] == '-'){ isNeg = true; } //check if isNeg
    else if ((val[0] >= '0') && (val[0] <= '9')){ isNeg = false; } //check if number present
    else { throw("error"); } //if error in string

    //if any other value in string is not a valid number
    for (int i = 1; i < val.length(); i++){
        if (!(val[i] >= '0' && val[i] <= '9')){
            throw("error");
        }
    }

    for(int j = 0; j < val.length(); j++) {
        //skips negative sign when pushing values into vector
        if (!(j==0 && isNeg)) {
            int x = val[j] - '0';
            intVec.push_back(x);
        }
    }
}



HugeInteger::HugeInteger(int n) {
    //if n is smaller than or not equal to 1
    if(n <= 0){
        throw("n is not larger than 1");
    }

    int number;
    (srand(time(0)));
    isNeg = (rand() % 2); //if number will be isNegative

    for(int i = 0; i < n; i++){
        if (i == 0) { number = 1 + (rand() % 9); } //to avoid getting 0 as first digit
        else { number = (rand() % 10); } //random numbers between 0-9 for rest of the digits
        intVec.push_back(number);
    }
}



HugeInteger HugeInteger::add(const HugeInteger& h) {
    int n;
    //to make both of them the same size
    if (intVec.size() > h.intVec.size()){
        n = intVec.size() - h.intVec.size();
        for (int c = 0; c < n; c++){ h.intVec.insert (h.intVec.begin(), 0); }
    }
    else if (h.intVec.size() > intVec.size()){
        n = h.intVec.size() - intVec.size();
        for (int c = 0; c < n; c++){ intVec.insert (intVec.begin(), 0); }
    }

    int i = intVec.size() - 1; //size of one vector since both are the same size now
    int carry = 0;
    int temp = 0;
    string sum = "";

    //addition
    while (i >= 0) {
        temp = h.intVec[i] + intVec[i] + carry; //add all numbers in last column
        //sum.insert (sum.begin(), (temp % 10)); //insert last digit of sum into start of vector
        sum = to_string(temp % 10) + sum;
        carry = temp / 10; //carry over any other values to the next column
        i--; //remove last column
    }

    //if there is a carry left behind after sum
    if (carry){
        //sum.insert (sum.begin(), carry);
        sum = "1" + sum;
    }

    return HugeInteger(sum);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


HugeInteger HugeInteger::subtract(const HugeInteger& h) {
    if (intVec.size() > h.intVec.size()){
        n = intVec.size() - h.intVec.size();
        for (int c = 0; c < n; c++){ h.intVec.insert (h.intVec.begin(), 0); }
    }
    else if (h.intVec.size() > intVec.size()){
        n = h.intVec.size() - intVec.size();
        for (int c = 0; c < n; c++){ intVec.insert (intVec.begin(), 0); }
    }

    int i = intVec.size() - 1; //size of one vector since both are the same size now
    int carry = 0;
    std::string diff = "";

    if (intVec == h.intVec) { return HugeInteger("0"); } //intVec and h are the same number
    if (h.intVec == 0) { return HugeInteger(intVec); } //if h is 0

    //if intVec is 0
    if (intVec[0] == 0) {

    	return HugeInteger(-h.intVec);
    }



	int n = intVec.size();
	int m = h.intVec.size();

	int l = 0;
	int carry = 0;
	std::string sum = "";

	int diff = 0;
	int j = 0;
	int i = 0;

	if ((intVec == h.intVec) && (isNeg == h.isNeg)) {
		return HugeInteger("0");
	}

	if (intVec[0] == 0 && h.isNeg == true) {  //0-4 = -4
		for (auto i = h.intVec.begin(); i != h.intVec.end(); i++) {
			sum += std::to_string(*i);
		}
		sum = "-" + sum;
		return HugeInteger(sum);
	}

	if (n >= m) {
		i = n - 1;
		j = m - 1;
		diff = n - m;

		while (j >= 0) { //locates the smallest array first
			l= intVec[j + diff] - h.intVec[j] - carry;
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

			l= h.intVec[j + diff] - intVec[j] - carry;
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
			if (h.intVec[i] == 0 && carry) {
				l= 9;
				sum = std::to_string((s)) + sum;
				continue;
			}
			int l= ((h.intVec[i]) - carry);
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
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

		return HugeInteger(sum);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int HugeInteger::compareTo(const HugeInteger& h) {
	int result = 0;

	if (this->isNeg == true && h.isNeg == false){ return 1; }
	else if (this->isNeg == false && h.isNeg == true){ return -1; }

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::string HugeInteger::toString() {
    string output = "";
    if(isNeg){ output += ("-"); } //if number was negative
    //Inputs the rest of the vector into the string
    for (int i = 0; i < intVec.size(); i++){
        output += to_string(intVec[i]);
    }
    return output;
}
