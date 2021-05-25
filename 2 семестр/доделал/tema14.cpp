#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int search(vector <int> arr, int x) {
  int j = -1;
  int l = 0;
  int r = arr.size() - 1;
  int m;

  while (l <= r) {
    m = ( l + r ) / 2;

    if (x < arr[m]) r = m - 1;
    else if (x > arr[m]) l = m + 1;
    else {
      j = m;

      break;
    }
  }

  return j;
} 

int main() {
  fstream file;
  int number;
  vector <int> buffer;

  file.open("numbers.txt");

  while (!file.eof()) {
    file >> number;

    buffer.push_back(number);
  }

  int x = 0;
  cout << "X: ";
  cin >> x;

  int pos = search(buffer, x);

  cout << "POS: " << pos << endl;

  int nextPos = pos;

  while (buffer[pos] == buffer[nextPos]) {
    cout << nextPos << ") " << buffer[nextPos] << endl;
    nextPos++;
  }

  cout << endl << nextPos - pos << endl;

  file.close();

  return 0;
}
