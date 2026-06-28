/**
 * @file GameLogic.cpp
 * @brief Implementation of the GameLogic class that manages game flow and player actions.
 *
 * This file contains the logic for handling turns, actions, special abilities,
 * and rules of the Coup-inspired card game. It coordinates role behavior,
 * turn rotation, and enforces game rules such as Coup, Tax, Spy Peek, etc.
 *
 * @author Gal Maymon
 */

#include "GameLogic.hpp"


std::string GameLogic::roleToString(Role r) {
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

GameLogic::GameLogic(std::vector<std::unique_ptr<Player>>&& playersVec)
    : players(std::move(playersVec)),
      currentPlayerIndex(0),
      rng(std::random_device{}()),
      aliveCount(players.size())
{
    drawnFlags.assign(players.size(), false);
    revealFlags.assign(players.size(), false);
}

bool GameLogic::isFirstRound() const {
    return firstRound;
}
bool GameLogic::isSetupComplete() const {
    return setupCompleted;
}

void GameLogic::setOnSetupCompleteCallback(std::function<void()> callback) {
    onSetupCompleteCallback = std::move(callback);
}
void GameLogic::markFirstRoundDoneIfNeeded() {
    bool allDrew = true;
    for (bool drawn : drawnFlags) {
        if (!drawn) {
            allDrew = false;
            break;
        }
    }
    if (allDrew && firstRound) {
        firstRound = false;
                       
        setupCompleted = true;     

        if (onSetupCompleteCallback) {
            onSetupCompleteCallback(); 
        }
    }
}


void GameLogic::selectRandomCardForPlayer(size_t playerIndex) {
    if (playerIndex >= players.size() || drawnFlags[playerIndex]) return;

    static const std::vector<Role> allRoles = {
        Role::Governor, Role::Spy, Role::Baron,
        Role::General, Role::Judge, Role::Merchant
    };

    std::uniform_int_distribution<size_t> dist(0, allRoles.size() - 1);
    size_t index = dist(rng);
    Role chosen = allRoles[index];

    std::string playerName = players[playerIndex]->getName();
    players[playerIndex] = createPlayerFromRole(playerName, chosen);

    drawnFlags[playerIndex] = true;  
}

bool GameLogic::canExpandTab(size_t playerIndex) const {
    return playerIndex == currentPlayerIndex; 
}


Player& GameLogic::getCurrentPlayer() {
    return *players[currentPlayerIndex];
}

size_t GameLogic::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}

void GameLogic::nextPlayer() {
    if (extraTurns > 0) {
        --extraTurns;
        return;
    }

    players[currentPlayerIndex]->decrementAllBlocks();

    size_t originalIndex = currentPlayerIndex;
    do {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    } while (players[currentPlayerIndex]->isEliminated() &&
             currentPlayerIndex != originalIndex); // כדי להימנע מלולאה אינסופית

    Player& current = *players[currentPlayerIndex];
    if (current.getRole() == Role::Merchant && current.getCoins() > 3) {
        current.changeCoins(1);
    }
}



bool GameLogic::cardAlreadyDrawn(size_t playerIndex) const {
    return drawnFlags[playerIndex];
}

void GameLogic::revealCard(size_t playerIndex) {
    if (playerIndex < players.size())
        revealFlags[playerIndex] = true;
}

bool GameLogic::isCardRevealed(size_t playerIndex) const {
    return playerIndex < revealFlags.size() && revealFlags[playerIndex];
}

bool GameLogic::isCurrentPlayerDone() const {
    return drawnFlags[currentPlayerIndex];
}

std::string GameLogic::getPlayerPublicInfo(size_t playerIndex) const {
    if (playerIndex >= players.size()) return "";

    const Player& p = *players[playerIndex];
    std::ostringstream info;
    info << p.getName() << " | Coins: " << p.getCoins();
    if (revealFlags[playerIndex]) {
        info << " | Card: " << p.getCard().getName();
    } else {
        info << " | Card: [Hidden]";
    }
    return info.str();
}

