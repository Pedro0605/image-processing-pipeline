//
// Created by mestre on 5/11/25.
//

#include "Command/Chain.hpp"
#include "ScrimParser.hpp"
#include "Scrim.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace prog {
    namespace command {

        // Initializes the Chain command with a list of filenames to chain.
        Chain::Chain(const std::vector<std::string>& filenames): Command("chain"), filenames(filenames) {}


        //Destructor.
        Chain::~Chain() {}

        Image* Chain::apply(Image* img) {
            for (const auto& filename : filenames) {

                // Prevent recursive inclusion using call stack
                if (std::find(ScrimParser::call_stack.begin(), ScrimParser::call_stack.end(), filename) != ScrimParser::call_stack.end()) {
                    continue;
                }

                // Push current file onto the call stack
                ScrimParser::call_stack.push_back(filename);

                std::ifstream chained_file_stream(filename);

                // Check if file opened successfully
                if (!chained_file_stream.is_open()) {
                    ScrimParser::call_stack.pop_back();
                    continue;
                }

                // Parse the scrim file into a Scrim object
                Scrim* chained_scrim = ScrimParser::parseScrim(filename, true);

                // Execute the filtered scrim
                img = chained_scrim->run(img);

                //Clean up.
                delete chained_scrim;

                // Pop the file from the call stack after processing
                ScrimParser::call_stack.pop_back();
            }
            // Return the final image after all chained scripts
            return img;
        }


        // Converts the chain command and its file list to a string
        std::string Chain::toString() const {
            std::ostringstream ss;
            ss << name();
            for (const auto& filename : filenames) {
                ss << " " << filename;
            }
            ss << " end";
            return ss.str();
        }

    }
}