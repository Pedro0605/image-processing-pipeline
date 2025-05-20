//
// Created by mestre on 11/5/2025.
//

#ifndef ROTATELEFT_HPP
#define ROTATELEFT_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class RotateLeft : public Command
        {
        public:

            RotateLeft();

            ~RotateLeft() override;

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif // ROTATELEFT_HPP