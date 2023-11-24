// Engine.cpp
#include "Engine.h"


#include "Command.h"


namespace engine {

  // Constructor with parameter
  Engine::Engine(state::GameState state) : currentState(state) {
    // Other initialization if needed
    init();
  }

  // Destructor
  Engine::~Engine() {
    // Clean up resources if needed
  }

  // Initialization method
  void Engine::init() {
<<<<<<< HEAD
    
=======
>>>>>>> c6ddbd7 (Engine.cpp ne compile pas)
    // Perform initialization tasks here
  }

  // Getter for the current game state
  state::GameState Engine::getState() {
    return currentState;
  }

  // Add a command to the list of commands
<<<<<<< HEAD
<<<<<<< HEAD
  
  void Engine::addCommand (std::unique_ptr<Command> cmd){

    listOfCommands.push_back(std::move(cmd));

  }


  void Engine::executeAllCommands(state::GameState state){
    for (auto& cmd : listOfCommands) {
    cmd->execute(state);
  }
  }


=======
  void Engine::addCommand(std::unique_ptr<Command> cmd) {
    // Add the unique command to the list
    listOfCommands.push_back(cmd);
  }
=======
  void addCommand (std::vector<std::unique_ptr<Command>> cmd){}
>>>>>>> 6cf1432 (ComprendsRien)

>>>>>>> c6ddbd7 (Engine.cpp ne compile pas)
  // Setters and Getters
  // You can add setters and getters for other attributes as needed

} // namespace engine
