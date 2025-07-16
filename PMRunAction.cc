#include "PMRunAction.hh"

PMRunAction::PMRunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateH1("Energy", "Energy spectrum of mesons;Energy (MeV);Counts", 100, 0., 12000.);
    analysisManager->CreateH1("Angle", "Angular distribution of mesons;Theta (deg);Counts", 90, 0., 180.);
    analysisManager->CreateH1("Multiplicity", "Meson multiplicity per event;Multiplicity;Events", 50, 0, 50);
    analysisManager->FinishNtuple(0);
    analysisManager->CreateH1("Edep", "Energy deposit", 100, 0., 1.1 * MeV);

    analysisManager->CreateNtuple("Photons", "Photons");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->CreateNtupleDColumn("fGlobalTime");
    analysisManager->CreateNtupleDColumn("fWlen");
   




void PMRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void PMRunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();

    G4int runID = run->GetRunID();

    G4cout << "Finishing run " << runID << G4endl;
}

