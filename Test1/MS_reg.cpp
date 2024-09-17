#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include "register_2_byte.hpp"

#include "MS_reg.hpp"

typedef uint8_t byte;
typedef uint16_t addr;

using namespace CPU;

    void MS_reg::set_1_byte(byte value)
    {
        slave.set_Addr_1_byte(value);
    }
    void MS_reg::set_2_byte(byte value)
    {
        MS_reg::slave.set_Addr_2_byte(value);
    }
    void MS_reg::write_slave_to_master()
    {
        master.set_Addr_full(slave.get_Addr_full());
    }
    byte MS_reg::get_1_MS()
    {
        return master.get_Addr_1_byte();
    }
    byte MS_reg::get_2_MS()
    {
        return master.get_Addr_2_byte();
    }
    addr MS_reg::get_full_MS()
    {
        return master.get_Addr_full();
    }