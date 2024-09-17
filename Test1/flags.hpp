#pragma once

namespace CPU
{
    class flags {
        bool flag;

    public:
        flags();

        void set_flag(bool val);

        bool get_flag();
    };
}