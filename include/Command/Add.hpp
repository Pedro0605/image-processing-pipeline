//
// Created by mestre on 5/1/25.
//

#ifndef ADD_HPP
#define ADD_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <string>

namespace prog
{
    namespace command {
        class Add : public Command {
        public:
            Add(std::string filename, Color neutral, int x, int y);

            ~Add();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            std::string filename;
            Color neutral;
            int target_x;
            int target_y;
        };
    }
}

#endif // ADD_HPP
