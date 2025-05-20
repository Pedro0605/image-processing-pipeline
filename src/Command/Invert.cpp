//
// Created by Lucas on 15/5/2025.
//

#include "Command/Invert.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Initializes the command with the name "invert".
        Invert::Invert() : Command("invert") {}

        // Destructor.
        Invert::~Invert() {}

        // Each color channel (red, green, blue) is inverted by subtracting it from 255.
        Image *Invert::apply(Image *img)
        {
            for (int y = 0; y < img->height(); y++) {
                for (int x = 0; x < img->width(); x++) {

                    // Access the pixel at position (x, y).
                    Color &color = img->at(x, y);

                    // Invert each color channel (R,G,B).
                    color.red() = 255 - color.red();
                    color.green() = 255 - color.green();
                    color.blue() = 255 - color.blue();

                }
            }
            return img;
        }

        // Returns the string representation of this command.
        std::string Invert::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}