#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>

using namespace std;

set <char> mergeMaps(map <char, int> fMap, map <char, int> gMap);

int main() {
    fstream f, g;
    string bufferOne, bufferTwo;

    map <char, int> fMap, gMap;

    f.open("f.txt");
    g.open("g.txt");

    if (!f.is_open() || !g.is_open()) {
        cerr << "Error opening files!\n";
        return 1;
    }

    while (getline(f, bufferOne) && getline(g, bufferTwo)) {
        for (const auto v : bufferOne) {
            if (fMap.find(v) != fMap.end()) {
                fMap[v] += 1;
            } else {
                fMap[v] = 1;
            }
        }

        for (const auto v : bufferTwo) {
            if (gMap.find(v) != gMap.end()) {
                gMap[v] += 1;
            } else {
                gMap[v] = 1;
            }
        }
    }

    set <char> result = mergeMaps(fMap, gMap);

    cout << "Different symbols:\n";
    for (const auto v : result)
        cout << v << " | ";
    cout << endl;

    f.close();
    g.close();

    return 0;
}

set <char> mergeMaps(map <char, int> fMap, map <char, int> gMap) {
    set <char> result;

    for (const auto f : fMap)
        if (gMap.find(f.first) == gMap.end())
            result.insert(f.first);
        else if (gMap[f.first] != fMap[f.first])
            result.insert(f.first);

    for (const auto g : gMap)
        if (fMap.find(g.first) == fMap.end())
            result.insert(g.first);
        else if (fMap[g.first] != gMap[g.first])
            result.insert(g.first);

    return result;
}