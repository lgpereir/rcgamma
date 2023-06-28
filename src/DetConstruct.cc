#include "DetConstruct.hh"
#include "G4MTRunManager.hh"

DetConstruct::DetConstruct(): G4VUserDetectorConstruction(), logicWorld(0)
{
    std::cout << "Chegou aqui" << std::endl;
    detectorMessenger = new DetectorMessenger(this);

    DefineMaterials();   
}    
      
DetConstruct::~DetConstruct()
{
    delete detectorMessenger;
}

void DetConstruct::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
      
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};   // corte em energia hcortado (eV)/lambda (um)
    
     // definindo ar    
    worldMat = nist->FindOrBuildMaterial("G4_AIR"); // mais tarde definir vacuo
    // indice de refracao
    G4double rindexWorld[2] = {1.0, 1.0}; 
    // setting            
   G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld); 
    
        // definindo ch4
     //composicao
    G4int natoms;
G4double Z;
G4double A;

    G4Element* elH = new G4Element("hydrogen","el_H",Z=1.,A=1.00794*g/mole); 

G4Element* elC = new G4Element("carbon","el_C",Z=6.,A=12.0107*g/mole); 

G4double density = 0.000667151*g/cm3;
G4double pressure    = 101325 *pascal;
G4double temperature = CLHEP::STP_Temperature;
    matCH4 = new G4Material("CH4", density, 2, kStateGas, temperature, pressure);
    matCH4->AddElement(elC, natoms=1);
    matCH4->AddElement(elH, natoms=4);
    matCH4->GetIonisation()->SetMeanExcitationEnergy(41.7*eV);

    // indice de refracao
    G4double rindexCH4[2] = {1.004, 1.004}; 
    // setting
    G4MaterialPropertiesTable *mptCH4 = new G4MaterialPropertiesTable();
    mptCH4->AddProperty("RINDEX", energy, rindexCH4, 2);
    matCH4->SetMaterialPropertiesTable(mptCH4);  

    worldMath = worldMat;
}  

G4VPhysicalVolume *DetConstruct::Construct()
{
    G4double xWorld = 5*km;
    G4double yWorld = 5*km;
    G4double zWorld = 5*km;
    
   
    
    
    
    solidWorld = new G4Box("solidWorld",xWorld,yWorld,zWorld);
    
    logicWorld = new G4LogicalVolume(solidWorld,worldMath,"logicWorld");
    
    physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);

    solidDetector = new G4Box("solidDetector", xWorld-xWorld/100.0, yWorld-yWorld/100.0,1.0*m);
    
    logicDetector = new G4LogicalVolume(solidDetector,worldMath,"logicDetector"); 
    
       

    for(G4int k = 0; k < 10; k++)
    {
       zw = zWorld/10.*2*k - zWorld + zWorld/10.;
       
       physDetector[k] = new G4PVPlacement(0,G4ThreeVector(0.,0.,zw), logicDetector,"physDetector",logicWorld,false,k,true);
       

    }
    
    return physWorld; 
}

void DetConstruct::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicDetector->SetSensitiveDetector(sensDet);
}

G4bool DetConstruct::SetMaterial(const G4String& value) {
  /*  if (value == "Air") { 
        worldMath = worldMat;
         G4cout << "Air" << G4endl;
    } else if (value == "CH4") {
        worldMath = matCH4;
         G4cout << "CH4" << G4endl;
    }*/

    if (logicWorld) {
        logicWorld->SetMaterial(worldMath);
	logicDetector->SetMaterial(worldMath);
        G4MTRunManager::GetRunManager()->PhysicsHasBeenModified();
        G4MTRunManager::GetRunManager()->GeometryHasBeenModified();
        G4cout << "The material has been changed to " << worldMath << G4endl;
    }
    return true;
}
