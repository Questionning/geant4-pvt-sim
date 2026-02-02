#include "action.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    MyPrimaryGenerator* generator = new MyPrimaryGenerator();
    SetUserAction(generator); // This transfers ownership to G4, so we don't need to delete it ourselves
    SetUserAction(new MySteppingAction());
}