#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction() : G4UserRunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->SetDefaultFileType("csv");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("output");


  analysisManager->CreateNtuple("Data", "Energy Deposition");
  analysisManager->CreateNtupleIColumn("EventID");      
  analysisManager->CreateNtupleDColumn("EnergyDep");   
  analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}