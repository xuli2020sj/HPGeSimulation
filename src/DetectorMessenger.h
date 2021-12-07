#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter; 
class DetectorMessenger: public G4UImessenger
{
	public:

		DetectorMessenger(DetectorConstruction* );
		~DetectorMessenger();

		virtual void SetNewValue(G4UIcommand*, G4String);

	private:

		DetectorConstruction*      fDetector;

		G4UIdirectory*             fDetDir;
		G4UIcmdWithADoubleAndUnit* fOutDeadLayerThicknessCmd;
		G4UIcmdWithADoubleAndUnit* fSampleMoveCmd;
		G4UIcmdWithADoubleAndUnit* fCollimatorMoveCmd;
		G4UIcmdWithABool*  fFlagPbShieldCmd;
		G4UIcmdWithABool* fFlagCollimatorCmd;
		G4UIcmdWithABool* fFlagSampleCmd ;
		G4UIcmdWithoutParameter *fUpdateCmd;
};

#endif

