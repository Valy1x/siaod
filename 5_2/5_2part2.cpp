#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

struct BankAccount {
    int account_number;
    string name;
    string address;
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

void measureSearchTime(const string& binaryFileName, int key, int numRecords) {
    write_binary_file(binaryFileName, generate_data(numRecords));
    clock_t start = clock();

    BankAccount record = linearSearch(binaryFileName, key, numRecords);

    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;

    if (FLAG) {
        cout << "Found : " << record.account_number << ", " << record.name << ", " << record.address << endl;
    }
    else {
        cout << "Record with key " << key << " not found." << endl;
    }

    cout << fixed << setprecision(6);
    cout << "Time of looking through " << numRecords << " records: " << duration * 1000 << " millisec." << std::endl;
}

int main() {
    srand(time(0));

    int num_records = 10000;
    vector<BankAccount> data = generate_data(num_records);

    string binary_filename = "accounts.dat";

    // write_binary_file(binary_filename, data);

    cout << "\nReading binary file: " << endl;

    // BankAccount record = linearSearch("accounts.dat", 1003779);

    measureSearchTime("accounts.dat", 1022896, 100);
    measureSearchTime("accounts.dat", 1022896, 1000);
    measureSearchTime("accounts.dat", 1022896, 10000);

    return 0;
}
