//
// Created by mestre on 5/1/25.
//

#include "Command/H_mirror.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        h_mirror::h_mirror() : Command("h_mirror") {}

        h_mirror::~h_mirror() {}

        // Loops through each row and swaps pixels horizontally across the middle
        Image *h_mirror::apply(Image *img)
        {
            int width = img->width();
            int height = img->height();

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width / 2; x++)
                {
                    Color &left = img->at(x, y);
                    Color &right = img->at(width - 1 - x, y);
                    std::swap(left, right);
                }
            }

            return img;
        }

        std::string h_mirror::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}
