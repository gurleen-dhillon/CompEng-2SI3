#include "HashTableLin.h"
#include <iostream>;
using namespace std;

HashTableLin::HashTableLin(int maxNum, double load)
{
	numKeys = 0;
	maxLoad = load;
	size = maxNum;
	int size = (int)ceil(maxNum / load);
	size = prime(size);
	for (int i = 0; i < size; i++) {
		table.push_back(0);
	}
}


//Best Case = O(1)
//O(n) - 1 for loop - worst case
bool HashTableLin::checkPrime(int n) {
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


//Best Case/Average Case = O(1)
//O(n) - 1 while loop - worst case
int HashTableLin::prime(int n) {
	while (true) {
		if (checkPrime(n) == true) { return n; }
		n++;
	}
}


//Best Case/Average Case = O(1)
//O(n) - 1 while loop - worst case
void HashTableLin::insert(int n)
{
	if (isIn(n) == false) {
		numKeys++;
		double numKeys_temp = numKeys;
		double tabSize_temp = table.size();
		double loadFac = numKeys_temp / tabSize_temp;
		if (loadFac > maxLoad) {
		//if ((numKeys / table.size()) > maxLoad) {
			rehash();
		}
		int i = n % table.size();
		if (table[i] == 0) {
			table[i] = n;
		}
		else {
			while (table[i] != 0 ) {
				i++;
				if (i == table.size()) {
					i = 0;
				}
			}
			table[i] = n;
		}
	}
}


//O(n) - 1 loop
void HashTableLin::rehash()
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


//O(n) - 1 loop
bool HashTableLin::isIn(int n)
{
	for (int i = 0; i < table.size(); i++) {
		if (table[i] == n) {
			return true;
		}
	}
	return false;
}


//O(n) - 1 loop
void HashTableLin::printKeys()
{
	for (int i = 0; i < table.size(); i++) {
		cout << table[i] << " ";
	}
}


//O(n) - 1 loop
void HashTableLin::printKeysAndIndexes()
{
	for (int i = 0; i < table.size(); i++) {
		cout << "array index: " << i << "; key: " << table[i] << " ";
	}
}


int HashTableLin::getNumKeys() { return numKeys; }
int HashTableLin::getTableSize() { return table.size(); }
double HashTableLin::getMaxLoadFactor() { return maxLoad; }


//simulation functions
std::vector<double> HashTableLin::simProbeSuccess()
{
	double keyIns = 0;
	double tot = 0;
	int i = 0;
	int n = 1000;

	vector<double> result(9);
	vector<int> probeCount(0);

	for (double l = 0.1; l <= 0.9; l = l + 0.1) {
		HashTableLin temp = HashTableLin(n, l);
		tot = 0;
		for (int j = 0; j < n; j++) {
			int probes = temp.count(rand());
			if (probes != 0) {
				probeCount.push_back(probes);
				keyIns++;
			}
		}
		for (int j = 0; j < probeCount.size(); j++) {
			tot += probeCount[j];
		}
		result[i] = tot/keyIns;
		i++;
	}
	return result;
}


int HashTableLin::count(int n) {
	int count = 0;
	if ((numKeys/size) > maxLoad) {
		rehash();
	}
	if (isIn(n) == false) {
		int i = n % table.size();
		for (int j = 0; j < table.size(); j++) {
			while (table[i] != 0) {
				i = (i+1) % table.size();
				count++;
			}
		}
		table[i] = n;
		numKeys++;
	}
	return count;
}


// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
	// TODO, change following code after completing this function
	vector<double> result(9);
	return result;
}