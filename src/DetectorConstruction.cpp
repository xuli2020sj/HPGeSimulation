#include "DetectorConstruction.h"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
//#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4NistManager.hh"
//#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "DetectorMessenger.h"

#include <cstdlib>
#include <G4RunManager.hh>

DetectorConstruction::DetectorConstruction()
        : G4VUserDetectorConstruction(){
//	initQSDectector();
    G4double fWorldLength = 5 * m;
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
    detectorMessenger = new DetectorMessenger(this);
}

void DetectorConstruction::initQSDectector() {
    coverThick = 3.0 * mm;
    // detector shell
    shellRadius = 0.5 * 76. * mm;
    shellLength = 120. * mm;
    shellThick = 1.5 * mm;                 //I=L=1 mm Al
    endGap = 5.0 * mm;                    //G=4 mm
    detectorMove = -0.5 * shellLength;
    // CUP
    CUPLength = 105. * mm;                //F=105 mm diameter
    CUPThick = 0.8 * mm;                  //K=0.8 mm diameter
    CUPTopThick = 0.03 * mm;              //H=0.03 mm diameter
    CUPBottomThick = 3. * mm;             //not to scale
    mylarThick = 0.03 * mm;               //H=0.03 mm diameter
    // Ge crystal

    crystalRadius = 0.5 * 60.9 * mm;       //A=70 mm crystal diameter
    crystalHalfLength = 0.5 * 51.8 * mm;  //B=84.9 mm crystal length
    crystalEndRadius = 8. * mm;           //J=8 mm nominal radius
    holeDepth = 38.2 * mm;                //D=70.3mm hole depth
    holeRadius = 0.5 * 8.7 * mm;         //C=9.3mm diameter
    outerDeadLayerThick = 0.7 * mm;       //M=0.7mm diameter
    innerDeadLayerThick = 0.3 * um;       //N=0.3um
    // sample
    shapeRad = 0.564 * cm;
    shapeHalfDepth = 0.5 * cm;
    sampleMove = 90. * mm;
    collimatorMove = 30. * mm;
}

void DetectorConstruction::init9Dectector() {
    // Pb Shield
    // Shield_Length = 630. * mm;
    // Shield_rMax = 0.5 * 510. * mm;
    // Shield_Fe_Thickness = 9.5 * mm;
    // Shield_Pb_Thickness = 101. * mm;
    // Shield_Cu_Thickness = 1.6 * mm;
    // Shield_Sn_Thickness = 0.5 * mm;
    // cover
    coverThick = 3.0 * mm;
    // detector shell
    shellRadius = 0.5 * 76. * mm;
    shellLength = 120. * mm;
    shellThick = 1. * mm;                 //I=L=1 mm Al
    endGap = 4.0 * mm;                    //G=4 mm
    detectorMove = -0.5 * shellLength;
    // CUP
    CUPLength = 105. * mm;                //F=105 mm diameter
    CUPThick = 0.8 * mm;                  //K=0.8 mm diameter
    CUPTopThick = 0.03 * mm;              //H=0.03 mm diameter
    CUPBottomThick = 3. * mm;             //not to scale
    mylarThick = 0.03 * mm;               //H=0.03 mm diameter
    // Ge crystal

    crystalRadius = 0.5 * 63. * mm;       //A=70 mm crystal diameter
    crystalHalfLength = 0.5 * 44.1 * mm;  //B=84.9 mm crystal length
    crystalEndRadius = 8. * mm;           //J=8 mm nominal radius
    holeDepth = 27.8 * mm;                //D=70.3mm hole depth
    holeRadius = 0.5 * 10.8 * mm;         //C=9.3mm diameter
    outerDeadLayerThick = 0.7 * mm;       //M=0.7mm diameter
    innerDeadLayerThick = 1.3 * um;       //N=0.3um
    // sample
    shapeRad = 0.564 * cm;
    shapeHalfDepth = 0.5 * cm;
    sampleMove = 90. * mm;
    collimatorMove = 30. * mm;
}

DetectorConstruction::~DetectorConstruction() {
    delete detectorMessenger;
}

