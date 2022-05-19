#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4MultiFunctionalDetector.hh"

class DetectorMessenger;
class G4GlobalMagFieldMessenger;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class G4MultiFunctionalDetector;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction() override;

public:
	G4VPhysicalVolume* Construct() override;
	void UpdateGeometry();
	void SetCollimatorMove(G4double value);
    void SetDetectorMoveX(G4double value);
    void SetDetectorMoveY(G4double value);
    void SetDetectorMoveZ(G4double value);
//    G4MultiFunctionalDetector* HPGeDetector{};
//    G4VSensitiveDetector* HPGeDetector;
    DetectorMessenger *detectorMessenger;
    void Construct200L(G4LogicalVolume *motherLogicalVolume);
private:
    void init9Dectector();
    void initQSDectector();
    void DefineMaterials();
    G4VPhysicalVolume* ConstructWorld();
    void ConstructHPGeDetector(G4LogicalVolume *);
    void ConstructCollimator(G4LogicalVolume* motherLogicalVolume);
    void ConstructGammaBox(G4LogicalVolume* motherLogicalVolume);
    void ConstructSDandField() override;
    G4VPhysicalVolume *physiWorld{};
    G4LogicalVolume  *logic_box{}, *logicWorld{},*logActiveCrystal{};


	G4Material *Fe{}, *Cu{},*Sn{}, *Pb{}, *Air{},*GeCrystal{},
    *concrete{},*Water{}, *coverMat{}, *vacuum{}, *mylar{}, *shellAl{};


	//Pb Shield
	G4double Shield_Length{};
	G4double Shield_rMax{} ;
	G4double Shield_Fe_Thickness{} ;
	G4double Shield_Pb_Thickness{} ;
	G4double Shield_Cu_Thickness{};
	G4double Shield_Sn_Thickness{};
	//cover
	G4double coverThick{};

	//HPGe parameter
	//detector shell
	G4double shellRadius{};
	G4double shellLength{};
	G4double shellThick{} ;
	G4double endGap{};
	G4double detectorMove{};
	//CUP
	G4double CUPLength{};
	G4double CUPThick{} ;
	G4double CUPTopThick{} ;
	G4double CUPBottomThick{} ;
	G4double mylarThick{};

	//Ge crystal
	G4double crystalRadius{};
	G4double crystalHalfLength{};
	G4double crystalEndRadius{};
	G4double holeDepth{};
	G4double holeRadius{};
	G4double outerDeadLayerThick{};
	G4double innerDeadLayerThick{} ;

	//sample
	G4double shapeRad{} ;
	G4double shapeHalfDepth{} ;
	G4double sampleMove{};
	G4double collimatorMove{};

	G4bool fCheckOverlaps{true};
	G4bool flagPbShield{};
	G4bool flagCollimator{};
	G4bool flagSample{} ;

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
#endif
