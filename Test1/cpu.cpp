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

using namespace CPU;

    cpu::cpu()
    {
        A_reg.set_Reg(0);
        B_reg.set_Reg(0);
        C_reg.set_Reg(0);
        Instr_reg.set_Reg(0);
        PC.set_Addr_full(0);
        Addr_reg.set_1_byte(0);
        Addr_reg.set_2_byte(0);
        Out_reg.set_Reg(0);
        TEMP_Addr.set_Addr_full(0);
        SP.set_Addr_full(65279); // Stack 265 byte deep

        RAM.init();
    }

    cpu::~cpu() = default;

    CPU::ram RAM;

    void cpu::ConsoleOutDecimal()
    {
        printf("%d", Out_reg.get_Reg());
    }

    void cpu::ConsoleOutChar()
    {
        printf("%c", Out_reg.get_Reg());
    }

    void cpu::ConsoleOutHex()
    {
        printf("%x", Out_reg.get_Reg());
    }

    void cpu::fetch()
    {
        Addr_reg.set_1_byte(PC.get_Addr_1_byte());
        Addr_reg.set_2_byte(PC.get_Addr_2_byte());
        Addr_reg.write_slave_to_master();

        Instr_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));

        printf("DEBUG: instruction %03d fetched\n", Instr_reg.get_Reg());
    }

    void cpu::execute()
    {
        byte instruction = Instr_reg.get_Reg();



        switch (instruction)
        {
        case (int)instructions::LDA:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());             // write values of 1 and 2 bytes from temporary register to address register
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            A_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));              // read value from memory stored in address from address register
            PC.incr();
            break;

        case (int)instructions::LDB:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            B_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::LDC:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            C_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::LDAI:
            PC.incr();
            Addr_reg.set_1_byte(PC.get_Addr_1_byte());
            Addr_reg.set_2_byte(PC.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            A_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::LDBI:
            PC.incr();
            Addr_reg.set_1_byte(PC.get_Addr_1_byte());
            Addr_reg.set_2_byte(PC.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            B_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::LDCI:
            PC.incr();
            Addr_reg.set_1_byte(PC.get_Addr_1_byte());
            Addr_reg.set_2_byte(PC.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            C_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::SUM:
            if ((A_reg.get_Reg() + B_reg.get_Reg()) > 255)
                Carry_flag.set_flag(true);
            else
                Carry_flag.set_flag(false);

            A_reg.set_Reg(A_reg.get_Reg() + B_reg.get_Reg());

            if (A_reg.get_Reg() > 255)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::SUB:
            if ((A_reg.get_Reg() + B_reg.get_Reg()) > 255)
                Carry_flag.set_flag(true);
            else
                Carry_flag.set_flag(false);

            A_reg.set_Reg(A_reg.get_Reg() - B_reg.get_Reg());

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::AND:
            A_reg.set_Reg(A_reg.get_Reg() & B_reg.get_Reg());

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::OR:
            A_reg.set_Reg(A_reg.get_Reg() | B_reg.get_Reg());

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::NOT:
            A_reg.set_Reg(~A_reg.get_Reg());

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::NAND:
            A_reg.set_Reg(~(A_reg.get_Reg() & B_reg.get_Reg()));

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::XOR:
            A_reg.set_Reg((A_reg.get_Reg() ^ B_reg.get_Reg()));

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::NXOR:
            A_reg.set_Reg(~(A_reg.get_Reg() ^ B_reg.get_Reg()));

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::ROTL:
            A_reg.set_Reg(A_reg.get_Reg() << 1);

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::ROTR:
            A_reg.set_Reg(A_reg.get_Reg() >> 1);

            if (A_reg.get_Reg() == 0)
                Zero_flag.set_flag(true);
            else
                Zero_flag.set_flag(false);

            PC.incr();
            break;

        case (int)instructions::CMP:

            if (A_reg.get_Reg() == B_reg.get_Reg())
            {
                Equal_flag.set_flag(true);
                Bigger_flag.set_flag(false);
            }
            else if (A_reg.get_Reg() > B_reg.get_Reg())
            {
                Bigger_flag.set_flag(true);
                Equal_flag.set_flag(false);
            }
            else
            {
                Bigger_flag.set_flag(false);
                Equal_flag.set_flag(false);
            }

            PC.incr();
            break;

        case (int)instructions::LOUTA:
            Out_reg.set_Reg(A_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::LOUTM:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            Out_reg.set_Reg(RAM.read(Addr_reg.get_full_MS()));
            PC.incr();
            break;

        case (int)instructions::DOUT:
            ConsoleOutDecimal();
            PC.incr();
            break;

        case (int)instructions::COUT:
            ConsoleOutChar();
            PC.incr();
            break;

        case (int)instructions::XOUT:
            ConsoleOutHex();
            PC.incr();
            break;

        case (int)instructions::JMP:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            PC.set_Addr_full(Addr_reg.get_full_MS());
            break;

        case (int)instructions::JZ:
            if (Zero_flag.get_flag() == true)
            {
                PC.incr();
                Addr_reg.set_1_byte(PC.get_Addr_1_byte());
                Addr_reg.set_2_byte(PC.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();
                TEMP_Addr.set_Addr_1_byte(RAM.read(Addr_reg.get_full_MS()));

                PC.incr();
                Addr_reg.set_1_byte(PC.get_Addr_1_byte());
                Addr_reg.set_2_byte(PC.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();
                TEMP_Addr.set_Addr_2_byte(RAM.read(Addr_reg.get_full_MS()));

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JNZ:
            if (Zero_flag.get_flag() == false)
            {
                PC.incr();
                Addr_reg.set_1_byte(PC.get_Addr_1_byte());
                Addr_reg.set_2_byte(PC.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();
                TEMP_Addr.set_Addr_1_byte(RAM.read(Addr_reg.get_full_MS()));

                PC.incr();
                Addr_reg.set_1_byte(PC.get_Addr_1_byte());
                Addr_reg.set_2_byte(PC.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();
                TEMP_Addr.set_Addr_2_byte(RAM.read(Addr_reg.get_full_MS()));

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JC:
            if (Carry_flag.get_flag() == true)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JNC:
            if (Carry_flag.get_flag() == false)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JE:
            if (Equal_flag.get_flag() == true)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JNE:
            if (Equal_flag.get_flag() == false)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JB:
            if (Bigger_flag.get_flag() == true)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::JL:
            if (Bigger_flag.get_flag() == false)
            {
                fetch2addresses();

                Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
                Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
                Addr_reg.write_slave_to_master();

                PC.set_Addr_full(Addr_reg.get_full_MS());
            }
            else
            {
                PC.incr();
                PC.incr();
                PC.incr();
            }
            break;

        case (int)instructions::CALL:
            // Сохранить PC следующей инструкции в стек
            // JMP по адресу

            RAM.write(PC.get_Addr_1_byte(), SP.get_Addr_full());
            SP.incr();
            RAM.write(PC.get_Addr_2_byte(), SP.get_Addr_full());
            SP.incr();

            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            PC.set_Addr_full(Addr_reg.get_full_MS());
            break;

        case (int)instructions::RET:
            // Сохранить PC следующей инструкции в стек
            // JMP по адресу
            SP.decr();
            TEMP_Addr.set_Addr_1_byte(RAM.read(SP.get_Addr_full()));
            SP.decr();
            TEMP_Addr.set_Addr_2_byte(RAM.read(SP.get_Addr_full()));
            TEMP_Addr.swap();

            PC.set_Addr_full(TEMP_Addr.get_Addr_full());

            PC.incr();
            PC.incr();
            PC.incr();
            break;

        case (int)instructions::HLT:
            printf("Execution finished\n");
            exit(0);
            break;

        case (int)instructions::NOOP:
            PC.incr();
            break;

        case (int)instructions::FLUSH:
            A_reg.set_Reg(0);
            B_reg.set_Reg(0);
            C_reg.set_Reg(0);
            Zero_flag.set_flag(false);
            Carry_flag.set_flag(false);
            Equal_flag.set_flag(false);
            Bigger_flag.set_flag(false);
            Addr_reg.set_1_byte(0);
            Addr_reg.set_2_byte(0);
            Addr_reg.write_slave_to_master();

            PC.incr();
            break;

        case (int)instructions::PUSHAD:
            RAM.write(PC.get_Addr_1_byte(), SP.get_Addr_full());
            SP.incr();
            RAM.write(PC.get_Addr_2_byte(), SP.get_Addr_full());
            SP.incr();

            PC.incr();
            break;

        case (int)instructions::POPAD:
            SP.decr();
            TEMP_Addr.set_Addr_1_byte(RAM.read(SP.get_Addr_full()));
            SP.decr();
            TEMP_Addr.set_Addr_2_byte(RAM.read(SP.get_Addr_full()));
            TEMP_Addr.swap();

            PC.set_Addr_full(TEMP_Addr.get_Addr_full());

            PC.incr();
            break;

        case (int)instructions::PUSHVA:
            RAM.write(A_reg.get_Reg(), SP.get_Addr_full());
            SP.incr();

            PC.incr();
            break;

        case (int)instructions::POPVA:
            SP.decr();
            A_reg.set_Reg(RAM.read(SP.get_Addr_full()));

            PC.incr();
            break;

        case (int)instructions::PUSHVB:
            RAM.write(B_reg.get_Reg(), SP.get_Addr_full());
            SP.incr();

            PC.incr();
            break;

        case (int)instructions::POPVB:
            SP.decr();
            B_reg.set_Reg(RAM.read(SP.get_Addr_full()));

            PC.incr();
            break;

        case (int)instructions::STOREA:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());             // write values of 1 and 2 bytes from temporary register to address register
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            RAM.write(A_reg.get_Reg(), Addr_reg.get_full_MS());

            PC.incr();
            break;

        case (int)instructions::STOREB:
            fetch2addresses();

            Addr_reg.set_1_byte(TEMP_Addr.get_Addr_1_byte());             // write values of 1 and 2 bytes from temporary register to address register
            Addr_reg.set_2_byte(TEMP_Addr.get_Addr_2_byte());
            Addr_reg.write_slave_to_master();

            RAM.write(B_reg.get_Reg(), Addr_reg.get_full_MS());

            PC.incr();
            break;

        case (int)instructions::MOVAB:
            B_reg.set_Reg(A_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::MOVBA:
            A_reg.set_Reg(B_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::MOVAC:
            A_reg.set_Reg(C_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::MOVBC:
            B_reg.set_Reg(C_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::MOVCA:
            C_reg.set_Reg(A_reg.get_Reg());
            PC.incr();
            break;

        case (int)instructions::MOVCB:
            C_reg.set_Reg(B_reg.get_Reg());
            PC.incr();
            break;

        default:
            printf("undefined instruction - %03d\n", Instr_reg.get_Reg());
            break;
        }
    }

    void cpu::fetch2addresses()
    {
        PC.incr();
        Addr_reg.set_1_byte(PC.get_Addr_1_byte());                    // set first byte of address register from PC
        Addr_reg.set_2_byte(PC.get_Addr_2_byte());                    // set second byte of address register from PC
        Addr_reg.write_slave_to_master();                             // write slave to master
        TEMP_Addr.set_Addr_1_byte(RAM.read(Addr_reg.get_full_MS()));  // write in temporary address register 1 byte of address where value stored from memory

        PC.incr();
        Addr_reg.set_1_byte(PC.get_Addr_1_byte());
        Addr_reg.set_2_byte(PC.get_Addr_2_byte());
        Addr_reg.write_slave_to_master();
        TEMP_Addr.set_Addr_2_byte(RAM.read(Addr_reg.get_full_MS()));  // write in temporary address register 2 byte of address where value stored from memory
    }

    void cpu::cycle(addr num)
    {
        for (addr i = 0; i < num; i++)
        {
            cpu::fetch();
            cpu::execute();
        }
    }