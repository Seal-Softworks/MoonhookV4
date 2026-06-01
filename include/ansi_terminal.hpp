#ifndef COLORS
#define COLORS

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>

#if defined(_WIN32)
    #define NOMINMAX
    #include <windows.h>
#elif defined(__unix__) || defined(__APPLE__)
    #include <unistd.h>
#endif

namespace ansi {

    static void enableANSI() {
#if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
#endif
    }

    static bool supportsColor() {
#if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        return GetConsoleMode(hOut, &dwMode) &&
               (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#elif defined(__unix__) || defined(__APPLE__)
        const char* term = std::getenv("TERM");
        const char* colorterm = std::getenv("COLORTERM");
        bool hasTerm = term && std::string(term) != "dumb";
        bool hasColor = colorterm != nullptr;
        return isatty(STDOUT_FILENO) && (hasTerm || hasColor);
#else
        return false;
#endif
    }

    static std::string rgb_to_ansi(int r, int g, int b) {
        return "\033[38;2;" + std::to_string(r) + ";" +
               std::to_string(g) + ";" +
               std::to_string(b) + "m";
    }

    static std::string ColorReset() {
        return "\033[0m";
    }

    struct Gradient {
        std::string start;
        std::string end;
    };

    static void print_gradient_ascii(
        const std::string& text,
        const Gradient& gradient
    ) {
        size_t mid = text.size() / 2;
        std::cout << gradient.start << text.substr(0, mid)
                << gradient.end   << text.substr(mid)
                << ColorReset()   << "\n";
    }

    static void clearConsole() {
    #if defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count, cellCount;
        COORD homeCoords = {0, 0};

        if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(hOut, ' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hOut, homeCoords);
    #else
        std::cout << "\033[H\033[2J" << std::flush;
    #endif
    }

    static void pause(const std::string& message = "Press any key to continue...") {
        if (!message.empty())
            std::cout << message << std::flush;

    #if defined(_WIN32)
        _getch();
    #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif

        std::cout << "\n";
    }
}

#endif // COLORS