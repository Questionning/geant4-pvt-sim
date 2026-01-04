#ifndef CONSTRUCTION_HH // the ifndef is used to avoid pasting the same package into my main file twice
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    // This is the specific function Geant4 looks for to build the world
    virtual G4VPhysicalVolume* Construct(); // Note: virtual is used to indicate overriding
                                            // G4VPhysicalVolume* means the function is returning the pointer to the physical volume instead of the volume
};

#endif 