//
// Created by JBispo on 05/04/2025.
//
#include "Scrim.hpp"
#include "Logger.hpp"

// Include necessary command headers for dynamic_cast type checking
#include "Command/Blank.hpp"
#include "Command/Save.hpp"
#include "Command/Open.hpp"

using prog::Command;

namespace prog {

    Scrim::Scrim(std::vector<Command *> &commands) : commands(commands) {}

    Scrim::~Scrim() {
        // Deallocate each command
        for (Command *c: commands) {
            delete c;
        }
    }

    Image *Scrim::run(Image *img) {
        for (Command *c: commands) {
            *Logger::out() << "Applying command '" << c->toString() << "'\n";
            img = c->apply(img);
        }

        *Logger::out() << "Scrim::run finished. Returning image pointer.\n";
        return img;
    }


    Image *Scrim::run() {
        return this->run(nullptr);
    }
}