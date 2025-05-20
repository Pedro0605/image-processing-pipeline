//
// Created by Lucas on 15/5/2025.
//

#include "Command/Move.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {


        // Initializes the command with the name "move".
        Move::Move(int dx, int dy)
            : Command("move"), dx(dx), dy(dy) {}

        // Destructor.
        Move::~Move() = default;

        // Moves all pixels horizontally by dx and vertically by dy.
        // Pixels that end up outside bounds are discarded. New areas get fill color.
        Image* Move::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();
            Image* new_img = new Image(old_width, old_height, Color(255, 255, 255));

            // Loop through every pixel in the original image.
            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {

                    // Calculate the new location for the current pixel.
                    int new_x = x + dx;
                    int new_y = y + dy;

                    // Check if the new position is within the new image bounds
                    if (new_x >= 0 && new_x < old_width && new_y >= 0 && new_y < old_height) {
                        new_img->at(new_x, new_y) = img->at(x, y);
                    }
                }
            }

            // Delete the original image to avoid memory leaks.
            delete img;
            return new_img;
        }

        // Converts this move command into a string that can be logged or stored.
        std::string Move::toString() const {
            std::ostringstream ss;
            ss << name() << " " << dx << " " << dy;
            return ss.str();
        }

    }
}