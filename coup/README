# Coup Game — README

This project is a C++ implementation of a strategic card game inspired by *Coup*, using SFML for a rich graphical interface. Each player is assigned a secret role and attempts to use actions to gain power and eliminate opponents.

---

## 🧠 Game Logic Overview

Each player has:

* A **name**
* A **role** (hidden from others)
* A number of **coins**

### On Each Turn

A player can perform **one** of the following actions:

#### General Actions (available to any player):

* **Gather** – Gain 1 coin from the treasury. Free to use. Can be blocked by *Sanction*.
* **Tax** – Gain 2 coins. Can be blocked by certain roles.
* **Bribe** – Pay 4 coins to gain an extra action in the same turn.
* **Arrest** – Steal 1 coin from another player. Cannot target the same player twice in a row.
* **Sanction** – Pay 3 coins to prevent another player from performing economic actions (Gather, Tax) on their next turn.
* **Coup** – Pay 7 coins to eliminate a player from the game. Can be blocked in some conditions.

> If a player has **10 or more coins**, they must perform a Coup.

---

## 🎭 Roles and Abilities

### 📫 Governor

* Receives **3 coins** from Tax instead of 2.
* Can block other players' **Tax**.

### 🕵️ Spy

* Can peek at another player's coin count.
* Prevents that player from using **Arrest** on their next turn.
* Costs 0 coins and does **not** consume a turn.

### 💼 Baron

* Can invest **3 coins** to gain **6 coins**.
* If hit by **Sanction**, he gains 1 coin as compensation (only loses 2 total).

### 🎖 General

* Can pay **5 coins** to block a **Coup** against any player.
* If hit by **Arrest**, the stolen coin is returned.

### ⚖ Judge

* Can cancel **Bribe** by another player, causing them to lose the 4 coins.
* If hit by **Sanction**, the attacker pays 1 extra coin to the treasury.

### 💰 Merchant

* Starts turn with ≥3 coins? Gains 1 bonus coin.
* If **Arrested**, pays 2 coins to the treasury instead of giving 1 to the attacker.

---

## 🕹️ Game Mechanics in UI

* Each player has a tab with their name.
* Clicking your own tab expands it to show your **coin count** and **card**.
* If you're the **Spy**, clicking another player while Spy Peek is active will reveal their coins and disable their Arrest.
* Buttons on screen allow available actions.
* If an action requires choosing a target (e.g., Coup, Sanction), clicking the target’s tab will execute it.
* Cards are revealed in the center of the screen when drawn.

---

## ⚙️ Compilation and Execution

Use this command to build:

```bash
make
```

Or manually:

```bash
g++ -std=c++17 -fsanitize=address -g main.cpp \
    Gui/GUI.cpp Gui/SelectPlayersGUI.cpp Gui/GameScreenGUI.cpp Gui/gameScreen.cpp \
    Players/Player.cpp Players/PlayerFactory.cpp \
    cards/Card.cpp Logic/GameLogic.cpp \
    -o coup -lsfml-graphics -lsfml-window -lsfml-system
```

### 🧪 Memory Leak Check

```bash
valgrind ./coup
```

Or detailed:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./coup
```

---
🧪 Testing


✅ What is tested?
Core logic (gather, tax, bribe, arrest, sanction, coup)

Role-specific abilities (Governor, Spy, Baron, etc.)

Turn rotation and game rules

Illegal action exceptions


🏃 How to Run Tests
Using the provided Makefile

make test_logic      
make test_players

## 📁 Project Structure

### Root

* `main.cpp` — Initializes the game window and state, and starts the GUI loop.
* `Makefile` — Compile and clean commands.

### `Gui/`

* `GUI.hpp` — Abstract base class for GUI screens.
* `GameScreenGUI.cpp / .hpp` — Main GUI logic: handles actions, button interaction, role tabs, events.
* `gameScreen.cpp / .hpp` — Rendering logic, layout drawing.
* `SelectPlayersGUI.cpp / .hpp` — Player selection interface.
* `GameState.hpp` — Enum for game states.
* `ActionType.hpp` — Enum defining possible player actions.

### `Logic/`

* `GameLogic.cpp / .hpp` — Core engine: rules enforcement, turn system, roles, blocking actions.

### `Players/`

* `Player.cpp / .hpp` — Base class for all players: manages name, coins, and holds a `Card`.
* `PlayerFactory.cpp / .hpp` — Factory that creates specific role-based player objects.
* `GovernorPlayer.hpp`, `SpyPlayer.hpp`, etc. — Subclasses of `Player`, each implementing the special ability logic of the role.

#### 🧬 Class Hierarchy (Player)

```
Player (base class)
├── GovernorPlayer
├── SpyPlayer
├── BaronPlayer
├── GeneralPlayer
├── JudgePlayer
└── MerchantPlayer
```

* These classes override behavior like `onStartTurn()`, `canBlock()`, or `specialAbility()` depending on role.

### `cards/`

* `Card.cpp / .hpp` — Base class for cards. A card holds the player's role and is used by `Player`.
* `Role.hpp` — Enum of all roles.
* `SpyCard.hpp`, `BaronCard.hpp`, etc. — Each holds image or visual logic tied to a role.

#### 🧬 Class Hierarchy (Card)

```
Card (base class)
├── GovernorCard
├── SpyCard
├── BaronCard
├── GeneralCard
├── JudgeCard
└── MerchantCard
```

* Used inside each `Player` to represent the player’s role and provide associated artwork.

* `photo_cards/` — Folder with card image files used by the game.

### Assets

* `menu_background.png`, `select_players_background.png`, `table_background.png` — Background images.
* `Merchant.jpg`, etc. — Card artwork images for players.

---

## ✅ Notes

* Multiple players can have the same role — this is allowed.
* Reactions to block actions occur "between turns" — simulated here as delayed responses before the acting player’s next turn.
* Illegal actions throw exceptions and trigger an on-screen error message.

---

## 📌 Authors and License

Created by Gal Maymon. Free to use for educational and non-commercial purposes.

---

If you'd like to contribute, improve graphics, or add animations/sound effects — pull requests are welcome!
