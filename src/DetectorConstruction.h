#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

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
	void UpdateGeometry();

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
	void SetMylarThick (G4double value);
	void SetCrystalRadius (G4double value);
	void SetCrystalHalfLength (G4double value);
	void SetCrystalEndRadius (G4double value);
	void SetHoleDepth(G4double value);
	void SetHoleRadius(G4double value);
	void SetOuterDeadLayerThick(G4double value);
	void SetInnerDeadLayerThick(G4double value);
	void SetSampleMove(G4double value);
	void SetCollimatorMove(G4double value);

	void SetPbShield(G4double value);
	void SetCollimator(G4double value);
	void SetSample(G4double value);

    void SetDetectorMoveX(G4double value);
    void SetDetectorMoveY(G4double value);
    void SetDetectorMoveZ(G4double value);



private:
	void DefineMaterials();
	G4VPhysicalVolume* ConstructWorld();
	void ConstructHPGeDetector(G4LogicalVolume *);
	void ConstructCollimator(G4LogicalVolume* motherLogicalVolume);
	void ConstructGammaBox(G4LogicalVolume* motherLogicalVolume);
	void ConstructSurfaceSource(G4LogicalVolume* motherLogicalVolume);
	void Construct200L(G4LogicalVolume* motherLogicalVolume);
	void ConstructQSHPGeDetector(G4LogicalVolume *motherLogicalVolume);

	void initQSDectector();
	void init9Dectector();

	virtual void ConstructSDandField() override;
private:
	G4VPhysicalVolume *physiWorld;
	DetectorMessenger *detectorMessenger;

	G4Material* Fe;
	G4Material* Cu;
	G4Material* Sn;
	G4Material* Pb;
	G4Material* Air;
	G4Material* GeCrystal, *concrete;
	G4Material* Water, *coverMat, *vacuum, *mylar, *shellAl;

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
	G4bool flagSample ;

    // box
    G4int numOfX = 5;
    G4int numOfY = 2;
    G4int numOfZ = 3;

    G4double xLength = 2438. * mm;
    G4double yLength = 1926. * mm;
    G4double zLength = 1331. * mm;

    //move
    G4ThreeVector moveDetector = {0, 0, 0};

//    G4double pos_x = xCellLength / 2;
//    G4double pos_y = yCellLength / 2 + 500;
//    G4double pos_z = zCellLength / 2;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
