#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "LBE.hh"
#include "DetConstruct.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
	G4UIExecutive *ui =0;
	//G4RunManager *runManager= new G4RunManager();
	G4int nThreads = 24;
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager= new G4MTRunManager();
		runManager->SetNumberOfThreads(3);
	#else
		G4RunManager *runManager= new G4RunManager();
	#endif
	
	runManager->SetUserInitialization(new DetConstruct());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	G4VModularPhysicsList* physics = new QGSP_BIC_HP();
	//G4VModularPhysicsList* physics = new LBE();
        physics->RegisterPhysics(new G4DecayPhysics());
        runManager->SetUserInitialization(physics);
	
	//runManager->Initialize();
		
	if(argc ==1)
	{
	 	ui=new G4UIExecutive(argc, argv);
	}
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	 
	if(ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();	
	}
	else
	{
		G4String command = "/control/execute ";
        	G4String fileName = argv[1];
        	UImanager->ApplyCommand(command+fileName);
	
	}
	
	return 0;
}
