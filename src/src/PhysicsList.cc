//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PhysicsList.cc　　P04_PhysicsList/source/src/PhysicsList.hh にOpticalPhotonプロセスを追加
// 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4OpticalParameters.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4StoppingPhysics.hh"
//------------------------------------------------------------------------------
  PhysicsList::PhysicsList()
  : G4VModularPhysicsList() 
//------------------------------------------------------------------------------
{

// Default physics
     RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
     RegisterPhysics(new G4DecayPhysics());
     RegisterPhysics(new G4StoppingPhysics());

// Radioactive decay
//   RegisterPhysics(ew G4RadioactiveDecayPhysics());

// EM physics
   RegisterPhysics(new G4EmStandardPhysics_option4());

// Optical Photon physics
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  RegisterPhysics( opticalPhysics );

}

//------------------------------------------------------------------------------
  PhysicsList::~PhysicsList()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void PhysicsList::SetCuts()
//------------------------------------------------------------------------------
{
    G4VUserPhysicsList::SetCuts();
}

