#include <iostream>
#include <string>
#include <map>
#include <vector>

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
std::string decodeText(Node* tree, std::string text);
void preOrder(Node* tree, int t = 1, int max = 0);
int height(Node* tree);

int main() {
    std::string text = "lorem ipsum dolor sit amet";
    std::map <char, std::string> keys;
    std::map <char, int> frequency = countOrder(text);
    std::vector <Node*> tree = changeToTree(frequency);

    Node* forest = buildNode(tree);
    
    std::cout << "Height: " << height(forest) << std::endl;

    return 0;
}

int height(Node* tree){
    int l, r;

    if(tree != NULL){
        l = (tree->left  != NULL) ? height(tree->left)  : 0;
        r = (tree->right != NULL) ? height(tree->right) : 0;
        return ((l > r) ? l : r) + 1;
    }

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

    node->left = val[0];
    node->right = val[1];

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
        result += map[v];
    }

    return result;
}

std::string decodeText(Node* tree, std::string text) {
    static std::string res = "";
    static Node* root = tree;

    if (tree->left == nullptr && tree->right == nullptr) {
        res += tree->value.key;

        return decodeText(root, text);
    }

    if (text[0] == '0')
        return decodeText(tree->left, text.substr(1));
    else if (text[0] == '1')
        return decodeText(tree->right, text.substr(1));
    else return res;

    return res;
}
