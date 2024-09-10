#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int binarium(unsigned short int byt5, int n) {
	byt5 = byt5 | ((1 << abs(n-7)));
	cout << bitset <8>(byt5) << endl;
	return byt5;
}

int main() {
	int x, p;
	unsigned short int posl = 0b00000000;
	cout << bitset <8>(posl) << endl;
	
	cout << "Enter number of nums: ";
	cin >> p;
	int list[p];
	for (int i = 0; i < p; i++) {
		cout << "Enter number: ";
		cin >> x;
		posl = binarium(posl, x);
	}
	cout <<  bitset <8>(posl) << endl;
}