/**
 * @file GameScreenGUI.cpp
 * @author Gal Maymon
 */

#include "GameScreenGUI.hpp"
#include <iostream>


GameScreenGUI::GameScreenGUI(sf::RenderWindow& win, GameLogic& logicRef)
: window(win),
  logic(logicRef),
  players(logicRef.getPlayers()),
  rng(std::random_device{}()),
  currentPlayer(logicRef.getCurrentPlayerIndex()),
  centerVisible(false)
{
    if (!tableTexture.loadFromFile("Gui/table_background.png")) {
        std::cerr << "Failed to load table background\n"; exit(1);
    }
    tableSprite.setTexture(tableTexture);
    auto ws = window.getSize(), ts = tableTexture.getSize();
    tableSprite.setScale(float(ws.x)/ts.x, float(ws.y)/ts.y);

    if (!font.loadFromFile("arial-font/arial.ttf")) {
        std::cerr << "Failed to load font\n"; exit(1);
    }

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);

   
    float origX = 880, origY = 550, origW = 220, origH = 110;
    deckArea = sf::FloatRect(
        origX * ws.x/ts.x, origY * ws.y/ts.y,
        origW * ws.x/ts.x, origH * ws.y/ts.y
    );
    deckHighlight.setPosition(deckArea.left, deckArea.top);
    deckHighlight.setSize({deckArea.width, deckArea.height});
    deckHighlight.setFillColor({0,0,0,0});
    deckHighlight.setOutlineColor({0,0,0,0});
    deckHighlight.setOutlineThickness(2.f);

    loadCardTextures();

    tabs.resize(players.size());
    drawnFlags.assign(players.size(), false);
    revealFlags.assign(players.size(), false);
    initTabs();

   
    float bw = 140, bh = 40, spacing = 10;
    float bx = 30;
    float by = window.getSize().y - (6 * (bh + spacing)) - 30;

    sf::Color buttonBackground(92, 64, 51);     // חום כהה
    sf::Color buttonTextColor(212, 175, 55);    // זהב
  

    // ⚙️ פונקציית עזר: כפתורים רגילים
    auto setupButton = [&](sf::RectangleShape& btn, sf::Text& txt, const std::string& label, int index, float offsetX = 0.f) {
        btn.setSize({bw, bh});
        btn.setPosition(bx + offsetX, by + index * (bh + spacing));
        btn.setFillColor(buttonBackground);
        btn.setOutlineColor(buttonTextColor);
        btn.setOutlineThickness(1.5f);

        txt.setFont(font);
        txt.setString(label);
        txt.setCharacterSize(18);
        txt.setFillColor(buttonTextColor);
        txt.setPosition(bx + offsetX + 10, by + index * (bh + spacing) + 8);
    };

    // 🎮 כפתורים רגילים
    setupButton(gatherButton,   gatherText,   "Gather",   0);
    setupButton(taxButton,      taxText,      "Tax",      1);
    setupButton(bribeButton,    bribeText,    "Bribe",    2);
    setupButton(arrestButton,   arrestText,   "Arrest",   3);
    setupButton(sanctionButton, sanctionText, "Sanction", 4);
    setupButton(coupButton,     coupText,     "Coup",     5);

    // ⭐ כפתורים מיוחדים – באותה שורה של Gather, ימינה
    float rightOffset = bw + 20;
    setupButton(governorBlockTaxButton,   governorBlockTaxText,   "Block Tax",   0, rightOffset);
    setupButton(spyPeekButton,            spyPeekText,            "Spy Peek",    0, rightOffset);
    setupButton(baronInvestButton,        baronInvestText,        "Invest",      0, rightOffset);
    setupButton(generalBlockCoupButton,   generalBlockCoupText,   "Block Coup",  0, rightOffset);
    setupButton(judgeBlockBribeButton,    judgeBlockBribeText,    "Block Bribe", 0, rightOffset);

    float boxW = 300.f, boxH = 50.f;
    errorBox.setSize({boxW, boxH});
    errorBox.setPosition(window.getSize().x - boxW - 20.f, window.getSize().y - boxH - 20.f);

    errorBox.setFillColor(sf::Color(30, 30, 30, 200));
    errorBox.setOutlineColor(sf::Color(212, 175, 55)); // זהב
    errorBox.setOutlineThickness(2.f);

    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(sf::Color::White);


    overlay.setSize( sf::Vector2f(window.getSize()) );
    overlay.setFillColor( sf::Color(0,0,0,180) );               // שחור שקוף

    winnerText.setFont(font);
    winnerText.setCharacterSize(40);
    winnerText.setFillColor(sf::Color::White);

    auto setupSmallBtn = [&](sf::RectangleShape& b, sf::Text& t,
                            const std::string& label, float y){
        b.setSize({180,50});
        b.setFillColor(sf::Color(30,30,30,220));
        b.setOutlineColor(sf::Color(212,175,55));
        b.setOutlineThickness(2);
        b.setPosition(
            (window.getSize().x - b.getSize().x)/2, y);

        t.setFont(font);
        t.setString(label);
        t.setCharacterSize(24);
        t.setFillColor(sf::Color::White);
        auto lb = t.getLocalBounds();
        t.setPosition(
            b.getPosition().x + (b.getSize().x-lb.width)/2 - lb.left,
            b.getPosition().y + (b.getSize().y-lb.height)/2 - lb.top);
    };
    setupSmallBtn(newGameBtn,newGameTxt,"New Game",
                window.getSize().y/2.f + 40);
    setupSmallBtn(exitBtn,   exitTxt,  "Exit",
                window.getSize().y/2.f + 110);
    float margin = 10.f;
    topNewGameBtn.setSize({120, 35});
    topNewGameBtn.setFillColor(sf::Color(30,30,30,220));
    topNewGameBtn.setOutlineColor(sf::Color(212,175,55));
    topNewGameBtn.setOutlineThickness(2);
    topNewGameBtn.setPosition(
        window.getSize().x - topNewGameBtn.getSize().x - margin,
        margin);

    topNewGameTxt.setFont(font);
    topNewGameTxt.setString("New Game");
    topNewGameTxt.setCharacterSize(16);
    topNewGameTxt.setFillColor(sf::Color::White);
    auto lb = topNewGameTxt.getLocalBounds();
    topNewGameTxt.setPosition(
        topNewGameBtn.getPosition().x + (topNewGameBtn.getSize().x-lb.width)/2 - lb.left,
        topNewGameBtn.getPosition().y + (topNewGameBtn.getSize().y-lb.height)/2 - lb.top);
}


