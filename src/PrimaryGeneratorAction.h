#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

//#define GUN 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"

// class   DetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4GeneralParticleSource;
class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction();
    G4ThreeVector getGunDirection();
    int n = 0;

public:
	void GeneratePrimaries(G4Event *);
//	G4GeneralParticleSource *GetParticleSource() { return particleGun; };
//	const G4ParticleGun* GetParticleGun() const { return particleGun; }

private:
#ifdef GUN
	G4ParticleGun* particleGun;
#else
	G4GeneralParticleSource* theParticleSource;
#endif
	// DetectorConstruction* myDetector;
};

#endif
