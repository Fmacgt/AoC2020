
#include <vector>
#include <set>
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
    std::set<int> checkedPool;

    // for each number x in the number list, compute the y = sum - x
    for (const int& x : numberList) {
        int y = sum - x;
        if (y >= 0) {
            // check if y already exists
            if (checkedPool.count(y) == 0) {
                // otherwise add y to the map
                checkedPool.emplace(x);
            } else {
                // return x * y if does
                std::cout << x << " x " << y << std::endl;
                return x * y;
            }
        }
    }
    
    return 0;
}
