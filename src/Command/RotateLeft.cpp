//
// Created by mestre on 11/5/2025.
//

#include "Command/RotateLeft.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Constructor initializing the command name "rotate_left".
        RotateLeft::RotateLeft(): Command("rotate_left") {}

        // Destructor.
        RotateLeft::~RotateLeft() {}

        // Rotates the image left by 90 degrees.
        Image* RotateLeft::apply(Image* img) {
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

                    // Calculate the new position
                    int new_x = y;
                    int new_y = old_width - 1 - x;

                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            // Delete the original image to prevent memory leak.
            delete img;
            return new_img;
        }

        // Returns the command name as a string.
        std::string RotateLeft::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}