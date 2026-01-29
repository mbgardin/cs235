//  :)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string operation;
    int left, right;

    while (true) {
        cout << "operation: ";
        getline(cin, operation);

        if (operation == "") {
            break;
        } else if (operation == "add") {
            cout << "left operand: ";
            cin >> left;
            cout << "right operand: ";
            cin >> right;
            cout << (left + right) << endl;
        } else if (operation == "subtract") {
            cout << "left operand: ";
            cin >> left;
            cout << "right operand: ";
            cin >> right;
            cout << (left - right) << endl;
        } else if (operation == "multiply") {
            cout << "left operand: ";
            cin >> left;
            cout << "right operand: ";
            cin >> right;
            cout << (left * right) << endl;
        } else if (operation == "divide") {
            cout << "left operand: ";
            cin >> left;
            cout << "right operand: ";
            cin >> right;
            cout << (left / right) << endl;
        } else if (operation == "mod") {
            cout << "left operand: ";
            cin >> left;
            cout << "right operand: ";
            cin >> right;
            cout << (left % right) << endl;
        } else {
            cout << operation << " isn't a valid operation" << endl;
        }

        // Clear leftover newline from input
        cin.ignore();
    }

    return 0;
}
