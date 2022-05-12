#if !defined(RunAction_h)
#define RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "DataManager.h"
#include "G4GenericAnalysisManager.hh"
#include "G4Timer.hh"
#include "EventAction.h"

class RunAction : public G4UserRunAction
{
private:
    G4Accumulable<G4double> validCount = 0;
    G4Accumulable<G4double> energy = 0;
    G4Accumulable<G4double> xPos = 0;
    G4Accumulable<G4double> yPos = 0;
    G4Accumulable<G4double> zPos = 0;
    DataManager* data_manager_;
    G4double averageNumericEfficiency = -1;
    G4Timer timer;
    G4double sEnergy = 0;
    G4ThreeVector sPos = {0, 0, 0};
    std::vector<G4double> numericEfficiency;
public:
    const G4Accumulable<G4double> &getXPos() const;
    void setXPos(const G4Accumulable<G4double> &xPos);
    const G4Accumulable<G4double> &getYPos() const;
    void setYPos(const G4Accumulable<G4double> &yPos);
    const G4Accumulable<G4double> &getZPos() const;
    void setZPos(const G4Accumulable<G4double> &zPos);
    const G4Accumulable<G4double> &getEnergy() const;
    void setEnergy(const G4Accumulable<G4double> &energy);
    G4double getNumericEfficiency() const;
    void setNumericEfficiency(G4double numericEfficiency);


public:
    void setSPos(const G4ThreeVector &sPos);
    void setSEnergy(G4double sEnergy);
    void pushEfficiency(G4double efficiency);

    RunAction(DataManager* DataManager);
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void AddValidCount();
};

#endif // RunAction_h
