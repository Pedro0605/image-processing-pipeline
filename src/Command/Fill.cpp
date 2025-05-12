//
// Created by mestre on 4/30/25.
//

#include "Command/Fill.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>
#include <algorithm>

namespace prog {
    namespace command {

        Fill::Fill(int x, int y, int w, int h, Color c)
            : Command("fill"), fill_x(x), fill_y(y), fill_w(w), fill_h(h), fill_color(c) {}

        Fill::~Fill() = default;

        // Fills a rectangle in the image with a given color
        Image* Fill::apply(Image* img) {
            int img_width = img->width();
            int img_height = img->height();

            // Calculate the actual region to fill, correcting to image bounds
            int start_x = std::max(0, fill_x);
            int start_y = std::max(0, fill_y);
            int end_x = std::min(img_width, fill_x + fill_w);
            int end_y = std::min(img_height, fill_y + fill_h);

            for (int y = start_y; y < end_y; ++y) {
                for (int x = start_x; x < end_x; ++x) {
                    img->at(x, y) = fill_color;
                }
            }

            return img; // Modified in place
        }

        std::string Fill::toString() const {
            std::ostringstream ss;
            ss << name() << " "
               << fill_x << " " << fill_y << " " << fill_w << " " << fill_h << " "
               << static_cast<int>(fill_color.red()) << " "
               << static_cast<int>(fill_color.green()) << " "
               << static_cast<int>(fill_color.blue());
            return ss.str();
        }

    }
}