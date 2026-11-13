#include "token.hpp"
#include "lexer.hpp"

using namespace std;

namespace lexer {

vector<token> lexer::tokenize () {

        bool donefile = false;
        vector<token> result;

        while (!donefile) {

            string buffer = "";
            ct::charType ctype = ct::identifier;
            bt::bufferType btype = bt::identifier;
            char cur = source[pos];
            bool doneword = false;
            bool first = true;
            index line_ = line;
            index column_ = column;

            while (!doneword) {

                cur = source[pos];

                if (end) {
                    ctype = ct::eof;
                } else if (pos >= MAX_POS) {
                    end = true;
                    doneword = true;
                    donefile = true;
                    break;
                }

                if (isalpha(cur) || cur == '_') {
                    ctype = ct::identifier;
                } else if (isdigit(cur)) {
                    ctype = ct::literal;
                } else if (isspace(cur)) {
                    ctype = ct::whitespace;
                } else if (isquote(cur)) {
                    ctype = ct::quote;
                } else { 
                    ctype = ct::symbol;
                }

                if (btype == bt::stringLiteral) {
                    if (ctype == ct::quote) {
                        // token finished
                    } else {
                        buffer += cur;
                        advance();
                        continue;
                    }
                }

                if (first && ctype != ct::whitespace) {
                    switch (ctype) {
                        case ct::identifier : btype = bt::identifier; break;
                        case ct::symbol : btype = bt::symbol; break;
                        case ct::literal : btype = bt::literal; break;
                        case ct::eof : btype = bt::eof;
                        case ct::quote : btype = bt::stringLiteral;
                    }

                    first = false;
                } else if (first && ctype == ct::whitespace) {
                    advance();
                    continue;
                } else if (!first && ctype == ct::whitespace) {

                    doneword = true;
                    continue;
                
                } else if (!first && ctype != ct::whitespace) {
                    if ((int)ctype != (int)btype) {
                        doneword = true;
                        continue;
                    }
                }

                buffer += cur;

                cur = advance();

            }

            tt ttype = tt::identifier_;

            switch (btype) {
                case bt::identifier :

                    ttype = tt::identifier_;

                    for (int i = 0; i < keywords.size(); i++) {
                        if (buffer == keywords[i].first) {
                            ttype = keywords[i].second;
                            break;
                        }
                    }

                break;

                case bt::symbol : 
                    for (int i = 0; i < symbols.size(); i++) {
                        if (buffer == symbols[i].first) {
                            ttype = symbols[i].second;
                            break;
                        }
                    }
                break;

                case bt::literal : 

                    ttype = integer_;

                break;

                case bt::eof : 
                    donefile = true;
                break;

                //next one should be for strings
            }

            if (!donefile) {

            token temp;

            temp.type = ttype;
            temp.value = buffer;
            temp.line = line_;
            temp.column = column;

            result.push_back(temp);
            std::cout << buffer << "\n";
            } else {
                continue;
            }

        }

        return result;
    }

}