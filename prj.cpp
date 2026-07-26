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
























































int safeInput() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Invalid input. Enter a number: ";
    }
    cin.ignore(10000, '\n');
    return val;
}

int pickSize() {
    cout << "\n  Choose dataset size:\n";
    cout << "  1.  100\n";
    cout << "  2.  500\n";
    cout << "  3.  1,000\n";
    cout << "  4.  5,000\n";
    cout << "  5.  50,000\n";
    cout << "  Choice: ";
    int c = safeInput();
    int sizes[] = {100, 500, 1000, 5000, 50000};
    if (c >= 1 && c <= 5) return sizes[c - 1];
    cout << "  Invalid choice, defaulting to 100.\n";
    return 100;
}


void optionDisplay() {
    int n = pickSize();
    loadData(n);
    cout << "\n--- All " << n << " Random Records ---";
    auto t1 = high_resolution_clock::now();
    showRecords();
    auto t2 = high_resolution_clock::now();
    cout << "  Display time: "
         << fixed << setprecision(4)
         << duration<double, milli>(t2 - t1).count()
         << " ms\n";
}

void optionSort() {
    if (!data) {
        cout << "\n  No data loaded. Use Option 1 or Option 5 first.\n";
        return;
    }
    cout << "\n  Choose sorting algorithm:\n";
    cout << "  1. Selection Sort\n";
    cout << "  2. Quick Sort\n";
    cout << "  3. Merge Sort\n";
    cout << "  Choice: ";
    int c = safeInput();
    if (c < 1 || c > 3) { cout << "  Invalid choice.\n"; return; }

    string names[] = {"Selection Sort", "Quick Sort", "Merge Sort"};
    cout << "\n  Sorting " << N << " records using " << names[c-1] << " ...\n";

    auto t1 = high_resolution_clock::now();
    if      (c == 1) selectionSort();
    else if (c == 2) quickSort(0, N - 1);
    else             mergeSort(0, N - 1);
    auto t2 = high_resolution_clock::now();

    isSorted = true;
    cout << "  Done!  Time: "
         << fixed << setprecision(4)
         << duration<double, milli>(t2 - t1).count()
         << " ms\n";

    cout << "\n  Show sorted records? (1 = Yes  /  2 = No): ";
    int show = safeInput();
    if (show == 1) showRecords();
}

void optionSearch() {
    if (!data) {
        cout << "\n  !! No data loaded. Use Option 1 or Option 5 first !!\n";
        return;
    }
    if (!isSorted) {
        cout << "\n  !! Data is not sorted !!\n";
        cout << "  Please sort using Option 2 before searching.\n";
        return;
    }
    cout << "\n  Choose searching algorithm:\n";
    cout << "  1. Binary Search\n";
    cout << "  2. Interpolation Search\n";
    cout << "  Choice: ";
    int c = safeInput();
    if (c < 1 || c > 2) { cout << "  Invalid choice.\n"; return; }

    cout << "  Enter number to search: ";
    int target = safeInput();

    auto t1  = high_resolution_clock::now();
    int  idx = (c == 1) ? binarySearch(target) : interpolationSearch(target);
    auto t2  = high_resolution_clock::now();

    if (idx != -1)
        cout << "\n  Found!  " << target
             << "  ->  Record ID" << data[idx].id
             << "  (index " << idx << ")\n";
    else
        cout << "\n  Not found: " << target << " is not in the dataset.\n";

    cout << "  Search time: "
         << fixed << setprecision(6)
         << duration<double, milli>(t2 - t1).count()
         << " ms\n";
}

void optionNewRandom() {
    int n = pickSize();
    loadData(n);
    cout << "\n  New random dataset of " << n << " records generated!\n";
    cout << "  (Sorted status reset - please sort again before searching)\n";
}

int main() {
    srand((unsigned)time(0));
    int choice;
    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Display All Records\n";
        cout << "2. Sort Records\n";
        cout << "3. Search for Number\n";
        cout << "4. Exit Application\n";
        cout << "5. Generate New Random Data\n";
        cout << "=====================\n";
        cout << "Enter choice: ";
        choice = safeInput();
        switch (choice) {
            case 1: optionDisplay();          break;
            case 2: optionSort();             break;
            case 3: optionSearch();           break;
            case 4: cout << "\n  Goodbye!\n"; break;
            case 5: optionNewRandom();        break;
            default: cout << "\n  Invalid option, enter 1-5.\n";
        }
    } while (choice != 4);

    delete[] data;
    return 0;
}








































