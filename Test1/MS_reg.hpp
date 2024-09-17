#pragma once

#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include "register_2_byte.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

namespace CPU
{
    class MS_reg {
        CPU::register_2_byte master;
        CPU::register_2_byte slave;

    public:
        void set_1_byte(byte value);

        void set_2_byte(byte value);
 
        void write_slave_to_master();

        byte get_1_MS();

        byte get_2_MS();

        addr get_full_MS();
    };
}