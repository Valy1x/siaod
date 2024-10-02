#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

struct BankAccount {
    int account_number;
    string name;
    string address;
};

struct TableEntry {
    int key;
    long long int offset;
};

set<int> generate_unique_accounts(int num_accounts) {
    set<int> accounts;
    while (accounts.size() < num_accounts) {
        accounts.insert((rand() % 9000000 + 1000000));
    }
    return accounts;
}

vector<BankAccount> generate_data(int num_records) {
    set<int> accounts = generate_unique_accounts(num_records);
    vector<BankAccount> data;

    for (int account : accounts) {
        BankAccount record;
        record.account_number = account;
        record.name = "Name_" + to_string(account);
        record.address = "Adress_" + to_string(account);
        data.push_back(record);
    }
    return data;
}

void write_binary_file(const string& binary_filename, const vector<BankAccount>& data) {
    ofstream binary_file(binary_filename, ios::binary);

    if (!binary_file.is_open()) {
        cerr << "Error! Can't open file." << endl;
        return;
    }

    for (auto record : data) {
        binary_file.write(reinterpret_cast<const char*>(&record.account_number), sizeof(record.account_number));
        
        size_t name_len = record.name.size();
        binary_file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        binary_file.write(record.name.c_str(), name_len);
        
        size_t address_len = record.address.size();
        binary_file.write(reinterpret_cast<const char*>(&address_len), sizeof(address_len));
        binary_file.write(record.address.c_str(), address_len);
    }

    binary_file.close();
    cout << "Binary file " << binary_filename << " is made." << endl;
}

bool FLAG = false;
int NUM = 10;


int binarySearh(const vector<TableEntry>& data, int code) {
    int left;
    int right = NUM - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid].key == code) {
            return data[mid].offset;
        }
        else if (data[mid].key < code) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

bool readRecordAtOffset(const string& binaryFileName, streampos offset, BankAccount& record) {
    ifstream inFile(binaryFileName, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия бинарного файла." << endl;
        return false;
    }
        // Перемещаемся на заданное смещение
    inFile.seekg(offset);

    // Читаем запись
    inFile.read(reinterpret_cast<char*>(&record.account_number), sizeof(record.account_number));

    // Чтение имени
    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    record.name.resize(size);
    inFile.read(&record.name[0], size);

    // Чтение адреса
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    record.address.resize(size);
    inFile.read(&record.address[0], size);

    inFile.close();
    return true;
}

void createIndexTable(const string& binaryFileName, vector<TableEntry>& TableEntrys) {
    ifstream inFile(binaryFileName, ios::binary);
    if (!inFile) {
        cerr << "Ошибка открытия бинарного файла." << endl;
        return;
    }

    streampos offset;
    BankAccount record;
    while (inFile) {
        offset = inFile.tellg();

        if (!inFile.read(reinterpret_cast<char*>(&record.account_number), sizeof(record.account_number))) {
            break;
        }

        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        record.name.resize(size);
        inFile.read(&record.name[0], size);

        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        record.address.resize(size);
        inFile.read(&record.address[0], size);

        TableEntrys.push_back({record.account_number, offset});
    }

    inFile.close();
}

bool searchInIndexTable(const vector<TableEntry>& indexTable, int key, streampos& offset) {
    for (const auto& entry : indexTable) {
        if (entry.key == key) {
            offset = entry.offset;
            return true;
        }
    }
    return false;
}

BankAccount linearSearch(string binary_filename, int looking_number, int num_accounts) {
    ifstream binary_file(binary_filename, ios::binary);

    if (!binary_file.is_open()) {
        cerr << "Error! Can't open file." << endl;
    }

    for (int i = 0; i <= num_accounts; i++) {
        BankAccount record;

        binary_file.read(reinterpret_cast<char*>(&record.account_number), sizeof(record.account_number));
        
        size_t name_len;
        binary_file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        record.name.resize(name_len);
        binary_file.read(&record.name[0], name_len);

        size_t address_len;
        binary_file.read(reinterpret_cast<char*>(&address_len), sizeof(address_len));
        record.address.resize(address_len);
        binary_file.read(&record.address[0], address_len);

        if (record.account_number == looking_number) {
            binary_file.close();
            FLAG = true;
            return record;
        }
    }
    return {0, "0", "0"};
}

void measureSearchTime(const string& binaryFileName, int key, const vector<TableEntry>& indexTable, int numRecords) {
    BankAccount record;
    streampos offset;

    auto start = chrono::high_resolution_clock::now();

    bool foundInIndex = searchInIndexTable(indexTable, key, offset);
    if (foundInIndex) {
        readRecordAtOffset(binaryFileName, offset, record);
    }
    else {
        linearSearch(binaryFileName, key, numRecords);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Время поиска среди " << numRecords << " записей: " << duration.count() << " миллисекунд." << endl;
}

int main() {
    setlocale(0, "");
    string binaryFileName = "accounts.dat";

    vector<TableEntry> indexTable;
    createIndexTable(binaryFileName, indexTable);

    int searchKey = 14866;

    measureSearchTime(binaryFileName, searchKey, indexTable, 100);
    measureSearchTime(binaryFileName, searchKey, indexTable, 1000);
    measureSearchTime(binaryFileName, searchKey, indexTable, 10000);
}
