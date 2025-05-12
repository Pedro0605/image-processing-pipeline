//
// Created by mestre on 5/3/25.
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
            int delta_x;
            int delta_y;
        };
    }
}

#endif // MOVE_HPP