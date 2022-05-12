#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;


class PhysicsListMessenger: public G4UImessenger
{
  public:
    PhysicsListMessenger(PhysicsList* );
   ~PhysicsListMessenger();
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    PhysicsList*               fPhysicsList;
    G4UIdirectory*             fPhysDir;
    G4UIcmdWithADoubleAndUnit* fGammaCutCmd;
    G4UIcmdWithADoubleAndUnit* fElectCutCmd;
    G4UIcmdWithADoubleAndUnit* fProtoCutCmd;    
    G4UIcmdWithADoubleAndUnit* fAllCutCmd;
    G4UIcmdWithAString*        fListCmd;
    G4UIcmdWithAString* fPackageListCmd;
};

#endif

