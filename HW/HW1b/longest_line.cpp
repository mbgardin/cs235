//  :-)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream input(argv[1]);
    string line, longestLine;
    int maxWords = 0;

    while (getline(input, line)) {
        int count = 0;
        string word;
        stringstream ss(line);

        while (ss >> word) {
            count++;
        }

        if (count > maxWords) {
            maxWords = count;
            longestLine = line;
        }
    }

    cout << longestLine << endl;
    input.close();

    return 0;
}
