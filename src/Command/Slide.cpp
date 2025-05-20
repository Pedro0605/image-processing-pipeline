//
// Created by Lucas on 15/5/2025.
//

#include "Command/Slide.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        // Initializes the command with horizontal (dx) and vertical (dy) displacement values.
        Slide::Slide(int dx, int dy): Command("slide"), delta_x(dx), delta_y(dy) {}

        // Destructor.
        Slide::~Slide() {}

        // Slides all pixels horizontally by dx and vertically by dy, wrapping around.
        Image* Slide::apply(Image* img) {
            int width = img->width();
            int height = img->height();

            // Create a new image to store the result of the slide.
            Image* new_img = new Image(width, height, Color());


            // Loop through all pixels in the original image.
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {

                    // Calculate the new wrapped position.
                    int new_x = (x + delta_x % width + width) % width;
                    int new_y = (y + delta_y % height + height) % height;

                    // Copy the pixel from the original position to the new wrapped position.
                    new_img->at(new_x, new_y) = img->at(x, y);
                }
            }

            // Delete the original image to prevent memory leak.
            delete img;
            return new_img;
        }

        // Converts the Slide command into a descriptive string for logging or saving.
        std::string Slide::toString() const {
            std::ostringstream ss;
            ss << name() << " " << delta_x << " " << delta_y;
            return ss.str();
        }

    }
}