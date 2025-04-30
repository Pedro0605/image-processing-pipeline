//
// Created by mestre on 4/30/25.
//

#include "Command/Replace.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {
    namespace command {

        Replace::Replace(Color target, Color replacer)
            : Command("replace"), target(target), replacer(replacer) {}

        Replace::~Replace() = default;

        Image* Replace::apply(Image* img) {
            for (int y = 0; y < img->height(); ++y) {
                for (int x = 0; x < img->width(); ++x) {
                    Color& color = img->at(x, y);
                    if (color.red() == target.red() && color.green() == target.green() &&color.blue() == target.blue()) {
                        color = replacer;
                    }
                }
            }
            return img;
        }

        std::string Replace::toString() const {
            std::ostringstream ss;
            ss << name() << " "
               << target.red() << " " << target.green() << " " << target.blue() << " "
               << replacer.red() << " " << replacer.green() << " " << replacer.blue();
            return ss.str();
        }

    }
}
