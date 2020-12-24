
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


/*
 * R[a] = {
 *  cos(a)  -sin(a)
 *  sin(a)   cos(a)
 * }
 * R[0] = {
 *  1, 0
 *  0, 1
 * }
 * R[90] = {
 *  0, -1
 *  1, 0
 * }
 * R[180] = {
 *  -1, 0,
 *  0, -1
 * }
 * R[270] = {
 *  0, 1,
 *  -1, 0
 * }
*/
const int Rotate[4][4] = {
    { 1, 0, 0, 1 },
    { 0, -1, 1, 0 },
    { -1, 0, 0, -1 },
    { 0, 1, -1, 0 }
};

struct Vec2
{
    int x;
    int y;
};

void applyOperation(Vec2& ship, Vec2& waypoint, char opCode, int opVal);


int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    Vec2 ship = { 0, 0 };
    Vec2 waypoint = { 10, 1 };

    std::string line;
    while (std::getline(fin, line)) {
        char opCode = line[0];
        int opVal = std::stoi(line.substr(1));

        applyOperation(ship, waypoint, opCode, opVal);
    }

    fin.close();

    int distance = std::abs(ship.x) + std::abs(ship.y);
    std::cout << "[" << ship.x << ", " << ship.y << "] => " << distance << std::endl;

    return 0;
}

void applyOperation(Vec2& ship, Vec2& waypoint, char opCode, int opVal)
{
    switch (opCode) {
        case 'N':
            waypoint.y += opVal;
            break;
        case 'S':
            waypoint.y -= opVal;
            break;
        case 'E':
            waypoint.x += opVal;
            break;
        case 'W':
            waypoint.x -= opVal;
            break;
        case 'L':
            {
                int angleIndex = opVal / 90;
                auto matrix = Rotate[angleIndex];
                int x = waypoint.x * matrix[0] + waypoint.y * matrix[1];
                int y = waypoint.x * matrix[2] + waypoint.y * matrix[3];
                waypoint.x = x;
                waypoint.y = y;
            }
            break;
        case 'R':
            {
                // clockwise => negative direction for sin() and cos()
                int angleIndex = (4 - opVal / 90);
                auto matrix = Rotate[angleIndex];
                int x = waypoint.x * matrix[0] + waypoint.y * matrix[1];
                int y = waypoint.x * matrix[2] + waypoint.y * matrix[3];
                waypoint.x = x;
                waypoint.y = y;
            }
            break;
        case 'F':
            ship.x += waypoint.x * opVal;
            ship.y += waypoint.y * opVal;
            break;
    }
}