//void DetectorConstruction::Construct200L(G4LogicalVolume *motherLogicalVolume) {
//    G4ThreeVector posDrum_200L_matrix = G4ThreeVector(0 * cm, 74 * cm, 0 * cm); //如果是底部为0，则设置z为42.5cm
//    G4double Drum_matrix_200L_pRMin = (0 / 2) * mm;
//    G4double Drum_matrix_200L_pRMax = (560 / 2) * mm;
//    G4double Drum_matrix_200L_pDz = (850 / 2) * mm; // 850
//    G4double Drum_matrix_200L_pSPhi = 0 * deg;
//    G4double Drum_matrix_200L_pDPhi = 360 * deg;
//    G4VSolid
//    G4Tubs *solidDrum_matrix_200L = new G4Tubs("200L_matrix_Drum", Drum_matrix_200L_pRMin, Drum_matrix_200L_pRMax,
//                                               Drum_matrix_200L_pDz,
//
//                                               Drum_matrix_200L_pSPhi, Drum_matrix_200L_pDPhi);
//
//    // LogicalVolume
//
//    G4LogicalVolume *logicDrum_matrix_200L = new G4LogicalVolume(solidDrum_matrix_200L, // its solid
//                                                                 Water,               // its material
//                                                                 "200L_matrix_Drum");   // its name
//
//
//    // PhysicalVolume
//    new G4PVPlacement(0,                     // no rotation,0
//                      posDrum_200L_matrix,     // at position
//                      logicDrum_matrix_200L, // its logical volume
//                      "200L_matrix_Drum",     // its name
//                      motherLogicalVolume,     // its mother  volume
//                      false,                 // no boolean operation
//                      0,                     // copy number
//                      true);                 // overlaps checking
//
//    G4VisAttributes *transblue = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
//    //  G4VisAttributes *transblue = new G4VisAttributes(G4Colour( 0.909804, 0.584314, 0.1176471, 0.2));
//    transblue->SetForceSolid(true);
//    logicDrum_matrix_200L->SetVisAttributes(transblue); // logical的颜色
//}

void DetectorConstruction::DefineMaterials() {
    G4NistManager *nistManager = G4NistManager::Instance();
    G4bool fromIsotopes = false;
    this->Fe = nistManager->FindOrBuildMaterial("G4_Fe", fromIsotopes);
    this->Cu = nistManager->FindOrBuildMaterial("G4_Cu", fromIsotopes);
    this->Pb = nistManager->FindOrBuildMaterial("G4_Pb", fromIsotopes);
    this->Sn = nistManager->FindOrBuildMaterial("G4_Sn", fromIsotopes);
    this->GeCrystal = nistManager->FindOrBuildMaterial("G4_Ge", fromIsotopes);
    this->Air = nistManager->FindOrBuildMaterial("G4_AIR");
    this->Water = nistManager->FindOrBuildMaterial("G4_WATER");
    shellAl = nistManager->FindOrBuildMaterial("G4_Al");
    vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");
    coverMat = nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
    mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
    concrete = nistManager->FindOrBuildMaterial("G4_CONCRETE");
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4LogicalVolumeStore::Clean();
    G4SolidStore::Clean();
    G4PhysicalVolumeStore::Clean();


    init9Dectector();
    DefineMaterials();

    physiWorld = this->ConstructWorld();
    auto pLV = physiWorld->GetLogicalVolume();
    this->DefineMaterials();
    this->ConstructHPGeDetector(pLV);
    this->ConstructGammaBox(pLV);
    this->ConstructCollimator(pLV);
//    this->Construct200L(pLV);
//    ConstructSDandField();
    return physiWorld;
}


G4VPhysicalVolume *DetectorConstruction::ConstructWorld() {
    G4double HalfWorldLength = 3 * m;
    G4VSolid *solidWorld = new G4Box("world", HalfWorldLength, HalfWorldLength, HalfWorldLength);
    logicWorld = new G4LogicalVolume(solidWorld, Air, "LogicWorld", 0, 0, 0);
    G4VPhysicalVolume *phyWorld = new G4PVPlacement(0,                 // no rotation
                                                    G4ThreeVector(), // at (0,0,0)
                                                    logicWorld,         // its logical volume
                                                    "PhysiWorld",     // its name
                                                    0,                 // its mother  volume
                                                    false,             // no boolean operations
                                                    0,                 // copy number
                                                    true);

    return phyWorld;
}

