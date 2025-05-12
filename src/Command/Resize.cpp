//
// Created by mestre on 5/4/25.
//

#include "Command/Resize.hpp"
#include "Image.hpp"
#include <sstream>
#include <algorithm>

namespace prog {
    namespace command {

        Resize::Resize(int x, int y, int w, int h)
            : Command("resize"), resize_x(x), resize_y(y), resize_w(w), resize_h(h) {}

        Resize::~Resize() = default;

        // Resizes the image to the specified dimensions, keeping pixels in the given rectangle.
        Image* Resize::apply(Image* img) {
            int old_width = img->width();
            int old_height = img->height();

            Image* new_img = new Image(resize_w, resize_h, Color(255, 255, 255));

            // Calculate the region to copy from the old image, correcting to bounds
            int src_start_x = std::max(0, resize_x);
            int src_start_y = std::max(0, resize_y);
            int src_end_x = std::min(old_width, resize_x + resize_w);
            int src_end_y = std::min(old_height, resize_y + resize_h);

            // Calculate the corresponding region in the new image
            int dst_start_x = std::max(0, -resize_x); // If resize_x is negative, the copy starts from x=0 in old image
            int dst_start_y = std::max(0, -resize_y); // If resize_y is negative, the copy starts from y=0 in old image

            // Calculate the dimensions of the region to copy
            int copy_width = src_end_x - src_start_x;
            int copy_height = src_end_y - src_start_y;

            // Ensure the copy region is valid
            if (copy_width > 0 && copy_height > 0) {
                 for (int y = 0; y < copy_height; ++y) {
                     for (int x = 0; x < copy_width; ++x) {
                         int src_x = src_start_x + x;
                         int src_y = src_start_y + y;
                         int dst_x = dst_start_x + x;
                         int dst_y = dst_start_y + y;
                         new_img->at(dst_x, dst_y) = img->at(src_x, src_y);
                     }
                 }
            }


            delete img;
            return new_img;
        }

        std::string Resize::toString() const {
            std::ostringstream ss;
            ss << name() << " " << resize_x << " " << resize_y << " " << resize_w << " " << resize_h;
            return ss.str();
        }

    }
}