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
#include "g4root.hh"

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

private:
    G4String fileName;
    G4bool factoryOn;

    G4int fHistId[MaxHisto];
    G4H1 *fHistPt[MaxHisto];
    G4int fNtColId[MaxNtCol];
};

#endif // DATAMANAGER_H
