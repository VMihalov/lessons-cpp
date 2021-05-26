#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Street {
  string name;
  string house;
  int year;
};

void read(string fileName);
void write(string fileName, vector <Street> arr);

int main() {
  int size = 3;

  vector <Street> arr;

  // Street tmp;
  // for (int i = 0; i < size; i++) {
  //   cout << i + 1 << ")\n";
  //   cout << "\tStreet: ";
  //   cin >> tmp.name;
  //   cout << "\tHouse: ";
  //   cin >> tmp.house;
  //   cout << "\tYear: ";
  //   cin >> tmp.year;
  //   arr.push_back(tmp);
  // }

  // arr.push_back(tmp);

  //write("street.bin", arr);

  read("street.bin");


  return 0;
}

void read(string fileName) {
  ifstream f;
  Street tmp;

  f.open("street.bin", ios::binary);

  if (!f.is_open()) return;
  
  f.read((char*)&tmp, sizeof(tmp));

  f.close();
}

void write(string fileName, vector <Street> arr) {
  ofstream file;

  file.open(fileName, ios::binary);

  for (auto v : arr)
    file.write((char *) &v, sizeof(Street));

  file.close();
}

















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
