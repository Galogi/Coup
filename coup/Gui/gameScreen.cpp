/**
 * @file gameScreen.cpp
 * @author Gal Maymon
 */

#include "gameScreen.hpp" 
#include <iostream>


static const char* toString(GameState s) {
    switch (s) {
        case GameState::MainMenu:      return "MainMenu";
        case GameState::SelectPlayers: return "SelectPlayers";
        case GameState::InGame:        return "InGame";
        case GameState::GameOver:      return "GameOver";
        default:                       return "Unknown";
    }
}

void LogicGame::run(sf::RenderWindow& window)
{
    std::vector<std::unique_ptr<Player>> players;

    GameState state     = GameState::MainMenu;
    GameState prevState = state;               

    MainMenuGUI       mainMenu(window);
    SelectPlayersGUI  selectPlayers(window);
    std::unique_ptr<GameLogic>     logic;
    std::unique_ptr<GameScreenGUI> gameGUI;

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); break; }

            switch (state)
            {
                case GameState::MainMenu:
                    mainMenu.handleEvent(event, state);
                    break;

                case GameState::SelectPlayers:
                    selectPlayers.handleEvent(event, state);

                  
                    if (state == GameState::InGame && !gameGUI)
                    {
                       
                        static std::mt19937 rng(std::random_device{}());
                        std::uniform_int_distribution<int> dist(0, 5);

                        int cnt = selectPlayers.getSelectedPlayerCount();
                        players.clear(); players.reserve(cnt);
                        for (int i = 0; i < cnt; ++i)
                        {
                            Role r = static_cast<Role>(dist(rng));
                            std::string name = "Player " + std::to_string(i + 1);
                            players.push_back(createPlayerFromRole(name, r));
                        }

                        logic   = std::make_unique<GameLogic>(std::move(players));
                        gameGUI = std::make_unique<GameScreenGUI>(window, *logic);

                        gameGUI->setNewGameCallback([&]() {
                            state = GameState::MainMenu;
                            gameGUI.reset();
                        });

                        logic->setOnSetupCompleteCallback([lg = logic.get()]() {
                            lg->startGameLoop();
                        });

                        logic->setOnGameOverCallback(
                            [&](const Player& winner)
                            {
                                gameGUI->showWinnerOverlay(
                                    winner.getName(),
                                    [&](bool newGame)
                                    {
                                        if (newGame) {
                                            state = GameState::MainMenu;
                                            gameGUI.reset();
                                        } else {
                                            window.close();
                                        }
                                    });

                                state = GameState::GameOver;
                            });
                    }
                    break;

                case GameState::InGame:
                case GameState::GameOver:
                    if (gameGUI)
                        gameGUI->handleEvent(event, state);
                    break;
            }
        }

        if (state == GameState::SelectPlayers &&
            prevState != GameState::SelectPlayers)
        {
            selectPlayers.resetSelection();
        }
        prevState = state;

        /* ───────── ציור ───────── */
        window.clear();
        switch (state)
        {
            case GameState::MainMenu:
                mainMenu.update();         mainMenu.render();
                break;

            case GameState::SelectPlayers:
                selectPlayers.update();    selectPlayers.render();
                break;

            case GameState::InGame:
            case GameState::GameOver:
                if (gameGUI) {
                    gameGUI->update();
                    gameGUI->render();
                }
                break;
        }
        window.display();
    }
}
