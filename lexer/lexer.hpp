#pragma once
#include <string>
#include <vector>
#include "token.hpp"
#include <cctype>
#include <iostream>


namespace ct {
enum charType {
    identifier,
    symbol,
    literal,
    eof,
    quote,
    whitespace
};
}

namespace bt {
enum bufferType {
    identifier,
    symbol,
    literal,
    eof,
    stringLiteral,
    whitespace
};
}


const std::vector<std::pair<std::string, tokenType>> keywords = {

    {"thread", thread_},
    {"once", once_},
    {"int", intType_},
    {"print", print_}
};

const std::vector<std::pair<std::string, tokenType>> symbols = {

    {"+", plus_},
    {"-", minus_},
    {"(", leftparen_},
    {")", rightparen_},
    {":", colon_},
    {"{", leftbrace_},
    {"}", rightbrace_},
    {"=", assign_},
    {";", semicolon_},
    {"<<", insertion_}

};

namespace lexer {

class lexer {

    private:
        std::string source;

        index pos = 0;
        index line = 1;
        index column = 1;
        index MAX_POS;

        bool end = false;

        void increment () {
            if (!(pos + 1 > MAX_POS)) {
                pos++;
                column++;
                if (source[pos] == '\n') {
                    line++;
                    column = 1;
                }
            } else {
                end = true;
            }
        }

        char advance () {
            char temp = source[pos];
            increment();
            return temp;
        }

        bool isquote (char c) {
            if (c == '\'' || c == '\"') {
                return true;
            } else {
                return false;
            }
        }
    
    public:
        
    lexer (std::string source_) {
        source = source_ += ' ';
        MAX_POS = source.length();
    }

    std::vector<token> tokenize ();
    
};

}