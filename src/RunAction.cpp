#include "RunAction.h"

RunAction::RunAction(DataManager* DataManager):G4UserRunAction(), data_manager_(DataManager)
{
}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run *run)
{
	G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
	data_manager_->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run *run)
{
	G4int numOfEvents = run->GetNumberOfEvent();
	G4cout << "### Run " << run->GetNumberOfEvent() << " end." << G4endl;
	if (numOfEvents == 0)	return;
	data_manager_->Save();
}
