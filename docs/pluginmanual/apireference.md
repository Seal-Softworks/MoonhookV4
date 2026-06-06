---
icon: material/language-lua
---

# Moonhook API Reference

## General Functions

### `moonhook.Option`
```luau
moonhook.Option(name: string, type: 0 | 1 | 2, fn: (ctx: {}?) -> nil): nil
```
Creates an option in the Main Menu, Webhooks Menu or Bots Menu.
Pass in `moonhook.MAIN_MENU_OPTION`, `moonhook.WEBHOOKS_OPTION` or `moonhook.BOTS_OPTION` as the **type** argument.

### `moonhook.Request`
```luau
moonhook.Request(
    options: {
        Url: string,
        Method: "GET" | "POST" | string,
        Headers: { [string]: string },
        Body: string
    }
) -> {
    Success: boolean,
    StatusCode: number,
    StatusMessage: string,
    Body: string
}
```
Sends an HTTP request to the provided url. Use the `moonhook.encode` and `moonhook.decode` functions to encode and decode JSON from Luau tables.

## Console Library

### `moonhook.log`
```luau
moonhook.log(text: string): nil
```
Logs text to the console.

### `moonhook.error`
```luau
moonhook.error(text: string): nil
```
Logs an error to the console.
!!! warning
    This function does not stop execution. use `return` or `error()` to actually stop execution after calling `moonhook.error`.

### `moonhook.input`
```luau
moonhook.input(text: string) -> string
```
Recieves text input from the user.

### `moonhook.int_input`
```luau
moonhook.int_input(text: string) -> number
```
Recieves input from the user as a number. Defaults to 0.

### `moonhook.setcolors`
```luau
moonhook.setcolors(
    gradient_start: { r: number, g: number, b: number },
    gradient_end: { r: number, g: number, b: number }
) -> nil
```
Sets the gradient and console output colors for your plugin's console functions.

### `moonhook.setbanner`
```luau
moonhook.setbanner(banner: string) -> nil
```
Originaly a :material-language-cpp: `ConsoleHelper` class function, ported to luau for shits and giggles.
Call this before calling `moonhook.printbanner`

### `moonhook.printbanner`
```luau
moonhook.printbanner() -> nil
```
Prints a banner to the console with a gradient. Call the `moonhook.setcolors` and `moonhoom.setbanner` functions before calling this function.

### `moonhook.wait`
```luau
moonhook.wait(milliseconds: number) -> nil
```
Sleeps for a specified amount of milliseconds. Execution will be paused until this function finishes.

### `moonhook.pause`
```luau
moonhook.pause() -> nil
```
Prompts the user to press `Space` / `Enter` to continue. Execution will be paused until the user completes the action.

## Filesystem Library

!!! note
    All filesystem functions are only allowed to run within the Workspace folder. The workspace folder is located in `./Plugins/Workspace` within your **Moonhook** installation folder.
    !!! note
        The following extensions are blocked from the filesystem functions:
        `.exe`, `.scr`, `.vbs`, `.bat`, `.cmd`, `.com`, `.msi`,
        `.ps1`, `.psm1`, `.psd1`,
        `.vbe`, `.wsf`, `.wsh`, `.js`, `.jse`, `.hta`,
        `.cpl`, `.msc`, `.reg`, `.inf`,
        `.lnk`, `.pif`,
        `.dll`, `.sys`,
        `.jar`, `.py`, `.sh`, `.rb`, `.application`, `.gadget`,
        `.ws`, `.sct`, `.crt`

### `moonhook.readfile`
```luau
moonhook.readfile(path: string) -> string
```
Reads a file inside of the workspace folder and returns it's content as a string.

### `moonhook.writefile`
```luau
moonhook.writefile(path: string, content: string) -> nil
```
Writes a string to a file inside of the workspace folder.

### `moonhook.appendfile`
```luau
moonhook.appendfile(path: string, content: string) -> nil
```
Appends content to a file inside of the workspace folder.

### `moonhook.makefolder`
```luau
moonhook.makefolder(path: string) -> nil
```
Creates a folder inside of the Workspace folder.

### `moonhook.delfolder`
```luau
moonhook.delfolder(path: string) -> nil
```
Deletes a folder from the Workspace folder.

## Constants

```luau
const moonhook.MAIN_MENU_OPTION = 0;
const moonhook.WEBHOOKS_OPTION = 1;
const moonhook.BOTS_OPTION = 2;
```

## `ctx` object
### Webhook Options

- ctx.url       *(The webhook URL)*
- ctx.new()     *(Function to create a `Webhook` object)*

