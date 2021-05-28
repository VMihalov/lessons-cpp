#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// File
void readFile(string filename, set <char> &kit);

int main() {
  set <char> f, g;
  vector <int> res;

  readFile("f.bin", f);
  readFile("g.bin", g);

  set_symmetric_difference(f.begin(), f.end(), g.begin(), g.end(), back_inserter(res));

  for (auto v : res)
    cout << (char)v << " | ";

  return 0;
}

void readFile(string filename, set <char> &kit) {
  ifstream file(filename, ios::binary);
  char buffer;

  int i = 1;
  while (file.read((char*)&buffer, sizeof(char))) {
    kit.insert(buffer);

    file.seekg(i * sizeof(char));
    i++;
  }

  file.close();
}
