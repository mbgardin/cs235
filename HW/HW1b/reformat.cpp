#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    string first, last;
    int points;
    double factor;

    while (input >> first >> last >> points >> factor) {
        output << last << ", " << first << ": " << (points * factor) << endl;
    }

    input.close();
    output.close();

    return 0;
}
