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
 
    while (a->next) {
      while (b) {
        if (a->product.sum < b->product.sum) {
          swap(a, b);
          // temp->product = left->product;
          // left->product = right->product;
          // right->product = temp->product;
          
          if(a->prev == NULL){   //если "взятая" структура первая в списке
            *first = a->next;                                    
          }
          else a->pred->next = a->next;

          if(b->next == 0){   //если структура, после которой вставляется "взятая" структура, последняя в списке 
            *close = b;
          }
          else b->next->pred = a;           
            a->next->pred = b->pred;     
            a->next = b->next;     
            b->next = a;                          
            a->pred = b;
            b = a->next;

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
  Product tmp("", 0);
  ifstream file;
  string buffer = "";

  file.open(fileName);

  while (getline(file, buffer)) {
    tmp = parseString(buffer);

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
