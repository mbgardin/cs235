#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    double input = atof(argv[1]);

    if (input < 0) {
        cout << "Input must be greater than 0" << endl;
        return 1;
    }

    double low = 0;
    double high = input;
    double mid;

    while (true) {
        mid = (low + high) / 2;
        double square = mid * mid;
        cout << mid << " (" << square << ")" << endl;

        if (fabs(square - input) < 0.0001) {
            break;
        }

        if (square < input) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return 0;
}
