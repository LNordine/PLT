// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

namespace engine {

  // Constructor
<<<<<<< HEAD
  ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer, state::Phase phase) {
    
=======
  ChangePhaseCommand::ChangePhaseCommand(state::Phase phase, state::PlayerId authorPlayer) {

>>>>>>> 3fdc9bc (engine tries)
  }

  // Destructor
  ChangePhaseCommand::~ChangePhaseCommand() {
  }

  // Execute method
  void ChangePhaseCommand::execute(state::GameState state) {
  }


} // namespace engine
