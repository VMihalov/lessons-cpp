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

  void sortBySum() {
    Node* a = first;
    Node* b = first->next;
 
    Node* tmp = new Node("#", 0);

    Node* c = new Node("Its me Mario", 1);
 
    while (a->next) {
      while (b) {
        if (a->product.sum < b->product.sum) {
          swap(a, b);
          // temp->product = left->product;
          // left->product = right->product;
          // right->product = temp->product;
          
        }

        if (a->product.sum == b->product.sum) {
          if(a->product.name > b->product.name) {
            // temp->product = left->product;
            // left->product = right->product;
            // right->product = temp->product;
          }
        }

        b = b->next;
      }
      a = a->next;
      b = a->next;
    }
  }

  void swap(Node* &a, Node* &b) {
    Node* tmpA = a; 
    Node* tmpB = b;

    
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
Product parseString(string buffer);
int main() {
  List list;

  parseFile("products.txt", list);

  list.sortBySum();

  list.print();

  return 0;
}

void parseFile(string fileName, List &list) {
  ifstream file;
  string buffer = "";

  file.open(fileName);

  while (getline(file, buffer)) {
    Product tmp = parseString(buffer);

    list.push(tmp.name, tmp.sum);
  }

  file.close();
}

Product parseString(string buffer) {
  string name = "#";
  int sum = 0;

  int separator = buffer.find_first_of(' ');

  if (separator != -1) {
    name = buffer.substr(0, separator);
    sum = stoi(buffer.substr(separator + 1));
  }

  return (Product) { name, sum };
}
