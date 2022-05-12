#include "PrimaryGeneratorAction.h"

#include "DetectorConstruction.h"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction()
{
#ifdef GUN
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("geantino");

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    particleGun->SetParticleEnergy(1.3325*MeV);
#else
    theParticleSource = new G4GeneralParticleSource();
#endif
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
#ifdef GUN
    delete particleGun;
#else
    delete theParticleSource;
#endif
}

// 每个event开始时被调用一次
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
#ifdef GUN
    particleGun->SetParticlePosition(G4ThreeVector(0 * cm, 0. * cm, 0. * cm));
    particleGun->SetParticleMomentumDirection(getGunDirection());
    particleGun->GeneratePrimaryVertex(anEvent);
    auto vertex = anEvent->GetPrimaryVertex(0);
    G4cout << "Gun position: " << vertex->GetPosition() << G4endl;
#else
    theParticleSource->GeneratePrimaryVertex(anEvent);
#endif
}

G4ThreeVector PrimaryGeneratorAction::getGunDirection() {
    return G4ThreeVector(n++, 1, 1);
}
