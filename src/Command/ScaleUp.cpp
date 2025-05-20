//
// Created by Lucas on 15/5/2025.
//

#include "Command/ScaleUp.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Constructor initializing the scale factors and command name.
        ScaleUp::ScaleUp(int fx, int fy): Command("scaleup"), factor_x(fx), factor_y(fy) {}

        // Destructor.
        ScaleUp::~ScaleUp() = default;

        // Scales up the image by integer factors fx horizontally and fy vertically.
        Image* ScaleUp::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // New image dimensions.
            int new_width = old_width * factor_x;
            int new_height = old_height * factor_y;

            // Create a new blank image with enlarged dimensions.
            Image* new_img = new Image(new_width, new_height, Color());

            // Iterate over each pixel in the original image.
            for (int y = 0; y < old_height; y++) {
                for (int x = 0; x < old_width; x++) {
                    Color pixel_color = img->at(x, y);

                    // Copy the pixel into a rectangle of dimensions (fx, fy) in the new image.
                    for (int dy = 0; dy < factor_y; dy++) {
                        for (int dx = 0; dx < factor_x; dx++) {
                            int new_x = x * factor_x + dx;
                            int new_y = y * factor_y + dy;
                            new_img->at(new_x, new_y) = pixel_color;
                        }
                    }
                }
            }

            // Delete the original image to prevent memory leak.
            delete img;
            return new_img;
        }

        // Returns the command name as a string.
        std::string ScaleUp::toString() const {
            std::ostringstream ss;
            ss << name() << " " << factor_x << " " << factor_y;
            return ss.str();
        }

    }
}