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
	: G4VUserDetectorConstruction(), physiWorld(0)
{
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

	//this->ConstructHPGeDetector(pLV);
	this->ConstructGammaBox(pLV);

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
