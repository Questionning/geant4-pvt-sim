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
    G4Material* ironMat = nist->FindOrBuildMaterial("G4_Fe");

    // Define PVT (as we did before)
    G4Element* C = nist->FindOrBuildElement("C");
    G4Element* H = nist->FindOrBuildElement("H");
    G4Material* PVT = new G4Material("PVT", 1.023*g/cm3, 2);
    PVT->AddElement(C, 9);
    PVT->AddElement(H, 10);

    // 2. World (1m cube is fine)
    G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

    // 3. Shapes (Note: G4Box takes HALF-lengths)
    // Iron: 10x10x20 cm -> half-lengths 5x5x10 cm
    G4Box* solidIron = new G4Box("solidIron", 5*cm, 5*cm, 10*cm);
    // PVT: 10x10x5 cm -> half-lengths 5x5x2.5 cm
    G4Box* solidPVT = new G4Box("solidPVT", 5*cm, 5*cm, 2.5*cm);

    // 4. Logical Volumes
    G4LogicalVolume* logicIron = new G4LogicalVolume(solidIron, ironMat, "logicIron");
    G4LogicalVolume* logicPVT = new G4LogicalVolume(solidPVT, PVT, "logicPVT");

    // 5. Placements
    // Middle: Iron
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicIron, "physIron", logicWorld, false, 0, true);

    // Top: PVT
    new G4PVPlacement(0, G4ThreeVector(0,0,12.5*cm), logicPVT, "physPVT_Top", logicWorld, false, 0, true);

    // Bottom: PVT
    new G4PVPlacement(0, G4ThreeVector(0,0,-12.5*cm), logicPVT, "physPVT_Bottom", logicWorld, false, 1, true);

    return physWorld;
}