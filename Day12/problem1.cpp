
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    fin.close();

    return 0;
}
