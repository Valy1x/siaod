#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream file;          // поток для записи
	file.open("numbers.txt");      // открываем файл для записи
	vector<unsigned char> list(8, 0);
	while (!file.eof()) {
		file >> x;
	}
}