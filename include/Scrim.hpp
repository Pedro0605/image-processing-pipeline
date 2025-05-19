//
// Created by JBispo on 05/04/2025.
//
#ifndef SCRIM_HPP
#define SCRIM_HPP

#include "Command.hpp"
#include "Image.hpp"
#include <vector>

namespace prog {
    class Scrim {
    private:
        std::vector<Command *> commands;

    public:
        Scrim(std::vector<Command *> &commands);

        ~Scrim();

        Image *run(Image *img, bool is_chained = false);

        Image *run();
    };
}

#endif // SCRIM_HPP