#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const* argv[]) {
    int num_lines = 10;
    istream* input = &cin;
    ifstream file;

    if (argc == 2) {
        string arg = argv[1];
        if (arg[0] == '-') {
            num_lines = stoi(arg.substr(1));  // "-5" → 5
        } else {
            file.open(arg);
            if (!file) {
                cerr << "ERROR: can't open " << arg << endl;
                return 1;
            }
            input = &file;
        }
    } else if (argc == 3) {
        string num_arg = argv[1];
        string filename = argv[2];
        if (num_arg[0] == '-') {
            num_lines = stoi(num_arg.substr(1));
        }

        file.open(filename);
        if (!file) {
            cerr << "ERROR: can't open " << filename << endl;
            return 1;
        }
        input = &file;
    }

    string line;
    for (int i = 0; i < num_lines && getline(*input, line); i++) {
        cout << line << endl;
    }

    return 0;
}
