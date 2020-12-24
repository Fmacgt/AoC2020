
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void printMap(const std::vector<std::string>& levelMap);
void evolveMap(const std::vector<std::string>& fromMap, std::vector<std::string>& toMap);
bool isIdentical(const std::vector<std::string>& fromMap, std::vector<std::string>& toMap);
int countOccupiedSeats(const std::vector<std::string>& levelMap);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    std::vector<std::string> levelMap;
    std::string line;
    while (std::getline(fin, line)) {
        levelMap.push_back(line);
    }

    fin.close();

    printMap(levelMap);

    std::vector<std::string> buffers[2];
    buffers[0] = levelMap;
    buffers[1] = levelMap;

    int fromPtr = 0;
    int toPtr = 1;
    bool stablized = true;
    int iterationCount = 0;
    do {
        evolveMap(buffers[fromPtr], buffers[toPtr]);
        stablized = isIdentical(buffers[fromPtr], buffers[toPtr]);
        if (!stablized) {
            iterationCount++;

            std::cout << "===== Iteration " << iterationCount << " =====" << std::endl;
            printMap(buffers[toPtr]);
        }

        fromPtr = fromPtr == 0 ? 1 : 0;
        toPtr = toPtr == 1 ? 0 : 1;
    } while (!stablized);

    std::cout << iterationCount << std::endl;
    std::cout << countOccupiedSeats(buffers[fromPtr]) << " occupied seats" << std::endl;

    return 0;
}


void printMap(const std::vector<std::string>& levelMap)
{
    for (const std::string& line : levelMap) {
        std::cout << line << std::endl;
    }
}

int countSeats(const std::vector<std::string>& levelMap, char token, int row, int col)
{
    int height = levelMap.size();
    int width = levelMap[0].size();

    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        int r = row + dr;
        if (r < 0 || r >= height) {
            continue;
        }

        for (int dc = -1; dc <= 1; dc++) {
            int c = col + dc;
            if (c < 0 || c >= width ||
                    (r == row && c == col)) {
                continue;
            }

            count += levelMap[r][c] == token;
        }
    }

    return count;
}

void evolveMap(const std::vector<std::string>& fromMap, std::vector<std::string>& toMap)
{
    int height = fromMap.size();
    int width = fromMap[0].size();

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            char token = fromMap[row][col];
            bool changed = false;
            switch (token) {
                case 'L':
                    if (countSeats(fromMap, '#', row, col) == 0) {
                        toMap[row][col] = '#';
                        changed = true;
                    }
                    break;
                case '#':
                    if (countSeats(fromMap, '#', row, col) >= 4) {
                        toMap[row][col] = 'L';
                        changed = true;
                    }
                    break;
            }

            if (!changed) {
                toMap[row][col] = token;
            }
        }
    }
}

bool isIdentical(const std::vector<std::string>& fromMap, std::vector<std::string>& toMap)
{
    bool result = true;
    int ptr = 0;
    while (result && ptr < fromMap.size()) {
        result &= fromMap[ptr] == toMap[ptr];
        ptr++;
    }

    return result;
}

int countOccupiedSeats(const std::vector<std::string>& levelMap)
{
    int height = levelMap.size();
    int width = levelMap[0].size();

    int count = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            char token = levelMap[row][col];
            count += token == '#' ? 1 : 0;
        }
    }

    return count;
}
