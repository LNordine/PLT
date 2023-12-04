#include "GameState.h"

#include <utility>

namespace state {

    std::vector<Player> GameState::getListOfPlayer (){
        return this->listOfPlayers;
    }

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> a82536c (Beginning of DrawCommand, adding the stack to the gamestate)
    int GameState::getNbCardToDraw () const{
        return this->nbOfCardToDraw;
    }


    void GameState::setNbCardToDraw (int nbCard){
        this->nbOfCardToDraw = nbCard;
    }

<<<<<<< HEAD
>>>>>>> f8eb613 (fixing query methods)
=======
=======
>>>>>>> 81887eb (Beginning of DrawCommand, adding the stack to the gamestate)
>>>>>>> a82536c (Beginning of DrawCommand, adding the stack to the gamestate)
    void GameState::setCurrentCharacter(CharacterType character) {
        this->currentCharacter=character;
    }

    CharacterType GameState::getCurrentCharacter() const{
        return this->currentCharacter;
    }



    GameState::GameState(std::vector<Player> listOfPlayer) {
        this->listOfPlayers = std::move(listOfPlayer);
        this->currentCharacter= CharacterType::NoCharacter;
        this->crownOwner = PlayerA;
        this->gamePhase = Phase::CHOOSECHARACTER;
    }

    void GameState::nextGamePhase() {
        switch (gamePhase) {
            case Phase::CHOOSECHARACTER :
                this->gamePhase = Phase::CALLCHARACTER;
                break;
            case Phase::ENDGAME:
                break;
            case Phase::CALLCHARACTER :
                this->gamePhase = Phase::CHOOSECHARACTER;
                break;
        }
    }

<<<<<<< HEAD
<<<<<<< HEAD
    Phase GameState::getGamePhase() {
=======
    GamePhase GameState::getGamePhase() const{
>>>>>>> f8eb613 (fixing query methods)
=======
    GamePhase GameState::getGamePhase() const{
=======
    Phase GameState::getGamePhase() {
>>>>>>> 736875c (Compilation ENGINE)
>>>>>>> 2d937c1 (Compilation ENGINE)
        return this->gamePhase;
    }

    void GameState::endGame() {
        this->gamePhase=Phase::ENDGAME;
    }

    PlayerId GameState::getCrownOwner() const{
        return this->crownOwner;
    }

    void GameState::setCrownOwner(PlayerId player) {
        this->crownOwner =player;
    }

    std::vector<Card> drawCards (int nbToDraw) {

    }

    std::vector<Card> initStack (){
        
    }
}