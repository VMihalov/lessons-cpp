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
    Node* a = first;
    Node* b = first->next;

    while (a->next) {
      while (b) {
        if (a->product.sum > b->product.sum) {
          swap(a, b);

          a = first;
        }

        if (a->product.sum == b->product.sum) {
          if (a->product.name > b->product.name) {
            swap(a, b);

            a = first;
          }
        }

        b = b->next;
      }

      a = a->next;
      b = a->next;
    }
  }

  void swap(Node* a , Node* b) {
    Node* aNext; Node* aPrev; Node* bNext; Node* bPrev;

    if (a == first && b == last) {
      aNext = a->next;
      aPrev = NULL;

      bNext = NULL;
      bPrev = b->prev;

      aNext->prev = b;
      bPrev->next = a;

      b->prev = NULL;
      b->next = aNext;

      a->next = NULL;
      a->prev = bPrev;

      first = b;
      last = a;

      return;
    }

    if (a->next == b && b->prev == a) {
      a->next = b->next;
      b->prev = a->prev;
      a->prev = b;
      b->next = a;

      if (first == a) {
        a->next->prev = a;
        b->prev = NULL;

        first = b;
      } else if (last == b) {
        a->next = NULL;
        b->prev->next = b;

        last = a;
      } else {
        a->next->prev = a;
        b->prev->next = b;
      }

      a = a->prev;
      b = a->next;

      return;
    }

    aNext = a->next;
    aPrev = a->prev;
    bNext = b->next;
    bPrev = b->prev;

    if (a == first) {
      bPrev->next = a;

      first = b;
    } else {
      aPrev->next = b;
      bPrev->next = a;
    }

    if (b == last) {
      aNext->prev = b;

      last = a;
    } else {
      aNext->prev = b;
      bNext->prev = a;
    }

    b->prev = aPrev;
    a->prev = bPrev;
    
    b->next = aNext;
    a->next = bNext;
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

  cout << "From file:" << endl;
  list.print();

  list.sort();

  cout << endl << "Sorted products:" << endl;
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
