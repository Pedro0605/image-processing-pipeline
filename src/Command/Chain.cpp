//
// Created by mestre on 5/11/25.
//

#include "Command/Chain.hpp"
#include "ScrimParser.hpp"
#include "Scrim.hpp"
#include "Logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace prog {
    namespace command {

        Chain::Chain(const std::vector<std::string>& filenames): Command("chain"), filenames(filenames) {}

        Chain::~Chain() = default;

        Image* Chain::apply(Image* img) {
            for (const auto& filename : filenames) {
                if (std::find(ScrimParser::call_stack.begin(), ScrimParser::call_stack.end(), filename) != ScrimParser::call_stack.end()) {
                    *Logger::out() << "Recursive chain detected for '" << filename << "'. Ignoring.\n";
                    continue;
                }

                ScrimParser::call_stack.push_back(filename);
                *Logger::out() << "Entering chained file: '" << filename << "'\n";

                std::ifstream chained_file_stream(filename);

                if (!chained_file_stream.is_open()) {
                    *Logger::err() << "Error opening chained file: '" << filename << "'\n";
                    ScrimParser::call_stack.pop_back();
                    continue;
                }

                Scrim* chained_scrim = ScrimParser::parseScrim(chained_file_stream);


                if (chained_scrim != nullptr) {
                    img = chained_scrim->run(img, true); // Pass true to indicate it's a chained run

                    delete chained_scrim;
                } else {
                     *Logger::err() << "Error parsing chained file: '" << filename << "'. Skipping its commands.\n";
                }

                ScrimParser::call_stack.pop_back();
                *Logger::out() << "Exiting chained file: '" << filename << "'\n";

            }

            return img;
        }

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