
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

    bool found[1024] = {0};
    for (const int& i : idList) {
        found[i] = true;
    }

    for (int i = 1; i < 1023; i++) {
        if (!found[i] && found[i - 1] && found[i + 1]) {
            std::cout << "Potential: " << i << std::endl;
        }
    }

    return 0;
}