void GameScreenGUI::loadCardTextures() {
    for (Role r : {Role::Governor, Role::Spy, Role::Baron,
                   Role::General, Role::Judge, Role::Merchant}) {
        sf::Texture tex;
        std::string fn = "cards/photo_cards/" + Card::roleToString(r) + ".jpg";  // ⬅️ שורה מתוקנת
        if (!tex.loadFromFile(fn)) {
            std::cerr << "Failed to load card image: " << fn << "\n";
            exit(1);
        }
        cardTextures[r] = std::move(tex);
    }
}


void GameScreenGUI::initTabs() {
    const float tabW=140, tabH=40, mX=10, mY=10, spY=10;
    sf::Color bd(212,175,55);

    for (size_t i = 0; i < players.size(); ++i) {
        float y = mY + i*(tabH+spY);
        auto& t = tabs[i];

        t.collapsedRect.setSize({tabW, tabH});
        t.collapsedRect.setOutlineColor(bd);
        t.collapsedRect.setOutlineThickness(2);
        t.collapsedRect.setPosition(mX, y);

        t.collapsedText.setFont(font);
        t.collapsedText.setString(players[i]->getName());
        t.collapsedText.setCharacterSize(18);
        t.collapsedText.setFillColor(sf::Color::White);
        auto cb = t.collapsedRect.getGlobalBounds();
        auto lb = t.collapsedText.getLocalBounds();
        t.collapsedText.setPosition(
            cb.left + (cb.width  - lb.width)*0.5f - lb.left,
            cb.top  + (cb.height - lb.height)*0.5f - lb.top
        );

        t.panelRect.setSize({220,100});
        t.panelRect.setFillColor({20,20,20,230});
        t.panelRect.setOutlineColor(bd);
        t.panelRect.setOutlineThickness(2);
        t.panelRect.setPosition(mX+tabW+8, y);

        t.moneyText.setFont(font);
        t.moneyText.setCharacterSize(16);
        t.moneyText.setFillColor(sf::Color::Yellow);
        t.moneyText.setString("$" + std::to_string(players[i]->getCoins()));
        t.moneyText.setPosition(mX+tabW+16, y+12);

        t.cardText.setFont(font);
        t.cardText.setCharacterSize(14);
        t.cardText.setFillColor(bd);
        t.cardText.setString("CARD");
        t.cardText.setPosition(mX+tabW+16, y+44);

        t.smallCardSprite.setColor({255,255,255,0});
        t.smallCardSprite.setPosition(mX+tabW+16, y+44);
        t.expanded = false;
    }
}

