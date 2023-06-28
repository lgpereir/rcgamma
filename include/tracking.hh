#ifndef TRACKING_HH
#define TRACKING_HH

#include "G4UserTrackingAction.hh"
#include <map>

class G4Region;
class G4ParticleDefinition;
class detectorC;

class TrackingAction : public G4UserTrackingAction
{
public:
    TrackingAction(detectorC* detector = 0);
    ~TrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);

    void SetDetector(detectorC* detector)
    {
        fDetector = detector;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInTarget()
    {
        return fNParticleInTarget;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInWorld()
    {
        return fNParticleInWorld;
    }

private:
    detectorC* fDetector;
    G4Region* fTargetRegion;
    std::map<const G4ParticleDefinition*, int> fNParticleInTarget;
    std::map<const G4ParticleDefinition*, int> fNParticleInWorld;
};


#endif 
