#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>

using namespace std;

int main() {
	const int NUMBERS_COUNT = 10000000;
    bitset<10000000> numberSet;
    ifstream inputFile("unique_numbers.txt");

    auto startTime = chrono::high_resolution_clock::now();
    unsigned int number;
    while (inputFile >> number) {
        numberSet.set(number);
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
    cout << "Time: " << elapsedTime.count() << endl;

    return 0;
}
