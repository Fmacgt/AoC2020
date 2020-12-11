
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>


typedef long long int64;


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

    adapters.push_back(0);
    std::sort(adapters.begin(), adapters.end());

    std::vector<int64> countBuffer(adapters.size(), 0);
    countBuffer[adapters.size() - 1] = 1;
    for (int i = adapters.size() - 2; i >= 0; i--) {
        int64 count = 0;
        int jolt = adapters[i];
        for (int j = 1; j <= 3; j++) {
            int ptr = i + j;
            if (ptr < adapters.size()) {
                int diff = adapters[ptr] - jolt;
                if (diff >= 1 && diff <= 3) {
                    count += countBuffer[ptr];
                }
            }
        }

        countBuffer[i] = count;
        std::cout << "[" << i << "]: " << jolt << "\t=> " << countBuffer[i] << std::endl;
    }

    std::cout << countBuffer[0] << std::endl;


    return 0;
}
