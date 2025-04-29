//
// Created by mestre on 4/29/25.
//

#ifndef INVERT_HPP
#define INVERT_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog
{
    namespace command {
        class Invert : public Command {
        public:
            Invert();

            ~Invert();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}
#endif //INVERT_HPP
