//
// Created by Lucas on 15/5/2025.
//

#include "Command/To_gray_scale.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Initializes the command with the name "to_gray_scale".
        to_gray_scale::to_gray_scale() : Command("To_gray_scale"){}

        // Destructor.
        to_gray_scale::~to_gray_scale() {}

        // Converts the image to grayscale by averaging each pixel's RGB values.
        // Then assigns the result to all three color channels.
        Image *to_gray_scale::apply(Image *img) {
            for (int y = 0; y < img->height(); y++) {
                for (int x = 0; x < img->width(); x++) {

                    // Access the pixel at position (x, y).
                    Color &color = img->at(x, y);

                    // Calculate the average of red, green, and blue components.
                    unsigned char new_color = (color.red() + color.green() + color.blue()) / 3;

                    // Set pixel's color to the computed grayscale value.
                    color = {new_color, new_color, new_color};

                }
            }
            return img;
        }

        // Returns a string representation of the command.
        std::string to_gray_scale::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}