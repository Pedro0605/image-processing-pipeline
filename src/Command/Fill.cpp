//
// Created by mestre on 9/5/2025.
//

#include "Command/Fill.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>
#include <algorithm>  // For std::max and std::min.

namespace prog {

    namespace command {

        // Initializes the fill region's top-left coordinates, dimensions, and color.
        Fill::Fill(int x, int y, int w, int h, Color c)
            : Command("fill"), fill_x(x), fill_y(y), fill_w(w), fill_h(h), fill_color(c) {}

        // Destructor.
        Fill::~Fill() {}

        // Executes the fill operation on the image by coloring the rectangular section.
        // The fill region is adjusted to remain within the image boundaries.
        Image* Fill::apply(Image* img) {
            int img_width = img->width();
            int img_height = img->height();

            // Limit the starting and ending points to ensure they are within the image limits.
            int start_x = std::max(0, fill_x);
            int start_y = std::max(0, fill_y);
            int end_x = std::min(img_width, fill_x + fill_w);
            int end_y = std::min(img_height, fill_y + fill_h);

            // Fill the specified rectangle with the chosen color.
            for (int y = start_y; y < end_y; y++) {
                for (int x = start_x; x < end_x; x++) {
                    img->at(x, y) = fill_color;
                }
            }

            return img;
        }

        // Returns a string representation of the v_mirror command.
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