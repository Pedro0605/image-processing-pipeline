//
// Created by mestre on 4/30/25.
//

#ifndef REPLACE_HPP
#define REPLACE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog
{
    namespace command {
        class Replace : public Command
        {
        public:

            Replace(Color target, Color replacer);

            ~Replace();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            Color target;
            Color replacer;
        };
    }
}

#endif //REPLACE_HPP
