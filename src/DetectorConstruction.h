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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

public:
	G4VPhysicalVolume *Construct();

	virtual void ConstructSDandField();
	void SetPbShield(G4bool value);
	void SetCollimator(G4bool value);
	void SetSample(G4bool value);

	void SetOutDeadLayerThickness(double value);
	void SetCoverThick(G4double value);
	void SetShellRadius(G4double value);
	void SetShellLength(G4double value);
	void SetShellThick(G4double value);
	void SetEndGap(G4double value);
	void SetCUPLength(G4double value);
	void SetCUPThick(G4double value);
	void SetCUPTopThick(G4double value);
	void SetCUPBottomThick(G4double value);
	void SetMylarThick(G4double value);
	void SetCrystalRadius(G4double value);
	void SetCrystalHalfLength(G4double value);
	void SetCrystalEndRadius(G4double value);
	void SetHoleDepth(G4double value);
	void SetHoleRadius(G4double value);
	void SetOuterDeadLayerThick(G4double value);
	void SetInnerDeadLayerThick(G4double value);
	void UpdateGeometry();
	void SetSampleMove(G4double value);
	void SetCollimatorMove(G4double value);

private:
	void DefineMaterials();
	G4VPhysicalVolume *ConstructWorld();
	G4VPhysicalVolume *ConstructPbShield(G4LogicalVolume *);
	void ConstructHPGeDetector(G4LogicalVolume *);
	void ConstructSample(G4LogicalVolume *motherLogicalVolume);
	void ConstructCollimator(G4LogicalVolume *motherLogicalVolume);

private:
	// data members
	//
	G4VPhysicalVolume *physiWorld; // pointer to the physical envelope
	G4UserLimits *stepLimit;	   // pointer to user step limits
	DetectorMessenger *detectorMessenger;
	G4Material *Shield_Fe;
	G4Material *Shield_Cu;
	G4Material *Shield_Sn;
	G4Material *Shield_Pb;
	G4Material *Shield_Air;
	G4Material *GeCrystal;
	G4Material *sampleMaterial;

	// Pb Shield
	G4double Shield_Length;
	G4double Shield_rMax;
	G4double Shield_Fe_Thickness;
	G4double Shield_Pb_Thickness;
	G4double Shield_Cu_Thickness;
	G4double Shield_Sn_Thickness;
	// cover
	G4double coverThick;

	// HPGe parameter
	// detector shell
	G4double shellRadius;
	G4double shellLength;
	G4double shellThick;
	G4double endGap;
	G4double detectorMove;
	// CUP
	G4double CUPLength;
	G4double CUPThick;
	G4double CUPTopThick;
	G4double CUPBottomThick;
	G4double mylarThick;

	// Ge crystal
	G4double crystalRadius;
	G4double crystalHalfLength;
	G4double crystalEndRadius;
	G4double holeDepth;
	G4double holeRadius;
	G4double outerDeadLayerThick;
	G4double innerDeadLayerThick;

	// sample
	G4double shapeRad;
	G4double shapeHalfDepth;
	G4double sampleMove;
	G4double collimatorMove;

	G4bool fCheckOverlaps;
	G4bool flagPbShield;
	G4bool flagCollimator;
	G4bool flagSample;

	static G4ThreadLocal G4GlobalMagFieldMessenger *fMagFieldMessenger;
	// magnetic field messenger
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
