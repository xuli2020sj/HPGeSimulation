#include "DetectorConstruction.h"
//#include "SD.hh"

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

DetectorConstruction::DetectorConstruction()
	: G4VUserDetectorConstruction(), physiWorld(0), fCheckOverlaps(true)
{
		// Pb Shield
	Shield_Length = 630. * mm;
	Shield_rMax = 0.5 * 510. * mm;
	Shield_Fe_Thickness = 9.5 * mm;
	Shield_Pb_Thickness = 101. * mm;
	Shield_Cu_Thickness = 1.6 * mm;
	Shield_Sn_Thickness = 0.5 * mm;
	// cover
	coverThick = 3.0 * mm;
	// detector shell
	shellRadius = 0.5 * 76. * mm;
	shellLength = 120. * mm;
	shellThick = 1. * mm;
	endGap = 4.0 * mm;
	detectorMove = -0.5 * shellLength;
	// CUP
	CUPLength = 105. * mm;
	CUPThick = 0.8 * mm;
	CUPTopThick = 0.03 * mm;
	CUPBottomThick = 3. * mm;
	mylarThick = 0.03 * mm;
	// Ge crystal
	crystalRadius = 0.5 * 63. * mm;
	crystalHalfLength = 0.5 * 44.1 * mm;
	crystalEndRadius = 8. * mm;
	holeDepth = 27.8 * mm;
	holeRadius = 0.5 * 10.8 * mm;
	outerDeadLayerThick = 0.7 * mm;
	innerDeadLayerThick = 1.3 * um;
	// sample
	shapeRad = 0.564 * cm;
	shapeHalfDepth = 0.5 * cm;
	sampleMove = 90. * mm;
	collimatorMove = 30. * mm;

	DefineMaterials();
	detectorMessenger = new DetectorMessenger(this);


}

DetectorConstruction::~DetectorConstruction()
{
	delete detectorMessenger;
}

void DetectorConstruction::DefineMaterials() {
	G4NistManager *nistManager = G4NistManager::Instance();
	G4bool fromIsotopes = false;

	this->Fe = nistManager->FindOrBuildMaterial("G4_Fe", fromIsotopes);
	this->Cu = nistManager->FindOrBuildMaterial("G4_Cu", fromIsotopes);
	this->Pb = nistManager->FindOrBuildMaterial("G4_Pb", fromIsotopes);
	this->Sn = nistManager->FindOrBuildMaterial("G4_Sn", fromIsotopes);
	this->GeCrystal = nistManager->FindOrBuildMaterial("G4_Ge", fromIsotopes);
	this->Air = nistManager->FindOrBuildMaterial("G4_AIR");

	//G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	physiWorld = this->ConstructWorld();
	auto pLV = physiWorld->GetLogicalVolume();

	this->ConstructHPGeDetector(pLV);
	//this->ConstructGammaBox(pLV);

	ConstructSDandField();
	return physiWorld;
}

G4VPhysicalVolume *DetectorConstruction::ConstructWorld()
{

	G4double fWorldLength = 4 * m;
	G4double HalfWorldLength = 4 * m;

	G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
	// G4cout << "Computed tolerance = "
	// 	   << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance() / mm
	// 	   << " mm" << G4endl;

	G4VSolid *solidWorld = new G4Box("world", HalfWorldLength, HalfWorldLength, HalfWorldLength);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, Air, "LogicWorld", 0, 0, 0);
	G4VPhysicalVolume *phyWorld = new G4PVPlacement(0,				 // no rotation
													G4ThreeVector(), // at (0,0,0)
													logicWorld,		 // its logical volume
													"PhysiWorld",	 // its name
													0,				 // its mother  volume
													false,			 // no boolean operations
													0,				 // copy number
													true);
	return phyWorld;
}

void DetectorConstruction::ConstructGammaBox(G4LogicalVolume *motherLogicalVolume)
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
	G4VSolid *in_box = new G4Box("concrete_box", 2438. * mm, 1331. * mm, 1926. * mm);

	G4LogicalVolume *logic_box = new G4LogicalVolume(in_box, concrete, "logic_box");

	G4double pos_x = 0.0 * meter;
	G4double pos_y = 0.0 * meter;
	G4double pos_z = 0.0 * meter;

	G4VPhysicalVolume *boxPhys = new G4PVPlacement(0, // no rotation
													   G4ThreeVector(pos_x, pos_y, pos_z),
													   // translation position
													   logic_box, // its logical volume
													   "Tracker",  // its name
													   motherLogicalVolume,   // its mother (logical) volume
													   false,	   // no boolean operations
													   0);		   // its copy number

	G4VisAttributes *visAttCollimator = new G4VisAttributes(G4Colour(0.3, 0.6, 1.0, 0.7));
	visAttCollimator->G4VisAttributes::SetForceSolid(true);
	logic_box->SetVisAttributes(visAttCollimator);											   
}

