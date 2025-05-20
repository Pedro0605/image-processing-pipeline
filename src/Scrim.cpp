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

    Image *Scrim::run(Image *img, bool is_chained) {
        *Logger::out() << "Scrim::run started. is_chained: " << std::boolalpha << is_chained << ". Number of commands: " << commands.size() << "\n";

        for (Command *c: commands) {
            if (is_chained) {
                if (dynamic_cast<command::Blank*>(c) != nullptr ||
                    dynamic_cast<command::Save*>(c) != nullptr ||
                    dynamic_cast<command::Open*>(c) != nullptr) {
                    continue;
                }
            } else {
                 *Logger::out() << "Not in chained run context. Applying command.\n";
            }

            *Logger::out() << "Applying command '" << c->toString() << "'\n";
            img = c->apply(img);
        }
        *Logger::out() << "Scrim::run finished. Returning image pointer.\n";
        return img;
    }


    Image *Scrim::run() {
        *Logger::out() << "Scrim::run() called (top-level).\n";
        return this->run(nullptr, false);
    }
}