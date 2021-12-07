#ifndef   PrimaryGeneratorAction_h
#define   PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
//class   DetectorConstruction;
//class G4ParticleGun;
class G4Event;
class G4GeneralParticleSource;

class   PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
      PrimaryGeneratorAction( );
      ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);
    G4GeneralParticleSource* GetParticleSource() {return theParticleSource;};

  private:
    //G4ParticleGun* particleGun;
    G4GeneralParticleSource* theParticleSource;
    //DetectorConstruction* myDetector;
};

#endif


