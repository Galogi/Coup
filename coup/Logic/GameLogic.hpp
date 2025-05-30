/**
 * @file GameLogic.hpp
 * @brief Definition of the GameLogic class that manages game flow and player actions.
 *
 * This header declares the GameLogic class which handles all rules and logic
 * for the Coup-inspired card game, including turn rotation, special actions,
 * and player role behavior coordination.
 *
 * @author Gal Maymon
 */


#pragma once
#include <vector>
#include <random>
#include "../Players/Player.hpp"
#include "../Players/GeneralPlayer.hpp"
#include "../Players/SpyPlayer.hpp"
#include "../Players/GovernorPlayer.hpp"
#include "../Players/BaronPlayer.hpp"
#include "../Players/JudgePlayer.hpp"
#include "../Players/MerchantPlayer.hpp"
#include "../cards/Card.hpp"
#include <sstream>
#include <functional>
#include "../Players/PlayerFactory.hpp"

class GameLogic {
public:

	GameLogic(std::vector<std::unique_ptr<Player>>&& players); 

	void selectRandomCardForPlayer(size_t playerIndex);
    Player& getCurrentPlayer();
    size_t getCurrentPlayerIndex() const;
    void nextPlayer();
	bool canExpandTab(size_t playerIndex) const;




    bool cardAlreadyDrawn(size_t playerIndex) const;
    void revealCard(size_t playerIndex);
    bool isCardRevealed(size_t playerIndex) const;
	std::vector<std::unique_ptr<Player>>& getPlayers();

    bool isCurrentPlayerDone() const;
	void startGameLoop();

    std::string getPlayerPublicInfo(size_t playerIndex) const;
    std::string getCurrentPlayerFullInfo() const;
	bool isFirstRound() const;
	bool isSetupComplete() const;
	void markFirstRoundDoneIfNeeded();
	void setOnSetupCompleteCallback(std::function<void()> callback);
	void performTax();
	void performGather();
	void performBribe();
	void performArrest(Player& target);
	void performSanction(Player& target);
	bool performCoup(Player& target);

	// מיוחדים
	void performBlockTax(Player& target);
	
	void performSpyPeek(Player& target);
	void performInvest();
	void performBlockCoup(Player& target);
	void performBlockBribe(Player& target); 
	void clearSpyPeek()            { spyPeekTargetIndex = -1; }
	int  getSpyPeekTarget() const  { return spyPeekTargetIndex; }
	bool   isGameOver()  const { return aliveCount == 1; }
    const Player& getWinner() const;          
    void   setOnGameOverCallback(std::function<void(const Player&)> cb)
           { onGameOver = std::move(cb); }
	static std::string roleToString(Role r);

private:
    bool firstRound = true;	
    std::vector<std::unique_ptr<Player>> players;
    size_t currentPlayerIndex;
    std::vector<bool> drawnFlags;
    std::vector<bool> revealFlags;
    std::mt19937 rng;
    bool setupCompleted = false;
    std::function<void()> onSetupCompleteCallback;
	int spyPeekTargetIndex = -1;
	int extraTurns = 0;
	size_t aliveCount; 
	std::function<void(const Player&)> onGameOver;    
};

