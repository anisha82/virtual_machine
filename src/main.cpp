// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <cstdint>

class VirtualMachine {
public:
    static const int MEMORY_SIZE = 256;
    std::vector<uint8_t> memory;

    uint8_t regA = 0;
    uint8_t regB = 0;
    uint8_t IP = 0;   // Instruction Pointer
    bool Z = false;   // Zero flag for comparisons

    enum InstructionSet {
        HLT = 0,  // Halt
        LDA,      // Load to register A
        LDB,      // Load to register B
        ADD,      // Add A and B, store result in A
        SUB,      // Subtract B from A, store result in A
        MUL,      // Multiply A and B, store result in A
        DIV,      // Divide A by B, store result in A
        AND,      // Bitwise AND between A and B
        OR,       // Bitwise OR between A and B
        XOR,      // Bitwise XOR between A and B
        CMP,      // Compare A and B, set Z if A == B
        JMP,      // Jump to an address
        JZ,       // Jump if zero flag is set
        JNZ,      // Jump if zero flag is not set
        PRN       // Print the value of register A
    };

    VirtualMachine() : memory(MEMORY_SIZE) {}

    void loadProgram(const std::vector<uint8_t>& program) {
        for (size_t i = 0; i < program.size() && i < MEMORY_SIZE; ++i) {
            memory[i] = program[i];
        }
    }

    void execute() {
        while (true) {
            uint8_t opcode = memory[IP];
            switch (opcode) {
                case HLT: return;
                case LDA: regA = memory[++IP]; break;
                case LDB: regB = memory[++IP]; break;
                case ADD: regA = regA + regB; Z = (regA == 0); break;
                case SUB: regA = regA - regB; Z = (regA == 0); break;
                case MUL: regA = regA * regB; Z = (regA == 0); break;
                case DIV:
                    if (regB != 0) regA = regA / regB;
                    else std::cerr << "Error: Division by zero\n";
                    Z = (regA == 0);
                    break;
                case AND: regA = regA & regB; Z = (regA == 0); break;
                case OR: regA = regA | regB; Z = (regA == 0); break;
                case XOR: regA = regA ^ regB; Z = (regA == 0); break;
                case CMP: Z = (regA == regB); break;
                case JMP: IP = memory[++IP] - 1; break;
                case JZ:  if (Z) IP = memory[++IP] - 1; else ++IP; break;
                case JNZ: if (!Z) IP = memory[++IP] - 1; else ++IP; break;
                case PRN: std::cout << "Output: " << (int)regA << std::endl; break;
                default: std::cerr << "Unknown instruction: " << (int)opcode << std::endl; return;
            }
            IP++;
        }
    }
};

int main() {
    VirtualMachine vm;

    std::vector<uint8_t> program = {
        VirtualMachine::LDA, 10,         // Load 10 into A
        VirtualMachine::LDB, 2,          // Load 2 into B
        VirtualMachine::MUL,             // Multiply A and B (A = 20)
        VirtualMachine::PRN,             // Print A (should print 20)
        
        VirtualMachine::DIV,             // Divide A by B (A = 10)
        VirtualMachine::PRN,             // Print A (should print 10)
        
        VirtualMachine::AND,             // Bitwise AND A and B (A = 0)
        VirtualMachine::PRN,             // Print A (should print 0)
        
        VirtualMachine::LDA, 5,          // Load 5 into A
        VirtualMachine::LDB, 3,          // Load 3 into B
        VirtualMachine::OR,              // Bitwise OR A and B (A = 7)
        VirtualMachine::PRN,             // Print A (should print 7)
        
        VirtualMachine::XOR,             // Bitwise XOR A and B (A = 4)
        VirtualMachine::PRN,             // Print A (should print 4)
        
        VirtualMachine::CMP,             // Compare A and B (sets Z flag to 0)
        VirtualMachine::JZ, 20,          // Jump to address 20 if A == B (doesn't jump)
        VirtualMachine::LDA, 100,        // Load 100 into A (since we didn't jump)
        VirtualMachine::PRN,             // Print A (should print 100)
        
        VirtualMachine::HLT              // Halt
    };

    vm.loadProgram(program);
    vm.execute();

    return 0;
}

