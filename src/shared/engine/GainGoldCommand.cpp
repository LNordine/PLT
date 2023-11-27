// Gain2GoldCommand.cpp
#include "GainGoldCommand.h"
#include <iostream>


namespace engine {

  // Constructor
<<<<<<< HEAD
  GainGoldCommand::GainGoldCommand(state::PlayerId authorPlayer,int nbOfGolds) : Command(){
=======
  Gain2GoldCommand::Gain2GoldCommand(state::PlayerId authorPlayer,int nbOfGolds) : Command(){
    this->playing=playing;
    this->nbOfGolds=nbOfGolds;
>>>>>>> 3fdc9bc (engine tries)
  }

  // Destructor
  GainGoldCommand::~GainGoldCommand() {
  }

  // Execute method
  void GainGoldCommand::execute(state::GameState state){
    
    /*switch (playing) {

        case state::Playing::PLAYERA:
            std::cout <<"A : + "<<nbOfGolds<< std::endl;
            break;

        case state::Playing::PLAYERB:
            std::cout <<"B : + "<<nbOfGolds<< std::endl;
            break;
          
          case state::Playing::PLAYERC:
            std::cout <<"C : + "<<nbOfGolds<< std::endl;
            break;
          
          case state::Playing::PLAYERD:
            std::cout <<"D : + "<<nbOfGolds<< std::endl;
            break;

        default:
            // Default case if the enumeration value is not recognized
            break;
    }*/

  }

  // Serialize method
  void GainGoldCommand::serialize() {

    
  }


} // namespace engine
