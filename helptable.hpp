#pragma once
#include <string>

std::string helpTable = 
R"(Usage: eisen -i <input_file> -o <output_file>

Options:

-i, --input <FILE>     File to read from
-o, --output <FILE>    File to write to
-h, --help             Show this help screen
-V, --version          Show version information
    --overwrite        Write out if output file already exists)";