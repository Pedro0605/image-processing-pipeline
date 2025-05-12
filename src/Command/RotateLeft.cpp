//
// Created by mestre on 5/5/25.
//

#include "Command/RotateLeft.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        RotateLeft::RotateLeft(): Command("rotate_left") {}

        RotateLeft::~RotateLeft() = default;

        // Rotates the image left by 90 degrees.
        Image* RotateLeft::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // The new image dimensions are swapped
            int new_width = old_height;
            int new_height = old_width;

            Image* new_img = new Image(new_width, new_height, Color()); // New image filled with default color

            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {
                    // Calculate the new position after rotating left 90 degrees
                    int new_x = y;
                    int new_y = old_width - 1 - x;
                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            delete img;
            return new_img;
        }

        std::string RotateLeft::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}