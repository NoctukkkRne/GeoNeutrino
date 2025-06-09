#define FineCrust1

#include <fstream>
#include <iostream>
#include <string>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/CrossSection.h"
#include "../Common/include/NeutrinoOscillation.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingLocation.h"

#include "GeoNeutrinoSpectrum.h"

int main() {
#ifdef FineCrust1
  std::cout << "Define FineCrust1" << std::endl;
#endif

  double R, Theta, Phi, X, Y, Z, Rho, V, M;
  int Type;
  double DecayRate_K40, DecayRate_Th232, DecayRate_U238;
  double E, L, P;
  double Neutrino_K40, NeutrinoE_K40, NeutrinoX_K40, AntiNeutrino_K40,
      AntiNeutrinoE_K40, AntiNeutrinoX_K40, AntiNeutrino_Th232,
      AntiNeutrinoE_Th232, AntiNeutrinoX_Th232, AntiNeutrino_U238,
      AntiNeutrinoE_U238, AntiNeutrinoX_U238;

  const double jinpingX = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          cos(jinpingLocation::Phi);
  const double jinpingY = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          sin(jinpingLocation::Phi);
  const double jinpingZ = jinpingLocation::R * cos(jinpingLocation::Theta);

  const double N_K[19] = {0.0,     0.0,     1.83e-2, 1.83e-2, 1.83e-2,
                          716e-6,  716e-6,  716e-6,  0.0,     0.0,
                          2.32e-2, 2.32e-2, 2.32e-2, 2.32e-2, 1.91e-2,
                          0.51e-2, 315e-6,  152e-6,  402e-6};
  const double N_Th[19] = {0.0,     0.0,     8.10e-6, 8.10e-6, 8.10e-6,
                           0.21e-6, 0.21e-6, 0.21e-6, 0.0,     0.0,
                           10.5e-6, 10.5e-6, 10.5e-6, 10.5e-6, 6.5e-6,
                           1.2e-6,  150e-9,  21.9e-9, 147e-9};
  const double N_U[19] = {0.0,     0.0,     1.73e-6, 1.73e-6, 1.73e-6,
                          0.07e-6, 0.07e-6, 0.07e-6, 0.0,     0.0,
                          2.7e-6,  2.7e-6,  2.7e-6,  2.7e-6,  1.3e-6,
                          0.2e-6,  33e-9,   8.0e-9,  30e-9};

  GeoNeutrinoSpectrum *gns = new GeoNeutrinoSpectrum();

  TFile *tfNeutrinoGrid =
      new TFile("./data_out/CalculateNeutrinoGrid.root", "recreate");
  TTree *ttNeutrinoGrid = new TTree("NeutrinoGrid", "");
  ttNeutrinoGrid->Branch("R", &R, "R/D");
  ttNeutrinoGrid->Branch("Theta", &Theta, "Theta/D");
  ttNeutrinoGrid->Branch("Phi", &Phi, "Phi/D");
  ttNeutrinoGrid->Branch("E", &E, "E/D");
  // Values below stand for flux
  ttNeutrinoGrid->Branch("Neutrino_K40", &Neutrino_K40, "Neutrino_K40/D");
  ttNeutrinoGrid->Branch("NeutrinoE_K40", &NeutrinoE_K40, "NeutrinoE_K40/D");
  ttNeutrinoGrid->Branch("NeutrinoX_K40", &NeutrinoX_K40, "NeutrinoX_K40/D");
  ttNeutrinoGrid->Branch("AntiNeutrino_K40", &AntiNeutrino_K40,
                         "AntiNeutrino_K40/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoE_K40", &AntiNeutrinoE_K40,
                         "AntiNeutrinoE_K40/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoX_K40", &AntiNeutrinoX_K40,
                         "AntiNeutrinoX_K40/D");
  ttNeutrinoGrid->Branch("AntiNeutrino_Th232", &AntiNeutrino_Th232,
                         "AntiNeutrino_Th232/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoE_Th232", &AntiNeutrinoE_Th232,
                         "AntiNeutrinoE_Th232/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoX_Th232", &AntiNeutrinoX_Th232,
                         "AntiNeutrinoX_Th232/D");
  ttNeutrinoGrid->Branch("AntiNeutrino_U238", &AntiNeutrino_U238,
                         "AntiNeutrino_U238/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoE_U238", &AntiNeutrinoE_U238,
                         "AntiNeutrinoE_U238/D");
  ttNeutrinoGrid->Branch("AntiNeutrinoX_U238", &AntiNeutrinoX_U238,
                         "AntiNeutrinoX_U238/D");

#ifdef FineCrust1
  TFile *tfFineCrust1 = new TFile("./data_out/FineCrust1.root");
#else
  TFile *tfFineCrust1 = new TFile("./data_out/Crust1.root");
#endif
  TTree *ttEarthGrid = (TTree *)tfFineCrust1->Get("EarthGrid");
  ttEarthGrid->SetBranchAddress("R", &R);
  ttEarthGrid->SetBranchAddress("Theta", &Theta);
  ttEarthGrid->SetBranchAddress("Phi", &Phi);
  ttEarthGrid->SetBranchAddress("X", &X);
  ttEarthGrid->SetBranchAddress("Y", &Y);
  ttEarthGrid->SetBranchAddress("Z", &Z);
  ttEarthGrid->SetBranchAddress("Rho", &Rho);
  ttEarthGrid->SetBranchAddress("V", &V);
  ttEarthGrid->SetBranchAddress("M", &M);
  ttEarthGrid->SetBranchAddress("Type", &Type);

  // for (int i = 0; i < ttEarthGrid->GetEntries(); ++i) {
  for (int i = 0; i < 10000; ++i) {
    if (i % 1000 == 0) {
      std::cout << "Processing " << i << "/" << ttEarthGrid->GetEntries()
                << std::endl;
    }
    ttEarthGrid->GetEntry(i);

    L = sqrt(pow(X - jinpingX, 2) + pow(Y - jinpingY, 2) +
             pow(Z - jinpingZ, 2));

    // Flux calculation
    DecayRate_K40 = M * N_K[Type] * Const::x_K40 / Const::mr_K40 * Const::Na *
                    Const::lambda_U238;
    DecayRate_Th232 = M * N_Th[Type] * Const::x_Th232 / Const::mr_Th232 *
                      Const::Na * Const::lambda_Th232;
    DecayRate_U238 = M * N_U[Type] * Const::x_U238 / Const::mr_U238 *
                     Const::Na * Const::lambda_U238;
    for (int m = 0; m < 250; ++m) {
      E = (0.02 * m + 0.01) * Unit::MeV;
      P = NeutrinoOscillation::Pee_vac(E, L);

      Neutrino_K40 = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_K40 *
                     gns->Neutrino_K40(E);
      NeutrinoE_K40 = Neutrino_K40 * P;
      NeutrinoX_K40 = Neutrino_K40 * (1.0 - P);

      AntiNeutrino_K40 = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_K40 *
                         gns->AntiNeutrino_K40(E);
      AntiNeutrinoE_K40 = AntiNeutrino_K40 * P;
      AntiNeutrinoX_K40 = AntiNeutrino_K40 * (1.0 - P);

      AntiNeutrino_Th232 = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_Th232 *
                           gns->AntiNeutrino_Th232(E);
      AntiNeutrinoE_Th232 = AntiNeutrino_Th232 * P;
      AntiNeutrinoX_Th232 = AntiNeutrino_Th232 * (1.0 - P);

      AntiNeutrino_U238 = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_U238 *
                          gns->AntiNeutrino_U238(E);
      AntiNeutrinoE_U238 = AntiNeutrino_U238 * P;
      AntiNeutrinoX_U238 = AntiNeutrino_U238 * (1.0 - P);

      ttNeutrinoGrid->Fill();
    }
  }

  tfNeutrinoGrid->cd();
  ttNeutrinoGrid->Write();
  tfNeutrinoGrid->Close();

  tfFineCrust1->Close();

  return 0;
}
