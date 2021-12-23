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

	virtual void ConstructSDandField() override;

private:
	G4VPhysicalVolume *physiWorld; // pointer to the physical envelope
	DetectorMessenger *detectorMessenger;

	G4Material* Fe;
	G4Material* Cu;
	G4Material* Sn;
	G4Material* Pb;
	G4Material* Air;
	G4Material* GeCrystal;

		//Pb Shield
		G4double Shield_Length;
		G4double Shield_rMax ;
		G4double Shield_Fe_Thickness ;
		G4double Shield_Pb_Thickness ;
		G4double Shield_Cu_Thickness;
		G4double Shield_Sn_Thickness;
		//cover
		G4double coverThick;

		//HPGe parameter
		//detector shell
		G4double shellRadius;
		G4double shellLength;
		G4double shellThick ;
		G4double endGap;
		G4double detectorMove;
		//CUP
		G4double CUPLength;
		G4double CUPThick ;
		G4double CUPTopThick ;
		G4double CUPBottomThick ;
		G4double mylarThick;

		//Ge crystal
		G4double crystalRadius;
		G4double crystalHalfLength;
		G4double crystalEndRadius;
		G4double holeDepth;
		G4double holeRadius;
		G4double outerDeadLayerThick;
		G4double innerDeadLayerThick ;

		//sample
		G4double shapeRad ;
		G4double shapeHalfDepth ;
		G4double sampleMove;
		G4double collimatorMove;

		G4bool fCheckOverlaps;
		G4bool flagPbShield;
		G4bool flagCollimator;
		G4bool	flagSample ;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
