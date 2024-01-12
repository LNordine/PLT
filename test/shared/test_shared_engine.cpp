#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"

using namespace ::engine;

#define STACK_SIZE 66
struct F {
    F() : gameState("player1",
                    "player2",
                    "player3",
                    "player4") { BOOST_TEST_MESSAGE("setup fixture"); }

    ~F() { BOOST_TEST_MESSAGE("teardown fixture"); }

    state::GameState gameState;
};

//____________________________________________________________________________//

BOOST_FIXTURE_TEST_SUITE(CommandTestCase, F)
    BOOST_AUTO_TEST_CASE(ShouldCommandBeCovered){
        Command c{};
        BOOST_CHECK_NO_THROW(c.execute(gameState));
 }

    BOOST_AUTO_TEST_CASE(TestBuildCommand) {

        gameState.setPlaying(state::PLAYER_B);

        state::Card card{"1", state::CardType::RELIGIOUS, 3};

        auto *command = new BuildCommand(state::PLAYER_A, card);
        BOOST_CHECK_EQUAL(command->getCommandTypeId(),CommandTypeId::BUILD);

        //Command not executed because not my turn
        BOOST_CHECK_EQUAL(command->check(gameState), false);
        gameState.setPlaying(state::PLAYER_A);
        //Test all case of non-available command

        //Command not executed because card is not in the hand
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);

        std::vector<state::Card> hand = std::vector<state::Card>{card};
        plr1.setHand(hand);
        plr1.setBoardOfPlayer(hand);
        gameState.updatePlayer(plr1);
        //Command not executed because already in the board
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        std::vector<state::Card> board = std::vector<state::Card>{};
        plr1.setBoardOfPlayer(board);
        gameState.updatePlayer(plr1);
        //Command not executed because not enough coin
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        plr1.setNumberOfCoins(4);
        gameState.updatePlayer(plr1);
        //True this time
        BOOST_CHECK_EQUAL(command->check(gameState), true);
        Engine::init(gameState);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();
        plr1 = gameState.getPlayer(state::PLAYER_A);

        BOOST_CHECK_EQUAL(plr1.getNumberOfCoins(), 1);
        BOOST_CHECK_EQUAL(plr1.getHand().size(), 0);
        BOOST_CHECK_EQUAL(plr1.getBoardOfPlayer().size(), 1);
    }

    BOOST_AUTO_TEST_CASE(TestDrawCommand) {
        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);

        plr1.setDrawAvailability(false);

        gameState.setPlaying(state::PLAYER_B);

        auto *command = new DrawCommand(state::PlayerId::PLAYER_A);
        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 0);
        BOOST_CHECK_EQUAL(command->getCommandTypeId(),CommandTypeId::DRAW_CARD);

        //Command not executed because not my turn
        BOOST_CHECK_EQUAL(command->check(gameState), false);
        gameState.setPlaying(state::PlayerId::PLAYER_A);

        //Command not executed because draw is not available
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        plr1.setDrawAvailability(true);
        gameState.updatePlayer(plr1);

        BOOST_CHECK_EQUAL(command->check(gameState), true);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 0);

        Engine::init(gameState);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 2);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), STACK_SIZE);

        state::Card cardWonder{"22", state::CardType::WONDER, 5};
        std::vector<state::Card> newBoard;
        newBoard.push_back(cardWonder);
        plr1.setBoardOfPlayer(newBoard);
        gameState.updatePlayer(plr1);
        command = new DrawCommand(state::PlayerId::PLAYER_A);

        Engine::init(gameState);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 3);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), STACK_SIZE-3);

    }

    BOOST_AUTO_TEST_CASE(TestEndOfTurnCommand) {
        state::Player playerC=gameState.getPlayer(state::PlayerId::PLAYER_C);
        playerC.setNumberOfCoins(10);
        gameState.updatePlayer(playerC);
        state::Player playerD=gameState.getPlayer(state::PlayerId::PLAYER_D);
        playerD.setNumberOfCoins(5);
        gameState.updatePlayer(playerD);
        
        gameState.setCrownOwner(state::PLAYER_B);
        gameState.setPlaying(state::PLAYER_B);
        gameState.setGamePhase(state::CHOOSE_CHARACTER);
        gameState.setCurrentCharacter(state::NO_CHARACTER);
        gameState.setAvailableCharacter({state::CharacterType::ASSASSIN,
                                             state::CharacterType::THIEF,
                                             state::CharacterType::MAGICIAN,
                                             state::CharacterType::KING,
                                             state::CharacterType::BISHOP,
                                             state::CharacterType::MERCHANT,
                                             state::CharacterType::ARCHITECT,
                                             state::CharacterType::WARLORD});
        

        
        auto* command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        auto* chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_B,state::CharacterType::KING);
        Engine::init(gameState);

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        BOOST_CHECK_EQUAL(command->check(gameState), true);

        Engine::getInstance().addCommand(chooseCharacter);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_C,state::CharacterType::WARLORD);
        Engine::getInstance().addCommand(chooseCharacter);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_D,state::CharacterType::THIEF);
        Engine::getInstance().addCommand(chooseCharacter);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_A);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_A,state::CharacterType::MERCHANT);
        Engine::getInstance().addCommand(chooseCharacter);
        Engine::getInstance().executeAllCommands();

        //Check if the switch pahse is OK
        //BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CALL_CHARACTER);

        //Check for the nextplayers during this phase
        //PlayerD=Assasin--PlayerB=King--PlayerA=Merchant--PlayerC=Warlord
