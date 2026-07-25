#include<iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include<chrono>
using namespace std;
using namespace std::chrono;

struct Record {int id, number;};
Record* data = nullptr;
int N = 0;
bool isSorted = false;

void loadData(int n) {
    delete[] data;
    data = new Record[n];
    N = n;
    isSorted = false;
    for (int i = 0; i < n; i++) {
        data[i].id = i + 1;
        data[i].number = rand() % 1000000 + 1;
    }
}

void showRecords() {
    cout << "\n  Total records: " << N << "\n\n";
    for (int i = 0; i < N; i++) {
        cout << "  ID" << data[i].id
             << " : " << setw(8) << data[i].number << "  ";
        if ((i + 1) % 5 == 0) cout << "\n";
    }
    if (N % 5 != 0) cout << "\n";
    cout << "\n";
}

