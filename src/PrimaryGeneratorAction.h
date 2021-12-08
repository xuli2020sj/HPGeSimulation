#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

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

public:
	void GeneratePrimaries(G4Event *);
	//G4GeneralParticleSource *GetParticleSource() { return particleGun; };
	const G4ParticleGun* GetParticleGun() const { return particleGun; }

private:
	G4ParticleGun* particleGun;
	// G4GeneralParticleSource* theParticleSource;
	// DetectorConstruction* myDetector;
};

#endif
