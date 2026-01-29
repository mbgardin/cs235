#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include "input.h"

using namespace std;

struct Person {
    int priority;
    string name;

    bool operator<(const Person& other) const {
        return priority < other.priority;
    }
};

int main(int argc, char const* argv[]) {
    priority_queue<Person> pq;
    string command;

    while (input("What do you want to do? ", command)) {
        if (command == "add") {
            string name;
            string priorityStr;
            input("Name: ", name);
            input("Priority: ", priorityStr);
            int priority = stoi(priorityStr);
            pq.push(Person{priority, name});
        } else if (command == "take") {
            if (pq.empty()) {
                cout << "There are no more people in line" << endl;
            } else {
                Person top = pq.top();
                pq.pop();
                cout << setfill('0') << setw(2) << top.priority << " - " << top.name << endl;
            }
        } else {
            cout << command << " isn't a valid operation" << endl;
        }
    }

    return 0;
}
