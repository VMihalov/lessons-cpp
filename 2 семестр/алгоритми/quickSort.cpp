#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector <int> arr, int low, int high);
int partition(vector <int> arr, int low, int high);

int main() {
    vector <int> arr({4, 9, 7, 6, 2, 3, 8});

    quickSort(arr, 0, arr.size() - 1);

    return 0;
}

void quickSort(vector <int> arr, int low, int high) {
    int pivot = arr[(low + high) / 2];
    int l = low;
    int r = high;

    do {
        while (arr[l] < pivot)
            l++;
        while (arr[r] > pivot)
            r--;
        
        if (l == r) {
            l++;
            r--;
            break;
        }

        swap(arr[l], arr[r]);
    } while (true);

    cout << "L: " << arr[l] << " R: " << arr[r] << endl;
    for (const auto v : arr)
        cout << v << " | ";

    if (l < high)
        quickSort(arr, low, l);
    if (l < high)
        quickSort(arr, r + 1, high);
}

int partition(vector <int> arr, int low, int high) {
    return 1;
}