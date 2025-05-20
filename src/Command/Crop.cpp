//
// Created by mestre on 11/5/25.
//

#include "Command/Crop.hpp"
#include "Image.hpp"
#include <sstream>
#include <algorithm>

namespace prog {

    namespace command {

        // Constructor: initializes the crop position and dimensions.
        Crop::Crop(int x, int y, int w, int h)
            : Command("crop"), crop_x(x), crop_y(y), crop_w(w), crop_h(h) {}

        // Destructor.
        Crop::~Crop() = default;

        // Crops the image to the specified rectangle.
        Image* Crop::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            // Calculate the actual region to crop from, correcting to image bounds.
            int src_start_x = std::max(0, crop_x);
            int src_start_y = std::max(0, crop_y);
            int src_end_x = std::min(old_width, crop_x + crop_w);
            int src_end_y = std::min(old_height, crop_y + crop_h);

            // Calculate the dimensions of the new cropped image.
            int new_width = src_end_x - src_start_x;
            int new_height = src_end_y - src_start_y;

            // Create new image.
            Image* new_img = new Image(new_width, new_height, Color());

            // Copy pixels from the source image to the cropped image.
            for (int y = src_start_y; y < src_end_y; y++) {
                for (int x = src_start_x; x < src_end_x; x++) {

                    // Calculate destination coordinates in the new image.
                    int dst_x = x - src_start_x;
                    int dst_y = y - src_start_y;

                    new_img->at(dst_x, dst_y) = img->at(x, y);
                }
            }

            // Delete the original image and return the cropped one.
            delete img;
            return new_img;
        }


        // Returns a string representation of the command and its parameters.
        std::string Crop::toString() const {
            std::ostringstream ss;
            ss << name() << " " << crop_x << " " << crop_y << " " << crop_w << " " << crop_h;
            return ss.str();
        }

    }
}