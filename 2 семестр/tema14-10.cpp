#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Street {
  char name[30];
  char house[30];
  int year;
};

bool comparator(Street a, Street b) {
  return a.year < b.year;
}

void read(vector <Street> &arr, string fileName);
void write(vector <Street> arr, string fileName);
int searchBinary(vector <Street> &arr, int key);
void countAndRender(vector <Street> &arr, int n, int m);
void insert(vector <Street> &arr, int length);
void render(vector <Street> &arr);

int main() {
  try {
    vector <Street> arr;
    int n, m;

    read(arr, "street.bin");

    sort(arr.begin(), arr.end(), comparator);

    cout << "From binary file:" << endl;
    
    render(arr);

    cout << endl;

    cout << "Infinum ";
    cin >> n;

    cout << "Suprerum ";
    cin >> m;

    countAndRender(arr, n, m);

    return 0;
  } catch(const char* error) {
    cerr << error << endl;

    return 1;
  }
}

void read(vector <Street> &arr, string fileName) {
  ifstream file;
  Street tmp;

  file.open("street.bin", ios::binary);

  if (!file.is_open()) throw "Error opening file";
  
  int i = 1;
  while (file.read((char*)&tmp, sizeof(Street))) {
    arr.push_back(tmp);
    file.seekg(i * sizeof(Street));
    i++;
  }

  arr.pop_back();

  file.close();
}

void write(vector <Street> arr, string fileName) {
  ofstream file;

  file.open(fileName, ios::binary);

  for (auto street : arr)
    file.write((char*)&street, sizeof(Street));

  file.close();
}

void countAndRender(vector <Street> &arr, int n, int m) {
  if (n > m) throw "Incorrect borders";

  int inf = searchBinary(arr, n);
  int sup = searchBinary(arr, m);
  
  if (inf == -1 || sup == -1) throw "Incorrect borders";

  cout << "Number of streets from " << n << " to " << m << " = " << sup - inf << endl;

  for (int i = inf; i < sup; i++)
    cout << arr[i].name << " " << arr[i].house << " " << arr[i].year << endl;
}

int searchBinary(vector <Street> &arr, int key) {
  if (arr[0].year > key || arr[arr.size() - 1].year < key) {
    return -1;
  }

  if (arr[0].year == key) return 0;

  if (arr[arr.size() - 1].year == key) return arr.size();

  int m, l = 0, r = arr.size() - 1;

  while (r > l) {
    m = (l + r) / 2;

    if (arr[m].year < key && arr[m + 1].year > key) return m + 1;
    else if (arr[m].year > key && arr[m - 1].year < key) return m;
    else if (arr[m].year < key) l = m + 1; 
    else if (arr[m].year > key) r = m - 1;
    else return m + 1;
  }

  if (arr[l].year == key) {
    return l;
  } else {
    return -1;
  }
}

void insert(vector <Street> &arr, int length) {
  Street tmp;

  for (int i = 0; i < length; i++) {
    cout << i + 1 << ")\n";
    cout << "\tStreet: ";
    cin >> tmp.name;
    cout << "\tHouse: ";
    cin >> tmp.house;
    cout << "\tYear: ";
    cin >> tmp.year;

    arr.push_back(tmp);
  }

  arr.push_back(tmp);
}

void render(vector <Street> &arr) {
  for (Street v : arr)
    cout << v.name << "   " << v.house << "   " << v.year << endl;
}
