#include "SteppingAction.h"
#include "G4Step.hh"

#include "EventAction.h"

#include "G4Track.hh"
#include "G4StepPoint.hh" 
//包含Geant4中处理每个相互作用点的头文件


SteppingAction::SteppingAction(EventAction *eventAction) : G4UserSteppingAction()
{
//    xEventAction = eventAction;
}

SteppingAction::~SteppingAction()
{

}

void SteppingAction::UserSteppingAction(const G4Step * step)
{
//    G4Track* xtrack = step->GetTrack();
//    xtrack->GetTotalEnergy();
//    xtrack->GetPosition();
//    xtrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
//    auto xVol = xtrack->GetVolume();
//    xEventAction->addLenMap(xVol->GetName(), step->GetStepLength());
//
//    G4cout << "Volume: " << xVol->GetName()
//        << " length: " << step->GetStepLength()<< G4endl;
//    G4cout << "Volume " << xVol->GetLogicalVolume()->GetMaterial() << G4endl;
}