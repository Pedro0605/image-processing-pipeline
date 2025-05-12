//
// Created by mestre on 5/11/25.
//

#ifndef RESIZE_HPP
#define RESIZE_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class Resize : public Command
        {
        public:

            Resize(int x, int y, int w, int h);

            ~Resize() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int resize_x;
            int resize_y;
            int resize_w;
            int resize_h;
        };
    }
}

#endif // RESIZE_HPP