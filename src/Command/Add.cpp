//
// Created by mestre on 15/5/2025.
//

#include "Command/Add.hpp"
#include "PNG.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include "Logger.hpp"
#include <sstream>

namespace prog {

    namespace command {

        // Initializes the command with "add" and sets the overlay parameters.
        Add::Add(std::string filename, Color neutral, int x, int y): Command("add"), filename(std::move(filename)), neutral(neutral), target_x(x), target_y(y) {}

        // Destructor.
        Add::~Add() {}

        // Applies the 'add' command to the provided image.
        // Overlays another image loaded from a file, skipping pixels that match the neutral color.
        Image *Add::apply(Image *img) {
            // Validate that the base image exists.
            if (img == nullptr) {
                *Logger::err() << "Error: 'add' command requires an existing image, but received a null image.\n";
                return nullptr;
            }

            // Load the overlay image from the provided filename.
            Image *source = loadFromPNG(filename);

            // Get dimensions of both images.
            int src_width = source->width();
            int src_height = source->height();
            int dst_width = img->width();
            int dst_height = img->height();

            // Iterate over every pixel in the source image.
            for (int y = 0; y < src_height; y++) {
                for (int x = 0; x < src_width; x++) {

                    // Get the color of the current pixel in the overlay image.
                    const Color &pixel = source->at(x, y);

                    // If the pixel matches the neutral color, skip it.
                    if (pixel.red() == neutral.red() &&
                        pixel.green() == neutral.green() &&
                        pixel.blue() == neutral.blue())
                    {
                        continue;
                    }

                    // dst_x and dst_y define the target coordinates where the source image pixels need to be inserted.
                    int dst_x = target_x + x;
                    int dst_y = target_y + y;

                    // Only copy the pixel if it's within the bounds of the destination image.
                    if (dst_x < dst_width && dst_y < dst_height)
                    {
                        img->at(dst_x, dst_y) = pixel;
                    }
                }
            }

            // Release the memory used by the overlay image.
            delete source;
            return img;
        }

        // Returns a string representation of the add command.
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