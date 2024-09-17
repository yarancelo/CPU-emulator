#pragma once

#include <iostream>
#include <cstdint>
#include <stdlib.h>

#include "register_1_byte.hpp"
#include "register_2_byte.hpp"
#include "flags.hpp"
#include "ram.hpp"
#include "MS_reg.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

namespace CPU
{
    class cpu {

        CPU::register_1_byte A_reg;      // Accumulator register 1 byte
        CPU::register_1_byte B_reg;      // B register 1 byte
        CPU::register_1_byte C_reg;      // C register 1 byte

        CPU::register_1_byte Instr_reg;  // Instruction register
        CPU::register_1_byte Out_reg;    // Output register

        CPU::MS_reg Addr_reg;            // Address reg
        CPU::register_2_byte TEMP_Addr;  // Temporary address reg
        CPU::register_2_byte PC;         // Programm counter
        CPU::register_2_byte SP;         // Stack pointer


        CPU::flags Zero_flag;            // Zero flag is set if res of an arithmethcal operation eq 0
        CPU::flags Carry_flag;           // Carry flag is set if res of an arithmetical operation > 255
        CPU::flags Equal_flag;           // Equal flag is set if values A and B are equal during CMP instr execution 
        CPU::flags Bigger_flag;          // Bigger flag is set if value A > value B during CMP instr execution
    public:
        //instructions:
        enum class instructions
        {
            // Инструкции загрузки регисторов
            LDA = 1,       // Load A Reg (Instr, 1 byte addr, 2 byte addr)                                       +
            LDB = 2,       // Load B Reg (Instr, 1 byte addr, 2 byte addr)                                       +
            LDC = 3,       // Load C Reg (Instr, 1 byte addr, 2 byte addr)                                       +
            LDAI = 4,      // Load A Reg immidiate (Instr, value)                                                +
            LDBI = 5,      // Load B Reg immidiate (Instr, value)                                                +
            LDCI = 6,      // Load C Reg immidiate (Instr, value)                                                +

            // Арифметические операции
            SUM = 7,       // Arithmetic sum of A + B stored in A (Instr)                                        +
            SUB = 8,       // Arithmetic sum of A - B stored in A (Instr)                                        +

            // Логические операции
            AND = 9,       // Logiacal A and B stored in A (Instr)                                               +
            OR = 10,       // Logiacal A or B stored in A (Instr)                                                +
            NOT = 11,      // Logiacal A not B stored in A (Instr)                                               +
            NAND = 12,     // Logiacal A nand B stored in A (Instr)                                              +
            NOR = 13,      // Logiacal A nor B stored in A (Instr)                                               +
            XOR = 14,      // Logiacal A xor B stored in A (Instr)                                               +
            NXOR = 15,     // Logiacal A nxor B stored in A (Instr)                                              +
            ROTL = 16,     // Rotate register A left (Instr)                                                     +     
            ROTR = 17,     // Rotete register A right (Instr)                                                    +
            CMP = 18,      // Compare A and B (Instr)                                                            +

            // Вывод данных
            LOUTA = 19,    // Load output register from A register (Instr)                                       +
            LOUTM = 20,    // Load Output register from memory (Instr, 1 byte addr, 2 byte addr)                 +
            DOUT = 21,     // Decimal console output of output register (Instr)                                  +
            COUT = 22,     // Char console output of output register (Instr)                                     +
            XOUT = 23,     // Hexademical output of output register (Instr)                                      +

            // Условный и безусловный переходы 
            JMP = 24,      // Jump to address following in memory (Instr, 1 byte addr, 2 byte addr)              +
            JZ = 25,       // Jump if zero flag == 1 (Instr, 1 byte addr, 2 byte addr)                           +
            JNZ = 26,      // Jump if zero flag == 0 (Instr, 1 byte addr, 2 byte addr)                           +
            JC = 27,       // Jump if carry flag == 1 (Instr, 1 byte addr, 2 byte addr)                          +
            JNC = 28,      // Jump if carry flag == 0 (Instr, 1 byte addr, 2 byte addr)                          +
            JE = 29,       // Jump if eqaul flag == 1 (Instr, 1 byte addr, 2 byte addr)                          +
            JNE = 30,      // Jump if equal flag == 0 (Instr, 1 byte addr, 2 byte addr)                          +
            JB = 31,       // Jump if bigger flag == 1 (Instr, 1 byte addr, 2 byte addr)                         +
            JL = 32,       // Jump if bigger flag == 0 (Instr, 1 byte addr, 2 byte addr)                         +

            // Микроинструкции
            CALL = 33,     // Call to subroutine, current address store in SP (Instr, 1 byte addr, 2 byte addr)  +
            RET = 34,      // Return from a subroutine to address in SP (Instr)                                  +

            // Общие
            NOOP = 35,     // Do nothing (Instr)                                   
            HLT = 36,      // Stop executing programm and exit (Instr)                                           +
            FLUSH = 37,    // Reset registers A, B, C, Address register and flags                                +

            // Операции над стеком 
            PUSHAD = 38,   // Push address from PC to SP (Instr)                                                 +
            POPAD = 39,    // Pop address from SP to PC (Instr)                                                  +
            PUSHVA = 40,   // Push A reg value to SP (Instr)                                                     +
            POPVA = 41,    // Pop SP value to A reg (Instr)                                                      +
            PUSHVB = 42,   // Push B reg value to SP (Instr)                                                     +
            POPVB = 43,    // Pop SP value to B reg (Instr)                                                      +           

            // Работа с памятью
            STOREA = 44,   // Store value from A reg to memory (Instr, 1 byte addr, 2 byte addr)                 +
            STOREB = 45,   // Store value from B reg to memory (Instr, 1 byte addr, 2 byte addr)                 +

            // Передвижение данных между регистрами
            MOVAB = 46,    // Move A -> B (Instr)                                                                +
            MOVBA = 47,    // Move B -> A (Instr)                                                                +
            MOVAC = 48,    // Move A -> C (Instr)                                                                +
            MOVBC = 49,    // Move B -> C (Instr)                                                                +
            MOVCA = 50,    // Move C -> A (Instr)                                                                +
            MOVCB = 51,    // Move C -> B (Instr)                                                                +
        };

        cpu();

        ~cpu();

        CPU::ram RAM;

        void ConsoleOutDecimal();

        void ConsoleOutChar();

        void ConsoleOutHex();

        void fetch();

        void execute();

        void fetch2addresses();

        void cycle(addr num);
    };
}