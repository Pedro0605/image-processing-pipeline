//
// Created by mestre on 10/5/25.
//

#include "Command/H_mirror.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>
#include <algorithm>

namespace prog {

    namespace command {

        // Initializes the command with the name "h_mirror".
        h_mirror::h_mirror() : Command("h_mirror") {}

        // Destructor.
        h_mirror::~h_mirror() {}

        // Performs a horizontal flip on the image by swapping pixels across the vertical axis.
        // Iterates through each row, exchanging pixels from the left and right sides.
        Image *h_mirror::apply(Image *img) {
            int width = img->width();
            int height = img->height();

            // Loop through each row.
            for (int y = 0; y < height; y++) {
                // Swap pixels from left and right sides of the row.
                // Iterates until the halfway  point of the image so that each pixel  is affected once.
                for (int x = 0; x < width / 2; x++) {

                    Color &left = img->at(x, y);
                    Color &right = img->at(width - 1 - x, y);
                    std::swap(left, right); // Swap pixels.
                }
            }
            return img;
        }

        // Returns a string representation of the h_mirror command.
        std::string h_mirror::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}