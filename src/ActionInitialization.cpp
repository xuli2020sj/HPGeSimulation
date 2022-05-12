#include "ActionInitialization.h"

ActionInitialization::ActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(new DataManager()));
}

void ActionInitialization::Build() const
{
    DataManager* dataManager = new DataManager();
    auto xRunAction = new RunAction(dataManager);
    auto xEventAction = new EventAction(xRunAction, dataManager);
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(xRunAction);
    SetUserAction(xEventAction);

//    auto xSteppingAction = new SteppingAction(xEventAction);
//    SetUserAction(xSteppingAction);
}
