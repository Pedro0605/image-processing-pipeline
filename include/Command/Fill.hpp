//
// Created by mestre on 4/30/25.
//

#ifndef FILL_HPP
#define FILL_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog
{
    namespace command {
        class Fill : public Command
        {
        public:

            Fill(int x, int y, int w, int h, Color c);

            ~Fill() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int fill_x;
            int fill_y;
            int fill_w;
            int fill_h;
            Color fill_color;
        };
    }
}

#endif // FILL_HPP