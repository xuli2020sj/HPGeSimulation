#if !defined(RunAction_h)
#define RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"
#include "G4Accumulable.hh"
#include "DataManager.h"
#include "G4GenericAnalysisManager.hh"

class RunAction : public G4UserRunAction
{
private:
    DataManager* data_manager_;
    void AddEdep(G4double edep);

public:
    RunAction(DataManager* DataManager);
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};




#endif // RunAction_h
