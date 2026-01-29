#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <file> <state> <year>" << endl;
        return 1;
    }

    string filename = argv[1];
    string target_state = argv[2];
    string target_year = argv[3];

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: could not open file" << endl;
        return 0;
    }

    string state, year, month, rate_str;
    float total = 0.0f;
    int count = 0;

    while (file >> state >> year >> month >> rate_str) {
        if (state == target_state && year == target_year) {
            total += stof(rate_str);
            count++;
        }
    }

    file.close();

    if (count > 0) {
        cout << (total / count) << endl;
    }

    return 0;
}
