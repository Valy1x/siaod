#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
	unsigned short int bytes = 0x02228;
	unsigned short int x, y, byt2, byt5;

	cout << "Start number: " << bitset <16>(bytes) << endl;
		// 1 пункт
	unsigned short int maska = 0b001010010000000;
	cout << "1st mask: " << bitset <16>(maska) << endl;
	cout << "Ones: " << bitset <16>(bytes | maska) << " " << (bytes | maska) << endl;
		// 2 пункт
	unsigned short int maska2 = 0b1100111111111111;
	cout << "Enter byt2: ";
	cin >> byt2;
	cout << "byt2: " << bitset <16>(byt2) << endl;
	cout << "2nd mask: " << bitset <16>(maska2) << endl;
	cout << "Twoes: " << bitset <16>(byt2 & maska2) << " " << (byt2 & maska2) << endl;
		// 3 пункт
	cout << "Enter byt3: ";
	cin >> x;
	cout << "byt3: " << bitset <16>(x) << endl;
	x = x << 4;
	cout << "Treas: " << " " << x << endl;
		// 4 пункт
	cout << "Enter byt4: ";
	cin >> y;
	cout << "byt4: " << bitset <16>(y) << endl;
	y = y >> 4;
	cout << "Fours: " <<  y << endl;
		// 5 пункт
	unsigned short int line = 0b0000000000000001;
	int n;
	cout << "Enter number of bit: ";
	cin >> n;
	cout << "Enter byt5: ";
	cin >> byt5;
	cout << "byt5: " << bitset <16>(byt5) << endl;
	byt5 = byt5 & (~(line << n));
	cout << "END: "<< bitset <16>(byt5) << " " << byt5 << endl;
	return 0;
}