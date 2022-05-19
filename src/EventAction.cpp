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
#include "G4RunManager.hh"

std::once_flag flagInfo;

EventAction::EventAction(RunAction* RunAction, DataManager *datamanager)
    : G4UserEventAction(),
      xRunAction(RunAction),
      xDataManager(datamanager),
      fHPGeEdepHCID(-1) {
}

EventAction::~EventAction() {
}

void EventAction::BeginOfEventAction(const G4Event *anEvent) {
    G4int currRunID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();
    if (currRunID != runID) {
        auto vertex = anEvent->GetPrimaryVertex(0);
        currEnergy = vertex->GetPrimary(0)->GetTotalEnergy();
        runID = currRunID;
        xRunAction->setXPos(vertex->GetPosition().x());
        xRunAction->setYPos(vertex->GetPosition().y());
        xRunAction->setZPos(vertex->GetPosition().z());
        xRunAction->setEnergy(currEnergy);
    }
//    std::call_once(flagInfo, [this, &anEvent]() {
//        if (!xRunAction->IsMaster()) {
//            auto vertex = anEvent->GetPrimaryVertex(0);
//            xRunAction->setXPos(vertex->GetPosition().x());
//            xRunAction->setYPos(vertex->GetPosition().y());
//            xRunAction->setZPos(vertex->GetPosition().z());
//            xRunAction->setEnergy(vertex->GetPrimary(0)->GetTotalEnergy());
//        }
//    });
}



void EventAction::EndOfEventAction(const G4Event *anEvent)
{

    // xDataManager->FillSourceData(primary_energy / MeV);
    // G4double energyShield = 0.65 * MeV;


    if (fHPGeEdepHCID < 0)
    {
//        G4double primary_energy = anEvent->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy();
//        auto pos = anEvent->GetPrimaryVertex()->GetPosition();
        fHPGeEdepHCID = G4SDManager::GetSDMpointer()->GetCollectionID("HPGe/Edep");
//        xRunAction->setSEnergy(primary_energy);
//        xRunAction->setSPos(pos);
    }

    // G4double HPGeEdep = *(GetHitsCollection(fHPGeEdepHCID, anEvent)->GetMap()->begin()->second);

    G4double HPGeEdep = GetSum(GetHitsCollection(fHPGeEdepHCID, anEvent));

    double a = 0;
    double b = 0.002;
    double c = 0;

    double FWHM = a+b*pow(currEnergy+c*pow(currEnergy,2),0.5);
//    G4cout << "low : " << currEnergy - 1.5 * FWHM << "high :" << currEnergy + 1.5 * FWHM << G4endl;
    if (HPGeEdep > currEnergy - 1.5 * FWHM && HPGeEdep < currEnergy + 1.5 * FWHM) {
        xRunAction->AddValidCount();
    }
}

inline G4double EventAction::GetSum(G4THitsMap<G4double> *hitsMap) const
{
    G4double sumValue = 0;
    // std::map<G4int, G4double *>::iterator it;
    // if (hitsMap->GetSize() > 1) G4cerr << "size: " << hitsMap->GetSize() << G4endl;

    for (auto it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
        sumValue += *(it->second);
    }
    return sumValue;
}

inline G4THitsMap<G4double> *EventAction::GetHitsCollection(G4int hcID, const G4Event *event) const
{
    G4THitsMap<G4double> *hitsCollection = dynamic_cast<G4THitsMap<G4double> *>(
        event->GetHCofThisEvent()->GetHC(hcID));
    if (!hitsCollection) {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("B4dEventAction::GetHitsCollection()",
                    "MyCode0003", FatalException, msg);
    }
    return hitsCollection;
}

G4double EventAction::getNumericEfficiency() const {
    return numericEfficiency;
}

void EventAction::setNumericEfficiency(G4double numericEfficiency) {
    EventAction::numericEfficiency = numericEfficiency;
}

void EventAction::addLenMap(const std::string& volume, G4double len) {
    if (lenMap.find(volume) == lenMap.end()) {
        lenMap[volume] = len;
    } else {
        lenMap[volume] += len;
    }
}

void EventAction::calculate() {
    G4double sumLen = 0;
    for (const auto& n : lenMap) {
        sumLen += n.second;
    }
    lenMap.clear();
    G4cout << sumLen << G4endl;
}
