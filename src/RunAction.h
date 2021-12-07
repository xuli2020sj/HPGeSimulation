#if !defined(RunAction_h)
#define RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"



class RunAction : public G4UserRunAction
{
private:
    /* data */
public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};




#endif // RunAction_h
