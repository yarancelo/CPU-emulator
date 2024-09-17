#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include "register_1_byte.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

using namespace CPU;


    void register_1_byte::set_Reg(byte value)
    {
        Reg = value;
    }

    byte register_1_byte::get_Reg()
    {
        return Reg;
    }