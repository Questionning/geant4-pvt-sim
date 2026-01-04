#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh" // A standard physics list
#include "G4StepLimiterPhysics.hh"
#include "construction.hh"
#include "action.hh"

int main(int argc, char** argv) {
    // 1. Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // 2. Set mandatory initialization classes (We will define these later)
    // For now, we use a pre-made Physics List
    runManager->SetUserInitialization(new FTFP_BERT);
    runManager -> SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyActionInitialization());

    // 3. Initialize G4 kernel
    runManager->Initialize(); // Commented out until we have geometry!

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Increase verbosity to see the details of each step the particle takes
    UImanager->ApplyCommand("/tracking/verbose 1");

    // 4. Start a run (shoot 10 particles)
    runManager->BeamOn(1);

    delete runManager;
    return 0;
}