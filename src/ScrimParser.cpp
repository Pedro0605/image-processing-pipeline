//
// Created by JBispo on 05/04/2025.
//
#include "ScrimParser.hpp"

#include "Command/Blank.hpp"
#include "Command/Save.hpp"
#include "Command/Open.hpp"
#include "Command/Invert.hpp"
#include "Command/To_gray_scale.hpp"
#include "Command/Replace.hpp"
#include "Logger.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>


using std::ifstream;
using std::istream;
using std::string;
using std::vector;

namespace prog {
    ScrimParser::ScrimParser() {
    };

    ScrimParser::~ScrimParser() {
    };


    Scrim *ScrimParser::parseScrim(std::istream &input) {
        // Create vector where commands will be stored
        vector<Command *> commands;

        // Parse commands while there is input in the stream
        string command_name;
        while (input >> command_name) {
            Command *command = parse_command(command_name, input);

            if (command == nullptr) {
                // Deallocate already allocated commands
                for (Command *allocated_command: commands) {
                    delete allocated_command;
                }


                *Logger::err() << "Error while parsing command\n";
                return nullptr;
            }

            commands.push_back(command);
        }

        // Create a new image pipeline
        return new Scrim(commands);
    }


    Scrim *ScrimParser::parseScrim(const std::string &filename) {
        ifstream in(filename);
        return parseScrim(in);
    }

    Command *ScrimParser::parse_command(string command_name, istream &input) {
        if (command_name == "blank") {
            // Read information for Blank command
            int w, h;
            Color fill;
            input >> w >> h >> fill;
            return new command::Blank(w, h, fill);
        }

        if (command_name == "save") {
            // Read information for Save command
            string filename;
            input >> filename;
            return new command::Save(filename);
        }

        if (command_name == "open") {
            string filename;
            input >> filename;
            return new command::Open(filename);
        }

        if (command_name == "invert") {
            return new command::Invert();
        }

        if (command_name == "to_gray_scale")
        {
            return new command::to_gray_scale();
        }

        if (command_name == "replace")
        {
            unsigned int r1, g1, b1, r2, g2, b2;
            input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
            Color target = Color(static_cast<unsigned char>(r1), static_cast<unsigned char>(g1), static_cast<unsigned char>(b1));
            Color replacer = Color(static_cast<unsigned char>(r2), static_cast<unsigned char>(g2), static_cast<unsigned char>(b2));
            return new command::Replace(target, replacer);
        }

        // TODO: implement cases for the new commands

        *Logger::err() << "Command not recognized: '" + command_name + "'\n";
        return nullptr;
    }
}
