
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const int LINE_LENGTH = 10;

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    std::vector<int> idList;
    std::string line;
    while (fin >> line) {
        // binary conversion
        int id = 0;
        for (int i = 0; i < LINE_LENGTH; i++) {
            id = id << 1;

            char c = line[i];
            if (c == 'B' || c == 'R') {
                id += 1;
            }
        }

        idList.push_back(id);
        std::cout << line << " -> " << id << std::endl;
    }

    fin.close();

    int maxId = 0;
    for (const int& id : idList) {
        if (id > maxId) {
            maxId = id;
        }
    }

    std::cout << "Max ID: " << maxId << std::endl;

    return 0;
}
