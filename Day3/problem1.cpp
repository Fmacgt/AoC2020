
#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char** argv)
{
    std::ifstream fin("input.txt");

    std::string line;
    int treeCount = 0;
    int x = 0;
    while (fin >> line) {
        if (line[x] == '#') {
            treeCount++;
            line[x] = 'X';
        } else {
            line[x] = 'O';
        }

        x = (x + 3) % line.size();
        std::cout << line << std::endl;
    }

    std::cout << treeCount << std::endl;

    return 0;
}
