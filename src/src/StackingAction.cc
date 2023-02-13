

#include "StackingAction.hh"
#include "EventAction.hh"

#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

//namespace B1
//{

StackingAction::StackingAction(EventAction* eventAction)
  : G4UserStackingAction(),
    fScintiCounter(0), fCerenCounter(0), fOpAbsorpCounter(0),
    fEventAction(eventAction)
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if (aTrack->GetGlobalTime() > 1000.*CLHEP::ns) {return fKill;}

  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintiCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        fCerenCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "OpAbsorption")
        fOpAbsorpCounter++;
    }
  }
  return fUrgent;
}


void StackingAction::NewStage()
{
  G4cout << " Scintillation photons :  " << std::setw(8) << fScintiCounter   << G4endl;
  G4cout << " Cerenkov photons      :  " << std::setw(8) << fCerenCounter    << G4endl;
  G4cout << " Optical Absorption    :  " << std::setw(8) << fOpAbsorpCounter << G4endl;

  fEventAction->SetNScintillation(fScintiCounter);
}

void StackingAction::PrepareNewEvent()
{
  fScintiCounter   = 0;
  fCerenCounter    = 0;
  fOpAbsorpCounter = 0;
}

//}