#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <random>
#include <cstring>
#include <vector>

using namespace std;

struct human {
    int number;
    char name[20];
    char address[20];
};

// bool search_in_file(string& filename, int key, human& person, int records) {
//     ifstream file(filename, ios::binary);

//     int counter = 0;
//     while (counter < records && file.read(reinterpret_cast<char*>(&person.number), sizeof(person.number))) {
//         size_t size;
//         file.read(reinterpret_cast<char*>(&size), sizeof(size));
//         person.name.resize(size);
//         file.read(&preson.name[0], size);

//         // Чтение адреса
//         file.read(reinterpret_cast<char*>(&size), sizeof(size));
//         person.address.resize(size);
//         file.read(&person.address[0], size);

//         if (person.number == key) {
//             file.close();
//             return true; 
//         }
//         counter++;
//     }

//     inFile.close();
//     return false;
// }

vector<int> generateUniqueRandomNumbers(int count, int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    vector<int> numbers;
    while (numbers.size() < count) {
        int num = distrib(gen);
        numbers.push_back(num);
    }
    return numbers;
}

// void measureSearchTime(const string& binaryFileName, int key, int numRecords) {
//     Reader foundReader;

//     auto start = chrono::high_resolution_clock::now();

//     bool found = linearSearchInBinaryFile(binaryFileName, key, foundReader, numRecords);

//     auto end = chrono::high_resolution_clock::now();

//     chrono::duration<double, milli> duration = end - start;

//     if (found) {
//         cout << "Запись найдена: " << foundReader.ticketNumber << ", " << foundReader.fullName << ", " << foundReader.address << endl;
//     }
//     else {
//         cout << "Запись с ключом " << key << " не найдена." << endl;
//     }
//     cout << fixed << setprecision(6);
//     cout << "Время поиска среди " << numRecords << " записей: " << duration.count() << " миллисекунд." << endl;
// }




int main() {
    ofstream textFile("people.txt");
    vector<int> codes = generateUniqueRandomNumbers(10, 1000, 9999); // 10 уникальных кодов
    vector<string> adress = {"ad1", "ad2", "ad3", "ad4", "ad5", "ad6", "ad7", "ad8", "ad9", "ad10"}; 
    vector<string> names = {
        "name1", "name2", "name3", "name4", "name5",
        "name6", "name7", "name8", "name9", "name10"};

    for (int i = 0; i < 10; i++) {
        textFile << codes[i] << ": " << names[i] << ", " << adress[i] << endl;
    }    
    textFile.close();


    ifstream inputFile("people.txt");
    ofstream binaryFile("people.bin", ios::binary);
    vector<human> humans;
    string line;
    while (getline(inputFile, line)) {
        human uni;
        int pos = line.find(": ");
        strcpy_s(uni.number, stoi(line.substr(pos + 2, pos - (pos + 2))));
        int pos2 = line.find(",");
        uni.name = stoi(line.substr(pos + 2, pos2 - (pos + 2))); 
        strcpy_s(uni.address, line.substr(0, pos).c_str());
        humans.push_back(uni);
    }
    inputFile.close();
    for (const auto& uni : humans) {
        binaryFile.write(reinterpret_cast<const char*>(&uni), sizeof(human));
    }
    binaryFile.close();
}

// void zd2_2() {
//     setlocale(0, "");
//     string binaryFileName = "readers.dat";

//     int searchKey = 14866;

//     measureSearchTime(binaryFileName, searchKey, 100);
//     measureSearchTime(binaryFileName, searchKey, 1000);
//     measureSearchTime(binaryFileName, searchKey, 10000);
// }
