//
// Created by mestre on 5/5/25.
//

#include "Command/RotateRight.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        RotateRight::RotateRight()
            : Command("rotate_right") {}

        RotateRight::~RotateRight() = default;

        // Rotates the image right by 90 degrees.
        Image* RotateRight::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // The new image dimensions are swapped
            int new_width = old_height;
            int new_height = old_width;

            Image* new_img = new Image(new_width, new_height, Color()); // New image filled with default color

            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {
                    // Calculate the new position after rotating right 90 degrees
                    int new_x = old_height - 1 - y;
                    int new_y = x;
                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            delete img;
            return new_img;
        }

        std::string RotateRight::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}