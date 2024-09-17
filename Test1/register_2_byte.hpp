#pragma once

#ifndef LLLLLL
#define LLLLLL

#include <iostream>
#include <cstdint>
#include <stdlib.h>

typedef uint8_t byte;
typedef uint16_t addr;

namespace CPU
{
    class register_2_byte
    {
        addr Address;

    public:
        void incr();

        void decr();

        void set_Addr_1_byte(byte value);

        void set_Addr_2_byte(byte value);

        byte get_Addr_2_byte();

        byte get_Addr_1_byte();

        addr get_Addr_full();

        void set_Addr_full(addr address);

        void swap();
    };
}

#endif 