// GameLogic_Test.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Logic/GameLogic.hpp"
#include "../Players/Player.hpp"
#include "../Players/BaronPlayer.hpp"
#include "../Players/GovernorPlayer.hpp"
#include "../Players/JudgePlayer.hpp"
#include "../Players/GeneralPlayer.hpp"
#include "../Players/MerchantPlayer.hpp"
#include "../Players/SpyPlayer.hpp"
#include <memory>
#include <vector>

TEST_CASE("GameLogic - Role assignment and player replacement") {
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::make_unique<GovernorPlayer>("A"));
    ps.push_back(std::make_unique<GovernorPlayer>("B"));

    GameLogic logic(std::move(ps));
    logic.selectRandomCardForPlayer(0);
    logic.selectRandomCardForPlayer(1);

    CHECK(logic.cardAlreadyDrawn(0));
    CHECK(logic.cardAlreadyDrawn(1));
    CHECK(logic.isCurrentPlayerDone());
}

TEST_CASE("GameLogic - next player rotation") {
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::make_unique<GovernorPlayer>("A"));
    ps.push_back(std::make_unique<GovernorPlayer>("B"));

    GameLogic logic(std::move(ps));
    CHECK(logic.getCurrentPlayerIndex() == 0);
    logic.nextPlayer();
    CHECK(logic.getCurrentPlayerIndex() == 1);
    logic.nextPlayer();
    CHECK(logic.getCurrentPlayerIndex() == 0);
}

TEST_CASE("GameLogic - performTax & performGather") {
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::make_unique<GovernorPlayer>("A"));
    GameLogic logic(std::move(ps));
    logic.performGather();
    logic.performTax();
    CHECK(logic.getCurrentPlayer().getCoins() == 4);
}

TEST_CASE("GameLogic - performBribe gives 2 extra turns") {
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::make_unique<GovernorPlayer>("A"));
    ps[0]->changeCoins(6);
    GameLogic logic(std::move(ps));
    logic.performBribe();
    logic.nextPlayer();
    CHECK(logic.getCurrentPlayerIndex() == 0);
    logic.nextPlayer();
    CHECK(logic.getCurrentPlayerIndex() == 0);
}

TEST_CASE("GameLogic - performArrest vs General refunds coin") {
    auto judge = std::make_unique<JudgePlayer>("J");
    auto gen = std::make_unique<GeneralPlayer>("G");
    gen->changeCoins(3);
    judge->changeCoins(3);

    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(judge));
    ps.push_back(std::move(gen));
    GameLogic logic(std::move(ps));

    logic.performArrest(*logic.getPlayers()[1]);
    CHECK(logic.getPlayers()[0]->getCoins() == 2);
    CHECK(logic.getPlayers()[1]->getCoins() == 4);
}

TEST_CASE("GameLogic - performSanction effects") {
    auto attacker = std::make_unique<JudgePlayer>("J");
    auto baron = std::make_unique<BaronPlayer>("B");
    attacker->changeCoins(6);
    baron->changeCoins(3);

    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(attacker));
    ps.push_back(std::move(baron));
    GameLogic logic(std::move(ps));

    logic.performSanction(*logic.getPlayers()[1]);
    CHECK(logic.getPlayers()[1]->getTaxBlockTurns() == 1);
    CHECK(logic.getPlayers()[1]->getGatherBlockTurns() == 1);
    CHECK(logic.getPlayers()[1]->getCoins() == 5);
    CHECK(logic.getPlayers()[0]->getCoins() == 3);
}
TEST_CASE("GameLogic - performCoup eliminates and ends game") {
    auto gov = std::make_unique<GovernorPlayer>("Gov");
    auto spy = std::make_unique<SpyPlayer>("Spy");
    gov->changeCoins(7);

    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(gov));
    ps.push_back(std::move(spy));
    GameLogic logic(std::move(ps));

    // מבצע coup על השחקן השני
    logic.performCoup(*logic.getPlayers()[1]);

    // כעת בודק אם ה-spy חוסל
    CHECK(logic.getPlayers()[1]->isEliminated());
}


TEST_CASE("GameLogic - spy peek and block") {
    auto spy = std::make_unique<SpyPlayer>("Spy");
    auto judge = std::make_unique<JudgePlayer>("J");

    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(spy));
    ps.push_back(std::move(judge));
    GameLogic logic(std::move(ps));

    logic.performSpyPeek(*logic.getPlayers()[1]);
    CHECK(logic.getPlayers()[1]->getArrestBlockTurns() == 1);
}

TEST_CASE("GameLogic - block tax throws if not Governor") {
    auto spy = std::make_unique<SpyPlayer>("S");
    auto judge = std::make_unique<JudgePlayer>("J");
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(spy));
    ps.push_back(std::move(judge));
    GameLogic logic(std::move(ps));
    CHECK_THROWS(logic.performBlockTax(*logic.getPlayers()[1]));
}

TEST_CASE("GameLogic - block coup throws if not General") {
    auto gov = std::make_unique<GovernorPlayer>("G");
    auto judge = std::make_unique<JudgePlayer>("J");
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(gov));
    ps.push_back(std::move(judge));
    GameLogic logic(std::move(ps));
    CHECK_THROWS(logic.performBlockCoup(*logic.getPlayers()[1]));
}

TEST_CASE("GameLogic - block bribe throws if not Judge") {
    auto gov = std::make_unique<GovernorPlayer>("G");
    auto baron = std::make_unique<BaronPlayer>("B");
    std::vector<std::unique_ptr<Player>> ps;
    ps.push_back(std::move(gov));
    ps.push_back(std::move(baron));
    GameLogic logic(std::move(ps));
    CHECK_THROWS(logic.performBlockBribe(*logic.getPlayers()[1]));
}

// Repeat tests for coverage

