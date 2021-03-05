#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>

struct NodeValue {
    char key = '#';
    int value = 0;
};

struct Node {
    NodeValue value;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(NodeValue val) {
        value = val;
    }
};

std::map <char, int> countOrder(std::string text);
std::vector <Node*> sortTree(std::vector <Node*> pairs);
std::vector <Node*> changeToTree(std::map <char, int> pairs);
Node* buildNode(std::vector <Node*> val);
std::map <char, std::string> countRoutes(Node* tree, std::string road = "");
std::string codeText(std::map <char, std::string> map, std::string text);
std::string decodeText(std::map <char, std::string> bits, std::string text);
void preOrder(Node* tree, int t = 1, int max = 0);

int main() {
    std::string text = "hello how are you good buy buy no yes okey ohhh";
    std::map <char, std::string> keys;
    std::map <char, int> frequency = countOrder(text);
    std::vector <Node*> tree = changeToTree(frequency);

    Node* forest = buildNode(tree);
    keys = countRoutes(forest);

    /*for (auto v : keys) {
        std::cout << v.first << " => " << v.second << std::endl;
    }*/

    std::cout << "String: " << text << std::endl;
    std::cout << "Coded: " << codeText(keys, text) << std::endl;
    std::cout << "Decoded: " << decodeText(keys, codeText(keys, text)) << std::endl;

    return 0;
}

std::map <char, int> countOrder(std::string text) {
    std::map <char, int> map;

    for (char s : text) {
        if (map.find(s) != map.end()) {
            map[s] += 1;
        } else {
            map[s] = 1;
        }
    }

    return map;
}

std::vector <Node*> changeToTree(std::map <char, int> pairs) {
    std::vector <Node*> arr;

    for (auto pair : pairs) {
        arr.push_back(new Node({ pair.first, pair.second }));
    }

    return arr;
}

std::vector <Node*> sortTree(std::vector <Node*> pairs) {
    Node* tmp;

    for (int i = 0; i < pairs.size(); i++) {
        for (int j = 0; j < pairs.size(); j++) {
            if (pairs[i]->value.value < pairs[j]->value.value) {
                tmp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = tmp;
            }
        }
    }

    return pairs;
}

Node* buildNode(std::vector <Node*> val) {
    if (val.size() < 2) {
        return val[0];
    }

    val = sortTree(val);

    Node* node = new Node({'#', val[0]->value.value + val[1]->value.value});

    if (val[0]->value.value < val[1]->value.value) {
        node->left = val[0];
        node->right = val[1];
    } else {
        node->left = val[1];
        node->right = val[0];
    }

    val.erase(val.begin());
    val[0] = node;

    return buildNode(val);
}

void preOrder(Node* tree, int t, int max) {
    if (tree == nullptr) return;
    std::cout << std::string(t, '-') << tree->value.key << "=>" << tree->value.value << std::endl;
    preOrder(tree->left, t++);
    t -= 1;
    preOrder(tree->right, t++);
}

std::map <char, std::string> countRoutes(Node* tree, std::string road) {
    static std::map <char, std::string> routes;
 
    if (tree->left == nullptr && tree->right == nullptr) {
        routes.insert(std::pair<char,std::string>(tree->value.key, road));
        return  routes;
    }

    countRoutes(tree->left, road += "0");
    road = road.substr(0, road.size() - 1);
    countRoutes(tree->right, road += "1");

    return routes;
}

std::string codeText(std::map <char, std::string> map, std::string text) {
    std::string result;

    for (auto v : text) {
        result += map[v] + ' ';
    }

    return result;
}

std::string decodeText(std::map <char, std::string> bits, std::string text) {
    for (auto bit : bits) {
        std::string s(1, bit.first);
        text = std::regex_replace(text, std::regex("\\b" + bit.second + "\\b", std::regex::ECMAScript), s);
    }

    return text;
}