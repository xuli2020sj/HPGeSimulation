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
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new RunAction(dataManager));
  SetUserAction(new EventAction(dataManager));
}
