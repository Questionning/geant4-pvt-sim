#include "construction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction() {}
MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    
    // 1. Materials
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Define PVT (Polyvinyl Toluene) - C9H10
    G4Element* C = nist->FindOrBuildElement("C");
    G4Element* H = nist->FindOrBuildElement("H");
    G4Material* PVT = new G4Material("PVT", 1.023*g/cm3, 2);
    PVT->AddElement(C, 9);
    PVT->AddElement(H, 10);

    // 2. World
    G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

    // 3. PVT Block (The Detector)
    // A 10cm x 10cm x 10cm block
    G4Box* solidPVT = new G4Box("solidPVT", 5*cm, 5*cm, 5*cm);
    G4LogicalVolume* logicPVT = new G4LogicalVolume(solidPVT, PVT, "logicPVT");

    // Place it in the center of the world
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicPVT, "physPVT", logicWorld, false, 0, true);

    return physWorld;
}