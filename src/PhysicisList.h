
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsListMessenger;
class G4VPhysicsConstructor;

class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList();
   ~PhysicsList();
   
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    
    void AddPhysicsList(const G4String& name);
    void AddPackage(const G4String& name);
    virtual void SetCuts();
    
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);
      
  private:
    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;
    G4double fCurrentDefaultCut;
    
    G4VPhysicsConstructor*  fEmPhysicsList;
    G4String                fEmName;
    
    PhysicsListMessenger*   fMessenger;         
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

