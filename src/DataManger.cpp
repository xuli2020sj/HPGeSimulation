#include "DataManager.h"
#include "G4SystemOfUnits.hh"


DataManager::DataManager()	:fileName("HPGe_data")
	 ,factoryOn(false)
{	// histograms
//	for (G4int k=0; k<MaxHisto; k++) {
//		fHistId[k] = 0;
//		fHistPt[k] = 0;
//	}
//	// ntuple
//	for (G4int k=0; k<MaxNtCol; k++) {
//		fNtColId[k] = 0;
//	}
	ofstream.open("/home/x/code/HPGeSimulation/doc/log.txt", std::ios::app);
	// Book();
}

DataManager::~DataManager()
{	
//	delete G4AnalysisManager::Instance();
	ofstream.close();
}



//void DataManager::Book()
//{
//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//	analysisManager->SetVerboseLevel(1);
//	//analysisManager->SetActivation(true);   //enable inactivation of histograms
//	G4cout << "Using"<< analysisManager->GetFileType() << G4endl;
//	analysisManager->SetFileName(fileName);
//
//	// Create directories
//	analysisManager->SetHistoDirectoryName("histo");
//	analysisManager->SetNtupleDirectoryName("ntuple");
//
//	// create selected histograms
//	//
//	analysisManager->SetFirstHistoId(1);
//	analysisManager->SetFirstNtupleId(1);
//	fHistId[0] = analysisManager->CreateH1("source","Gamma source (MeV)",
//			8192, 0., 2.0*MeV);
//	fHistPt[0] = analysisManager->GetH1(fHistId[0]);
//
//	fHistId[1] = analysisManager->CreateH1("HPGe","Gamma HPGe (MeV)",
//			8192, 0., 2.0*MeV);
//	fHistPt[1] = analysisManager->GetH1(fHistId[1]);
//
//	// Creating ntuple ID=1
//	//
//	analysisManager->CreateNtuple("101", "source");
//	fNtColId[0] = analysisManager->CreateNtupleDColumn("Edep_source");
//	analysisManager->FinishNtuple();
//	// Creating ntuple ID=2
//	analysisManager->CreateNtuple("102", "HPGe");
//	fNtColId[1] = analysisManager->CreateNtupleDColumn("Edep_HPGe");
//	analysisManager->FinishNtuple();
//}
//
//void DataManager::OpenFile()
//{
//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//	fileName = 	analysisManager->GetFileName();
//	G4bool fileOpen = analysisManager->OpenFile();
//	if (!fileOpen) {
//		G4cout << "\n---> HistoManager::OpenFile(): cannot open " << fileName
//			<< G4endl;
//		return;
//	}
//
//	factoryOn = true;
//	G4cout << "\n----> Histogram Tree is opened in " << fileName << G4endl;
//}


//void DataManager::Save()
//{
//	if (factoryOn) {
//		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//		analysisManager->Write();
//		analysisManager->CloseFile();
//		G4cout << "\n----> Histogram Tree is saved in " << fileName << G4endl;
//		factoryOn = false;
//	}
//}

//void DataManager::Normalize(G4int ih, G4double fac)
//{
//	if (ih >= MaxHisto) {
//		G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
//			<< "  fac= " << fac << G4endl;
//		return;
//	}
//}
//
//void DataManager::FillHisto(G4int ih, G4double e, G4double weight)
//{
//	if (ih > MaxHisto) {
//		G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
//			<< "does note xist; xbin= " << e << " w= " << weight << G4endl;
//		return;
//	}
//
//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//	if (analysisManager) analysisManager->FillH1(ih, e, weight);
//}
//
//void DataManager::FillNtuple(int ih ,int NtColID,G4double energy)
//{
//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//	analysisManager->FillNtupleDColumn(ih,fNtColId[NtColID], energy);
//	analysisManager->AddNtupleRow(ih);
//}
//
//void DataManager::FillSourceData(G4double energy)
//{
//	this -> FillHisto(1,energy);
//}
//
//void DataManager::FillSDData(G4double energy)
//{
//	if (energy > 1.3288 && energy < 1.3362) {
//		validCount += 1;
//	}
//
//	// this -> FillHisto(2,energy);
//}

G4double DataManager::getValidCount() const {
	return validCount;
}

void DataManager::PrintStatistic() {
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ofstream << "### Run " << this->runID << "\t"
			 << std::put_time(std::localtime(&t), "%Y-%m-%d %X")
             << "\t"
             << "### "
             << "Run Time: " << this->getRealTime()
             << G4endl;
	ofstream << "Total count: " << this->count << G4endl;
    ofstream << "Source position : " << this->sPos << G4endl;
    ofstream << "Source energy: " << this->energy << G4endl;
	ofstream << "Detection efficiency: " << detectionEffeciency << G4endl << G4endl;
}

void DataManager::setdetectionEffeciency(G4double detectionEffeciencyv) {
	this->detectionEffeciency = detectionEffeciencyv;
}

G4double DataManager::getCount() const {
    return count;
}

void DataManager::setCount(G4double count) {
    DataManager::count = count;
}

G4double DataManager::getEnergy() const {
    return energy;
}

void DataManager::setEnergy(G4double energy) {
    DataManager::energy = energy;
}

G4int DataManager::getRunId() const {
	return runID;
}

void DataManager::setRunId(G4int runId) {
	runID = runId;
}

void DataManager::setSPos(G4ThreeVector &sPos) {
	DataManager::sPos = sPos;
}

G4double DataManager::getRealTime() const {
    return realTime;
}

void DataManager::setRealTime(G4double realTime) {
    DataManager::realTime = realTime;
}


//void DataManager::setSPos(G4ThreeVector &sPos) {
//    DataManager::sPos = sPos;
//}

