#include <iostream>
#include <vector>

std::vector <int> heapSort(std::vector <int> arr, bool toIncrease = false);
std::vector <int> buildHeapMax(std::vector <int> arr, int current = 0);
std::vector <int> buildHeapMin(std::vector <int> arr, int current = 0);
void print(std::vector <int> arr);

int main() {
    bool toIncrease = false;
    std::vector <int> numbers({3, 10, 6, 5, 7, 3, 4, 2, 1, 5, 6, 4, 4, 4});

    print(numbers);

    std::cout << "Sort 0 - descending, 1 - ascending\n> "; std::cin >> toIncrease;

    numbers = heapSort(numbers, toIncrease);

    print(numbers);

    return 0;
}

std::vector <int> heapSort(std::vector <int> arr, bool toIncrease) {
    int size = arr.size();
    std::vector <int> result;

    while(result.size() < size) {
        for (int i = arr.size() / 2; i >= 0; i--) {
            if (toIncrease)
                arr = buildHeapMin(arr, i);
            else
                arr = buildHeapMax(arr, i);
        }

        result.push_back(arr[0]);
        arr.erase(arr.begin());
    }

    return result;
}

std::vector <int> buildHeapMax(std::vector <int> arr, int current) {
    int firstChild = 2 * current + 1;
    int secondChild = 2 * current + 2;
    int max = current;

    if (firstChild < arr.size() && arr[firstChild] > arr[max]) {
        max = firstChild;
    }

    if (secondChild < arr.size() && arr[secondChild] > arr[max]) {
        max = secondChild;
    }

    if (current == max)
        return arr;

    std::swap(arr[current], arr[max]);

    return buildHeapMax(arr, max);
}

std::vector <int> buildHeapMin(std::vector <int> arr, int current) {
    int firstChild = 2 * current + 1;
    int secondChild = 2 * current + 2;
    int max = current;

    if (firstChild < arr.size() && arr[firstChild] < arr[max]) {
        max = firstChild;
    }

    if (secondChild < arr.size() && arr[secondChild] < arr[max]) {
        max = secondChild;
    }

    if (current == max)
        return arr;

    std::swap(arr[current], arr[max]);

    return buildHeapMin(arr, max);
}

void print(std::vector <int> arr) {
    std::cout << "| ";
    for (int v : arr)
        std::cout << v << " | ";
    std::cout << std::endl;
}
