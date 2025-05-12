//
// Created by mestre on 5/3/25.
//

#include "Command/Slide.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        Slide::Slide(int dx, int dy): Command("slide"), delta_x(dx), delta_y(dy) {}

        Slide::~Slide() = default;

        // Slides all pixels horizontally by delta_x and vertically by delta_y, wrapping around.
        Image* Slide::apply(Image* img) {
            int width = img->width();
            int height = img->height();
            // Create a new image to store the result of the slide
            Image* new_img = new Image(width, height, Color());

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    // Calculate the new wrapped position
                    int new_x = (x + delta_x % width + width) % width;
                    int new_y = (y + delta_y % height + height) % height;

                    // Copy the pixel from the original position to the new wrapped position
                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            delete img;
            return new_img;
        }

        std::string Slide::toString() const {
            std::ostringstream ss;
            ss << name() << " " << delta_x << " " << delta_y;
            return ss.str();
        }

    }
}