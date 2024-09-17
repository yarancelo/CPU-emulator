#pragma once

#include <iostream>
#include <cstdint>
#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t addr;

namespace CPU
{
    class register_1_byte
    {
        byte Reg;

    public:
        void set_Reg(byte value);

        byte get_Reg();
    };
}