#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include "register_2_byte.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

using namespace CPU;

    void register_2_byte::incr()
    {
        Address++;
    }

    void register_2_byte::decr()
    {
        Address--;
    }

    void register_2_byte::set_Addr_1_byte(byte value)
    {
        Address = value;
    }
    void register_2_byte::set_Addr_2_byte(byte value)
    {
        Address = Address << 8;
        Address += value;
    }
    byte register_2_byte::get_Addr_2_byte()
    {
        return (byte)Address;
    }
    byte register_2_byte::get_Addr_1_byte()
    {
        addr copy = Address;
        copy = copy >> 8;
        return (byte)copy;
    }
    addr register_2_byte::get_Addr_full()
    {
        return Address;
    }
    void register_2_byte::set_Addr_full(addr address)
    {
        Address = address;
    }

    void register_2_byte::swap()
    {
        byte a2 = get_Addr_1_byte();
        byte a1 = get_Addr_2_byte();
        set_Addr_1_byte(a1);
        set_Addr_2_byte(a2);
    }