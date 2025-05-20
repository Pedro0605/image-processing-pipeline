//
// Created by mestre on 10/5/2025.
//

#include "Command/V_mirror.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>
#include <algorithm> // For std::swap.

namespace prog {

    namespace command {

        // Initializes the command with the name "v_mirror".
        v_mirror::v_mirror() : Command("v_mirror") {}

        // Destructor.
        v_mirror::~v_mirror() {}

        // Applies a vertical mirror by swapping pixels across the horizontal axis.
        // For each column, swaps each pixel with its vertically opposite counterpart.
        Image *v_mirror::apply(Image *img) {
            int width = img->width();
            int height = img->height();

            // Loop through each row up to the vertical midpoint
            for (int y = 0; y < height / 2; y++) {
                for (int x = 0; x < width; x++) {
                    Color &top = img->at(x, y);
                    Color &bottom = img->at(x, height - 1 - y);
                    std::swap(top, bottom); // Swap the vertically mirrored pixels.
                }
            }
            return img;
        }

        // Returns a string representation of the v_mirror command.
        std::string v_mirror::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}