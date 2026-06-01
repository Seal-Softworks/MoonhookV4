#pragma once

#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <optional>
#include <atomic>
#include <csignal>

#include <console.hpp>
#include <option.hpp>
#include <ansi_terminal.hpp>
#include <webhook.hpp>

namespace InternalOptions {
    Option Webhooks = {
        "Webhooks",
        [&](ConsoleHelper* console, std::optional<std::string> prev = std::nullopt) -> void {
            std::string WEBHOOK_URL;
            
            if (prev)

            console->log("Initializing webhook...");
            moon::Webhook hook(WEBHOOK_URL);

            const std::string& WebhooksBanner = R"(
██╗    ██╗███████╗██████╗ ██╗  ██╗ ██████╗  ██████╗ ██╗  ██╗███████╗
██║    ██║██╔════╝██╔══██╗██║  ██║██╔═══██╗██╔═══██╗██║ ██╔╝██╔════╝
██║ █╗ ██║█████╗  ██████╔╝███████║██║   ██║██║   ██║█████╔╝ ███████╗
██║███╗██║██╔══╝  ██╔══██╗██╔══██║██║   ██║██║   ██║██╔═██╗ ╚════██║
╚███╔███╔╝███████╗██████╔╝██║  ██║╚██████╔╝╚██████╔╝██║  ██╗███████║
 ╚══╝╚══╝ ╚══════╝╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝
        MoonHook V4
                                                                    
            )";

            ansi::clearConsole();
            ansi::print_gradient_ascii(WebhooksBanner, console->gmain);

            std::cout << "MoonHook Webhook Panel\n";

//---------------------------------- SUB OPTIONS -------------------------------------------------//
            std::vector<Option> sub_options = {
                {
                    "Send Message",
                    [&](ConsoleHelper* c) -> void {
                        const std::string& TEXT = c->input("Text to send: ");
                        bool success = hook.send(TEXT);
                        if (success)
                        {
                            c->log("Sent successfully!");
                            return;
                        } else {
                            const std::string& last_err = hook.last_error();
                            c->log("Failed to send webhook! Error: "+last_err);
                            return;
                        }
                    }
                },
                {
                    "Spam Webhook",
                    [&](ConsoleHelper* c) -> void {
                        const std::string& TEXT = c->input("Text to spam: ");
                        int DELAY = c->int_input("Delay(seconds): ");
                        if (DELAY == 0) DELAY = 1;
                        std::atomic<bool> spamming = true;

                        static std::atomic<bool>* g_spamming = nullptr;

                        std::signal(SIGINT, [](int) {
                            if (g_spamming)
                                *g_spamming = false;
                        });

                        g_spamming = &spamming;

                        std::thread t([&]() {
                            while (spamming)
                            {
                                hook.send(TEXT);
                                std::this_thread::sleep_for(std::chrono::seconds(DELAY));
                            }
                        });

                        t.join();
                    }
                },
                {
                    "Set Webhook Name",
                    [&](ConsoleHelper* c) -> void {
                        const std::string& NAME = c->input("New webhook name: ");
                        c->log("Attempting to set webhook name...");
                        bool success = hook.set_name(NAME);
                        if (success)
                        {
                            c->log("Success!");
                            return;
                        } else {
                            const std::string& err = hook.last_error();
                            c->error("Failed to set webhook name! Error: "+err);
                            return;
                        }
                    }
                },
                {
                    "Set Webhook Avatar",
                    [&](ConsoleHelper* c) -> void {}
                }
            };
//------------------------------------------------------------------------------------------------//
        }
    };
}
