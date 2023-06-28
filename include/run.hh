#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh" 
#include "G4AnalysisManager.hh"
#include "globals.hh"
#include <iostream>
#include "G4Run.hh"
#include "tracking.hh"
#include "G4ParticleDefinition.hh"
#include "G4RunManager.hh"


class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