//        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        gameState.setRobbedCharacter(state::CharacterType::WARLORD);
        //PlayerC will be roobed by PlayerD
        gameState.setKilledCharacter(state::CharacterType::MERCHANT);
        //PlayerA will pass his turn
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        gameState.setCrownOwner(state::PlayerId::PLAYER_B);
        //at the end of this phase B will be the first player
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();

        //playerA is supposed to be killed because he is the MERCHANT
        //It's supposed to be PlayerC turn, but he got robbed by D

//        BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_C).getNumberOfCoins(),0);
//        BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_D).getNumberOfCoins(),15);

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        Engine::getInstance().addCommand(command);
        Engine::getInstance().executeAllCommands();
        
         //Check if the switch phase is OK
        BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CHOOSE_CHARACTER);
//        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        
    }



    BOOST_AUTO_TEST_CASE(ChangePhaseCHOOSEtoCALL) {
    // Création d'une instance de ChangePhaseCommand
    gameState.setGamePhase(state::Phase::CHOOSE_CHARACTER);
    engine::ChangePhaseCommand command(state::PlayerId::PLAYER_A, state::Phase::CHOOSE_CHARACTER);

    // Vérification des propriétés après la création
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CHOOSE_CHARACTER);
    BOOST_CHECK_EQUAL(command.getCommandTypeId(), engine::CommandTypeId::SWITCH_PHASE);

    // Exécution de la commande
    command.execute(gameState);

    // Vérification que la phase a été changée correctement
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CALL_CHARACTER);
}

    BOOST_AUTO_TEST_CASE(ChangePhaseToEndGame) {
    // Création d'une instance de ChangePhaseCommand
    gameState.setGamePhase(state::Phase::CALL_CHARACTER);
    gameState.setPlaying(state::PlayerId::PLAYER_A);
    engine::ChangePhaseCommand command(state::PlayerId::PLAYER_A, state::Phase::CALL_CHARACTER);

    state::Player playerA = gameState.getPlayer(state::PlayerId::PLAYER_A);
    state::Card cardWonder{"22", state::CardType::WONDER, 5};
    playerA.setBoardOfPlayer({cardWonder,cardWonder,cardWonder,cardWonder,cardWonder,cardWonder,cardWonder,cardWonder});
    gameState.updatePlayer(playerA);

    // Exécution de la commande
    command.execute(gameState);

    // Vérification que la phase a été changée correctement
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::END_GAME);
}

//TEST Claim building command
BOOST_AUTO_TEST_CASE(ClaimBuildingCommand) {

    gameState.setPlaying(state::PlayerId::PLAYER_A);

    // Création d'une instance de ClaimBuildingGold
    engine::ClaimBuildingGold command(state::PlayerId::PLAYER_A);

    // Vérification des propriétés après la création
    BOOST_CHECK_EQUAL(command.getCommandTypeId(), engine::CommandTypeId::CLAIM_BUILDING_GOLD);

    // Exécution de la commande
    command.execute(gameState);

    // Vérification que le nombre de pièces du joueur a été mis à jour correctement
    state::Player playerA = gameState.getPlayer(state::PlayerId::PLAYER_A);
    playerA.setCharacter(state::CharacterType::WARLORD);
    BOOST_CHECK_EQUAL(playerA.getNumberOfCoins(), 2);  // Aucune carte sur le plateau, aucune pièce gagnée

    // Ajout de cartes au joueur pour simuler une condition
    playerA.setBoardOfPlayer({{"1", state::CardType::MILITARY, 2}, {"2", state::CardType::MILITARY, 3}});
    gameState.updatePlayer(playerA);

    // Exécution de la commande après ajout de cartes
    command.execute(gameState);
    

    // Vérification que le nombre de pièces du joueur a été mis à jour correctement
    BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_A).getNumberOfCoins(), 4);  // 2 cartes MILITARY avec un total de 2+2=4 pièces d'or
}


