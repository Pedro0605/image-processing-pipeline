//
// Created by Lucas on 14/5/2025.
//

#include "Command/Replace.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Initializes the command with the name "replace".
        Replace::Replace(Color target, Color replacer)
            : Command("replace"), target(target), replacer(replacer) {}

        // Destructor.
        Replace::~Replace() = default;

        // Pixels matching the target color are replaced with the specified replacer color.
        Image* Replace::apply(Image* img) {
            for (int y = 0; y < img->height(); y++) {
                for (int x = 0; x < img->width(); x++) {

                    // Access the pixel at position (x, y).
                    Color& color = img->at(x, y);

                    // Check if current pixel matches the target color.
                    // Then replaces pixel's color with the replacer color.
                    if (color.red() == target.red() && color.green() == target.green() &&color.blue() == target.blue()) {
                        color = replacer;
                    }
                }
            }
            return img;
        }

        // Returns a string representing the command and its parameters.
        std::string Replace::toString() const {
            std::ostringstream ss;
            ss << name() << " "
               << target.red() << " " << target.green() << " " << target.blue() << " "
               << replacer.red() << " " << replacer.green() << " " << replacer.blue();
            return ss.str();
        }

    }
}