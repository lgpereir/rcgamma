#include "stepping.hh"


MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{   
     G4double flagParticle=0.;
     G4double flagProcess=0.;
     
  /*   
     if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "e-")      	  flagParticle = 1;    
     if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "proton")  	  flagParticle = 2;
     if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "GenericIon")    flagParticle = 3;
         if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "mu-")      	  flagParticle = 4;  */
         
         //---------------------------------------------------------------------------------------------------
         // invensao
         
            if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "e-")      	  flagParticle = 11;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "e+")      	  flagParticle = -11;  
           if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "mu-")      	  flagParticle = 13;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "mu+")      	  flagParticle = -13;  
               if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "alpha")      	  flagParticle = 42212;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "deutron")      	  flagParticle = 32212;  
          
           if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "proton")      	  flagParticle = 2212;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "neutron")      	  flagParticle = 2112;  
                     if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "anti_proton")      	  flagParticle = -2212;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "anti_neutron")      	  flagParticle = -2112;  
          
            if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "pi+")      	  flagParticle = 211;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "pi-")      	  flagParticle = -211;  
                     if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "pi0")      	  flagParticle = 111;  
          if (step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName() == "J/psi")      	  flagParticle = 443;  
         
         //-------------------------------------------------------------------------------
     
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    const DetConstruct *detectorConstruction = static_cast<const DetConstruct*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
    
    if(volume != fScoringVolume)
        return;
    
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep); 
    
    //G4AnalysisManager *man = G4AnalysisManager::Instance();
      
   
} 


    
