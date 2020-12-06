
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int treeCount(int xOffset, int yOffset, const std::vector<std::string> treeMap, int width);

int dx[] = { 1, 3, 5, 7, 1 };
int dy[] = { 1, 1, 1, 1, 2 };

int main(int argc, char** argv)
{
    std::ifstream fin("input.txt");
    std::vector<std::string> treeMap;

    std::string line;
    while (fin >> line) {
        treeMap.push_back(line);
    }

    int width = treeMap[0].size();

    long long result = 1;
    for (int i = 0; i < 5; i++) {
        int subresult = treeCount(dx[i], dy[i], treeMap, width);
        result *= subresult;
        std::cout << "[" << dx[i] << ", " << dy[i] << "]: " << subresult << " => " << result << std::endl;
    }

    std::cout << result << std::endl;

    return 0;
}

int treeCount(int xOffset, int yOffset, const std::vector<std::string> treeMap, int width)
{
    int rowCount = treeMap.size();

    int treeCount = 0;
    int x = 0;
    int y = 0;
    while (y < rowCount) {
        char tile = treeMap[y][x];
        if (tile == '#') {
            treeCount++;
        }

        x = (x + xOffset) % width;
        y += yOffset;
    }

    return treeCount;
}
