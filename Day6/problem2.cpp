
#include <iostream>
#include <fstream>
#include <string>
#include <map>

int getAnswerCount(std::ifstream& fin);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    int totalCount = 0;
    while (!fin.eof()) {
        int yesCount = getAnswerCount(fin);
        std::cout << yesCount << std::endl;
        totalCount += yesCount;
    }

    fin.close();

    std::cout << "Total: " << totalCount << std::endl;

    return 0;
}

int getAnswerCount(std::ifstream& fin)
{
    std::map<char, int> occurenceMap;

    int personCount = 0;
    std::string line;
    while (getline(fin, line)) {
        int length = line.size();

        // try to filter out empty lines...
        if (length < 1) {
            break;
        }
        char leader = line[0];
        if (leader < 'a' || leader > 'z') {
            break;
        }


        personCount++;
        int lineCount = 0;
        for (const char& c : line) {
            if (c < 'a' || c > 'z') {
                continue;
            }

            if (occurenceMap.count(c) == 0) {
                lineCount++;
            }
            occurenceMap[c] += 1;
        }

        std::cout << "[" << lineCount << "]\t" << line << std::endl;
    }

    int yesCount = 0;
    auto iter = occurenceMap.begin();
    while (iter != occurenceMap.end()) {
        if (iter->second >= personCount) {
            yesCount++;
        }

        iter++;
    }

    return yesCount;
}
