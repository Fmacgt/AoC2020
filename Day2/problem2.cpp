
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main(int argc, char** argv)
{
    std::ifstream fin("input.txt");

    int validCount = 0;

    std::string line;
    while (std::getline(fin, line)) {
        auto dashIndex = line.find('-');
        auto space1Index = line.find(' ');
        auto passwordIndex = space1Index + 4; // 1 for space, 1 for target char, 1 for colon; 1 for space 2

        int min = std::stoi(line.substr(0, dashIndex));
        int max = std::stoi(line.substr(dashIndex + 1, space1Index - dashIndex - 1));
        char targetChar = line[space1Index + 1];
        std::string password = line.substr(passwordIndex);

        std::cout << password << " / " << targetChar << ": [" << min << "] - " << password[min-1] << "; [" << max << "] - " << password[max-1] << ": ";

        int count = 0;
        bool firstMatch = password[min - 1] == targetChar;
        bool secondMatch = password[max - 1] == targetChar;
        if (firstMatch != secondMatch) {
            validCount++;
            std::cout << ": Valid" << std::endl;
        } else {
            std::cout << ": Invalid" << std::endl;
        }
    }

    std::cout << validCount << std::endl;
    
    return 0;
}
