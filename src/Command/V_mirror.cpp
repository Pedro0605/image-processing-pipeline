//
// Created by mestre on 5/1/25.
//

#include "Command/V_mirror.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        v_mirror::v_mirror() : Command("v_mirror") {}

        v_mirror::~v_mirror() {}

        // Loops through each column and swaps pixels vertically across the middle
        Image *v_mirror::apply(Image *img)
        {
            int width = img->width();
            int height = img->height();

            for (int y = 0; y < height / 2; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Color &top = img->at(x, y);
                    Color &bottom = img->at(x, height - 1 - y);
                    std::swap(top, bottom);
                }
            }

            return img;
        }

        std::string v_mirror::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }

    }
}
