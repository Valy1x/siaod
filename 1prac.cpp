#include <iostream>
#include <bitset>

using namespace std;

int main() {
	unsigned short int bytes = 0x02228;
	unsigned short int x;
	unsigned short int y;
	cout << bitset <16>(bytes) << endl;
	unsigned short int maska = 0b001010010000000;
	cout << bitset <16>(maska) << endl;
	cout << bitset <16>(bytes | maska) << " " << (bytes | maska) << endl;
	unsigned short int maska2 = 0b1100111111111111;
	cout << bitset <16>(maska2) << endl;
	cout << bitset <16>(bytes & maska2) << " " << (bytes & maska2) << endl;
	cin >> x;
	x = x << 4;
	cout << x << endl;
	cin >> y;
	y = y >> 4;
	cout << y << endl;

	unsigned short int maska3 = 0b000000000000001;

	return 0;
}