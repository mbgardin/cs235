// :)

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


unordered_map<string, vector<string>> trainModel(istream& in) {
    unordered_map<string, vector<string>> model;
    string prev = "";
    string curr;

    while (in >> curr) {
        model[prev].push_back(curr);
        prev = curr;
    }

    return model;
}

void generateText(const unordered_map<string, vector<string>>& model, string start, int count, ostream& out) {
    string prev = start;
    for (int i = 0; i < count; ++i) {
        auto it = model.find(prev);
        if (it == model.end() || it->second.empty()) {
            break;
        }

        const vector<string>& options = it->second;
        int index = rand() % options.size();
        string next = options[index];
        out << next << " ";
        prev = next;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <word_count>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "ERROR: could not open file" << endl;
        return 1;
    }

    int wordCount = stoi(argv[2]);

    srand(time(nullptr));

    auto model = trainModel(inputFile);
    inputFile.close();

    generateText(model, "", wordCount, cout);
    cout << endl;

    return 0;
}
