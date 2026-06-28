# Coup

A C++17 implementation of a Coup-inspired strategy card game with an SFML 3 graphical interface.

Players receive hidden roles, collect coins, use role abilities, and try to eliminate the other players. The project is split into game logic, player-role classes, card classes, GUI screens, and doctest-based unit tests.

## Features

- SFML 3 desktop GUI.
- Role-based player hierarchy using polymorphism.
- Core actions: gather, tax, bribe, arrest, sanction, coup.
- Role actions: Governor tax block, Spy peek, Baron invest, General coup block, Judge bribe block, Merchant bonus.
- Unit tests for player behavior and game logic.

## Requirements

- Windows with MSYS2 MinGW64.
- `mingw-w64-x86_64-gcc`
- `mingw-w64-x86_64-sfml`
- `mingw32-make`

Install dependencies from the MSYS2 MinGW64 terminal if needed:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sfml mingw-w64-x86_64-make
```

## Build And Run

Open the MSYS2 MinGW64 terminal, then run:

```bash
cd ~/Desktop/project/Coup/coup
mingw32-make clean
mingw32-make
./coup.exe
```

The executable must be run from the project root because assets are loaded by relative paths such as `Gui/menu_background.png` and `arial-font/arial.ttf`.

## Tests

Run all tests:

```bash
mingw32-make test
```

Run individual suites:

```bash
mingw32-make test_logic
mingw32-make test_players
```

## Optional Sanitizer Build

AddressSanitizer support depends on the installed MinGW toolchain. If your environment has ASan available:

```bash
mingw32-make clean
mingw32-make SANITIZE=-fsanitize=address
```

## Project Structure

```text
.
|-- cards/      Role cards and card artwork loading
|-- Gui/        SFML screens, rendering, and user interaction
|-- Logic/      Core game rules and turn handling
|-- Players/    Base player class and role-specific player classes
|-- Test/       doctest test suites
|-- main.cpp    Application entry point
`-- Makefile    Build and test commands
```

## Main Classes

- `GameLogic` owns the players, turn order, setup flow, and rule execution.
- `Player` defines shared player state and common actions.
- `GovernorPlayer`, `SpyPlayer`, `BaronPlayer`, `GeneralPlayer`, `JudgePlayer`, and `MerchantPlayer` implement role-specific behavior.
- `Card` and derived card classes represent role identity and artwork.
- `MainMenuGUI`, `SelectPlayersGUI`, and `GameScreenGUI` handle the SFML user interface.

## Notes

- Multiple players can receive the same role.
- A player with 10 or more coins must perform a coup.
- Build artifacts are ignored by Git through `.gitignore`.

## Author

Created by Gal Maymon for an educational C++ project.
