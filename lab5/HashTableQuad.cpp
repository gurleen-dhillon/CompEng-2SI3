#include "HashTableQuad.h"
#include <iostream>
using namespace std;


bool HashTableQuad::checkPrime(int n) {
	if (n <= 1) {
		return false;
	}
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}


int HashTableQuad::prime(int n) {
	while (true) {
		if (checkPrime(n) == true) { return n; }
		n++;
	}
}


HashTableQuad::HashTableQuad(int maxNum, double load)
{
	numKeys = 0;
	maxLoad = load;
	size = maxNum;
	int size = (int)ceil(maxNum / load);
	size = prime(size);
	//temp 0 fill in
	for (int i = 0; i < size; i++) {
		table.push_back(0);
	}
}



void HashTableQuad::insert(int n)
{
	if (isIn(n) == false) {
		numKeys++;
		double numKeys_temp = numKeys;
		double tabSize_temp = table.size();
		double loadFac = (numKeys_temp / tabSize_temp);
		if (loadFac > maxLoad) {
			//if ((numKeys / table.size()) > maxLoad) {
			rehash();
		}
		int i = n % table.size();
		int j = i;
		int count = 0;
		//collision check going through table
		while (table[i] != 0 && count < table.size()) {
			count++;
			i = (j + count*count) % table.size();//increment
		}
		if (count < table.size()) {
			table[i] = n;
			numKeys++;
		}
	}
}


void HashTableQuad::rehash()
{
    vector<int> temp = table;
    int newTableSize = prime(2 * table.size());
    //change original table size
    vector<int> new_table(newTableSize, 0);
    table = new_table;
    numKeys = 1;
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] != 0) {
            insert(temp[i]);
        }
    }
}


bool HashTableQuad::isIn(int n)
{
	int i = n % table.size();
	int j = i;
	int count = 0;
	for (int k = 0; k < table.size(); k++) {
	    if (table[i] != 0 && table[i] == n) {
	        return true;
	    }
		count = count + 1;
		i = (j + count*count) % table.size(); //increment
	}
	return false;
}


void HashTableQuad::printKeys()
{
	for (int i = 0; i < table.size(); i++) {
		cout << table[i] << " ";
	}
}


void HashTableQuad::printKeysAndIndexes()
{
	for (int i = 0; i < table.size(); i++) {
		cout << "array index: " << i << "; key: " << table[i] << " ";
	}
}


int HashTableQuad::getNumKeys() { return numKeys; }
int HashTableQuad::getTableSize() { return table.size();; }
double HashTableQuad::getMaxLoadFactor() { return maxLoad; }


std::vector<double> HashTableQuad::simProbeSuccess()
{
	double keyIns = 0;
	double tot = 0;
	int i = 0;
	int num = 100000;

	vector<double> result(9);
	vector<int> probeCount(0);

	for (double l = 0.1; l <= 0.9; l = l + 0.1) {
		HashTableQuad temp = HashTableQuad(num, l);
		tot = 0;

		for (int j = 0; j < num; j++) {
			int probes = temp.count(rand());
			if (probes != 0) {
				probeCount.push_back(probes);
				keyIns++;
			}
		}
		for (int k = 0; k < probeCount.size(); k++) {
			tot += probeCount[k];
		}
		result[i] = tot / keyIns;
		i++;
	}
	return result;
}


int HashTableQuad::count(int n) {
	int insertCount = 0;
	if (isIn(n) == false) {
		if ((numKeys / size) > maxLoad) {
			rehash();
		}
		int index = n % table.size();
		int original_Index = index;
		int count = 0;
		for (int i = 0; i < table.size(); i++) {
			//collisions
			while (table[index] != 0 && count < table.size()) {
				count++;
				index = (original_Index + count * count) % table.size();
				insertCount++;
			}
		}
		if (count < table.size()) {
			this->numKeys = numKeys + 1;
			this->table[index] = n;
		}
	}
	return insertCount;
}