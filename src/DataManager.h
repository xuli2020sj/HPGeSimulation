/**
 * @file DataManager.h
 * @author Xu Li (xuli2020sj@gmail.com)
 * @brief
 * @date 2021-12-21
 *
 */
#if !defined(DATAMANAGER_H)
#define DATAMANAGER_H

#include "globals.hh"
#include "G4ThreeVector.hh"
//#include "g4root.hh"
#include <fstream>
#include <chrono>
#include <ctime>

const G4int MaxHisto = 2;
const G4int MaxNtCol = 2;

/**
 * @brief analyze data
 *
 */
class DataManager
{
public:
    DataManager();
    ~DataManager();

    void Book();
    void Save();

    void OpenFile();
    void FillHisto(G4int id, G4double e, G4double weight = 1.0);
    void FillNtuple(int ih, int NtColID, G4double energy);

    void FillSourceData(G4double energy);
    void FillSDData(G4double energy);

    void Normalize(G4int id, G4double fac);
    void PrintStatistic();

    G4double getValidCount() const;
    void setdetectionEffeciency(G4double detectionEffeciency);

private:
    G4String fileName;
    G4int runID;
    G4double realTime;
public:
    G4double getRealTime() const;

    void setRealTime(G4double realTime);

public:
    G4int getRunId() const;

    void setRunId(G4int runId);

private:
    G4bool factoryOn;
    std::ofstream ofstream;

    G4double validCount = 0;
    G4int fHistId[MaxHisto];
//    G4H1 *fHistPt[MaxHisto];
    G4int fNtColId[MaxNtCol];

    G4double detectionEffeciency = -1;
    G4double count = 0;
    G4double xPos = 0;
public:
    G4double getCount() const;
    void setCount(G4double count);
    G4double getEnergy() const;
    void setEnergy(G4double energy);

private:
    G4ThreeVector sPos = {0, 0 ,0};
public:
    void setSPos(G4ThreeVector &sPos);

private:
    G4double energy = 0;
};

#endif // DATAMANAGER_H
