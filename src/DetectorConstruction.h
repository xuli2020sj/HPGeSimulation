#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorMessenger;
class G4GlobalMagFieldMessenger;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

public:
	G4VPhysicalVolume*Construct();


private:
	void DefineMaterials();
	G4VPhysicalVolume* ConstructWorld();
	void ConstructHPGeDetector(G4LogicalVolume *);
	void ConstructGammaBox(G4LogicalVolume* motherLogicalVolume);

private:
	G4VPhysicalVolume *physiWorld; // pointer to the physical envelope
	DetectorMessenger *detectorMessenger;

	G4Material* Fe;
	G4Material* Cu;
	G4Material* Sn;
	G4Material* Pb;
	G4Material* Air;
	G4Material* GeCrystal;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
