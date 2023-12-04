// DrawCommand.cpp
#include "DrawCommand.h"

namespace engine {

  // Constructor
<<<<<<< HEAD
  DrawCommand::DrawCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, int nbOfCards) {

    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->nbOfCards = nbOfCards;

=======
  DrawCommand::DrawCommand(state::PlayerId authorPlayer, int nbOfCards) : nbOfCards(nbOfCards) {
>>>>>>> 3fdc9bc (engine tries)
  }

  // Destructor
  DrawCommand::~DrawCommand() {
  }

  // Execute method
  void DrawCommand::execute(state::GameState state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Getting his hand
    std::vector<state::Card> hand = player.getHand();

    // Adding the new cards to the player's hand
<<<<<<< HEAD
    for (int i=0; i< nbOfCards; i++){
      //hand.push_back(gameState.)
    }
=======
>>>>>>> a82536c (Beginning of DrawCommand, adding the stack to the gamestate)

    // Setting the player's new hand
    player.setHand(hand);
  }

  // Serialize method
  void DrawCommand::serialize() {
  }


} // namespace engine
