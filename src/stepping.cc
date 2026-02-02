#include "stepping.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"


MySteppingAction::MySteppingAction() {} // Constructor, means it runs when the class is created
MySteppingAction::~MySteppingAction() {} // Destructor, means it runs when the class is deleted

void MySteppingAction::UserSteppingAction(const G4Step* aStep) {
    auto analysisManager = G4AnalysisManager::Instance();

    // 1. Get the Track and the Points
    G4Track* track = aStep->GetTrack();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    // 2. Extract the values
    G4int stepNum = track->GetCurrentStepNumber();
    G4ThreeVector pos = postStepPoint->GetPosition();
    G4double kinE = postStepPoint->GetKineticEnergy();
    G4double dE = aStep->GetTotalEnergyDeposit();
    G4double stepL = aStep->GetStepLength();
    G4double trackL = track->GetTrackLength();

    // Get Volume Name (Check for null if particle leaves the world!)
    G4String volName = "OutOfWorld";
    if (postStepPoint->GetPhysicalVolume()) {
        volName = postStepPoint->GetPhysicalVolume()->GetName();
    }

    // Get Process Name
    G4String procName = "InitStep";
    if (postStepPoint->GetProcessDefinedStep()) {
        procName = postStepPoint->GetProcessDefinedStep()->GetProcessName();
    }

    // 3. Fill the columns (index starts at 0)
    analysisManager->FillNtupleIColumn(0, stepNum);
    analysisManager->FillNtupleDColumn(1, pos.x());
    analysisManager->FillNtupleDColumn(2, pos.y());
    analysisManager->FillNtupleDColumn(3, pos.z());
    analysisManager->FillNtupleDColumn(4, kinE);
    analysisManager->FillNtupleDColumn(5, dE);
    analysisManager->FillNtupleDColumn(6, stepL);
    analysisManager->FillNtupleDColumn(7, trackL);
    analysisManager->FillNtupleSColumn(8, volName);
    analysisManager->FillNtupleSColumn(9, procName);
    
    analysisManager->AddNtupleRow();

    // The analysis manager takes care of storing the data for us at the end of the run
}