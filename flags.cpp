#include "flags.hpp"

using namespace std;

namespace flags {

    vector<string> createList(const int argc, const char* argv[]) {
        return vector<string>(argv + 1, argv + argc);
    }

    args handleFlags(const int argc, const char* argv[]) {

        vector<string> list = createList(argc, argv);

        args final;

        final.extra = false;
        final.opmode = mode::regular;

        for (uint i = 0; i < list.size();) {

            if (list[i] == "-i" || list[i] == "--input") {
                if (i + 1 < list.size()) {
                    final.input = list[i + 1];
                    list.erase(list.begin() + i);
                    list.erase(list.begin() + i);
                    continue;
                }
            }

            if (list[i] == "-o" || list[i] == "--output") {
                if (i + 1 < list.size()) {
                    final.output = list[i + 1];
                    list.erase(list.begin() + i);
                    list.erase(list.begin() + i);
                    continue;
                }
            }

            if (list[i] == "--overwrite") {
                final.overwrite = true;
                list.erase(list.begin() + i);
                continue;
            } else {
                final.overwrite = false;
            }

            if (list[i] == "-V" || list[i] == "--version") {
                final.opmode = mode::version;
                list.erase(list.begin() + i);
                continue;
            } else if (list[i] == "-h" || list[i] == "--help") {
                final.opmode = mode::help;
                list.erase(list.begin() + i);
                continue;
            }

            std::cerr << "\nInvalid flag: " << '\"' << list[i] << "\"\n";

            final.extra = true;

            i++;
        
        }

        return final;

    }

}