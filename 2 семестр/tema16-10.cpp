#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Component {
  int pos;
  Component* next = NULL;

  Component(int pos) : pos(pos), next(nullptr) {}
};

struct Stack {
  Component* top = NULL;

  void push(int pos) {
    Component* node = new Component(pos);

    if (top == NULL) {
      top = node;

      return;
    }

    node->next = top;
    top = node;

    return;
  }

  int remove() {
    if (top == NULL) {
      return -1;
    }

    int res = top->pos;
    top = top->next;

    return res;
  }

  void print() {
    Component* comp = top;
    while (comp) {
      cout << comp->pos << endl;
      comp = comp->next;
    }
  }
};

struct Pair {
  int open;
  int close;
};

void parseString(string formula, vector <Pair> &pairs);

bool comp(Pair a, Pair b) {
  return (a.close - a.open) < (b.close - b.open);
}

int main() {
  string formula = "A+(45-F(X)*(B-C))";
  vector <Pair> pairs;

  parseString(formula, pairs);

  sort(pairs.begin(), pairs.end(), comp);

  for (auto v : pairs)
    cout << v.open << " " << v.close << "; ";
  
  return 0;
}

void parseString(string formula, vector <Pair> &pairs) {
  Stack stack;

  for(int i = 0; i < formula.length(); i++) {
    if (formula[i] == '(') {
      stack.push(i + 1);
    }

    if (formula[i] == ')') {
      int open = stack.remove();

      Pair pair = { open, i + 1 };
      pairs.push_back(pair);
    }
  }
}
