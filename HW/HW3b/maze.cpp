#include <iostream>
#include <fstream>
#include <vector>
#include "Grid.h"

using namespace std;

struct Coord {
    int row, col, level;
};

const int dRow[] = {1, -1, 0, 0, 0, 0};
const int dCol[] = {0, 0, 1, -1, 0, 0};
const int dLvl[] = {0, 0, 0, 0, 1, -1};

bool isValid(Grid& maze, int r, int c, int l) {
    return r >= 0 && r < maze.height() &&
           c >= 0 && c < maze.width() &&
           l >= 0 && l < maze.depth() &&
           maze.at(r, c, l) == 1;
}

bool findPath(Grid& maze, int r, int c, int l, vector<Coord>& path) {
    if (!isValid(maze, r, c, l)) return false;

    path.push_back({r, c, l});
    maze.at(r, c, l) = 2;

    if (r == maze.height() - 1 && c == maze.width() - 1 && l == maze.depth() - 1)
        return true;

    for (int i = 0; i < 6; ++i) {
        int nr = r + dRow[i];
        int nc = c + dCol[i];
        int nl = l + dLvl[i];
        if (findPath(maze, nr, nc, nl, path))
            return true;
    }

    path.pop_back();
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./maze <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin || !fout) {
        cerr << "ERROR: Could not open file." << endl;
        return 1;
    }

    Grid maze;
    fin >> maze;
    fin.close();

    vector<Coord> path;
    if (findPath(maze, 0, 0, 0, path)) {
        fout << "SOLUTION\n";
        for (size_t i = 0; i < path.size(); ++i) {
            fout << path[i].row << " " << path[i].col << " " << path[i].level << "\n";
        }
    } else {
        fout << "NO SOLUTION\n";
    }

    fout.close();
    return 0;
}