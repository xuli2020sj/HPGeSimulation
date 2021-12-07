#include "RunAction.h"

RunAction::RunAction()
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
	G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
}

void RunAction::EndOfRunAction(const G4Run *run)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0)
		return;
}
