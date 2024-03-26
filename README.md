# Lifty Client
This project is a DLL designed to demonstrate game hacking techniques on Assault Cube. The tool offers features such as infinite health, ammo, and no recoil when injected into the game process. It's built for educational purposes to showcase how memory manipulation works in Windows applications.
Features

    Infinite Health: Keeps the player's health at a constant, high value.
    Infinite Ammo: Ensures the player never runs out of ammunition.
    No Recoil: Removes the recoil effect when shooting, allowing for steadier aim.

## Getting Started

These instructions will guide you through the setup and usage of this game hacking tool.
Prerequisites

    Windows operating system.
    AC Client game installed.
    A DLL injector (not included).

## Usage

    Build the Project:
        Compile the project using Visual Studio to generate the DLL file.

    Inject the DLL:
        Use a DLL injector to inject the compiled DLL into the AC Client game process. Ensure the game is running before attempting to inject.

    Activate Features:
        Once injected, a console window should appear, indicating the tool is active.
        Use the following keys to toggle the features:
            Numpad 1: Toggle Infinite Health
            Numpad 2: Toggle Infinite Ammo
            Numpad 3: Toggle No Recoil

    Exit:
        Press the ESC key to safely detach and exit the tool.

Building from Source

Open the solution in Visual Studio, ensure the configuration is set to "Release" mode for optimal performance, and then build the solution. The resulting DLL will be found in the Release directory.