std::string GameLogic::getCurrentPlayerFullInfo() const {
    const Player& p = *players[currentPlayerIndex];
    std::ostringstream info;
    info << p.getName() << " | Coins: " << p.getCoins()
         << " | Card: " << (drawnFlags[currentPlayerIndex] ? p.getCard().getName() : "[Not Drawn Yet]");
    return info.str();
}
std::vector<std::unique_ptr<Player>>& GameLogic::getPlayers() {
    return players;
}

void GameLogic::startGameLoop() {
    currentPlayerIndex = 0;
}
void GameLogic::performTax() {
    players[currentPlayerIndex]->tax();
}

void GameLogic::performGather() {
    players[currentPlayerIndex]->gather();
}

void GameLogic::performBribe() {
    players[currentPlayerIndex]->bribe();
    extraTurns += 2;  
}

void GameLogic::performArrest(Player& target) {
	
    Player& arrestingPlayer = *players[currentPlayerIndex];

    
    arrestingPlayer.arrest(target);

    
    if (target.getRole() == Role::General) {
        target.changeCoins(1);
        arrestingPlayer.changeCoins(-1);
    }
}

void GameLogic::performSanction(Player& target) {
    Player& attacker = *players[currentPlayerIndex];

    attacker.sanction(target);
}

bool GameLogic::performCoup(Player& target)
{
    Player& attacker = *players[currentPlayerIndex];
    if (attacker.getCoins() < 7)
        throw std::runtime_error("You need 7 coins for a Coup");

    attacker.changeCoins(-7);

    if (target.isEliminated()) return false;       

    target.eliminate();
    --aliveCount;                                  

    if (isGameOver() && onGameOver) {              
        onGameOver(getWinner());
    }
    return true;
}



void GameLogic::performBlockTax(Player& target) {
    if (players[currentPlayerIndex]->getRole() != Role::Governor)
        throw std::runtime_error("Only Governor can block tax");

    target.blockTaxForTurns();  
}
void GameLogic::performSpyPeek(Player& target) {
    if (players[currentPlayerIndex]->getRole() != Role::Spy)
        throw std::runtime_error("Only Spy can peek");

    auto* spy = dynamic_cast<SpyPlayer*>(players[currentPlayerIndex].get());
    if (!spy)
        throw std::runtime_error("Internal error: player is not actually a SpyPlayer");

   
    spyPeekTargetIndex = -1;
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].get() == &target) {
            spyPeekTargetIndex = static_cast<int>(i);
            break;
        }
    }
    spy->peekAndBlock(target); 
}

void GameLogic::performInvest() {
    if (players[currentPlayerIndex]->getRole() != Role::Baron)
        throw std::runtime_error("Only Baron can invest");

    auto* baron = dynamic_cast<BaronPlayer*>(players[currentPlayerIndex].get());
    if (!baron)
        throw std::runtime_error("Internal error: player is not actually a BaronPlayer");

    baron->invest();
}


void GameLogic::performBlockCoup(Player& target) {
    if (players[currentPlayerIndex]->getRole() != Role::General)
        throw std::runtime_error("Only General can block coup");

    auto* general = dynamic_cast<GeneralPlayer*>(players[currentPlayerIndex].get());
    if (!general)
        throw std::runtime_error("Internal error: player is not actually a GeneralPlayer");

    general->blockCoup(target);
}

void GameLogic::performBlockBribe(Player& target) {
    if (players[currentPlayerIndex]->getRole() != Role::Judge)
        throw std::runtime_error("Only Judge can block bribe");

    auto* judge = dynamic_cast<JudgePlayer*>(players[currentPlayerIndex].get());
    if (!judge)
        throw std::runtime_error("Internal error: player is not a JudgePlayer");

    judge->blockBribe(target); 
}


const Player& GameLogic::getWinner() const
{
    if (!isGameOver()) throw std::logic_error("Game not finished");
    for (const auto& playerPtr : players)
        if (!playerPtr->isEliminated()) return *playerPtr;
    throw std::logic_error("No winner found");      
}


