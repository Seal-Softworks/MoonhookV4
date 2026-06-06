---
icon: lucide/download
---

# Moonhook V4 Installation

To use **Moonhook** any platform or architechture other than **Windows**(*x64*) you need to compile it from it's source code.

The first step to doing this is to **clone the [Github Repository](https://github.com/Seal-Softworks/MoonhookV4) using git**.
To do this, run the following commands in your terminal:

```sh
git clone https://github.com/Seal-Softworks/MoonhookV4.git
cd MoonhookV4
```

After you have ran the commands, you will have cloned the **Moonhook** github repository and entered the folder that contains the source code.

Now, you can compile **Moonhook**.

!!! note
    To compile :material-language-cpp: code, you need a :material-language-cpp: compiler installed on your machine.

Do this by running the following commands:

```sh
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

Now you can use **Moonhook V4**.
