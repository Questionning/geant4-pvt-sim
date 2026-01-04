#ifndef ACTION_HH
#define ACTION_HH
#include "G4VUserActionInitialization.hh"
#include "generator.hh"

class MyActionInitialization : public G4VUserActionInitialization {
public:
    MyActionInitialization();
    ~MyActionInitialization();
    virtual void Build() const; // We need the const keyword to tell G4 that this function
                                // will not modify any member variables, which is important for 
                                // thread safety in multi-threaded simulations in G4
};
#endif