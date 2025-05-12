//
// Created by mestre on 5/3/25.
//

#include "Command/Move.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        Move::Move(int dx, int dy)
            : Command("move"), delta_x(dx), delta_y(dy) {}

        Move::~Move() = default;

        // Moves all pixels horizontally by delta_x and vertically by delta_y.
        // Pixels that end up outside bounds are discarded. New areas get fill color.
        Image* Move::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();
            Image* new_img = new Image(old_width, old_height, Color(255, 255, 255));

            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {
                    int new_x = x + delta_x;
                    int new_y = y + delta_y;

                    // Check if the new position is within the new image bounds
                    if (new_x >= 0 && new_x < old_width && new_y >= 0 && new_y < old_height) {
                        new_img->at(new_x, new_y) = img->at(x, y);
                    }
                    // Pixels outside the bounds are discarded
                    // New areas are already filled with the default Color()
                }
            }

            delete img;
            return new_img;
        }

        std::string Move::toString() const {
            std::ostringstream ss;
            ss << name() << " " << delta_x << " " << delta_y;
            return ss.str();
        }

    }
}