void DetectorConstruction::ConstructGammaBox(G4LogicalVolume *motherLogicalVolume) {
    G4double xCellLength = xLength / numOfX;
    G4double yCellLength = yLength / numOfY;
    G4double zCellLength = zLength / numOfZ;
    G4double pos_x = xCellLength / 2;
    G4double pos_y = yCellLength / 2 + 500;
    G4double pos_z = zCellLength / 2;

    G4VSolid *in_box = new G4Box("concrete_box", xCellLength / 2, yCellLength / 2, zCellLength / 2);
    logic_box = new G4LogicalVolume(in_box, concrete, "logic_box");
    for (G4int i = 0; i < numOfX; i++) {
        for (G4int j = 0; j < numOfY; j++) {
            for (G4int k = 0; k < numOfZ; k++) {
                G4VPhysicalVolume *boxPhys = new G4PVPlacement(0,
                                                               G4ThreeVector(pos_x + i * xCellLength,
                                                                             pos_y + j * yCellLength,
                                                                             pos_z + k * zCellLength),
                                                               logic_box,
                                                               "cell",
                                                               motherLogicalVolume,
                                                               false,
                                                               i * 100 + j * 10 + k,
                                                               true);
            }
        }
    }

//	 G4VPhysicalVolume *boxPhys = new G4PVPlacement(0, // no rotation
//	 											G4ThreeVector(pos_x, pos_y, pos_z), // translation position
//	 											logic_box, // its logical volume
//	 											"box",  // its name
//	 											motherLogicalVolume,   // its mother (logical) volume
//	 											false,	   // no boolean operations
//	 											0);		   // its copy number

    auto *visAttBox = new G4VisAttributes(G4Colour(0.7, 0.6, 1.0, 0.3));
    visAttBox->G4VisAttributes::SetForceSolid(true);
    visAttBox->G4VisAttributes::SetForceAuxEdgeVisible();
    logic_box->SetVisAttributes(visAttBox);
}


