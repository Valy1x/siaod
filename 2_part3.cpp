#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const int NUMBERS_COUNT = 10000000;
    bitset<10000000> numberSet;
    ifstream inputFile("5_1.txt");

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
    cout << "Время выполнения: " << elapsedTime.count() << " секунд" << endl;

    return 0;
}
