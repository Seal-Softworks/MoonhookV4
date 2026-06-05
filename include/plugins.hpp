#pragma once

#include <iostream>
#include <optional>

#include <option.hpp>

#include <lua.h>
#include <lualib.h>

struct MoonhookPlugin
{
    int type = 0; // 0 - source, 1 - compiled
    
    MoonhookPlugin(std::string content, int type = 0)
        : content(std::move(content)), type(type) {}

    std::string get_bytecode();
    bool valid_bytecode();
    Option get_option();

    std::string last_error();

    /*
    ok so it should be like err

    --!plugin
    Name: Test Plugin
    Description: Plugin description or sum
    Author: Me
    Version: v0.1.0
    --!end

    put it in the start of the file or somewhere yes
    */
    struct PluginHeader {
        std::string name;
        std::string description;
        std::string author;
        std::string version;
    };

    std::optional<PluginHeader> parse_plugin_header();

private:
    const std::string content;
    std::string bc;
    std::string last_err;
};

namespace PluginEnvironment
{
    extern const luaL_Reg MoonhookLibrary[];
    extern const luaL_Reg ConsoleLibrary[];
    void install(lua_State* L);
};
