#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Players/Player.hpp"
#include "../Players/BaronPlayer.hpp"
#include "../Players/GovernorPlayer.hpp"
#include "../Players/JudgePlayer.hpp"
#include "../Players/GeneralPlayer.hpp"
#include "../Players/MerchantPlayer.hpp"
#include "../Players/SpyPlayer.hpp"

TEST_CASE("Basic coin management") {
    MerchantPlayer mp("Maya");
    CHECK(mp.getCoins() == 0);
    mp.changeCoins(5);
    CHECK(mp.getCoins() == 5);
    mp.changeCoins(-3);
    CHECK(mp.getCoins() == 2);
    CHECK_THROWS_WITH(mp.changeCoins(-5), "Not enough coins");
}

TEST_CASE("Gather adds 1 coin") {
    GovernorPlayer gp("Gal");
    gp.gather();
    CHECK(gp.getCoins() == 1);
}

TEST_CASE("Tax action") {
    GovernorPlayer gp("Gal");
    gp.tax();
    CHECK(gp.getCoins() == 3);

    JudgePlayer jp("Jon");
    jp.tax();
    CHECK(jp.getCoins() == 2);

    jp.blockTaxForTurns();
    jp.tax();
    CHECK(jp.getCoins() == 2);
}

TEST_CASE("Bribe action") {
    JudgePlayer jp("Judge");
    jp.changeCoins(6);
    jp.bribe();
    CHECK(jp.getCoins() == 2);
    CHECK_THROWS(jp.bribe());
}

TEST_CASE("Arrest action on various players") {
    JudgePlayer a("A");
    GeneralPlayer b("B");
    a.changeCoins(3);
    b.changeCoins(3);
    a.arrest(b);
    CHECK(b.getCoins() == 3);

    MerchantPlayer c("C");
    c.changeCoins(3);
    a.arrest(c);
    CHECK(c.getCoins() == 1);

    BaronPlayer d("D");
    d.changeCoins(3);
    a.arrest(d);
    CHECK(d.getCoins() == 2);
    CHECK(a.getCoins() == 4);
}

TEST_CASE("Sanction mechanics and Judge penalty") {
    JudgePlayer jp("Judge");
    BaronPlayer bp("Baron");
    jp.changeCoins(6);
    bp.changeCoins(3);
    jp.sanction(bp);
    CHECK(jp.getCoins() == 3);
    CHECK(bp.getGatherBlockTurns() == 1);
    CHECK(bp.getTaxBlockTurns() == 1);

    JudgePlayer victim("Vic");
    victim.changeCoins(3);
    jp.changeCoins(6);
    jp.sanction(victim);
    CHECK(jp.getCoins() == 5);
}

TEST_CASE("Coup mechanics and blocking") {
    GeneralPlayer attacker("G");
    GovernorPlayer target("Gov");

    GeneralPlayer def("Gen");
    def.changeCoins(5);
    def.BlockCoup(target);

    attacker.changeCoins(7);
    attacker.coup(target);
    CHECK_FALSE(target.isEliminated());
    CHECK(attacker.getCoins() == 0);

    attacker.changeCoins(7);
    attacker.coup(target);
    CHECK(target.isEliminated());
    CHECK(attacker.getCoins() == 0);
}

TEST_CASE("Spy peeking") {
    SpyPlayer spy("Spy");
    MerchantPlayer victim("V");
    victim.changeCoins(3);
    spy.peekAndBlock(victim);
    CHECK(victim.getArrestBlockTurns() == 1);
}

TEST_CASE("Baron investing") {
    BaronPlayer baron("Bar");
    baron.changeCoins(4);
    baron.invest();
    CHECK(baron.getCoins() == 7);
    baron.changeCoins(-7);
    CHECK_THROWS(baron.invest());
}

TEST_CASE("General blocks coup for ally") {
    GeneralPlayer gen("Gen");
    JudgePlayer ally("Ally");
    gen.changeCoins(5);
    gen.blockCoup(ally);
    CHECK(ally.getCoupBlockTurns() == 1);
    CHECK(gen.getCoins() == 0);
}

TEST_CASE("Judge blocks bribe") {
    JudgePlayer judge("Judge");
    BaronPlayer cheater("Cheater");
	judge.changeCoins(4);
    cheater.changeCoins(6);
    cheater.bribe();
    judge.blockBribe(cheater);
    CHECK(cheater.getBribeBlockTurns() == 1);
    CHECK(judge.getCoins() == 0);
}


TEST_CASE("Governor blocks tax") {
    GovernorPlayer gov("Gov");
    JudgePlayer victim("Vic");
    gov.blockTax(victim);
    victim.tax();
    CHECK(victim.getCoins() == 0);
}

TEST_CASE("Baron gains coin when sanctioned") {
    BaronPlayer baron("B");
    JudgePlayer judge("J");
    baron.changeCoins(3);
    judge.changeCoins(6);
    judge.sanction(baron);
    CHECK(baron.getCoins() == 4);
}

TEST_CASE("Illegal coup throws") {
    GovernorPlayer gov("G");
    JudgePlayer target("T");
    CHECK_THROWS(gov.coup(target));
}

TEST_CASE("Illegal bribe throws") {
    GovernorPlayer gov("G");
    CHECK_THROWS(gov.bribe());
}

TEST_CASE("Spy cannot peek twice") {
    SpyPlayer spy("Spy");
    JudgePlayer target("J");
    spy.peekAndBlock(target);
    CHECK(target.getArrestBlockTurns() == 1);
    spy.peekAndBlock(target);
    CHECK(target.getArrestBlockTurns() == 1);
}

TEST_CASE("Block counters reset") {
    JudgePlayer player("P");
    player.blockBribeForTurns();
    player.blockGatherForTurns();
    player.blockTaxForTurns();
    player.blockArrestForTurns();
    player.decrementAllBlocks();
    CHECK(player.getBribeBlockTurns() == 0);
    CHECK(player.getGatherBlockTurns() == 0);
    CHECK(player.getTaxBlockTurns() == 0);
    CHECK(player.getArrestBlockTurns() == 0);
}
