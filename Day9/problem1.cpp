
#include <iostream>
#include <fstream>
#include <string>


typedef long long i64;
bool isValid(i64 n, i64* preambles, int size);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    int preambleCount = 25;
    if (argc > 2) {
        preambleCount = std::stoi(argv[2]);
    }

    i64* preambles = new i64[preambleCount];

    std::ifstream fin(inputFile);

    for (int i = 0; i < preambleCount; i++) {
        fin >> preambles[i];
    }

    // dequeue and enqueue at the same time...
    int headTail = 0;
    i64 n;
    while (fin >> n) {
        if (!isValid(n, preambles, preambleCount)) {
            std::cout << n << std::endl;
            break;
        }

        preambles[headTail] = n;
        headTail = (headTail + 1) % preambleCount;
    }

    fin.close();

    return 0;
}

bool isValid(i64 n, i64* preambles, int size)
{
    // 25^2 search
    for (int i = 0; i < size - 1; i++) {
        i64 a = preambles[i];
        for (int j = i + 1; j < size; j++) {
            if (a + preambles[j] == n) {
                return true;
            }
        }
    }

    return false;
}
