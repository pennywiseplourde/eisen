#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace flags {

    enum class mode {
        regular,
        version,
        help
    };

    struct args {
        std::string input;
        std::string output;
        bool overwrite;
        bool extra;
        mode opmode;
    };

    std::vector<std::string> createList(const int argc, const char* argv[]);

    flags::args handleFlags(const int argc, const char* argv[]);

}