void DetectorConstruction::ConstructHPGeDetector(G4LogicalVolume* motherLogicalVolume) {
		G4NistManager *nist = G4NistManager::Instance();
	G4Material *shellAl = nist->FindOrBuildMaterial("G4_Al");
	G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material *coverMat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
	G4Material *mylar = nist->FindOrBuildMaterial("G4_MYLAR");

	G4double sphi = 0. * deg;
	G4double dphi = 360. * deg;

	// Cover
	// G4VSolid *cover = new G4Tubs("cover",
	// 							 0. * mm,
	// 							 shellRadius,
	// 							 0.5 * coverThick,
	// 							 sphi,
	// 							 dphi);
	// G4LogicalVolume *logCover = new G4LogicalVolume(cover, coverMat, "logCover", 0, 0, 0);
	// new G4PVPlacement(0, G4ThreeVector(0., 0., detectorMove + 0.5 * shellLength + 0.5 * coverThick), logCover, "physiCover",
	// 				  motherLogicalVolume, false, 0, fCheckOverlaps);

	// detector
	G4VSolid *HPGe = new G4Tubs("HPGe",
								0. * mm,
								shellRadius,
								0.5 * shellLength,
								sphi,
								dphi);
	G4LogicalVolume *logHPGe = new G4LogicalVolume(HPGe, vacuum, "logHPGe", 0, 0, 0);
	new G4PVPlacement(0, G4ThreeVector(0., 0., detectorMove), logHPGe, "physiHPGe",
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
										  crystal3, tor1, 0, G4ThreeVector(0., 0., crystalHalfLength - crystalEndRadius));

	// Making the Active Crystal shap
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
												activeCrystal1, activeCrystal2, 0, G4ThreeVector(0., 0., -0.5 * (activeEndRadius)));
	G4VSolid *activeCrystal4 = new G4UnionSolid("cry4",
												activeCrystal3, activeTor1, 0, G4ThreeVector(0., 0., activeHalfLength - activeEndRadius));

	// making outer dead layer
	G4VSolid *outerDeadLayer = new G4SubtractionSolid("outerDeadLayer",
													  crystal4, activeCrystal4, 0, G4ThreeVector(0., 0., -0.5 * outerDeadLayerThick));

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
											innerDead1, innerDead2, 0, G4ThreeVector(0., 0., 0.5 * (holeDepth - holeRadius)));
	G4VSolid *innerDeadLayer = new G4SubtractionSolid("innerDeadLayer",
													  innerDead3, hole, 0, G4ThreeVector(0., 0., 0.));

	// Making final detector shape
	G4VSolid *activeCrystal = new G4SubtractionSolid("activeCrystal",
													 activeCrystal4, innerDead3, 0, G4ThreeVector(0., 0., -activeHalfLength + 0.5 * (holeDepth - holeRadius)));

	G4LogicalVolume *logOuterDeadLayer = new G4LogicalVolume(outerDeadLayer, GeCrystal, "logOuterDeadLayer", 0, 0, 0);
	G4LogicalVolume *logInnerDeadLayer = new G4LogicalVolume(innerDeadLayer, GeCrystal, "logInnerDeadLayer", 0, 0, 0);
	G4LogicalVolume *logActiveCrystal = new G4LogicalVolume(activeCrystal, GeCrystal, "logActiveCrystal", 0, 0, 0);

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

	new G4PVPlacement(0, G4ThreeVector(), logShell, "physiShell",
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
					  G4ThreeVector(0., 0., 0.5 * shellLength - activeHalfLength - shellThick - endGap - CUPTopThick - outerDeadLayerThick),
					  logActiveCrystal, "physiActiveCrystal",
					  logHPGe, false, 0, fCheckOverlaps);
	// new G4PVPlacement(0,
	// 				  G4ThreeVector(0., 0., 0.5 * (shellLength - holeDepth + holeRadius) - shellThick - endGap - CUPTopThick - (2. * crystalHalfLength - holeDepth + holeRadius)),
	// 				  logInnerDeadLayer, "physiInnerDeadLayer",
	// 				  logHPGe, false, 0, fCheckOverlaps);

	// Detector Visualization Attributes
	G4VisAttributes *HPGeVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.00));
	logHPGe->SetVisAttributes(HPGeVisAtt);

	G4VisAttributes *shellVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.00));
	logShell->SetVisAttributes(shellVisAtt);

	G4VisAttributes *CUPVisAtt = new G4VisAttributes(G4Colour(0.2, 1.0, 0.00));
	logCUP->SetVisAttributes(CUPVisAtt);

	G4VisAttributes *outerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9, 1.0, 0.0, 0.80));
	outerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
	logOuterDeadLayer->SetVisAttributes(outerDeadLayerVisAtt);

	G4VisAttributes *activeCrystalVisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.3, 0.20));
	activeCrystalVisAtt->G4VisAttributes::SetForceSolid(true);
	logActiveCrystal->SetVisAttributes(activeCrystalVisAtt);

	G4VisAttributes *innerDeadLayerVisAtt = new G4VisAttributes(G4Colour(0.9, 1.0, 0.0, 0.80));
	innerDeadLayerVisAtt->G4VisAttributes::SetForceSolid(true);
	logInnerDeadLayer->SetVisAttributes(innerDeadLayerVisAtt);

	G4bool detectorInvisible = 0;
	if (detectorInvisible)
	{
		logOuterDeadLayer->SetVisAttributes(G4VisAttributes::Invisible);
		logActiveCrystal->SetVisAttributes(G4VisAttributes::Invisible);
		logInnerDeadLayer->SetVisAttributes(G4VisAttributes::Invisible);
	}
	G4bool shellInvisible = 1;
	if (shellInvisible)
	{
		logHPGe->SetVisAttributes(G4VisAttributes::Invisible);
		logShell->SetVisAttributes(G4VisAttributes::Invisible);
		logCUP->SetVisAttributes(G4VisAttributes::Invisible);
	}
}

void DetectorConstruction::ConstructSDandField() {
	G4MultiFunctionalDetector* HPGeDetector = new G4MultiFunctionalDetector("HPGe");
	G4SDManager::GetSDMpointer()->AddNewDetector(HPGeDetector);

	G4VPrimitiveScorer *primitive = new G4PSEnergyDeposit("Edep");
	HPGeDetector->RegisterPrimitive(primitive);
	SetSensitiveDetector("logActiveCrystal", HPGeDetector);
}