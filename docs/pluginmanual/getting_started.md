---
icon: lucide/rocket
---

# Getting Started

All **Moonhook** plugins are written in **[Luau](https://luau.org/):material-language-lua:**
Before creating plugins for **Moonhook**, you should learn the **Luau syntax** first.

!!! note
    Luau is a fork of lua. If you know lua, you can just write plugins in lua code.

## Making your first plugin

To make your first plugin, navigate to the **Plugins** within your **Moonhook** installation.
Create a file with a `.luau` or `.lua` extension. This will be your plugin.

Before writing the code for your plugin, you should add headers. Headers for **Moonhook** plugins are defined like:

```
--!plugin
Name: Plugin Name
Description: Plugin Description
Author: Your Name
Version: v0.1.0 (or your plugin version)
--!end
```

After you've defined the headers, you can get to writing the code.
To make options, you need to use the `moonhook.Option` function. Let's make a test main menu option.

```luau
moonhook.Option("Option Name", moonhook.MAIN_MENU_OPTION, function ()
    moonhook.log("Hello, world!");
    moonhook.pause();
end)
```

This code will create a main menu option, which will be visible when you open **Moonhook**.

!!! note
    You can create multiple options within one plugin.
    !!! note
        Call the `moonhook.pause()` function after your plugin finishes, so that it doesn't go back to the menu immediately.

Now, for **Webhook menu** options:

```luau
moonhook.Option("Send Message", moonhook.WEBHOOKS_OPTION, function (ctx)
    local hook = ctx.new(ctx.url);
    moonhook.log("Sending hello...");
    hook:send("Hello from my test plugin!");
    moonhook.log("Sent!");
    moonhook.pause();
end)
```

Webhook options recieve a `ctx` table that contains:

- ctx.url       (The webhook url)
- ctx.new()     (Function to create a `Webhook` object.)

To be able to send messages or use a webhook, you need to create a `Webhook` object.

Bot options recieve a `ctx` table that contains:

- ctx.token      (The bot token)
- ctx.guild_id   (The guild ID)
- ctx.new(token) (Funtion to create a `Bot` object.)

To be able to use the bot, you need to create a `Bot` object.

!!! note
    To get the full reference for the `moonhook` library and functions, take a look at the [API Reference](apireference.md).
