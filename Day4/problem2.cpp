
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>


struct Passport
{
    int byr;
    int iyr;
    int eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid;

    Passport() 
        : byr(-1), iyr(-1), eyr(-1)
    {}
};

Passport getNextPassport(std::ifstream& fin);
bool isValid(const Passport& passport);

std::regex hclRule("#[0-9a-f]{6}");
std::regex eclRule("amb|blu|brn|gry|grn|hzl|oth");
std::regex pidRule("[0-9]{9}");

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::cout << "Input: " << inputFile << std::endl;

    std::ifstream fin(inputFile);

    int validCount = 0;
    while (!fin.eof()) {
        auto passport = getNextPassport(fin);
//        std::cout << "byr: " << passport.byr << "; iyr: " << passport.iyr << "; eyr: " << passport.eyr << "; hgt: " << passport.hgt
//            << "; hcl: " << passport.hcl << "; ecl: " << passport.ecl << "; pid: " << passport.pid << "; cid: " << passport.cid << std::endl;

        bool validPassport = isValid(passport);
        validCount += validPassport ? 1 : 0;
        std::cout << (validPassport ? "Valid" : "Invalid") << std::endl;
    }
    
    fin.close();

    std::cout << validCount << std::endl;

    return 0;
}

Passport getNextPassport(std::ifstream& fin)
{
    Passport result;

    std::string line;
    while (getline(fin, line)) {
        std::cout << "[" << line.size() << "] " << line << std::endl;
        if (line.size() < 3) {
            return result;
        }

        std::istringstream lineReader(line);
        std::string entry;
        while (lineReader >> entry) {
            std::string key = entry.substr(0, 3);
            std::string value = entry.substr(4);
            if (key == "byr") {
                result.byr = stoi(value);
            } else if (key == "iyr") {
                result.iyr = stoi(value);
            } else if (key == "eyr") {
                result.eyr = stoi(value);
            } else if (key == "hgt") {
                result.hgt = value;
            } else if (key == "hcl") {
                result.hcl = value;
            } else if (key == "ecl") {
                result.ecl = value;
            } else if (key == "pid") {
                result.pid = value;
            } else if (key == "cid") {
                result.cid = value;
            }
        }
    }

    return result;
}

bool isValidHeight(const std::string& heightString)
{
    int length = heightString.size();
    if (length > 2) {
        bool usingCM = heightString[length - 2] == 'c' && heightString[length - 1] == 'm';
        bool usingIN = heightString[length - 2] == 'i' && heightString[length - 1] == 'n';
        int value = stoi(heightString.substr(0, length - 2));
        if (usingCM) {
            return value >= 150 && value <= 193;
        } else if (usingIN) {
            return value >= 59 && value <= 76;
        }
    }

    return false;
}

bool isValid(const Passport& passport)
{
    bool validByr = passport.byr >= 1920 && passport.byr <= 2002;
    bool validIyr = passport.iyr >= 2010 && passport.iyr <= 2020;
    bool validEyr = passport.eyr >= 2020 && passport.eyr <= 2030;

    bool validHgt = isValidHeight(passport.hgt);
    bool validHcl = std::regex_match(passport.hcl, hclRule);
    bool validEcl = std::regex_match(passport.ecl, eclRule);
    bool validPid = std::regex_match(passport.pid, pidRule);

    return validByr && validIyr && validEyr &&
        validHgt && validHcl && validEcl && validPid;
}
