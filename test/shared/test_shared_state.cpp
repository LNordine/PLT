#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/GameState.h"

using namespace ::state;


BOOST_AUTO_TEST_CASE(TestState){

    Card card{"card1", CardType::MILITARY, 2};
    BOOST_CHECK_EQUAL(card.getNameOfCard(), std::string("card1"));
    BOOST_CHECK_EQUAL(card.getColorOfCard(), CardType::MILITARY);
    BOOST_CHECK_EQUAL(card.getCostOfCard(), 2);

    Card cardReligious{"card2", CardType::RELIGIOUS, 4};
    BOOST_CHECK_EQUAL(cardReligious.getNameOfCard(), std::string("card2"));
    BOOST_CHECK_EQUAL(cardReligious.getColorOfCard(), CardType::RELIGIOUS);
    BOOST_CHECK_EQUAL(cardReligious.getCostOfCard(), 4);

    Card cardCommercial{"card3", CardType::COMMERCIAL, 8};
    BOOST_CHECK_EQUAL(cardCommercial.getNameOfCard(), std::string("card3"));
    BOOST_CHECK_EQUAL(cardCommercial.getColorOfCard(), CardType::COMMERCIAL);
    BOOST_CHECK_EQUAL(cardCommercial.getCostOfCard(), 8);

    Card cardNoble{"card1", CardType::NOBLE, 2};
    BOOST_CHECK_EQUAL(cardNoble.getColorOfCard(), CardType::NOBLE);

    Card cardWonder{"card1", CardType::WONDER, 2};
    BOOST_CHECK_EQUAL(cardWonder.getColorOfCard(), CardType::WONDER);

    std::string playerName = "player1";
    Player plr{playerName, PlayerId::PLAYER_A};
    BOOST_CHECK_EQUAL(plr.getNameOfPlayer(), "player1");
    BOOST_CHECK_EQUAL(plr.getIdOfPlayer(), PlayerId::PLAYER_A);
    BOOST_CHECK_EQUAL(plr.getCharacter(), CharacterType::NO_CHARACTER);
    std::vector<Card> hand{card};
    plr.setHand(hand);
    BOOST_CHECK_EQUAL(plr.getHand()[0].getNameOfCard(), hand[0].getNameOfCard());
    BOOST_CHECK_EQUAL(plr.getNumberOfCards(), 1);
    plr.setNumberOfCoins(5);
    BOOST_CHECK_EQUAL(plr.getNumberOfCoins(), 5);
    std::vector<Card> board;
    plr.setBoardOfPlayer(board);
    BOOST_CHECK_EQUAL(plr.getBoardOfPlayer().size(), board.size());
    plr.setCharacter(CharacterType::WARLORD);
    BOOST_CHECK_EQUAL(plr.getCharacter(), CharacterType::WARLORD);

    GameState gameState{std::vector<Player>{plr}};
    BOOST_CHECK_EQUAL(gameState.getListOfPlayer().size(), 1);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(), CharacterType::NO_CHARACTER);
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), Phase::CHOOSE_CHARACTER);

    gameState.setCrownOwner(PlayerId::PLAYER_A);
    BOOST_CHECK_EQUAL((gameState.getCrownOwner()), plr.getIdOfPlayer());

    gameState.setCurrentCharacter(CharacterType::KING);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(), CharacterType::KING);

    gameState.setPlaying(PLAYER_D);
    BOOST_CHECK_EQUAL(gameState.getPlaying(), PLAYER_D);

    BOOST_CHECK_EQUAL(gameState.getPlayer(PLAYER_A).getNameOfPlayer(), plr.getNameOfPlayer());
    BOOST_CHECK_THROW(gameState.getPlayer(PLAYER_D), std::exception);
    BOOST_CHECK_NO_THROW(gameState.updatePlayer(plr));

    plr.setCapacityAvailability(true);
    gameState.updatePlayer(plr);

    BOOST_CHECK_EQUAL(gameState.getPlayer(PLAYER_A).getCapacityAvailability(),true);

    gameState.setKilledCharacter(KING);
    BOOST_CHECK_EQUAL(gameState.getKilledCharacter(),KING);

    gameState.setRobbedCharacter(KING);
    BOOST_CHECK_EQUAL(gameState.getRobbedCharacter(),KING);

    gameState.setDrawableCards(std::vector<Card>{card});
    BOOST_CHECK_EQUAL(gameState.getDrawableCards().at(0).getNameOfCard(),"card1");

    gameState.setAvailableCharacter(std::vector<CharacterType>{WARLORD,KING});
    BOOST_CHECK_EQUAL(gameState.getAvailableCharacter().size(),2);

    gameState.setGamePhase(CALL_CHARACTER);
    BOOST_CHECK_EQUAL(gameState.getGamePhase(),CALL_CHARACTER);

}

/* vim: set sw=2 sts=2 et : */
