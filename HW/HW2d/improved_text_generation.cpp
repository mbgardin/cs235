#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

using Model = unordered_map<string, vector<string>>;

Model trainModel(istream& in) {
    Model model;
    string prev = "";
    string curr;
    while (in >> curr) {
        model[prev].push_back(curr);
        prev = curr;
    }
    return model;
}

void generateText(const Model& model, const string& startWord, int wordCount, ostream& out) {
    string prev = startWord;
    for (int i = 0; i < wordCount; ++i) {
        auto it = model.find(prev);
        if (it == model.end() || it->second.empty()) {
            break;
        }
        const vector<string>& options = it->second;
        string next = options[rand() % options.size()];
        out << next << " ";
        prev = next;
    }
    out << endl;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <word_count> [starting_word]" << endl;
        return 1;
    }

    string inputFile = argv[1];
    int wordCount = atoi(argv[2]);
    string startWord = (argc >= 4) ? argv[3] : "";

    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "ERROR: could not open " << inputFile << endl;
        return 1;
    }

    Model model = trainModel(fin);
    fin.close();

    generateText(model, startWord, wordCount, cout);

    return 0;
}