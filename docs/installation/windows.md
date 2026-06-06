---
icon: lucide/download
---
 
# Moonhook V4 Installation

There are **two ways** you can get **Moonhook V4** working on your *Windows* device.

1. Downloading already compiled binaries
2. Compiling **Moonhook** yourself.

You can find out how to do this below:

=== "Downloading Binaries"
    If you are running **Windows**(*x64*), you can download already compiled binaries from the [Github Repository](https://github.com/Seal-Softworks/MoonhookV4).

    Go to the [Github Releases](https://github.com/Seal-Softworks/MoonhookV4/releases/latest) page to get the latest release of **Moonhook**.
    Download the attached `.zip` file. It will be named similar to: `moonhook-VERSION-windows_x64.zip`
    The `.zip` file name will vary depending on the version.

    Once you've acquired the `.zip` file, extract it. You will see an **executable***(.exe)* called `moonhookv4.exe`. That's the **Moonhook** executable.

    All that's left is to run *(by double clicking)* the `.exe` file and you will be able to use **Moonhook**.

=== "Compiling from Source Code"
    To compile **Moonhook** from the source code, you first need to **clone the [Github Repository](https://github.com/Seal-Softworks/MoonhookV4)**.
    You can do this by the command below in your terminal:
    
    ```sh
    git clone https://github.com/Seal-Softworks/MoonhookV4.git
    cd MoonhookV4
    ```

    After you ran the command, you will have cloned the github repository and entered the **MoonhookV4** folder. This folder contains the source code.

    Now, you can compile the Source Code using **cmake**. To find out how to do this, read the text below.

    !!! note
        You will need to have a :material-language-cpp: compiler installed in order to compile **Moonhook**.

    === "Visual Studio"
        To compile **Moonhook** from the source code using **cmake** with the **Microsoft Visual Studio** compiler, run the following commands in your **Powershell terminal**.
        ```powershell
        mkdir build
        cd build

        cmake .. -G "Visual Studio 17 2022" -A x64
        cmake --build . --config Release
        ```
    === "Ninja"
        To compile **Moonhook** from the source code using **cmake** with **Ninja**, run the following commands in your **Powershell terminal**.
        ```powershell
        mkdir build
        cd build

        cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
        cmake --build .
        ```
        
