#include <iostream>
#include <cstdint>
#include <stdlib.h>

#include "ram.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

using namespace CPU;

    void ram::init()
    {
        for (int i = 0; i < ram_size; i++)
        {
            memory[i] = 0;
        }
    }

    void ram::write(byte value, addr address)
    {
        memory[address] = value;
    }
    byte ram::read(addr address)
    {
        return memory[address];
    }