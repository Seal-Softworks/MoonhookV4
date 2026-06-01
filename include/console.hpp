#pragma once

#include <iostream>
#include <ansi_terminal.hpp>
#include <chrono>
#include <string>

class ConsoleHelper {
public:
    const ansi::Gradient& gmain;
    const std::string& banner;

    ConsoleHelper(const ansi::Gradient& gradient, const std::string& banner)
        : gmain(gradient), banner(banner) {}

    inline void log(std::string text)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&t);
        char buf[6];
        std::strftime(buf, sizeof(buf), "%H:%M", tm);

        const std::string& TIME = std::string(buf);
        std::cout << gmain.start << "(" << TIME << ")" << "[MoonHook]: " << ansi::ColorReset() << text << std::endl;
    }

    inline void error(std::string text)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&t);
        char buf[6];
        std::strftime(buf, sizeof(buf), "%H:%M", tm);

        const std::string& TIME = std::string(buf);
        std::cout << ansi::rgb_to_ansi(255, 0, 0) << "(" << TIME << ")" << "[MoonHook]: " << ansi::ColorReset() << text << std::endl;
    }

    inline void printbanner()
    {
        ansi::print_gradient_ascii(banner, gmain);
    }

    // too lazy to do these manually 
    inline std::string input(std::string text)
    {
        std::cout << this->gmain.start << "[>>][MoonHook]: " << ansi::ColorReset() << text;
        std::string out;
        std::getline(std::cin, out);
        return out;
    }

    inline int int_input(std::string text)
    {
        std::cout << this->gmain.start << "[>>][MoonHook]: " << ansi::ColorReset() << text;
        std::string txt;
        std::getline(std::cin, txt);
        int out = 0;
        try {
            out = std::stoi(txt);
        }
        catch (...) {
            std::cout << "Invalid number! Using 0 instead.\n";
        }
        return out;
    }
};
