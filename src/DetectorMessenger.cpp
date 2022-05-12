
#include "DetectorMessenger.h"

#include "DetectorConstruction.h"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction *Det)
	: G4UImessenger(),
	  fDetector(Det), fDetDir(0), fOutDeadLayerThicknessCmd(0), fFlagPbShieldCmd(0)
{

	G4bool broadcast = false;
	fDetDir = new G4UIdirectory("/HPGe_simulation/det/", broadcast);
	fDetDir->SetGuidance("detector construction commands");

	fOutDeadLayerThicknessCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setOutDeadLayerThickness", this);
	fOutDeadLayerThicknessCmd->SetGuidance("Set out dead layer thickness of HPGe .");
	fOutDeadLayerThicknessCmd->SetParameterName("outDeadLayerThickness", false);
	fOutDeadLayerThicknessCmd->SetDefaultUnit("mm");
	fOutDeadLayerThicknessCmd->SetUnitCategory("Length");
	fOutDeadLayerThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fSampleMoveCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setSampleMove", this);
	fSampleMoveCmd->SetGuidance("Set sample move .");
	fSampleMoveCmd->SetParameterName("sampleMove", false);
	fSampleMoveCmd->SetDefaultUnit("mm");
	fSampleMoveCmd->SetUnitCategory("Length");
	fSampleMoveCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fCollimatorMoveCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setCollimatorMove", this);
	fCollimatorMoveCmd->SetGuidance("Set Collimatormove .");
	fCollimatorMoveCmd->SetParameterName("CollimatorMove", false);
	fCollimatorMoveCmd->SetDefaultUnit("mm");
	fCollimatorMoveCmd->SetUnitCategory("Length");
	fCollimatorMoveCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fFlagPbShieldCmd = new G4UIcmdWithABool("/HPGe_simulation/det/setPbShield", this);
	fFlagPbShieldCmd->SetGuidance("add Pb Shield .");
	fFlagPbShieldCmd->SetParameterName("flagPbShield", false);
	fFlagPbShieldCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fFlagSampleCmd = new G4UIcmdWithABool("/HPGe_simulat0ion/det/setSample", this);
	fFlagSampleCmd->SetGuidance("add Sample .");
	fFlagSampleCmd->SetParameterName("flagSample", false);
	fFlagSampleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

//	fFlagCollimatorCmd = new G4UIcmdWithABool("/HPGe_simulation/det/setCollimator", this);
//	fFlagCollimatorCmd->SetGuidance("add Collimator .");
//	fFlagCollimatorCmd->SetParameterName("flagCollimator", false);
//	fFlagCollimatorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	fUpdateCmd = new G4UIcmdWithoutParameter("/HPGe_simulation/det/update", this);
	fUpdateCmd->SetGuidance("Update geometry.");
	fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
	fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
	fUpdateCmd->AvailableForStates(G4State_Idle,G4State_PreInit);

    fDetectorMoveXCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setDetectorMoveX", this);
    fDetectorMoveXCmd->SetGuidance("Set DetectorMoveX .");
    fDetectorMoveXCmd->SetParameterName("DetectorMoveX", false);
    fDetectorMoveXCmd->SetDefaultUnit("mm");
    fDetectorMoveXCmd->SetUnitCategory("Length");
    fDetectorMoveXCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    fDetectorMoveYCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setDetectorMoveY", this);
    fDetectorMoveYCmd->SetGuidance("Set DetectorMoveY .");
    fDetectorMoveYCmd->SetParameterName("DetectorMoveY", false);
    fDetectorMoveYCmd->SetDefaultUnit("mm");
    fDetectorMoveYCmd->SetUnitCategory("Length");
    fDetectorMoveYCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    fDetectorMoveZCmd = new G4UIcmdWithADoubleAndUnit("/HPGe_simulation/det/setDetectorMoveZ", this);
    fDetectorMoveZCmd->SetGuidance("Set DetectorMoveZ .");
    fDetectorMoveZCmd->SetParameterName("DetectorMoveZ", false);
    fDetectorMoveZCmd->SetDefaultUnit("mm");
    fDetectorMoveZCmd->SetUnitCategory("Length");
    fDetectorMoveZCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}


DetectorMessenger::~DetectorMessenger()
{
	delete fOutDeadLayerThicknessCmd;
	delete fSampleMoveCmd;
	delete fCollimatorMoveCmd;
	delete fDetDir;
	delete fFlagPbShieldCmd;
	delete fFlagCollimatorCmd;
	delete fFlagSampleCmd;
	delete fUpdateCmd;
    delete fDetectorMoveXCmd;
    delete fDetectorMoveYCmd;
    delete fDetectorMoveZCmd;
}


void DetectorMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
	// if( command == fOutDeadLayerThicknessCmd )
	// { 
	// 	fDetector->SetOutDeadLayerThickness(fOutDeadLayerThicknessCmd->GetNewDoubleValue(newValue));
	// }

	// if( command == fSampleMoveCmd )
	// { fDetector->SetSampleMove(fSampleMoveCmd ->GetNewDoubleValue(newValue));}

	if( command == fCollimatorMoveCmd)
	{ fDetector->SetCollimatorMove(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));}

    if( command == fDetectorMoveXCmd) {
        fDetector->SetDetectorMoveX(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));
    }

    if( command == fDetectorMoveYCmd)
    { fDetector->SetDetectorMoveY(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));}

    if( command == fDetectorMoveZCmd)
    { fDetector->SetDetectorMoveZ(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));}

	// if(command == fFlagPbShieldCmd)
	// {
	// 	fDetector->SetPbShield(fFlagPbShieldCmd->GetNewBoolValue(newValue));
	// }

	// if(command == fFlagCollimatorCmd)
	// {
	// 	fDetector->SetCollimator(fFlagCollimatorCmd->GetNewBoolValue(newValue));
	// }

	// if(command == fFlagSampleCmd )
	// {
	// 	fDetector->SetSample(fFlagSampleCmd ->GetNewBoolValue(newValue));
	// }
	if(command == fUpdateCmd )
	{
		fDetector->UpdateGeometry();
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
