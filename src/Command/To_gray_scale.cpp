//
// Created by mestre on 4/30/25.
//

#include "Command/To_gray_scale.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        to_gray_scale::to_gray_scale() : Command("to_gray_scale"){}

        to_gray_scale::~to_gray_scale() {}

        //Loops through each "pixel" and changes it to the average between the r, g and b values
        Image *to_gray_scale::apply(Image *img)
        {
            for (int y = 0; y < img->height(); y++)
            {
                for (int x = 0; x < img->width(); x++)
                {
                    Color &color = img->at(x, y);
                    unsigned char new_color = (color.red() + color.green() + color.blue()) / 3;
                    color = {new_color, new_color, new_color};
                }
            }
            return img;
        }

        std::string to_gray_scale::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }
    }
}