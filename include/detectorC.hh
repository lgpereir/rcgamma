#ifndef DETECTORC_HH
#define DETECTORC_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicsVectorType.hh"
#include <fstream>   // for std::ifstream
#include <iostream>  // for std::cout
#include <string>    // for std::string and std::getline
#include "G4PhysicsVector.hh"
#include "G4PhysicsFreeVector.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    
};

#endif
