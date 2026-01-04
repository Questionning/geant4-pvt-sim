#include "construction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh" // Handles the math for a box
#include "G4LogicalVolume.hh" // Combines shape and material
#include "G4PVPlacement.hh" // Allows me to place the volume at a specific coordinate
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction() {} // Scope resolution operator (::) to indicate this function belongs to the class
MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    // 1. Get access to a database of materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // 2. Define the SHAPE (Solid)
    // A box with half-lengths: 0.5m x 0.5m x 0.5m (Total 1m cube)
    G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

    // 3. Define the PROPERTIES (Logical Volume)
    // Combines the shape with a material
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // 4. Define the PLACEMENT (Physical Volume)
    // Actually puts it in the simulation universe
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0,                  // No rotation
        G4ThreeVector(0,0,0), // At (0,0,0)
        logicWorld,         // Its logical volume
        "physWorld",        // Its name
        0,                  // Its mother volume (0 because it's the world)
        false,              // No boolean operations
        0,                  // Copy number
        true                // Check for overlaps
    );

    return physWorld;
}