void DetectorConstruction::ConstructHPGeDetector(G4LogicalVolume *motherLogicalVolume) {
    // MOVE DETECTOR!!!
    G4double revise = -(endGap + crystalHalfLength * 2);
    auto mv = G4ThreeVector(0. * mm, revise * mm, 0 * mm) + moveDetector;
    G4double sphi = 0. * deg;
    G4double dphi = 360. * deg;
    // Cover
    G4VSolid *cover = new G4Tubs("cover",
                                 0. * mm,
                                 shellRadius,
                                 0.5 * coverThick,
                                 sphi,
                                 dphi);
    G4LogicalVolume *logCover = new G4LogicalVolume(cover, coverMat, "logCover", 0, 0, 0);
    // new G4PVPlacement(0, G4ThreeVector(0., 0., detectorMove + 0.5 * shellLength + 0.5 * coverThick), logCover, "physiCover",
    // 				  motherLogicalVolume, false, 0, fCheckOverlaps);
    // detector
    G4VSolid *HPGe = new G4Tubs("HPGe",
                                0. * mm,
                                shellRadius,
                                0.5 * shellLength,
                                sphi,
                                dphi);

    auto *roVec = new G4RotationMatrix(0, 4.7123, 0);
    auto *logHPGe = new G4LogicalVolume(HPGe, vacuum, "logHPGe", 0, 0, 0);

    new G4PVPlacement(roVec, mv,
                      logHPGe, "physiHPGe",
                      motherLogicalVolume, false, 0, fCheckOverlaps);

    // Crystal
    G4VSolid *crystal1 = new G4Tubs("cyl1",
                                    0. * mm,
                                    crystalRadius - crystalEndRadius,
                                    crystalHalfLength,
                                    sphi,
                                    dphi);
    G4VSolid *crystal2 = new G4Tubs("cyl2",
                                    0. * mm,
                                    crystalRadius,
                                    crystalHalfLength - 0.5 * crystalEndRadius,
                                    sphi,
                                    dphi);
    G4VSolid *tor1 = new G4Torus("tor1",
                                 0. * mm,
                                 crystalEndRadius,
                                 crystalRadius - crystalEndRadius,
                                 sphi,
                                 dphi);
    G4VSolid *crystal3 = new G4UnionSolid("cry3",
                                          crystal1, crystal2, 0, G4ThreeVector(0., 0., -0.5 * (crystalEndRadius)));
    G4VSolid *crystal4 = new G4UnionSolid("cry4",
                                          crystal3, tor1, 0,
                                          G4ThreeVector(0., 0., crystalHalfLength - crystalEndRadius));

    // Making the Active Crystal shape
    G4double activeRadius = crystalRadius - outerDeadLayerThick;
    G4double activeHalfLength = crystalHalfLength - 0.5 * outerDeadLayerThick;
    G4double activeEndRadius = crystalEndRadius - outerDeadLayerThick;
    G4VSolid *activeCrystal1 = new G4Tubs("acyl1",
                                          0. * mm,
                                          activeRadius - activeEndRadius,
                                          activeHalfLength,
                                          sphi,
                                          dphi);
    G4VSolid *activeCrystal2 = new G4Tubs("acyl2",
                                          0. * mm,
                                          activeRadius,
                                          activeHalfLength - 0.5 * activeEndRadius,
                                          sphi,
                                          dphi);
    G4VSolid *activeTor1 = new G4Torus("activeTor1",
                                       0. * mm,
                                       activeEndRadius,
                                       activeRadius - activeEndRadius,
                                       sphi,
                                       dphi);
    G4VSolid *activeCrystal3 = new G4UnionSolid("cry3",
                                                activeCrystal1, activeCrystal2, 0,
                                                G4ThreeVector(0., 0., -0.5 * (activeEndRadius)));
    G4VSolid *activeCrystal4 = new G4UnionSolid("cry4",
                                                activeCrystal3, activeTor1, 0,
                                                G4ThreeVector(0., 0., activeHalfLength - activeEndRadius));

    // making outer dead layer
    G4VSolid *outerDeadLayer = new G4SubtractionSolid("outerDeadLayer",
                                                      crystal4, activeCrystal4, 0,
                                                      G4ThreeVector(0., 0., -0.5 * outerDeadLayerThick));

    // making the hole
    G4VSolid *hole1 = new G4Tubs("hole1",
                                 0. * mm,
                                 holeRadius,
                                 0.5 * (holeDepth - holeRadius),
                                 sphi,
                                 dphi);
    G4VSolid *hole2 = new G4Orb("hole2", holeRadius);
    G4VSolid *hole = new G4UnionSolid("hole",
                                      hole1, hole2, 0, G4ThreeVector(0., 0., 0.5 * (holeDepth - holeRadius)));

    // Making the inner dead layer
    G4VSolid *innerDead1 = new G4Tubs("innerDead1",
                                      0. * mm,
                                      holeRadius + innerDeadLayerThick,
                                      0.5 * (holeDepth - holeRadius),
                                      sphi,
                                      dphi);
    G4VSolid *innerDead2 = new G4Orb("innerDead2", holeRadius + innerDeadLayerThick);
    G4VSolid *innerDead3 = new G4UnionSolid("innerDead3",
                                            innerDead1, innerDead2, 0,
                                            G4ThreeVector(0., 0., 0.5 * (holeDepth - holeRadius)));
    G4VSolid *innerDeadLayer = new G4SubtractionSolid("innerDeadLayer",
                                                      innerDead3, hole, 0, G4ThreeVector(0., 0., 0.));

    // Making final detector shape
    G4VSolid *activeCrystal = new G4SubtractionSolid("activeCrystal",
                                                     activeCrystal4, innerDead3, 0, G4ThreeVector(0., 0.,
                                                                                                  -activeHalfLength +
                                                                                                  0.5 * (holeDepth -
                                                                                                         holeRadius)));

    G4LogicalVolume *logOuterDeadLayer = new G4LogicalVolume(outerDeadLayer, GeCrystal, "logOuterDeadLayer", 0, 0, 0);
    G4LogicalVolume *logInnerDeadLayer = new G4LogicalVolume(innerDeadLayer, GeCrystal, "logInnerDeadLayer", 0, 0, 0);
    logActiveCrystal = new G4LogicalVolume(activeCrystal, GeCrystal, "logActiveCrystal", 0, 0, 0);

    // mylar
    G4VSolid *mylarLayer = new G4Tubs("mylarLayer",
                                      0. * mm,
                                      CUPThick + crystalRadius,
                                      0.5 * mylarThick,
                                      sphi,
                                      dphi);
    G4LogicalVolume *logMylar = new G4LogicalVolume(mylarLayer, mylar, "logMylar", 0, 0, 0);
    // CUP
    G4VSolid *CUP1 = new G4Tubs("CUP1",
                                0. * mm,
                                CUPThick + crystalRadius,
                                0.5 * CUPLength,
                                sphi,
                                dphi);
    G4VSolid *CUP2 = new G4Tubs("CUP2",
                                0. * mm,
                                crystalRadius,
                                0.5 * (CUPLength - CUPTopThick - CUPBottomThick),
                                sphi,
                                dphi);
    G4VSolid *CUP = new G4SubtractionSolid("CUP",
                                           CUP1, CUP2, 0, G4ThreeVector(0., 0., 0.5 * (CUPBottomThick - CUPTopThick)));
    G4LogicalVolume *logCUP = new G4LogicalVolume(CUP, shellAl, "logCUP", 0, 0, 0);
    // detector shell
    G4VSolid *shell1 = new G4Tubs("shell1",
                                  0. * mm,
                                  shellRadius,
                                  0.5 * shellLength,
                                  sphi,
                                  dphi);
    G4VSolid *shell2 = new G4Tubs("shell2",
                                  0. * mm,
                                  shellRadius - shellThick,
                                  0.5 * shellLength - shellThick,
                                  sphi,
                                  dphi);
    G4VSolid *shell = new G4SubtractionSolid("shell",
                                             shell1, shell2, 0, G4ThreeVector(0., 0., 0.0));
    G4LogicalVolume *logShell = new G4LogicalVolume(shell, shellAl, "logShell", 0, 0, 0);

    new G4PVPlacement(0,
                      G4ThreeVector(), logShell, "physiShell",
                      logHPGe, false, 0, fCheckOverlaps);

    new G4PVPlacement(0,
                      G4ThreeVector(0., 0., 0.5 * (shellLength + mylarThick) - shellThick - endGap),
                      logMylar, "physiMylarLayer",
                      logHPGe, false, 0, fCheckOverlaps);
    new G4PVPlacement(0,
                      G4ThreeVector(0., 0., 0.5 * (shellLength - CUPLength) - shellThick - endGap),
                      logCUP, "physiCUP",
                      logHPGe, false, 0, fCheckOverlaps);
    new G4PVPlacement(0,
                      G4ThreeVector(0., 0., 0.5 * shellLength - crystalHalfLength - shellThick - endGap - CUPTopThick),
                      logOuterDeadLayer, "physiOuterDeadLayer",
                      logHPGe, false, 0, fCheckOverlaps);
    new G4PVPlacement(0,
                      G4ThreeVector(0., 0., 0.5 * shellLength - activeHalfLength - shellThick - endGap - CUPTopThick -
                                            outerDeadLayerThick),
                      logActiveCrystal, "physiActiveCrystal",
                      logHPGe, false, 0, fCheckOverlaps);
    // new G4PVPlacement(0,
    // 				  G4ThreeVector(0., 0., 0.5 * (shellLength - holeDepth + holeRadius) - shellThick - endGap - CUPTopThick - (2. * crystalHalfLength - holeDepth + holeRadius)),
    // 				  logInnerDeadLayer, "physiInnerDeadLayer",
    // 				  logHPGe, false, 0, fCheckOverlaps);

    // Detector Visualization Attributes
    auto *HPGeVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.00));
    logHPGe->SetVisAttributes(HPGeVisAtt);

    auto *shellVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.00));
    logShell->SetVisAttributes(shellVisAtt);

    auto *CUPVisAtt = new G4VisAttributes(G4Colour(0.2, 1.0, 0.00));
    logCUP->SetVisAttributes(CUPVisAtt);

    auto *outerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9, 1.0, 0.0, 0.80));
    outerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
    logOuterDeadLayer->SetVisAttributes(outerDeadLayerVisAtt);

    auto *activeCrystalVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.3, 0.20));
    activeCrystalVisAtt->G4VisAttributes::SetForceSolid(true);
    logActiveCrystal->SetVisAttributes(activeCrystalVisAtt);

    G4VisAttributes *innerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9, 1.0, 0.0, 0.80));
    innerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
    logInnerDeadLayer->SetVisAttributes(innerDeadLayerVisAtt);

