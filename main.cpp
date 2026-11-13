#include "flags.hpp"
#include "lineguard.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "helptable.hpp"
#include "lexer/lexer.hpp"


int main (const int argc, const char* argv[]) {

    lineGuard guard;

    const flags::args options = flags::handleFlags(argc, argv);

    if (options.extra) {
        std::cerr << "\nUse -h or --help";
        return 1;
    }

    if (options.opmode == flags::mode::version) {
        std::cout << "Eisen v0\n(c) Parker Plourde 2026";
        return 0;
    }

    if (options.opmode == flags::mode::help) {
        std::cout << helpTable;
        return 0;
    }

    if (options.input.empty() && options.output.empty()) {
        std::cout << helpTable;
        return 1;
    }

    if (options.input.empty()) {
        std::cerr << "Use -i <file> to provide input.";
        return 1;
    }

    if (options.output.empty()) {
        std::cerr << "Use -o <file> to provide output.";
        return 1;
    }

    std::string file;

    {

        std::ifstream inFile(options.input);
        std::stringstream buffer;
        if (!inFile.is_open()) {
            std::cerr << "Couldn't open file: " << "\"" << options.input << "\"";
            return 1;
        } else {
            buffer << inFile.rdbuf();

        }

        file = buffer.str();

    }

    lexer::lexer lexer(file);

    std::vector<token> tokens = lexer.tokenize();

    file = "--TOKENS--\n";

    for (int i = 0; i < tokens.size(); i++) {
        file += tokens[i].string();
        file += "----------\n";
    }

    {
        if (std::filesystem::exists(options.output) && !options.overwrite) {
            std::cerr << "File: " << "\"" << options.output << "\"" << " already exists. Use --overwrite.";
        }
        std::ofstream outFile(options.output);

        if (!outFile.is_open()) {
            std::cerr << "Couldn't write to file: " << "\"" << options.output << "\"";
            return 1;
        } else {
            outFile << file;
        }
    }

    return 0;
}
