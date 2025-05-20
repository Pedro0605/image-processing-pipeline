//
// Created by mestre on 18/5/2025.
//

#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "Command.hpp"
#include "Image.hpp"
#include <string>
#include <vector>
#include <istream>

namespace prog
{
    namespace command {
        class Chain : public Command
        {
        public:

            Chain(const std::vector<std::string>& filenames);

            ~Chain() override;

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            std::vector<std::string> filenames;
        };
    }
}

#endif // CHAIN_HPP