#include "ActionInitialization.h"


ActionInitialization::ActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {

   SetUserAction(new PrimaryGeneratorAction());

   RunAction* runAction = new RunAction();
   SetUserAction(runAction);
  //指定其为Geant4程序的RunAction
  
  // EventAction* eventAction = new EventAction();
  // SetUserAction(eventAction);
  // //指定其为Geant4程序的EventAction

  // SteppingAction* steppingAction = new SteppingAction(eventAction);
  // SetUserAction(steppingAction);
}
