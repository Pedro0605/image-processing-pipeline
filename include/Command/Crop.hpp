//
// Created by mestre on 5/4/25.
//

#ifndef CROP_HPP
#define CROP_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class Crop : public Command
        {
        public:

            Crop(int x, int y, int w, int h);

            ~Crop() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int crop_x;
            int crop_y;
            int crop_w;
            int crop_h;
        };
    }
}

#endif // CROP_HPP