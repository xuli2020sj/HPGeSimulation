#include "PrimaryGeneratorAction.h"

#include "DetectorConstruction.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction()
{
	theParticleSource = new G4GeneralParticleSource();
	/*
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  // default particle

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("proton");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun->SetParticleEnergy(3.0*GeV);
  */
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete theParticleSource;
	// delete particleGun;
}

// 每个event开始时被调用一次
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	/*
  //G4double position = -0.5*(myDetector->GetWorldFullLength());
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));

  particleGun->GeneratePrimaryVertex(anEvent);
  */
	theParticleSource->GeneratePrimaryVertex(anEvent);
}
