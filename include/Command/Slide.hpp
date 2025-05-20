//
// Created by Lucas on 15/5/2025.
//

#ifndef SLIDE_HPP
#define SLIDE_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class Slide : public Command
        {
        public:

            Slide(int dx, int dy);

            ~Slide() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int delta_x;
            int delta_y;
        };
    }
}

#endif // SLIDE_HPP