#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include <vector>

using namespace std;

struct Node {
  string word = "";
  Node* next = NULL;

  Node(string word) : word(word), next(nullptr) {}
};

struct Queue {
  Node* first = NULL;
  Node* last = NULL;

  int isEmpty() {
    if (first == NULL && last == NULL) {
      return 1;
    }

    return 0;
  }

  void push(string word) {
    Node* node = new Node(word);

    if (first == NULL && last == NULL) {
      first = node;
      last = node;

      return;
    }

    last->next = node;
    last = node;

    return;
  }

  string pop() {
    if (first == NULL && last == NULL)
      return "";

    if (!first) {
      first = NULL;
      last = NULL;

      return "";
    }
    string res = first->word;
    Node* node = first->next;

    first = node;

    return res;
  }

  void clear() {
    if (first == NULL && last == NULL) return;

    Node* node;

    while (first != last) {
      node = first->next;
      first = node;
    }

    first = NULL;
    last = NULL;
  }

  string getLast() {
    if (first == NULL && last == NULL)
      return "";

    if (!first) {
      first = NULL;
      last = NULL;

      return "";
    }

    return first->word;
  }

  void print() {
    Node* node = first;

    while(node) {
      cout << node->word << endl;
      node = node->next;
    }
  }
};

void parseFile(string fileName, Queue &big, Queue &little);
void writeFile(string fileName, Queue queue);

int main() {
  try {
    Queue big, little;

    parseFile("text.txt", big, little);

    writeFile("short.txt", little);
    writeFile("big.txt", big);

  } catch(const char* error) {
    cerr << error << endl;
  }

  return 0;
}

void parseFile(string fileName, Queue &big, Queue &little) {
  ifstream file;
  string buffer, word;

  file.open(fileName);

  if (!file.is_open()) throw "Error opening file";

  string inside;
  while (!file.eof()) {
    file >> buffer;

    if (big.isEmpty() && little.isEmpty()) {
      big.push(buffer);
      little.push(buffer);
    }

    if (buffer.length() == little.getLast().length()) {
      little.push(buffer);
    } else if (buffer.length() < little.getLast().length()) {
      little.clear();
      little.push(buffer);
    }

    if (buffer.length() == big.getLast().length()) {
      big.push(buffer);
    } else if (buffer.length() > big.getLast().length()) {
      big.clear();
      big.push(buffer);
    }

  }

  file.close();
}

void writeFile(string fileName, Queue queue) {
  ofstream file(fileName);
  string buffer;

  while (!queue.isEmpty()) {
    buffer = queue.pop();
    file << buffer << " ";
  }

  file.close();
}
