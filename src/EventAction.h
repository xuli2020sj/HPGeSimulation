#if !defined(EventAction_H)
#define EventAction_H

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4EventManager.hh"


class EventAction : public G4UserEventAction
{
private:
    /* data */
public:
    EventAction(/* args */);
    ~EventAction();

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);
};




#endif // EventAction_H
