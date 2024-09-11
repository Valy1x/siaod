#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

int main() {
    vector<unsigned char> list(8, 0);

    int num, n;
    cout << "Enter number of nums: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num;
        list[num / 8] |= (1 << (num % 8));
    }

    cout << "Sorted nums:" << endl;
    for (int i = 0; i < 64; i++) {
        if (list[i / 8] & (1 << (i % 8))) {
            cout << i << " ";
        }
    }
}
