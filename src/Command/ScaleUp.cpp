//
// Created by mestre on 5/6/25.
//

#include "Command/ScaleUp.hpp"
#include "Image.hpp"
#include <sstream>

namespace prog {
    namespace command {

        ScaleUp::ScaleUp(int fx, int fy): Command("scaleup"), factor_x(fx), factor_y(fy) {}

        ScaleUp::~ScaleUp() = default;

        // Scales up the image by integer factors fx horizontally and fy vertically.
        Image* ScaleUp::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // New image dimensions
            int new_width = old_width * factor_x;
            int new_height = old_height * factor_y;

            Image* new_img = new Image(new_width, new_height, Color()); // New image filled with default color

            for (int y = 0; y < old_height; ++y) {
                for (int x = 0; x < old_width; ++x) {
                    Color pixel_color = img->at(x, y);
                    // Copy the pixel color to the corresponding block in the new image
                    for (int dy = 0; dy < factor_y; ++dy) {
                        for (int dx = 0; dx < factor_x; ++dx) {
                            int new_x = x * factor_x + dx;
                            int new_y = y * factor_y + dy;
                            new_img->at(new_x, new_y) = pixel_color;
                        }
                    }
                }
            }

            delete img;
            return new_img;
        }

        std::string ScaleUp::toString() const {
            std::ostringstream ss;
            ss << name() << " " << factor_x << " " << factor_y;
            return ss.str();
        }

    }
}