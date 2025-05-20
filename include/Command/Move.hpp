//
// Created by Lucas on 15/5/2025.
//

#ifndef MOVE_HPP
#define MOVE_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class Move : public Command
        {
        public:

            Move(int dx, int dy);

            ~Move() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int dx;
            int dy;
        };
    }
}

#endif // MOVE_HPP