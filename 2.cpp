#include <iostream>
#include <string>
#include <bitset>

// C:\Users\Valy1x\Documents\GitHub\siaod

using namespace std;

unsigned char binarium(unsigned char byt5, int n) {
	byt5 = byt5 | ((1 << n));
	return byt5;
}

int main() {
	int x, p;
	unsigned char posl = 00000000;
	cout << bitset <8>(posl) << endl;
	
	cout << "Enter number of nums: ";
	// cin >> p;
	cin >> x;
	posl = posl | ((1 << x));
	cout << bitset <8>(posl);
	int list[p];
	for (int i = 0; i < p; i++) {
		cout << "Enter number: ";
		cin >> x;
		posl = binarium(posl, x);
	}
	cout <<  bitset <8>(posl) << endl;
	for (int i = 0; i <= 7; i++) {
		if (posl & (1 << i)) {
			list[i] = i;
			cout << list[i];
		}
	}
}