/**
 * @file Player.hpp
 * @brief Base class for all player types in the Coup-inspired card game.
 *
 * This file defines the abstract Player class, which represents a game participant.
 * It provides shared functionality for coin management, action blocking,
 * and basic actions such as tax, bribe, gather, arrest, and coup.
 * 
 * Specific player types (like Spy, Baron, Judge) override and extend these behaviors.
 *
 * @author Gal Maymon
 */

#pragma once

#include <string>
#include <stdexcept>
#include <memory>
#include "../cards/Card.hpp"

class Player {
public:
    explicit Player(const std::string& name);
    virtual ~Player() = default;

    const std::string& getName() const;
    virtual Role getRole() const;
    virtual const Card& getCard() const;

    void changeCoins(int delta);
    int getCoins() const { return coins; }

    virtual void gather();
    virtual void tax();
    virtual void bribe();
    virtual void arrest(Player& target);
    virtual void sanction(Player& target);
    virtual void coup(Player& target);
    virtual void blocksanctionForTurns(){blockTaxForTurns(),blockGatherForTurns();}

    virtual void blockTaxForTurns(){taxBlockTurns=1;}
    virtual void blockGatherForTurns(){gatherBlockTurns=1;}
    virtual void addCoupBlockFromAlly(){coupBlockTurns++;}
    virtual void blockArrestForTurns(){arrestBlockTurns=1;}
    virtual void blockBribeForTurns(){BribeBlockTurns=1;}
    
    
    

    void eliminate() {
        eliminated = true;
    }

    bool isEliminated() const {
        return eliminated;
    }

    void decrementAllBlocks() {
        if (taxBlockTurns > 0) taxBlockTurns = 0;
        if (arrestBlockTurns > 0) arrestBlockTurns = 0;
        if (gatherBlockTurns > 0) gatherBlockTurns = 0;
        if (BribeBlockTurns > 0) BribeBlockTurns = 0;
    
    }
    int getTaxBlockTurns() const { return taxBlockTurns; }
    int getArrestBlockTurns() const { return arrestBlockTurns; }
    int getGatherBlockTurns() const { return gatherBlockTurns; }
    int getCoupBlockTurns() const { return coupBlockTurns; }
    int getBribeBlockTurns() const { return BribeBlockTurns; }

protected:
    std::string name;
    int coins = 0;
    int taxBlockTurns = 0;
    int arrestBlockTurns = 0;
    int gatherBlockTurns = 0;
    int coupBlockTurns = 0;
    int BribeBlockTurns = 0;
    bool eliminated = false;
};
