
#include <vector>
#include <fstream>
#include <iostream>


int solution(const std::vector<int> numberList, int sum);


int main(int argc, char** argv)
{
    std::vector<int> numberList;

    std::ifstream fin("problem1.txt");
    int number;
    while (fin >> number) {
        numberList.push_back(number);
    }

    std::cout << solution(numberList, 2020) << std::endl;

    return 0;
}

int solution(const std::vector<int> numberList, int sum)
{
    int listSize = numberList.size();
    for (int i = 0; i < listSize - 2; i++) {
        int x = numberList[i];
        for (int j = i + 1; j < listSize - 1; j++) {
            int y = numberList[j];
            int twoSum = x + y;
            for (int k = j + 1; k < listSize; k++) {
                int z = numberList[k];
                if (twoSum + z == sum) {
                    std::cout << x << " x " << y << " x " << z << std::endl;
                    return x * y * z;
                }
            }
        }
    }

    return 0;
}
