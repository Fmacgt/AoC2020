
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


typedef long long i64;

bool isValid(i64 n, i64* preambles, int size);
i64 findWeakness(int start, int end, const std::vector<i64>& numbers);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    int preambleCount = 25;
    if (argc > 2) {
        preambleCount = std::stoi(argv[2]);
    }

    i64* preambles = new i64[preambleCount];
    std::vector<i64> numberBuffer;

    std::ifstream fin(inputFile);

    for (int i = 0; i < preambleCount; i++) {
        fin >> preambles[i];
        numberBuffer.push_back(preambles[i]);
    }

    // dequeue and enqueue at the same time...
    int headTail = 0;
    i64 n;
    while (fin >> n) {
        numberBuffer.push_back(n);

        if (!isValid(n, preambles, preambleCount)) {
            std::cout << n << std::endl;
            break;
        }

        preambles[headTail] = n;
        headTail = (headTail + 1) % preambleCount;
    }

    fin.close();

    // find the interval [a, b] s.t. sum(a, b) equals n
    i64 start = 0;
    i64 end = 0;
    size_t bufferSize = numberBuffer.size();
    i64 target = numberBuffer[bufferSize - 1];
    i64 sum = numberBuffer[start];
    i64 weakness = -1;
    while (start <= end && end < bufferSize) {
        if (sum < target) {
            // add one more number to the end if sum < n
            end++;
            if (end < bufferSize) {
                sum += numberBuffer[end];
            }
        } else if (sum > target) {
            // remove one number from the left if sun > n
            sum -= numberBuffer[start];
            start++;
        } else {
            // found the range
            weakness = findWeakness(start, end, numberBuffer);
            break;
        }
    }

    std::cout << "weakness: " << weakness << std::endl;

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

i64 findWeakness(int start, int end, const std::vector<i64>& numbers)
{
    std::cout << "[" << start << ", " << end << "]" << std::endl;
    i64 min = numbers[start];
    i64 max = numbers[start];
    i64 checksum = 0;
    for (int i = start; i <= end; i++) {
        i64 n = numbers[i];
        checksum += n;
        if (n < min) {
            min = n;
        }
        if (n > max) {
            max = n;
        }

        std::cout << n << ", ";
    }
    std::cout << std::endl;
    std::cout << "sum: " << checksum << std::endl;

    std::cout << "Min: " << min << "; Max: " << max << std::endl;

    return min + max;
}
