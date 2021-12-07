#include "SteppingAction.h"
//包含对应的头文件
#include "G4Step.hh"  
//包含Geant4中输出信息至程序外的G4cout与G4endl所对应的头文件

#include "EventAction.h"  
//包含EventAction的头文件

#include "G4Track.hh" 
//包含Geant4中Track的头文件，将在后续使用

#include "G4StepPoint.hh" 
//包含Geant4中处理每个相互作用点的头文件


SteppingAction::SteppingAction(EventAction *eventAction) : G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step *)
{

}