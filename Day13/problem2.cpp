
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <sstream>


void parseInput(std::string& line, std::vector<std::int64_t>& idList, std::vector<std::int64_t>& offsetList);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    std::string line;
    std::getline(fin, line);    // dummy line
    std::getline(fin, line);

    fin.close();

    std::vector<std::int64_t> idList;
    std::vector<std::int64_t> offsetList;
    parseInput(line, idList, offsetList);

    int maxIdIndex = 0;
    std::int64_t maxId = idList[0];
    for (int i = 1; i < idList.size(); i++) {
        auto id = idList[i];
        if (id > maxId) {
            maxId = id;
            maxIdIndex = i;
        }
    }

    {
        auto offsetChange = offsetList[maxIdIndex];
        for (int i = 0; i < offsetList.size(); i++) {
            offsetList[i] -= offsetChange;
        }
    }

    std::int64_t t = 100000000000000ll;
    auto actualT = t;
    while (true) {
        bool allMatch = true;
        std::cout << t;
        for (int i = 0; i < idList.size(); i++) {
            if ((t + offsetList[i]) % idList[i] != 0) {
                std::cout << ": Mismatch " << idList[i] << std::endl;
                allMatch = false;
                break;
            }
        }

        if (!allMatch) {
            t += maxId;
        } else {
            actualT = t - offsetList[0];
            break;
        }
    }

    std::cout << std::endl << "T: " << actualT << std::endl;

    return 0;
}

void parseInput(std::string& line, 
        std::vector<std::int64_t>& idList, std::vector<std::int64_t>& offsetList)
{
    std::int64_t offset = 0;
    std::stringstream lineReader(line);
    std::string part;
    while (std::getline(lineReader, part, ',')) {
        if (part[0] != 'x') {
            int n = std::stoi(part);
            idList.push_back((std::int64_t)n);
            offsetList.push_back(offset);
        }

        offset++;
    }
}
