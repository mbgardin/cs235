//  :)
#include <iostream>
#include <cstdlib> // for atof

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "prod requires 2 arguments\n";
        return 1;
    }

    double num1 = atof(argv[1]);
    double num2 = atof(argv[2]);

    std::cout << num1 << " * " << num2 << " = " << num1 * num2 << "\n";

    return 0;
}
