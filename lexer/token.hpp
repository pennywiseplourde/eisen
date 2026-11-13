#pragma once
#include <string>

typedef size_t index;

enum tokenType {
    //literals
    integer_,
    decimal_,
    bool_,
    string_,

    identifier_,

    thread_,
    once_,
    loop,
    let_,
    if_,
    elif_,
    else_,
    fail_,
    exit_,
    free_,
    print_,
    
    intType_,
    decimalType_,
    boolType_,
    stringType_,

    plus_,
    minus_,
    assign_,
    insertion_,
    less_,

    leftparen_,
    rightparen_,
    leftbrace_,
    rightbrace_,
    semicolon_,
    colon_,
    dot_,
    openquote_,
    closequote_,

    newline_,

    eof_

};

typedef tokenType tt;

struct token {
    tokenType type;
    std::string value;

    index line;
    index column;

    std::string string() {
        return "type: " + std::to_string((int)type) + "\nvalue: " + value + "\nline: " + std::to_string(line) + "\n";
    }
};