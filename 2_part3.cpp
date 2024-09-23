#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>

using namespace std;

int main() {
	const int NUMBERS_COUNT = 10000000;
    bitset<10000000> numberSet;
    ifstream inputFile("5_1.txt");
    vector<unsigned char> megabite(1024, 0);
	vector<unsigned char> kilobite(1024, 0);
    vector<unsigned char> bite(8, 0);

    auto startTime = chrono::high_resolution_clock::now();
    unsigned int number;
    while (inputFile >> number) {
        megabite[number / 1024] = megabite[number / 8] | (1 << (number % 8));
    }

    inputFile.close();

    ofstream outputFile("output5_1.txt");
    for (int i = 0; i < NUMBERS_COUNT; i++) {
        if (numberSet.test(i)) {
            outputFile << i << endl;
        }
    }

    outputFile.close();

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedTime = endTime - startTime;
    cout << "Время выполнения: " << elapsedTime.count() << " секунд" << endl;

    vector<unsigned char> megabite(8, 0);
	vector<unsigned char> kilobite(8, 0);
    vector<unsigned char> bite(8, 0);

    unsigned int num, n;
    for (int i = 0; i < n; i++) {
        cin >> num;
        list[num / 8] = list[num / 8] | (1 << (num % 8));
    }

    cout << "Sorted nums:" << endl;
    for (int i = 0; i < 64; i++) {
        if (list[i / 8] & (1 << (i % 8))) {
            cout << i;
        }
    }
    return 0;
}