void GameScreenGUI::selectCardForCurrentPlayer() {
    if (currentPlayer >= players.size() || drawnFlags[currentPlayer]) return;

    
    Role r = players[currentPlayer]->getCard().getRole();

    auto& tab = tabs[currentPlayer];
    tab.smallCardSprite.setTexture(cardTextures[r]);
    tab.smallCardSprite.setColor(sf::Color::White);
    tab.smallCardSprite.setScale(0.5f, 0.5f);

    centerSprite.setTexture(cardTextures[r]);
    auto cs = cardTextures[r].getSize();
    float cscale = std::min(window.getSize().x * 0.5f / cs.x,
                            window.getSize().y * 0.5f / cs.y);
    centerSprite.setScale(cscale, cscale);
    centerSprite.setPosition((window.getSize().x - cs.x * cscale) / 2,
                             (window.getSize().y - cs.y * cscale) / 2);
    centerVisible = true;
}


void GameScreenGUI::handleEvent(const sf::Event& e, GameState&) {
    if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mp = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (size_t i = 0; i < players.size(); ++i) {
            if (i != currentPlayer) continue;

            if (tabs[i].expanded &&
                tabs[i].cardText.getGlobalBounds().contains(mp) &&
                logic.cardAlreadyDrawn(i)) {

                Role r = players[i]->getCard().getRole();
                std::cout << "[DEBUG] Showing player card: " << cardToString(r) << "\n";

                centerSprite.setTexture(cardTextures[r]);
                auto cs = cardTextures[r].getSize();
                float scale = std::min(
                    window.getSize().x * 0.5f / cs.x,
                    window.getSize().y * 0.5f / cs.y
                );
                centerSprite.setScale(scale, scale);
                centerSprite.setPosition(
                    (window.getSize().x - cs.x * scale) / 2.f,
                    (window.getSize().y - cs.y * scale) / 2.f
                );
                centerVisible = true;
                return;
            }
        }

        if (centerVisible) {
            for (size_t i = 0; i < tabs.size(); ++i) {
                if (tabs[i].expanded &&
                    tabs[i].cardText.getGlobalBounds().contains(mp) &&
                    logic.cardAlreadyDrawn(i)) {
                    break;
                }

                if (i == tabs.size() - 1) {
                    centerVisible = false;
                    if (logic.isFirstRound()) {
                        logic.nextPlayer();
                    }
                    logic.markFirstRoundDoneIfNeeded();
                    currentPlayer = logic.getCurrentPlayerIndex();

                      
                        gatherButton.setFillColor({92, 64, 51});
                        taxButton.setFillColor({92, 64, 51});
                        bribeButton.setFillColor({92, 64, 51});
                        arrestButton.setFillColor({92, 64, 51});
                        sanctionButton.setFillColor({92, 64, 51});
                        coupButton.setFillColor({92, 64, 51});
                        governorBlockTaxButton.setFillColor({92, 64, 51});
                        spyPeekButton.setFillColor({92, 64, 51});
                        generalBlockCoupButton.setFillColor({92, 64, 51});
                        judgeBlockBribeButton.setFillColor({92, 64, 51});

                        
                        gatherButton.setFillColor({92, 64, 51});
                        taxButton.setFillColor({92, 64, 51});
                        bribeButton.setFillColor({92, 64, 51});
                        arrestButton.setFillColor({92, 64, 51});
                        sanctionButton.setFillColor({92, 64, 51});
                        coupButton.setFillColor({92, 64, 51});
                        governorBlockTaxButton.setFillColor({92, 64, 51});
                        spyPeekButton.setFillColor({92, 64, 51});
                        generalBlockCoupButton.setFillColor({92, 64, 51});
                        judgeBlockBribeButton.setFillColor({92, 64, 51});
                    return;
                }
            }
        }

        sf::Color activeColor(60, 40, 30);

        gatherButton.setFillColor({92, 64, 51});
        taxButton.setFillColor({92, 64, 51});
        bribeButton.setFillColor({92, 64, 51});
        arrestButton.setFillColor({92, 64, 51});
        sanctionButton.setFillColor({92, 64, 51});
        coupButton.setFillColor({92, 64, 51});
        governorBlockTaxButton.setFillColor({92, 64, 51});
        spyPeekButton.setFillColor({92, 64, 51});
        generalBlockCoupButton.setFillColor({92, 64, 51});
        judgeBlockBribeButton.setFillColor({92, 64, 51});

        if (pendingAction == ActionType::None) {
            for (auto& tab : tabs) tab.expanded = false;
        }

        if (!logic.isFirstRound()) {
            if (players[currentPlayer]->getCoins() >= 10 && pendingAction != ActionType::Coup) {
    
                if (!coupButton.getGlobalBounds().contains(mp)) {
                    showError("You have 10 coins!\nYou must perform a Coup.");
                    return;
                }
                // אם לחצו על coupButton – הפוך אותו לפעולה ממתינה
                pendingAction = ActionType::Coup;
                coupButton.setFillColor(activeColor);
                logic.clearSpyPeek();
                return;
            }
            
            
            try {
                if (gatherButton.getGlobalBounds().contains(mp)) {
                    logic.performGather(); logic.clearSpyPeek(); logic.nextPlayer();
                    currentPlayer = logic.getCurrentPlayerIndex(); return;
                }
                if (taxButton.getGlobalBounds().contains(mp)) {
                    logic.performTax(); logic.clearSpyPeek(); logic.nextPlayer();
                    currentPlayer = logic.getCurrentPlayerIndex(); return;
                }
                if (bribeButton.getGlobalBounds().contains(mp)) {
                    logic.performBribe(); logic.clearSpyPeek(); logic.nextPlayer();
                    currentPlayer = logic.getCurrentPlayerIndex(); return;
                }
                if (arrestButton.getGlobalBounds().contains(mp)) {
                    showError("Select a player"); pendingAction = ActionType::Arrest;
                    arrestButton.setFillColor(activeColor); logic.clearSpyPeek(); return;
                }
                if (sanctionButton.getGlobalBounds().contains(mp)) {
                    showError("Select a player"); pendingAction = ActionType::Sanction;
                    sanctionButton.setFillColor(activeColor); logic.clearSpyPeek(); return;
                }
                if (coupButton.getGlobalBounds().contains(mp)) {
                    pendingAction = ActionType::Coup;
                    coupButton.setFillColor(activeColor); logic.clearSpyPeek(); return;
                }
                Role role = players[currentPlayer]->getRole();
                if (role == Role::Governor && governorBlockTaxButton.getGlobalBounds().contains(mp)) {
                    pendingAction = ActionType::BlockTax;
                    governorBlockTaxButton.setFillColor(activeColor); return;
                }
                if (role == Role::Spy && spyPeekButton.getGlobalBounds().contains(mp)) {
                    showError("Select a player");
                    if (logic.getSpyPeekTarget() == -1) {
                        pendingAction = ActionType::SpyPeek;
                        spyPeekButton.setFillColor(activeColor);
                    } else {
                        std::cout << "[WARNING] Spy Peek already used this turn\n";
                    }
                    return;
                }
                if (role == Role::Baron && baronInvestButton.getGlobalBounds().contains(mp)) {
                    logic.performInvest(); logic.nextPlayer();
                    currentPlayer = logic.getCurrentPlayerIndex(); return;
                }
                if (role == Role::General && generalBlockCoupButton.getGlobalBounds().contains(mp)) {
                    showError("Select a player");
                    pendingAction = ActionType::BlockCoup;
                    generalBlockCoupButton.setFillColor(activeColor);
                    return;
                }
                if (role == Role::Judge && judgeBlockBribeButton.getGlobalBounds().contains(mp)) {
                    showError("Select a player");
                    pendingAction = ActionType::BlockBribe;
                    judgeBlockBribeButton.setFillColor(activeColor);
                    return;
                }
            } catch (const std::exception& ex) {
                std::cerr << "[ERROR] Action failed: " << ex.what() << "\n";
                showError(std::string("[ERROR] ") + ex.what());
                pendingAction = ActionType::None;
                return;
            }
        }

        if (topNewGameBtn.getGlobalBounds().contains(mp) && newGameCb) {
            newGameCb(); return;
        }

        if (!logic.cardAlreadyDrawn(currentPlayer) && deckArea.contains(mp)) {
        logic.selectRandomCardForPlayer(currentPlayer);

        Role r = players[currentPlayer]->getCard().getRole();
        std::cout << "[DEBUG] Showing drawn card: " << cardToString(r) << "\n";

        
        tabs[currentPlayer].cardText.setString(cardToString(r));
        tabs[currentPlayer].smallCardSprite.setTexture(cardTextures[r]);
        tabs[currentPlayer].smallCardSprite.setColor(sf::Color::White);
        tabs[currentPlayer].smallCardSprite.setScale(0.5f, 0.5f);

        // הצגת התמונה הגדולה במרכז
        centerSprite.setTexture(cardTextures[r]);
        auto cs = cardTextures[r].getSize();
        float scale = std::min(
            window.getSize().x * 0.5f / cs.x,
            window.getSize().y * 0.5f / cs.y
        );
        centerSprite.setScale(scale, scale);
        centerSprite.setPosition(
            (window.getSize().x - cs.x * scale) / 2.f,
            (window.getSize().y - cs.y * scale) / 2.f
        );
        centerVisible = true;
        return;
    }

        if (logic.canExpandTab(currentPlayer) && tabs[currentPlayer].collapsedRect.getGlobalBounds().contains(mp)) {
            tabs[currentPlayer].expanded = !tabs[currentPlayer].expanded;
            return;
        }

        if (showWinner && e.mouseButton.button == sf::Mouse::Left) {
            if (newGameBtn.getGlobalBounds().contains(mp)) {
                overlayChoiceCb(true); return;
            }
            if (exitBtn.getGlobalBounds().contains(mp)) {
                overlayChoiceCb(false); return;
            }
        }

        if (pendingAction != ActionType::None) {
            for (size_t i = 0; i < players.size(); ++i) {
                if (i == currentPlayer) continue;
                if (tabs[i].collapsedRect.getGlobalBounds().contains(mp)) {
                    try {
                        switch (pendingAction) {
                            case ActionType::Arrest:
                                logic.performArrest(*players[i]); logic.nextPlayer(); break;
                            case ActionType::Sanction:
                                logic.performSanction(*players[i]); logic.nextPlayer(); break;
                            case ActionType::Coup:
                                if (logic.performCoup(*players[i])) tabs[i].expanded = false;
                                logic.nextPlayer(); break;
                            case ActionType::BlockTax:
                                logic.performBlockTax(*players[i]); logic.nextPlayer(); break;
                            case ActionType::SpyPeek:
                                logic.performSpyPeek(*players[i]); tabs[i].expanded = !tabs[i].expanded; break;
                            case ActionType::BlockCoup:
                                logic.performBlockCoup(*players[i]); logic.nextPlayer(); break;
                            case ActionType::BlockBribe:
                                logic.performBlockBribe(*players[i]); logic.nextPlayer(); break;
                            default: break;
                        }
                        pendingAction = ActionType::None;
                        currentPlayer = logic.getCurrentPlayerIndex();
                    } catch (const std::exception& ex) {
                        std::cerr << "[ERROR] Action on target failed: " << ex.what() << "\n";
                        showError(std::string("[ERROR] ") + ex.what());
                        pendingAction = ActionType::None;
                    }
                    return;
                }
            }
        }
    }
}


