//
// Created by mestre on 5/1/25.
//

#include "Command/Add.hpp"
#include "PNG.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Logger.hpp"
#include <sstream>

namespace prog {

    namespace command {

        Add::Add(std::string filename, Color neutral, int x, int y): Command("add"), filename(std::move(filename)), neutral(neutral), target_x(x), target_y(y) {}

        Add::~Add() {}

        // Copies non-neutral pixels from the given image into the current image at (x, y)
        Image *Add::apply(Image *img)
        {
            if (img == nullptr) {
                *Logger::err() << "Error: 'add' command requires an existing image, but received a null image.\n";
                return nullptr;
            }

            Image *source = loadFromPNG(filename);
            int src_width = source->width();
            int src_height = source->height();
            int dst_width = img->width();
            int dst_height = img->height();

            for (int y = 0; y < src_height; y++)
            {
                for (int x = 0; x < src_width; x++)
                {
                    const Color &pixel = source->at(x, y);
                    if (pixel.red() == neutral.red() &&
                        pixel.green() == neutral.green() &&
                        pixel.blue() == neutral.blue())
                    {
                        continue; // skip neutral
                    }

                    // dst_x and dst_y define the target coordinates where the source image pixels need to be inserted
                    int dst_x = target_x + x;
                    int dst_y = target_y + y;

                    if (dst_x < dst_width && dst_y < dst_height)
                    {
                        img->at(dst_x, dst_y) = pixel;
                    }
                }
            }

            delete source;
            return img;
        }

        std::string Add::toString() const {
            std::ostringstream ss;
            ss << name() << " "
               << filename << " "
               << static_cast<int>(neutral.red()) << " "
               << static_cast<int>(neutral.green()) << " "
               << static_cast<int>(neutral.blue()) << " "
               << target_x << " "
               << target_y;
            return ss.str();
        }

    }
}