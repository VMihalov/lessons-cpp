#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product {
  string name = "";
  int sum = 0;

  Product(string _name, int _sum): name(_name), sum(_sum) {}
};

struct Node {
  Product product;
  Node* next;
  Node* prev;

  Node(string _name, int _sum):  product(_name, _sum),
                                 next(NULL),
                                 prev(NULL) {}
  
};

struct List {
  Node* first;
  Node* last;

  List() : first(nullptr), last(nullptr) {}

  int isEmpty() {
    return first == nullptr;
  }

  void push(string _name, int _sum) {
    Node* node = new Node(_name, _sum);

    if (isEmpty()) {
      first = node;
      last = node;
      
      return;
    }

    last->next = node;
    node->prev = last;
    last = node;
  }

  void sort() {
    
  }
  
  void print() {
    if (isEmpty()) return;

    Node* node = first;
    while (node) {
      cout << node->product.name << " -> " << node->product.sum << endl;
      node = node->next;
    }
  }

  void printLast() {
    if (isEmpty()) return;

    Node* node = last;
    while (node) {
      cout << node->product.name << " -> " << node->product.sum << endl;
      node = node->prev;
    }
  }
};

void parseFile(string fileName, List &list);

int main() {
  List list;

  parseFile("products.txt", list);

  list.sort();

  list.print();

  return 0;
}

void parseFile(string fileName, List &list) {
  Product tmp("", 0);
  ifstream file;

  file.open(fileName);

  while (!file.eof()) {
    file >> tmp.name;
    file >> tmp.sum;

    list.push(tmp.name, tmp.sum);
  }

  file.close();
}
