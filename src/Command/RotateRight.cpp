//
// Created by mestre on 11/5/2025.
//

#include "Command/RotateRight.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Constructor initializing the command name "rotate_right".
        RotateRight::RotateRight() : Command("rotate_right") {}

        // Destructor.
        RotateRight::~RotateRight() {}

        // Rotates the image right by 90 degrees.
        Image* RotateRight::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // The new image dimensions are swapped.
            int new_width = old_height;
            int new_height = old_width;

            // Create a new image with rotated dimensions, filled with default color.
            Image* new_img = new Image(new_width, new_height, Color());

            // Copy each pixel from the original to its rotated position.
            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {

                    // Calculate the new position.
                    int new_x = old_height - 1 - y;
                    int new_y = x;

                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            // Delete the original image to prevent memory leak.
            delete img;
            return new_img;
        }

        // Returns a string representing the command.
        std::string RotateRight::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}