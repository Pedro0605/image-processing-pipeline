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
#include "Command/Fill.hpp"
#include "Command/H_mirror.hpp"
#include "Command/V_mirror.hpp"
#include "Command/Move.hpp"
#include "Command/Slide.hpp"
#include "Command/Crop.hpp"
#include "Command/Resize.hpp"
#include "Command/RotateLeft.hpp"
#include "Command/RotateRight.hpp"
#include "Command/ScaleUp.hpp"
#include "Command/Add.hpp"
#include "Command/Chain.hpp"

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

    std::vector<std::string> ScrimParser::call_stack;


    ScrimParser::ScrimParser() {
    };

    ScrimParser::~ScrimParser() {
    };

    // Parses a Scrim pipeline from an input stream.
    // Reads command names and parses individual commands until the stream ends.
    Scrim *ScrimParser::parseScrim(std::istream &input) {
        vector<Command *> commands;

        // Parse commands while there is input in the stream
        string command_name;
        while (input >> command_name) {
            Command *command = parse_command(command_name, input);

            if (command == nullptr) {
                // Deallocate already allocated commands if parsing fails
                for (Command *allocated_command: commands) {
                    delete allocated_command;
                }

                *Logger::err() << "Error while parsing command '" << command_name << "'. Aborting scrim parsing.\n";
                return nullptr; // Indicate parsing failure
            }

            commands.push_back(command);
        }

        return new Scrim(commands);
    }


    // Parses a Scrim pipeline from a file.
    // This version is primarily a helper for Chain::apply.
    // Note: Recursion check for 'filename' must be done by the caller (Chain::apply)
    // BEFORE calling this method.
    Scrim *ScrimParser::parseScrim(const std::string &filename) {
        ifstream in(filename);
        if (!in.is_open()) {
             *Logger::err() << "Error opening file for parsing: '" << filename << "'\n";
             return nullptr; // Indicate file opening failure
        }
        // Delegate the actual parsing from the stream to the other parseScrim method
        return parseScrim(in);
    }

    // Parses a single command based on its name and the input stream.
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

        if (command_name == "to_gray_scale") {
            return new command::to_gray_scale();
        }

        if (command_name == "replace") {
            unsigned int r1, g1, b1, r2, g2, b2;
            input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
            Color target = Color(static_cast<unsigned char>(r1), static_cast<unsigned char>(g1), static_cast<unsigned char>(b1));
            Color replacer = Color(static_cast<unsigned char>(r2), static_cast<unsigned char>(g2), static_cast<unsigned char>(b2));
            return new command::Replace(target, replacer);
        }

        if (command_name == "fill") {
            int x, y, w, h;
            unsigned int r, g, b;
            input >> x >> y >> w >> h >> r >> g >> b;
            Color fill_color = Color(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
            return new command::Fill(x, y, w, h, fill_color);
        }

        if (command_name == "h_mirror") {
            return new command::h_mirror();
        }

        if (command_name == "v_mirror")
        {
            return new command::v_mirror();
        }

        if (command_name == "add") {
            string filename;
            unsigned int r, g, b;
            int x, y;
            input >> filename >> r >> g >> b >> x >> y;
            Color neutral = Color(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b));
            return new command::Add(filename, neutral, x, y);
        }

        if (command_name == "move") {
            int dx, dy;
            input >> dx >> dy;
            return new command::Move(dx, dy);
        }

        if (command_name == "slide") {
            int dx, dy;
            input >> dx >> dy;
            return new command::Slide(dx, dy);
        }

        if (command_name == "crop") {
            int x, y, w, h;
            input >> x >> y >> w >> h;
            return new command::Crop(x, y, w, h);
        }

        if (command_name == "resize") {
            int x, y, w, h;
            input >> x >> y >> w >> h;
            return new command::Resize(x, y, w, h);
        }

        if (command_name == "rotate_left") {
            return new command::RotateLeft();
        }

        if (command_name == "rotate_right") {
            return new command::RotateRight();
        }

        if (command_name == "scaleup") {
            int fx, fy;
            input >> fx >> fy;
            return new command::ScaleUp(fx, fy);
        }

        if (command_name == "chain") {
            std::vector<std::string> chained_filenames;
            std::string current_token;
            while (input >> current_token && current_token != "end") {
                if (current_token == "blank") {
                    int w, h, r, g, b;
                    input >> w >> h >> r >> g >> b;
                } else if (current_token == "save") {
                    std::string filename;
                    input >> filename;
                } else if (current_token == "open") {
                    std::string filename;
                    input >> filename;
                } else {
                    chained_filenames.push_back(current_token);
                }
            }
            return new command::Chain(chained_filenames);
        }


        *Logger::err() << "Command not recognized: '" + command_name + "'\n";
        // Return nullptr for unrecognized commands
        return nullptr;
    }
}