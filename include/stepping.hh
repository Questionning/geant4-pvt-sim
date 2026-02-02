#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh" // This is the magic header for CSV/ROOT output

class MySteppingAction : public G4UserSteppingAction {
public:
    MySteppingAction();
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*); // This method is called at each step of the simulation
                                                    // virtual keyword indicates that this method overrides a base class method
};

#endif