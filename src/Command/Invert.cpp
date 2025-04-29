//
// Created by mestre on 4/29/25.
//

#include "Command/Invert.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "vector"
#include <sstream>

namespace prog {

    namespace command {

        Invert::Invert() : Command("invert"){}

        Invert::~Invert() {}

        Image *Invert::apply(Image *img)
        {
            for (int y = 0; y < img->height(); ++y)
            {
                for (int x = 0; x < img->width(); ++x)
                {
                    Color &color = img->at(x, y);
                    color.red() = 255 - color.red();
                    color.green() = 255 - color.green();
                    color.blue() = 255 - color.blue();
                }
            }
            return img;
        }

        std::string Invert::toString() const {
            std::ostringstream ss;
            ss << name();
            return ss.str();
        }
    }
}