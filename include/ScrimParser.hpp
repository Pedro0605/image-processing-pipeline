//
// Created by JBispo on 05/04/2025.
//
#ifndef PROJECT_SCRIMPARSER_H
#define PROJECT_SCRIMPARSER_H

#include "Scrim.hpp"
#include "Command.hpp" // Required for parse_command return type
#include "Image.hpp" // Required by some commands
#include "Color.hpp" // Required by some commands
#include <iostream>
#include <string>
#include <vector> // Required for call_stack

namespace prog {
    class ScrimParser {
    public:
        ScrimParser();

        ~ScrimParser();

        static std::vector<std::string> call_stack;

        static Scrim *parseScrim(std::istream &input, bool chained = false);

        static Scrim *parseScrim(const std::string &filename);

        static Scrim *parseScrim(const std::string &filename, bool chained);

        static Command *parse_command(std::string command_name, std::istream &input);
    };
}

#endif //PROJECT_SCRIMPARSER_H