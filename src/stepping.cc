#include "stepping.hh"


MySteppingAction::MySteppingAction() {} // Constructor, means it runs when the class is created
MySteppingAction::~MySteppingAction() {} // Destructor, means it runs when the class is deleted

void MySteppingAction::UserSteppingAction(const G4Step* aStep) {
    // Get the analysis manager instance
    auto analysisManager = G4AnalysisManager::Instance(); // Singleton pattern (There is only one instance of this class in the program for safety)
                                                            // Auto just means figure out the type automatically

    // Get the kinetic energy at the end of the step
    G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy();
    
    // Get the Z position
    G4double z = aStep->GetPostStepPoint()->GetPosition().z();

    // Fill the Ntuple (our data table)
    analysisManager->FillNtupleDColumn(0, z);
    analysisManager->FillNtupleDColumn(1, energy);
    analysisManager->AddNtupleRow();

    // The analysis manager will handle writing to file at the end of the run
}