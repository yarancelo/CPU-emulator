#pragma once

#include <iostream>
#include <cstdint>
#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t addr;

namespace CPU
{
    class ram {
    public:
        static const int ram_size = 65536;

    private:
        byte memory[ram_size];

    public:

        void init();

        void write(byte value, addr address);

        byte read(addr address);
    };
}