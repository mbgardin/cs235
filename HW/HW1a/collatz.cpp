#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);

    if (n <= 0) {
        cout << "Input must be a positive integer" << endl;
        return 1;
    }

    while (n != 1) {
        cout << n << endl;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }

    cout << 1 << endl;
    return 0;
}
