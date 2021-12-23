#if !defined(EventAction_H)
#define EventAction_H

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "DataManager.h"
#include "G4THitsMap.hh"
#include "DataManager.h"

class DataManager;
class EventAction : public G4UserEventAction
{
private:
    DataManager* xDataManager;
    G4int fHPGeEdepHCID;
    G4THitsMap<G4double> *GetHitsCollection(G4int hcID,
                                            const G4Event *event) const;
    G4double GetSum(G4THitsMap<G4double> *hitsMap) const;

public:
    EventAction(DataManager* dataMangaer);
    ~EventAction();

    virtual void BeginOfEventAction(const G4Event *anEvent);
    virtual void EndOfEventAction(const G4Event *anEvent);
};

#endif // EventAction_H
