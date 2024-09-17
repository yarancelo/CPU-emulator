#include <iostream>
#include <cstdint>
#include <stdlib.h>

#include "register_1_byte.hpp"
#include "register_2_byte.hpp"
#include "flags.hpp"
#include "ram.hpp"
#include "MS_reg.hpp"
#include "cpu.hpp"

typedef uint8_t byte;
typedef uint16_t addr;


int main()
{
    CPU::cpu CPU;
    CPU.RAM.init();
    CPU.RAM.write((int)CPU::cpu::instructions::LDAI, 0);
    CPU.RAM.write(100, 1);
    CPU.RAM.write((int)CPU::cpu::instructions::LDBI, 2);
    CPU.RAM.write(200, 3);
    CPU.RAM.write((int)CPU::cpu::instructions::STOREA, 4);
    CPU.RAM.write(0, 5);
    CPU.RAM.write(101, 6);
    CPU.RAM.write((int)CPU::cpu::instructions::STOREB, 7);
    CPU.RAM.write(0, 8);
    CPU.RAM.write(102, 9);
    CPU.RAM.write((int)CPU::cpu::instructions::HLT, 10);

    for (int i = 0; i < 25; i++)
    {
        CPU.cycle(1);
    }

    return 0;
}
