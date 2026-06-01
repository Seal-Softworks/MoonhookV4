// option.hpp

#pragma once

#include <functional>
#include <console.hpp>

struct Option {
    std::string name;
    std::function<void(ConsoleHelper*)> action;

    Option(const std::string& name, std::function<void(ConsoleHelper*)> action)
        : name(name), action(action) {}

    void run(ConsoleHelper* console) {
        action(console);
    }
};