void GameScreenGUI::update() {
    sf::Vector2f mp = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool over = !centerVisible && deckArea.contains(mp);
    window.setMouseCursor(over ? handCursor : arrowCursor);
    if (errorVisible && errorTimer.getElapsedTime().asSeconds() > 4) {
    errorVisible = false;
}
}

void GameScreenGUI::render() {
    window.draw(tableSprite);
    window.draw(deckHighlight);

    if (centerVisible) {
        window.draw(centerSprite);
    }

   
    bool isSpy = players[currentPlayer]->getRole() == Role::Spy;
    int spyTarget = logic.getSpyPeekTarget(); 

    for (size_t i = 0; i < tabs.size(); ++i) {
        if (!isAlive(i)) continue;          
        auto& t = tabs[i];

        if (i == currentPlayer && !centerVisible) {
            t.collapsedRect.setFillColor({255, 255, 150});
            t.collapsedText.setFillColor(sf::Color::Black);
            t.collapsedText.setStyle(sf::Text::Bold);
        } else {
            t.collapsedRect.setFillColor({30, 30, 30, 200});
            t.collapsedText.setFillColor(sf::Color::White);
            t.collapsedText.setStyle(sf::Text::Regular);
            if (!(isSpy && spyTarget == int(i))) {
            t.expanded = false;
        }
        }

        window.draw(t.collapsedRect);
        window.draw(t.collapsedText);

        
        bool expandedNormally = t.expanded && logic.canExpandTab(i);
        bool expandedBySpy = isSpy && (spyTarget == int(i)) && t.expanded;

        if (expandedNormally || expandedBySpy) {
            window.draw(t.panelRect);
            t.moneyText.setString("$" + std::to_string(players[i]->getCoins()));
            window.draw(t.moneyText);

            
            if (expandedNormally) {
                if (logic.cardAlreadyDrawn(i)) {
                    window.draw(t.cardText);
                }
                if (logic.isCardRevealed(i)) {
                    window.draw(t.smallCardSprite);
                }
            }
        }
    }
        if (errorVisible) {
        window.draw(errorBox);
        window.draw(errorText);
    }
    


  
    if (!centerVisible && !logic.isFirstRound()) {
        window.draw(gatherButton);   window.draw(gatherText);
        window.draw(taxButton);      window.draw(taxText);
        window.draw(bribeButton);    window.draw(bribeText);
        window.draw(arrestButton);   window.draw(arrestText);
        window.draw(sanctionButton); window.draw(sanctionText);
        window.draw(coupButton);     window.draw(coupText);

        Role role = players[currentPlayer]->getCard().getRole();
        switch (role) {
            case Role::Governor:
                window.draw(governorBlockTaxButton); window.draw(governorBlockTaxText);
                break;
            case Role::Spy:
                window.draw(spyPeekButton); window.draw(spyPeekText);
                break;
            case Role::Baron:
                window.draw(baronInvestButton); window.draw(baronInvestText);
                break;
            case Role::General:
                window.draw(generalBlockCoupButton); window.draw(generalBlockCoupText);
                break;
            case Role::Judge:
                window.draw(judgeBlockBribeButton); window.draw(judgeBlockBribeText);
                break;
            default:
                break;
        }
    }
    if (showWinner) {
    window.draw(overlay);
    window.draw(winnerText);
    window.draw(newGameBtn);  window.draw(newGameTxt);
    window.draw(exitBtn);     window.draw(exitTxt);
    }

    window.draw(topNewGameBtn);
    window.draw(topNewGameTxt);

    if (showWinner) {
        window.draw(overlay);
        window.draw(winnerText);
        window.draw(newGameBtn);  window.draw(newGameTxt);
        window.draw(exitBtn);     window.draw(exitTxt);
    }
}
void GameScreenGUI::showError(const std::string& msg) {
    errorText.setString( msg);
    sf::FloatRect textBounds = errorText.getLocalBounds();
    errorText.setPosition(
        errorBox.getPosition().x + 10,
        errorBox.getPosition().y + (errorBox.getSize().y - textBounds.height) / 2 - textBounds.top
    );
    errorVisible = true;
    errorTimer.restart();
}

bool GameScreenGUI::isAlive(size_t idx)
{
    return !players[idx]->isEliminated();
}

void GameScreenGUI::showWinnerOverlay(const std::string& name,
                                      std::function<void(bool)> onChoice)
{
    overlayChoiceCb = std::move(onChoice);   // שומרים

    winnerText.setString("Winner: " + name + "!");
    auto lb = winnerText.getLocalBounds();
    winnerText.setPosition(
        (window.getSize().x - lb.width) / 2.f - lb.left,
        (window.getSize().y - lb.height) / 2.f - 120);

    showWinner = true;
}
