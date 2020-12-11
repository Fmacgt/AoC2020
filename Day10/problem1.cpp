
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";

    std::vector<int> adapters;

    std::ifstream fin(inputFile);
    int n;
    while (fin >> n) {
        adapters.push_back(n);
    }
    fin.close();

    std::sort(adapters.begin(), adapters.end());
    std::map<int, int> diffMap;

    int prev = 0;
    for (const int& i : adapters) {
        std::cout << i << "; ";
        diffMap[i - prev]++;
        prev = i;
    }
    diffMap[3]++;

    std::cout << std::endl << diffMap[1] << "; " << diffMap[3] << std::endl;
    std::cout << diffMap[1] * diffMap[3] << std::endl;

    return 0;
}
