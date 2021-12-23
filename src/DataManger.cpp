#include "DataManager.h"
#include "G4SystemOfUnits.hh"


DataManager::DataManager(/* args */)	:fileName("HPGe_data")
	 ,factoryOn(false)
{	// histograms
	for (G4int k=0; k<MaxHisto; k++) {
		fHistId[k] = 0;
		fHistPt[k] = 0;    
	}
	// ntuple
	for (G4int k=0; k<MaxNtCol; k++) {
		fNtColId[k] = 0;
	}  

	Book();
}

DataManager::~DataManager()
{	delete G4AnalysisManager::Instance();
}



void DataManager::Book()
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);
	//analysisManager->SetActivation(true);   //enable inactivation of histograms
	G4cout << "Using"<< analysisManager->GetFileType() << G4endl;
	analysisManager->SetFileName(fileName);

	// Create directories 
	analysisManager->SetHistoDirectoryName("histo");
	analysisManager->SetNtupleDirectoryName("ntuple");

	// create selected histograms
	//
	analysisManager->SetFirstHistoId(1);
	analysisManager->SetFirstNtupleId(1);
	fHistId[0] = analysisManager->CreateH1("source","Gamma source (MeV)",
			8192, 0., 2.0*MeV);
	fHistPt[0] = analysisManager->GetH1(fHistId[0]);

	fHistId[1] = analysisManager->CreateH1("HPGe","Gamma HPGe (MeV)",
			8192, 0., 2.0*MeV);
	fHistPt[1] = analysisManager->GetH1(fHistId[1]);

	// Creating ntuple ID=1
	//
	analysisManager->CreateNtuple("101", "source");
	fNtColId[0] = analysisManager->CreateNtupleDColumn("Edep_source");
	analysisManager->FinishNtuple();
	// Creating ntuple ID=2
	analysisManager->CreateNtuple("102", "HPGe");
	fNtColId[1] = analysisManager->CreateNtupleDColumn("Edep_HPGe");
	analysisManager->FinishNtuple();

}

void DataManager::OpenFile()
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	fileName = 	analysisManager->GetFileName();
	G4bool fileOpen = analysisManager->OpenFile();
	if (!fileOpen) {
		G4cout << "\n---> HistoManager::OpenFile(): cannot open " << fileName 
			<< G4endl;
		return;
	}

	factoryOn = true;       
	G4cout << "\n----> Histogram Tree is opened in " << fileName << G4endl;
}


void DataManager::Save()
{
	if (factoryOn) {
		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
		analysisManager->Write();
		analysisManager->CloseFile();  
		G4cout << "\n----> Histogram Tree is saved in " << fileName << G4endl;
		factoryOn = false;
	}                    
}

void DataManager::Normalize(G4int ih, G4double fac)
{
	if (ih >= MaxHisto) {
		G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
			<< "  fac= " << fac << G4endl;
		return;
	}
}

void DataManager::FillHisto(G4int ih, G4double e, G4double weight)
{
	if (ih > MaxHisto) {
		G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
			<< "does note xist; xbin= " << e << " w= " << weight << G4endl;
		return;
	}

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	if (analysisManager) analysisManager->FillH1(ih, e, weight);
}

void DataManager::FillNtuple(int ih ,int NtColID,G4double energy)
{                
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleDColumn(ih,fNtColId[NtColID], energy);
	analysisManager->AddNtupleRow(ih);  
}  

void DataManager::FillSourceData(G4double energy)
{
	this -> FillHisto(1,energy);
}

void DataManager::FillSDData(G4double energy)
{
	this -> FillHisto(2,energy);
}