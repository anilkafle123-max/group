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



















int partition(int lo, int hi) {
    int piv = data[hi].number;
    int b   = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (data[j].number < piv) {
            b++;
            Record tmp = data[b];
            data[b]    = data[j];
            data[j]    = tmp;
        }
    }
    Record tmp  = data[b + 1];
    data[b + 1] = data[hi];
    data[hi]    = tmp;
    return b + 1;
}

void quickSort(int lo, int hi) {
    if (lo < hi) {
        int p = partition(lo, hi);
        quickSort(lo, p - 1);
        quickSort(p + 1, hi);
    }
}








































