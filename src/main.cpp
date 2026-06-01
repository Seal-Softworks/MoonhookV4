// omg moonhook v4

#define MOONHOOK_VERSION "v4.0.0"

#include <iostream>
#include <functional>
#include <string>

#include <include/ansi_terminal.hpp>
#include <include/consolerandom.hpp>
#include <include/console.hpp>
#include <include/option.hpp>
#include <include/internal_options.hpp>

const std::string& MoonhookBanner = ConsoleRandom::GetBanner();
const ansi::Gradient& MainGradient = ConsoleRandom::GetGradient();

int main()
{
    ansi::enableANSI();
    if (!ansi::supportsColor())
    {
        std::cout << "Your terminal does not support ANSI, please use a different terminal emulator to get better output.\n";
    }
    ansi::clearConsole();

    ConsoleHelper console(MainGradient, MoonhookBanner);

    console.printbanner();
    
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Moonhook " << std::string(MOONHOOK_VERSION) << "!" << std::endl;
    std::cout << ConsoleRandom::GetText() << std::endl;
    std::cout << "----------------------------------------------------------------\n\n";

    std::vector<Option> main_menu_options = {
        InternalOptions::Webhooks
    };

    for (size_t i = 0; i < main_menu_options.size(); i++)
    {
        Option* o = &main_menu_options[i];
        std::cout << "  " << std::to_string(i + 1) << ". " << o->name << std::endl;
    }

    std::cout << "Select an option(1-" << main_menu_options.size() << "): ";
    std::string selection;
    std::getline(std::cin, selection);
    
    int idx = 0;
    try {
        idx = std::stoi(selection) + 1;
    }
    catch (...)
    {
        std::cout << ansi::rgb_to_ansi(255, 0, 0) << "\nInvalid selection!\n" << ansi::ColorReset();
        ansi::pause();
        main();
    }

    Option selected = main_menu_options[idx];
    try {
        ConsoleHelper* c = &console;
        selected.run(c);
    }
    catch (...)
    {
        std::cout << ansi::rgb_to_ansi(255, 0, 0) << "This option had errored!\n" << ansi::ColorReset();
        ansi::pause();
        main();
    }
}
