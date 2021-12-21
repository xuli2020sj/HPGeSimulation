#include "PhysicsListMessenger.h"

#include "PhysicsList.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"


PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys)
:G4UImessenger(),
 fPhysicsList(pPhys),fPhysDir(0),fGammaCutCmd(0),fElectCutCmd(0),
 fProtoCutCmd(0),fAllCutCmd(0),fListCmd(0),fPackageListCmd(0)
{ 
  fPhysDir = new G4UIdirectory("/HPGe_simulation/phys/");
  fPhysDir->SetGuidance("physics list commands");

  fGammaCutCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/phys/setGCut",this);  
  fGammaCutCmd->SetGuidance("Set gamma cut.");
  fGammaCutCmd->SetParameterName("Gcut",false);
  fGammaCutCmd->SetUnitCategory("Length");
  fGammaCutCmd->SetRange("Gcut>0.0");
  fGammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fElectCutCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/phys/setECut",this);  
  fElectCutCmd->SetGuidance("Set electron cut.");
  fElectCutCmd->SetParameterName("Ecut",false);
  fElectCutCmd->SetUnitCategory("Length");
  fElectCutCmd->SetRange("Ecut>0.0");
  fElectCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fProtoCutCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/phys/setPCut",this);  
  fProtoCutCmd->SetGuidance("Set positron cut.");
  fProtoCutCmd->SetParameterName("Pcut",false);
  fProtoCutCmd->SetUnitCategory("Length");
  fProtoCutCmd->SetRange("Pcut>0.0");
  fProtoCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  fAllCutCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/phys/setCuts",this);  
  fAllCutCmd->SetGuidance("Set cut for all.");
  fAllCutCmd->SetParameterName("cut",false);
  fAllCutCmd->SetUnitCategory("Length");
  fAllCutCmd->SetRange("cut>0.0");
  fAllCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fListCmd = new G4UIcmdWithAString("/HPGe_simulation/phys/addPhysics",this);  
  fListCmd->SetGuidance("Add modula physics list.");
  fListCmd->SetParameterName("PList",false);
  fListCmd->AvailableForStates(G4State_PreInit);

  fPackageListCmd = new G4UIcmdWithAString("/HPGe_simulation/phys/addPackage",this);
  fPackageListCmd->SetGuidance("Add physics package.");
  fPackageListCmd->SetParameterName("package",false);
  fPackageListCmd->AvailableForStates(G4State_PreInit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fGammaCutCmd;
  delete fElectCutCmd;
  delete fProtoCutCmd;
  delete fAllCutCmd;
  delete fListCmd;
  delete fPhysDir;
delete fPackageListCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
  if( command == fGammaCutCmd )
   { fPhysicsList->SetCutForGamma(fGammaCutCmd->GetNewDoubleValue(newValue));}
     
  if( command == fElectCutCmd )
   { fPhysicsList->SetCutForElectron(fElectCutCmd->GetNewDoubleValue(newValue));}
     
  if( command == fProtoCutCmd )
   { fPhysicsList->SetCutForPositron(fProtoCutCmd->GetNewDoubleValue(newValue));}

  if( command == fAllCutCmd )
    {
      G4double cut = fAllCutCmd->GetNewDoubleValue(newValue);
      fPhysicsList->SetCutForGamma(cut);
      fPhysicsList->SetCutForElectron(cut);
      fPhysicsList->SetCutForPositron(cut);
    }
    
  if( command == fListCmd )
   { fPhysicsList->AddPhysicsList(newValue);}

if( command == fPackageListCmd )
   { fPhysicsList->AddPackage(newValue);}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
