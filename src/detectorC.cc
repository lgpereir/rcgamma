#include "detectorC.hh"
#include "G4AnalysisManager.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include <fstream>   // for std::ifstream
#include <iostream>  // for std::cout
#include <string>    // for std::string and std::getline
#include "G4PhysicsVectorType.hh"
#include "G4PhysicsVector.hh"
#include "G4PhysicsFreeVector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
        G4double flagParticle=0.;

          if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "gamma") flagParticle = 7;
          
        G4Track *track = aStep->GetTrack();
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
    	
    	G4ThreeVector posPhoton = preStepPoint->GetPosition();
    	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
	
	G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03;
	
        const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

        G4int copyNo = touchable->GetCopyNumber();
        
        G4VPhysicalVolume *physVol = touchable->GetVolume();
        
        G4ThreeVector posDetector = physVol->GetTranslation();
        
        G4int evt = G4RunManager::GetRunManager()-> GetCurrentEvent()->GetEventID();
    
        G4AnalysisManager *man = G4AnalysisManager::Instance();
      
        if (flagParticle !=0) {
        	if (flagParticle ==7){
        		man->FillNtupleIColumn(copyNo , 0, evt);
        		man->FillNtupleDColumn(copyNo , 1, posPhoton[0]);
        		man->FillNtupleDColumn(copyNo , 2, posPhoton[1]);
        		man->FillNtupleDColumn(copyNo , 3, posPhoton[2]);
        		man->FillNtupleDColumn(copyNo , 4, wlen);
        		man->AddNtupleRow(copyNo );
        }
        }
        
     	return true;
}
