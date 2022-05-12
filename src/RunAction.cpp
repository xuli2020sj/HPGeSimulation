#include <G4RunManager.hh>
#include "RunAction.h"

RunAction::RunAction(DataManager* DataManager):G4UserRunAction(), data_manager_(DataManager)
{
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->RegisterAccumulable(validCount);
    accumulableManager->RegisterAccumulable(energy);
    accumulableManager->RegisterAccumulable(xPos);
    accumulableManager->RegisterAccumulable(yPos);
    accumulableManager->RegisterAccumulable(zPos);
}

RunAction::~RunAction()
{
    G4cout << "Run finished" << G4endl;
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    if (isMaster) {
        timer.Start();
    }
}

void RunAction::EndOfRunAction(const G4Run *run)
{
	G4int numOfEvents = run->GetNumberOfEvent();
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Merge();
    G4double validCountSum = validCount.GetValue();
    G4double energySum = energy.GetValue();

    if (isMaster) {
        timer.Stop();
        G4int threadNum = 16;
        sPos.set(xPos.GetValue() / threadNum, yPos.GetValue()/ threadNum,zPos.GetValue()/ threadNum);
        data_manager_->setRealTime(timer.GetRealElapsed());
        data_manager_->setCount(run->GetNumberOfEvent());
        data_manager_->setdetectionEffeciency(validCountSum  / numOfEvents / 2);
        data_manager_->setRunId(run->GetRunID());
        data_manager_->setSPos(sPos);
        data_manager_->setEnergy(energySum  / threadNum);
        data_manager_->PrintStatistic();
        G4cout << "Detection efficiency : " << validCountSum  / numOfEvents / 2 << G4endl;
    }

    validCount.Reset();
    energy.Reset();
    xPos.Reset();
    yPos.Reset();
    zPos.Reset();
}

void RunAction::AddValidCount() {
	validCount += 1;
}

void RunAction::setSPos(const G4ThreeVector &sPos) {
    RunAction::sPos = sPos;
}

void RunAction::setSEnergy(G4double sEnergy) {
    RunAction::sEnergy = sEnergy;
}

G4double RunAction::getNumericEfficiency() const {
    return averageNumericEfficiency;
}

void RunAction::setNumericEfficiency(G4double numericEfficiency) {
    RunAction::averageNumericEfficiency = numericEfficiency;
}

void RunAction::pushEfficiency(G4double efficiency) {
    if (efficiency > 0) numericEfficiency.push_back(efficiency);
}

const G4Accumulable<G4double> &RunAction::getEnergy() const {
    return energy;
}

void RunAction::setEnergy(const G4Accumulable<G4double> &energy) {
    RunAction::energy = energy;
}

const G4Accumulable<G4double> &RunAction::getXPos() const {
    return xPos;
}

void RunAction::setXPos(const G4Accumulable<G4double> &xPos) {
    RunAction::xPos = xPos;
}

const G4Accumulable<G4double> &RunAction::getYPos() const {
    return yPos;
}

void RunAction::setYPos(const G4Accumulable<G4double> &yPos) {
    RunAction::yPos = yPos;
}

const G4Accumulable<G4double> &RunAction::getZPos() const {
    return zPos;
}

void RunAction::setZPos(const G4Accumulable<G4double> &zPos) {
    RunAction::zPos = zPos;
}
