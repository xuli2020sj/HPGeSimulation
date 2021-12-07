#if !defined(SteppingAction_H)
#define SteppingAction_H

#include "G4UserSteppingAction.hh"

#include "EventAction.h"


class SteppingAction : public G4UserSteppingAction
{
private:
    /* data */
public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};




#endif // SteppingAction_H
