#include "EventAction.h"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "DataManager.h"

EventAction::EventAction(DataManager *datamanager)
    : G4UserEventAction(),
      xDataManager(datamanager),
      fHPGeEdepHCID(-1)
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *anEvent)
{
}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{
    // Get the energy of primary particle
    G4double primary_energy = anEvent->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy();
    xDataManager->FillSourceData(primary_energy / MeV);
    // Get hist collections IDs
    G4double energyShield = 0.1 * keV;
    if (fHPGeEdepHCID < 0)
    {
        fHPGeEdepHCID = G4SDManager::GetSDMpointer()->GetCollectionID("HPGe/Edep");
    }
    G4double HPGeEdep = GetSum(GetHitsCollection(fHPGeEdepHCID, anEvent));
    if (HPGeEdep > energyShield)
    {
        xDataManager->FillSDData(HPGeEdep / MeV);
    }
}

G4double EventAction::GetSum(G4THitsMap<G4double> *hitsMap) const
{
    G4double sumValue = 0;
    std::map<G4int, G4double *>::iterator it;
    for (it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++)
    {
        sumValue += *(it->second);
    }
    return sumValue;
}

G4THitsMap<G4double> *EventAction::GetHitsCollection(G4int hcID,
                                                     const G4Event *event) const
{
    G4THitsMap<G4double> *hitsCollection = static_cast<G4THitsMap<G4double> *>(
        event->GetHCofThisEvent()->GetHC(hcID));

    if (!hitsCollection)
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("B4dEventAction::GetHitsCollection()",
                    "MyCode0003", FatalException, msg);
    }

    return hitsCollection;
}