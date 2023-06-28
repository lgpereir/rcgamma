#ifndef DETCONSTRUCT_HH
#define DETCONSTRUCT_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "DetectorMessenger.hh"
#include "detectorC.hh"

class DetectorMessenger;
class DetConstruct :  public G4VUserDetectorConstruction
{
public:
	DetConstruct();
	~DetConstruct();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume *Construct();
	G4bool SetMaterial(const G4String& value);
	
private:
	
	G4Box *solidWorld,  *solidDetector;
	G4LogicalVolume *logicWorld, *logicDetector;
	G4VPhysicalVolume *physWorld, *physDetector[10];
	
	G4Material *worldMat, *CH4, *worldMath, *matCH4;
	G4Element *C, *H;
	
	void DefineMaterials();
	virtual void ConstructSDandField();
	
	G4GenericMessenger *fMessenger;
	DetectorMessenger* detectorMessenger;
	
	G4LogicalVolume *fScoringVolume;
	
	G4double zw;
	
	G4int nCols,nRows;
	
};

#endif
