#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char const* argv[]) {
    istream* input = &cin;
    ifstream file;
    unordered_set<string> seen;

    if (argc == 2) {
        file.open(argv[1]);
        if (!file) {
            cerr << "ERROR: can't open " << argv[1] << endl;
            return 1;
        }
        input = &file;
    }

    string line;
    while (getline(*input, line)) {
        if (seen.find(line) == seen.end()) {
            cout << line << endl;
            seen.insert(line);
        }
    }

    return 0;
}
