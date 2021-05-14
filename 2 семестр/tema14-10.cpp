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
