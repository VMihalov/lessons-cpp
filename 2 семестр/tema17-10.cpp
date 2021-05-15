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

  void print() {
    Node* node = first;

    while(node) {
      cout << node->word << endl;
      node = node->next;
    }
  }

  int getAverageLength() {
    vector <int> lengths;

    Node* node = first;

    while (node) {
      lengths.push_back(node->word.length());
      node = node->next;
    }

    int sum = 0;

    sum = accumulate(lengths.begin(), lengths.end(), sum);

    return sum / lengths.size();
  }

};

void parseFile(string fileName, Queue &queue);
void parseString(string text, Queue &queue);
void sortWords(Queue &queue);

int main() {
  Queue queue;

  parseFile("text.txt", queue);

  sortWords(queue);

  return 0;
}

void parseFile(string fileName, Queue &queue) {
  ifstream file;
  string buffer;

  file.open(fileName);

  while(getline(file, buffer)) {
    parseString(buffer, queue);
  }

  file.close();
}

void parseString(string text, Queue &queue) {
  int start = 0;
  int stop = 0;

  while (text.find_first_of(' ') != -1) {
    stop = text.find_first_of(' ');

    queue.push(text.substr(0, stop));

    text = text.substr(stop + 1);
  }

  queue.push(text);
}

void sortWords(Queue &queue) {
  ofstream big, small;
  int averageLength = queue.getAverageLength();

  big.open("big.txt", ios::trunc);
  small.open("small.txt", ios::trunc);

  while (!queue.isEmpty()) {
    string word = queue.pop();

    if (word.length() >= averageLength)
      big << word << " ";
    else
      small << word << " ";
  }

  big.close();
  small.close();
}
