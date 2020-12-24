
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


const int XOffsets[4] = {
    1, 0, -1, 0
};
const int YOffsets[4] = {
    0, -1, 0, 1
};

struct Ship
{
    int x;
    int y;
    int heading;
};

void applyOperation(Ship& ship, char opCode, int opVal);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    Ship ship = { 0, 0, 0 };

    std::string line;
    while (std::getline(fin, line)) {
        char opCode = line[0];
        int opVal = std::stoi(line.substr(1));

        applyOperation(ship, opCode, opVal);
    }

    fin.close();

    int distance = std::abs(ship.x) + std::abs(ship.y);
    std::cout << "[" << ship.x << ", " << ship.y << "] => " << distance << std::endl;

    return 0;
}

void applyOperation(Ship& ship, char opCode, int opVal)
{
    switch (opCode) {
        case 'N':
            ship.y += opVal;
            break;
        case 'S':
            ship.y -= opVal;
            break;
        case 'E':
            ship.x += opVal;
            break;
        case 'W':
            ship.x -= opVal;
            break;
        case 'L':
            ship.heading = (ship.heading + 360 - opVal) % 360;
            break;
        case 'R':
            ship.heading = (ship.heading + opVal) % 360;
            break;
        case 'F':
            int directIndex = ship.heading / 90;
            ship.x += XOffsets[directIndex] * opVal;
            ship.y += YOffsets[directIndex] * opVal;
            break;
    }
}