//TEST DrawCommand
BOOST_AUTO_TEST_CASE(ConstructionAndExecution) {
    // Création d'une instance de DrawCommand
    engine::DrawCommand command(state::PlayerId::PLAYER_A);

    gameState.setPlaying(state::PlayerId::PLAYER_A);

    // Vérification des propriétés après la création
    BOOST_CHECK_EQUAL(command.getCommandTypeId(), engine::CommandTypeId::DRAW_CARD);

    // Création d'un stack avec suffisamment de cartes
    gameState.setStack(StackUtils::initStack());

    // Ajout d'une carte "22" (Observatory) à la board du joueur A
    state::Player playerA = gameState.getPlayer(state::PlayerId::PLAYER_A);
    playerA.setHand({});//Hand vide
    playerA.setBoardOfPlayer({{"22", state::CardType::WONDER, 5}});
    gameState.updatePlayer(playerA);

    // Exécution de la commande
    command.execute(gameState);

    // Vérification que la phase du jeu a été changée à Draft
    BOOST_CHECK_EQUAL(gameState.getSubPhase(), state::SubPhase::Draft);

    std::vector<state::Card> drawableCards = gameState.getDrawableCards();
    
    state::Card card0=drawableCards[0];
    state::Card card1=drawableCards[1];
    state::Card card2=drawableCards[2];

    //appel de choosecardCommand
    engine::ChooseCardCommand chooseCommand1(state::PlayerId::PLAYER_A, card0);
    chooseCommand1.execute(gameState);
    Engine::getInstance(gameState).executeAllCommands();
    //on pioche une carte les options de draw se réduisent de 1
    BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(),2);
    BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_A).getHand().size(),1);
    engine::ChooseCardCommand chooseCommnd2(state::PlayerId::PLAYER_A, card1);
    chooseCommnd2.execute(gameState);
    Engine::getInstance(gameState).executeAllCommands();
    BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_A).getHand().size(),2);


}
BOOST_AUTO_TEST_CASE(DefaultDraw) {
    // Création d'une instance de DrawCommand
    engine::DrawCommand command(state::PlayerId::PLAYER_A);
    gameState.setPlaying(state::PlayerId::PLAYER_A);

    // Vérification des propriétés après la création
    BOOST_CHECK_EQUAL(command.getCommandTypeId(), engine::CommandTypeId::DRAW_CARD);

    // Création d'un stack avec suffisamment de cartes
    gameState.setStack(StackUtils::initStack());

    // Ajout d'une carte "22" (Observatory) à la board du joueur A
    state::Player playerA = gameState.getPlayer(state::PlayerId::PLAYER_A);
    playerA.setHand({});//Hand vide
    playerA.setBoardOfPlayer({{}});
    gameState.updatePlayer(playerA);

    // Exécution de la commande
    command.execute(gameState);

    // Vérification que la phase du jeu a été changée à Draft
    BOOST_CHECK_EQUAL(gameState.getSubPhase(), state::SubPhase::Draft);
    std::vector<state::Card> drawableCards = gameState.getDrawableCards();
    state::Card card0=drawableCards[0];
    //appel de choosecardCommand
    engine::ChooseCardCommand chooseCommand1(state::PlayerId::PLAYER_A, card0);
    chooseCommand1.execute(gameState);
    Engine::getInstance(gameState).executeAllCommands();
    //on pioche une carte les options de draw se réduisent de 1
    BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_A).getHand().size(),1); 
}

//Test gainGold command
// Test case for the execute method
BOOST_AUTO_TEST_CASE(GainGoldCommandTest1) {
    
    engine::GainGoldCommand gainGoldCommand(state::PlayerId::PLAYER_A, 5);
    
    gainGoldCommand.execute(gameState);

    // Add assertions to check if the execution had the desired effect on the game state
    state::Player player = gameState.getPlayer(state::PlayerId::PLAYER_A);

    BOOST_CHECK_EQUAL(player.getNumberOfCoins(), 7); // Assuming the initial number of coins was 0
    BOOST_CHECK(!player.isDrawAvailable());  // Assuming the draw availability is set to false in execute
}

BOOST_AUTO_TEST_CASE(ExecuteTestStartGame) {
    
    engine::StartGameCommand startGameCommand(state::PlayerId::PLAYER_A);
    
    startGameCommand.execute(gameState);

    // Add assertions to check if the execution had the desired effect on the game state
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(), state::CharacterType::NO_CHARACTER);
    BOOST_CHECK_EQUAL(gameState.getCrownOwner(), state::PlayerId::PLAYER_A);
    BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);
    BOOST_CHECK_EQUAL(gameState.getKilledCharacter(), state::CharacterType::NO_CHARACTER);
    BOOST_CHECK_EQUAL(gameState.getRobbedCharacter(), state::CharacterType::NO_CHARACTER);
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CHOOSE_CHARACTER);
}







BOOST_AUTO_TEST_SUITE_END()

