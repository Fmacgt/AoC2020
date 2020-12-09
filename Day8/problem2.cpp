
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>


const int NOP = 0;
const int ACC = 1;
const int JMP = 2;

struct Instruction
{
    int opcode;
    int operand;
};


bool detectLoop(const std::vector<Instruction> instructions, int& result);

int main(int argc, char** argv)
{
    std::string inputFile = argc > 1 ? std::string(argv[1]) : "input.txt";
    std::ifstream fin(inputFile);

    std::vector<Instruction> instructions;

    std::string line;
    while (getline(fin, line)) {
        Instruction instruction;
        int sign = line[4] == '-' ? -1 : 1;
        instruction.operand = sign * stoi(line.substr(5));

        char opChar = line[0];
        switch (opChar) {
            case 'a':
                instruction.opcode = ACC;
                instructions.push_back(instruction);
                break;
            case 'n':
                instruction.opcode = NOP;
                instructions.push_back(instruction);
                break;
            case 'j':
                instruction.opcode = JMP;
                instructions.push_back(instruction);
                break;
        }
    }

    fin.close();

    // use a stupid n^2 search (there are about 500 instructions, so about 250000 loops :P
    int result = 0;
    int changeOp = -1;
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i].opcode == NOP) {
            instructions[i].opcode = JMP;
            if (detectLoop(instructions, result)) {
                changeOp = i;
                break;
            }
            // restore changes
            instructions[i].opcode = NOP;
        } else if (instructions[i].opcode == JMP) {
            instructions[i].opcode = NOP;
            if (detectLoop(instructions, result)) {
                changeOp = i;
                break;
            }
            // restore changes
            instructions[i].opcode = JMP;
        }
    }

    std::cout << result << "; Change: " << changeOp << std::endl;

    return 0;
}

bool detectLoop(const std::vector<Instruction> instructions, int& result)
{
    std::unordered_set<int> occurrenceMap;

    int pc = 0;
    int accumulator = 0;

    while (pc >= 0 && pc < instructions.size() && 
            occurrenceMap.count(pc) == 0) {
        occurrenceMap.emplace(pc);

        auto instruction = instructions[pc];
        switch (instruction.opcode) {
            case ACC:
                accumulator += instruction.operand;
            case NOP:
                pc++;
                break;
            case JMP:
                pc += instruction.operand;
                break;
        }
    }

    result = accumulator;
    return pc >= instructions.size();
}
