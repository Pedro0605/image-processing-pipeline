//
// Created by mestre on 11/5/2025.
//

#ifndef ROTATERIGHT_HPP
#define ROTATERIGHT_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class RotateRight : public Command
        {
        public:

            RotateRight();

            ~RotateRight() override;

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif // ROTATERIGHT_HPP