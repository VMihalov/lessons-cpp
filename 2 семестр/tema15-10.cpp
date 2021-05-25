#include <iostream>

using namespace std;

struct Node {
  int number;
  Node* next;
  Node(int _number) : number(_number), next(NULL) {}
};

struct List {
  Node* first;
  Node* last;

  List() : first(nullptr), last(nullptr) {}

  bool is_empty() {
    return first == nullptr;
  }

  void push(int _number) {
    Node* node = new Node(_number);
    if (is_empty()) {
      first = node;
      last = node;
      return;
    }

    last->next = node;
    last = node;
  }

  void remove(int _number) {
    if (is_empty()) return;

    if (first->number == _number) {
      cout << first->number << " ";
      remove_first();
      return;
    } else if (last->number == _number) {
      cout << last->number << " ";
      remove_last();
      return;
    }

    Node* node = first;

    Node* slow = first;
    Node* fast = first->next;

    while (fast && fast->number != _number) {
      fast = fast->next;
      slow = slow->next;
    }

    if (!fast) {
      return;
    }

    cout << fast->number << " ";

    slow->next = fast->next;

    delete fast;

    return;
  }

  void removeByIndex(int index, int current = 1) {
    Node* node = first;

    while (node && current != index) {
      current++;
      node = node->next;
    }

    remove(node->number);
  }

  void print() {
    if (is_empty()) return;

    Node* node = first;
    while (node) {
      cout << node->number << " ";
      node = node->next;
    }
  }

  void remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
  }

  void remove_last() {
    if (is_empty()) return;
    if (first == last) {
        remove_first();
        return;
    }
    Node* p = first;
    while (p->next != last) p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
  }
};

int main() {
  List list;
  int size = 10, step = 3;

  for (int i = 1; i <= size; i++) {
    list.push(i);
  }

  int numberOfChildrens = size;
  int pos = step;
  cout << endl;
  while(numberOfChildrens >= step) {
    if (pos > numberOfChildrens) {
      pos = pos - numberOfChildrens;
    }
    
    list.removeByIndex(pos);
    numberOfChildrens--;

    pos += step - 1;
    
  }

  cout << endl;
  list.print();

  return 0;
}
