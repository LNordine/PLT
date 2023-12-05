// DrawCommand.cpp
#include "DrawCommand.h"

namespace engine {

  // Constructor
  DrawCommand::DrawCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, int nbOfCards) {

    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->nbOfCards = nbOfCards;

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
    for (int i=0; i< nbOfCards; i++){
      //hand.push_back(gameState.)
    }

    // Setting the player's new hand
    player.setHand(hand);
  }

  // Serialize method
  void DrawCommand::serialize() {
  }


} // namespace engine