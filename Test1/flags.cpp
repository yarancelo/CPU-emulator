#include "flags.hpp"

using namespace CPU;

    flags::flags()
    {
        flag = false;
    }
    void flags::set_flag(bool val)
    {
        flag = val;
    }
    bool flags::get_flag()
    {
        return flag;
    }