//	G4bool detectorInvisible = 0;
//	if (detectorInvisible)
//	{
//		logOuterDeadLayer->SetVisAttributes(G4VisAttributes::Invisible);
//		logActiveCrystal->SetVisAttributes(G4VisAttributes::Invisible);
//		logInnerDeadLayer->SetVisAttributes(G4VisAttributes::Invisible);
//	}
//	G4bool shellInvisible = 1;
//	if (shellInvisible)
//	{
//		logHPGe->SetVisAttributes(G4VisAttributes::Invisible);
//		logShell->SetVisAttributes(G4VisAttributes::Invisible);
//		logCUP->SetVisAttributes(G4VisAttributes::Invisible);
//	}
}

void DetectorConstruction::ConstructCollimator(G4LogicalVolume *motherLogicalVolume) {
    G4double collimatorHLength = 50. * mm;
    G4double outerRadius = 75. * mm;
    G4double holeRadiusMax = 50. * mm;

    G4double holeWidth = 300. / 2 * mm;
    G4double sHoleDepth = 600. / 2 * mm;
    G4double holeLenghth = 300. / 2 * mm;


    G4VSolid *collimator1
            = new G4Tubs("collimator1", holeRadiusMax, outerRadius, collimatorHLength,
                         180. * deg, 360. * deg);
    G4VSolid *collimator2
            = new G4Tubs("collimator1", 0. * cm, holeRadiusMax, collimatorHLength + 10,
                         0. * deg, 360. * deg);
//    G4VSolid *collimator = new G4SubtractionSolid("collimator", collimator1, collimator2,0,G4ThreeVector(0., 0., 0.));

    G4VSolid *innerBox = new G4Box("innerShell", holeWidth, sHoleDepth, holeLenghth);
    G4VSolid *outerBox = new G4Box("outerShell", holeWidth + 50. * mm, sHoleDepth, holeLenghth + 50. * mm);
    G4VSolid *collimator3 = new G4SubtractionSolid("coll_box", outerBox, innerBox, 0, G4ThreeVector(0, -50 * mm, 0));
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateX(90 * deg);

    G4VSolid *collimator = new G4UnionSolid("coll", collimator3, collimator1, rot,
                                            G4ThreeVector(0, sHoleDepth + collimatorHLength / 2 + 50, 0));
    collimator = new G4SubtractionSolid("final_coll", collimator, collimator2, rot, G4ThreeVector(0, sHoleDepth, 0));
    //    G4VSolid *


//	G4VSolid * collimator2
//		= new G4Cons("collimator2", 0.*mm,holeRadiusMin,0. *mm,holeRadiusMax , holeHalfLength ,
//				0. *deg,360. *deg);
//	G4RotationMatrix* yRot = new G4RotationMatrix();
//	yRot ->rotateY(180. *deg);
//	G4VSolid *collimator3 = new G4UnionSolid("collimator3 ",
//			collimator2 ,collimator2 ,yRot,G4ThreeVector(0., 0., -2.0 *holeHalfLength ));
//	G4VSolid *collimator = new G4SubtractionSolid("collimator",
//			collimator1, collimator3,0,G4ThreeVector(0., 0., 0.5 *collimatorHalfLength ));

    G4LogicalVolume *logCollimator
            = new G4LogicalVolume(collimator, Pb, "collimator_log", 0, 0, 0);

    //	G4VPhysicalVolume * physiWorldPbShield =
    new G4PVPlacement(0, G4ThreeVector(0., -sHoleDepth, 0) + moveDetector, logCollimator, "collimator_phys",
                      motherLogicalVolume, false, 0, fCheckOverlaps);

    auto *visAttCollimator = new G4VisAttributes(G4Colour(0.3, 0.6, 1.0, 1));
    visAttCollimator->G4VisAttributes::SetForceSolid(true);
    logCollimator->SetVisAttributes(visAttCollimator);
}

void DetectorConstruction::ConstructSDandField() {
//    if (HPGeDetector != nullptr) return;
    G4cerr << "fuckSD";
    auto HPGeDetector = new G4MultiFunctionalDetector("HPGe");
    G4SDManager::GetSDMpointer()->AddNewDetector(HPGeDetector);
    G4VPrimitiveScorer *primitive = new G4PSEnergyDeposit("Edep");
    HPGeDetector->RegisterPrimitive(primitive);
    SetSensitiveDetector("logActiveCrystal", HPGeDetector);
}

void DetectorConstruction::UpdateGeometry() {
    G4RunManager::GetRunManager()->DefineWorldVolume(this->Construct());
}

void DetectorConstruction::SetCollimatorMove(G4double value) {
    collimatorMove = value;
}

void DetectorConstruction::SetDetectorMoveX(G4double value) {
    moveDetector += G4ThreeVector(value, 0, 0);

}

void DetectorConstruction::SetDetectorMoveY(G4double value) {
    moveDetector += G4ThreeVector(0, value, 0);
}

void DetectorConstruction::SetDetectorMoveZ(G4double value) {
    moveDetector += G4ThreeVector(0, 0, value);
}

