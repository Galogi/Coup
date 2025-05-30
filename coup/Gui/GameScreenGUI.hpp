/**
 * @file GameScreenGUI.hpp
 * @author Gal Maymon
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <map>
#include <random>

#include "../Players/Player.hpp"
#include "../cards/Card.hpp"
#include "../Logic/GameLogic.hpp"
#include "GameState.hpp"
#include "ActionType.hpp"


struct PlayerTab {
    sf::RectangleShape collapsedRect;
    sf::Text           collapsedText;

    sf::RectangleShape panelRect;
    sf::Text           moneyText;
    sf::Text           cardText;
    sf::Sprite         smallCardSprite;

    bool expanded = false;
};


class GameScreenGUI
{
public:
    GameScreenGUI(sf::RenderWindow& window, GameLogic& logic);

 
    void handleEvent(const sf::Event& event, GameState& state);
    void update();
    void render();

   
    void setNewGameCallback(std::function<void()> cb) { newGameCb = std::move(cb); }

  
    void showWinnerOverlay(const std::string& winnerName,
                           std::function<void(bool)> onChoice);

 
    bool isAlive(size_t idx);

private:
 
    std::string cardToString(Role r) {
        switch (r) {
            case Role::Governor: return "Governor";
            case Role::Spy:      return "Spy";
            case Role::Baron:    return "Baron";
            case Role::General:  return "General";
            case Role::Judge:    return "Judge";
            case Role::Merchant: return "Merchant";
            default:             return "Unknown";
        }
    }

   
    sf::RenderWindow& window;
    GameLogic&        logic;
    std::vector<std::unique_ptr<Player>>& players;
    std::vector<PlayerTab> tabs;

    size_t       currentPlayer = 0;
    std::mt19937 rng;

    
    sf::Texture tableTexture;
    sf::Sprite  tableSprite;

    sf::Font   font;
    sf::Cursor arrowCursor, handCursor;

 
    sf::FloatRect      deckArea;
    sf::RectangleShape deckHighlight;


    std::map<Role, sf::Texture> cardTextures;


    sf::RectangleShape errorBox;
    sf::Text           errorText;
    sf::Clock          errorTimer;
    bool               errorVisible = false;
    void showError(const std::string& msg);


    sf::Sprite centerSprite;
    bool       centerVisible = false;


    std::vector<bool> drawnFlags;
    std::vector<bool> revealFlags;


    sf::RectangleShape gatherButton, taxButton, bribeButton, arrestButton,
                       sanctionButton, coupButton,
                       governorBlockTaxButton, spyPeekButton,
                       baronInvestButton, generalBlockCoupButton,
                       judgeBlockBribeButton;

    sf::Text gatherText, taxText, bribeText, arrestText,
             sanctionText, coupText,
             governorBlockTaxText, spyPeekText, baronInvestText,
             generalBlockCoupText, judgeBlockBribeText;

    ActionType pendingAction = ActionType::None;

  
    bool               showWinner = false;
    sf::RectangleShape overlay;
    sf::Text           winnerText;

    sf::RectangleShape newGameBtn, exitBtn;
    sf::Text           newGameTxt, exitTxt;

    std::function<void(bool)> overlayChoiceCb;   


    sf::RectangleShape topNewGameBtn;
    sf::Text           topNewGameTxt;
    std::function<void()> newGameCb;   

  
    void initTabs();
    void loadCardTextures();
    void selectCardForCurrentPlayer();
};