### Bot Options

- ctx.token     *(The discord bot token)*
- ctx.guild_id  *(The provieded discord guild ID)*
- ctx.new()     *(Function to create a `Bot` object)*

## `Webhook` class

!!! note
    To create an object of this class, use the `ctx` object provided when you register a Webhooks menu option.

### `Webhook:send`
```luau
Webhook:send(text: string) -> boolean
```
Sends a message to the discord webhook. If the function succeeds, it will return `true`, otherwise `false`.

### `Webhook:set_proxy`
```luau
Webhook:set_proxy(proxy_url: string) -> nil
```
Sets a HTTP proxy.

### `Webhook:get_proxy`
```luau
Webhook:get_proxy() -> string
```
Gets the currently active HTTP proxy.

### `Webhook:last_error`
```luau
Webhook:last_error() -> string
```
Returns the last occured error as a string.

### `Webhook:retry_after_ms`
```luau
Webhook:retry_after_ms() -> number
```
If the webhook has been rate limited, will return the amount of time left until you can send another HTTP request in milliseconds.

### `Webhook:set_name`
```luau
Webhook:set_name(name: string) -> boolean
```
Sets the name of the discord webhook by making an HTTP request. Returns `true` on success, and `false` on failure. 

### `Webhook:set_avatar_from_url`
```luau
Webhook:set_avatar_from_url(url: string) -> boolean
```
Sets the avatar of the discord webhook by making an HTTP request. Returns `true` on success, and `false` on failure.

### `Webhook:set_avatar_from_file`
```luau
Webhook:set_avatar_from_file(filepath: string) -> boolean
```
Sets the avatar of the discord webhook by making an HTTP request. Same as `set_avatar_from_url`, but sets the discord webhook avatar by reading an image file. Returns `true` on success, and `false` on failure. 

### `Webhook:get_name`
```luau
Webhook:get_name() -> string
```
Returns the name of the discord webhook as a string. Returns an empty string on failure.

### `Webhook.delete_webhook`
```luau
Webhooks:delete_webhook() -> boolean
```
Deletes the discord webhook. Returns `true` on success, and `false` on failure. 
!!! warning
    After this function is called, the discord webhook will be **deleted** and will no longer be usable!

## `Bot` class

### `Bot:validate_guild`
```luau
Bot:validate_guild(guild_id: string) -> string
```
Checks if a guild is valid and exists. If the guild exists, the guild name will be returned as a string. Otherwise, an empty string will be returned.

### `Bot:get_channels`
```luau
Bot:get_channels(guild_id: string) -> {
    id: string,
    name: string,
    type: number -- 0 = text, 2 = voice, 4 = category
}
```

!!! note
    Discord guild channels have 3 types. 0 is a text channel, 2 is a voice channel and 4 is a category.

### `Bot:delete_channel`
```luau
Bot:delete_channel(channel_id: string) -> boolean
```
Attempts to delete a discord channel. Will return `true` on success and `false` on failure.

### `Bot:create_text_channel`
```luau
Bot:create_text_channel(guild_id: string, role_name: string) -> boolean
```
Attempts to create a discord channel. Will return `true` on success and `false` on failure.

### `Bot:get_roles`
```luau
Bot:get_roles(guild_id: string) -> {
    id: string,
    name: string
}
```
Returns all the roles in the discord server.

### `Bot:delete_role`
```luau
Bot:delete_role(guild_id: string, role_id: string) -> boolean
```
Attempts to delete a discord role. Will return `true` on success and `false` on failure.

### `Bot:get_members`
```luau
Bot:get_members(guild_id: string, owner_id: string) -> {
    user_id: string,
    username: string,
    discriminator: string,
    is_owner: boolean
}
```
Returns all the members in a discord guild.

!!! note
    In the `Bot:get_members` function, if you do not have the discord guild owner's ID, just pass an empty string as the last argument. The function will still work properly, however it will just not detect is_owner.

### `Bot:ban_member()`
```luau
Bot:ban_member(guild_id: string, user_id: string, reason: string) -> boolean
```
Attempts to ban a discord user from the specified guild with the specified reason. Returns `true` on success, and `false` on failure. 

### `Bot:create_webhook`
```luau
Bot:create_webhook(channel_id: string, webhook_name: string) -> {
    id: string,
    token: string,
    url: string
}
```
Attempts to create a webhook in the specified channel. Will return `true` on success and `false` on failure.

### `Bot:last_error`
```luau
Bot:last_error() -> string
```
If the bot had encountered an error in any of the functions, this function will return the error that had occured as a string.
