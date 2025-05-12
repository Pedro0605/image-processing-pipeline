//
// Created by mestre on 5/6/25.
//

#ifndef SCALEUP_HPP
#define SCALEUP_HPP

#include "Command.hpp"
#include "Image.hpp"

namespace prog
{
    namespace command {
        class ScaleUp : public Command
        {
        public:

            ScaleUp(int fx, int fy);

            ~ScaleUp() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int factor_x;
            int factor_y;
        };
    }
}

#endif // SCALEUP_HPP