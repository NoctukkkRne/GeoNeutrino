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

  const int NbinsCosTheta_earth = 100;
  const int NBinsPhi_earth = 100;
  const int NBinsE = 250;
  const double Emin = 0.0 * Unit::MeV;
  const double Emax = 5.0 * Unit::MeV;

  double CosTheta_earth, CosPhi_earth, SinPhi_earth, Phi_earth, E;
  double Neutrino_K40, NeutrinoE_K40, NeutrinoX_K40, AntiNeutrino_K40,
      AntiNeutrinoE_K40, AntiNeutrinoX_K40, AntiNeutrino_Th232,
      AntiNeutrinoE_Th232, AntiNeutrinoX_Th232, AntiNeutrino_U238,
      AntiNeutrinoE_U238, AntiNeutrinoX_U238;

  double jinpingZaxis[3], jinpingXaxis[3], jinpingYaxis[3],
      Direction_Neutrino[3], DirectionScale;
  double R, Theta, Phi, X, Y, Z, Rho, V, M;
  int Type;
  double DecayRate_K40, DecayRate_Th232, DecayRate_U238;
  double L, P;

  const double jinpingX = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          cos(jinpingLocation::Phi);
  const double jinpingY = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          sin(jinpingLocation::Phi);
  const double jinpingZ = jinpingLocation::R * cos(jinpingLocation::Theta);
  jinpingZaxis[0] = sin(jinpingLocation::Theta) * cos(jinpingLocation::Phi);
  jinpingZaxis[1] = sin(jinpingLocation::Theta) * sin(jinpingLocation::Phi);
  jinpingZaxis[2] = cos(jinpingLocation::Theta);
  jinpingXaxis[0] = cos(jinpingLocation::Theta) * cos(jinpingLocation::Phi);
  jinpingXaxis[1] = cos(jinpingLocation::Theta) * sin(jinpingLocation::Phi);
  jinpingXaxis[2] = -sin(jinpingLocation::Theta);
  jinpingYaxis[0] = -sin(jinpingLocation::Phi);
  jinpingYaxis[1] = cos(jinpingLocation::Phi);
  jinpingYaxis[2] = 0.0;

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

  TFile *tfCalculateNeutrinoFlux =
      new TFile("./data_out/CalculateNeutrinoFlux.root", "recreate");
  TTree *ttNeutrinoFlux = new TTree("NeutrinoFlux", "");
  ttNeutrinoFlux->Branch("R", &R, "R/D");
  ttNeutrinoFlux->Branch("Theta", &Theta, "Theta/D");
  ttNeutrinoFlux->Branch("Phi", &Phi, "Phi/D");
  ttNeutrinoFlux->Branch("E", &E, "E/D");
  // Values below stand for flux
  ttNeutrinoFlux->Branch("Neutrino_K40", &Neutrino_K40, "Neutrino_K40/D");
  ttNeutrinoFlux->Branch("NeutrinoE_K40", &NeutrinoE_K40, "NeutrinoE_K40/D");
  ttNeutrinoFlux->Branch("NeutrinoX_K40", &NeutrinoX_K40, "NeutrinoX_K40/D");
  ttNeutrinoFlux->Branch("AntiNeutrino_K40", &AntiNeutrino_K40,
                         "AntiNeutrino_K40/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoE_K40", &AntiNeutrinoE_K40,
                         "AntiNeutrinoE_K40/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoX_K40", &AntiNeutrinoX_K40,
                         "AntiNeutrinoX_K40/D");
  ttNeutrinoFlux->Branch("AntiNeutrino_Th232", &AntiNeutrino_Th232,
                         "AntiNeutrino_Th232/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoE_Th232", &AntiNeutrinoE_Th232,
                         "AntiNeutrinoE_Th232/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoX_Th232", &AntiNeutrinoX_Th232,
                         "AntiNeutrinoX_Th232/D");
  ttNeutrinoFlux->Branch("AntiNeutrino_U238", &AntiNeutrino_U238,
                         "AntiNeutrino_U238/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoE_U238", &AntiNeutrinoE_U238,
                         "AntiNeutrinoE_U238/D");
  ttNeutrinoFlux->Branch("AntiNeutrinoX_U238", &AntiNeutrinoX_U238,
                         "AntiNeutrinoX_U238/D");

  TH3D *h3dNeutrino_K40 =
      new TH3D("h3dNeutrino_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dNeutrinoE_K40 =
      new TH3D("h3dNeutrinoE_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dNeutrinoX_K40 =
      new TH3D("h3dNeutrinoX_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);

  TH3D *h3dAntiNeutrino_K40 =
      new TH3D("h3dAntiNeutrino_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoE_K40 =
      new TH3D("h3dAntiNeutrinoE_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoX_K40 =
      new TH3D("h3dAntiNeutrinoX_K40", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);

  TH3D *h3dAntiNeutrino_Th232 =
      new TH3D("h3dAntiNeutrino_Th232", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoE_Th232 =
      new TH3D("h3dAntiNeutrinoE_Th232", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoX_Th232 =
      new TH3D("h3dAntiNeutrinoX_Th232", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);

  TH3D *h3dAntiNeutrino_U238 =
      new TH3D("h3dAntiNeutrino_U238", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoE_U238 =
      new TH3D("h3dAntiNeutrinoE_U238", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);
  TH3D *h3dAntiNeutrinoX_U238 =
      new TH3D("h3dAntiNeutrinoX_U238", "", NbinsCosTheta_earth, -1.0, 1.0,
               NBinsPhi_earth, -Const::pi, Const::pi, NBinsE, Emin, Emax);

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

  for (int i = 0; i < ttEarthGrid->GetEntries(); ++i) {
    if (i % 1000 == 0) {
      std::cout << "Processing " << i << "/" << ttEarthGrid->GetEntries()
                << std::endl;
    }
    ttEarthGrid->GetEntry(i);

    Direction_Neutrino[0] = jinpingX - X;
    Direction_Neutrino[1] = jinpingY - Y;
    Direction_Neutrino[2] = jinpingZ - Z;
    DirectionScale =
        sqrt(pow(Direction_Neutrino[0], 2) + pow(Direction_Neutrino[1], 2) +
             pow(Direction_Neutrino[2], 2));
    Direction_Neutrino[0] /= DirectionScale;
    Direction_Neutrino[1] /= DirectionScale;
    Direction_Neutrino[2] /= DirectionScale;

    CosTheta_earth = Direction_Neutrino[0] * jinpingZaxis[0] +
                     Direction_Neutrino[1] * jinpingZaxis[1] +
                     Direction_Neutrino[2] * jinpingZaxis[2];

    Direction_Neutrino[0] =
        Direction_Neutrino[0] - CosTheta_earth * jinpingZaxis[0];
    Direction_Neutrino[1] =
        Direction_Neutrino[1] - CosTheta_earth * jinpingZaxis[1];
    DirectionScale =
        sqrt(pow(Direction_Neutrino[0], 2) + pow(Direction_Neutrino[1], 2));
    Direction_Neutrino[0] /= DirectionScale;
    Direction_Neutrino[1] /= DirectionScale;

    CosPhi_earth = Direction_Neutrino[0] * jinpingXaxis[0] +
                   Direction_Neutrino[1] * jinpingXaxis[1] +
                   Direction_Neutrino[2] * jinpingXaxis[2];
    SinPhi_earth = Direction_Neutrino[0] * jinpingYaxis[0] +
                   Direction_Neutrino[1] * jinpingYaxis[1] +
                   Direction_Neutrino[2] * jinpingYaxis[2];
    if (SinPhi_earth > 0.0) {
      Phi_earth = acos(CosPhi_earth);
    } else {
      Phi_earth = -acos(CosPhi_earth);
    }

    h3dNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, Neutrino_K40);
    h3dNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, Neutrino_K40);
    h3dNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, Neutrino_K40);
    h3dNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, Neutrino_K40);

    L = sqrt(pow(X - jinpingX, 2) + pow(Y - jinpingY, 2) +
             pow(Z - jinpingZ, 2));

    // Flux calculation
    DecayRate_K40 = M * N_K[Type] * Const::x_K40 / Const::mr_K40 * Const::Na *
                    Const::lambda_U238;
    DecayRate_Th232 = M * N_Th[Type] * Const::x_Th232 / Const::mr_Th232 *
                      Const::Na * Const::lambda_Th232;
    DecayRate_U238 = M * N_U[Type] * Const::x_U238 / Const::mr_U238 *
                     Const::Na * Const::lambda_U238;
    // Adjusting the energy precision here.
    for (int m = 0; m < NBinsE; ++m) {
      E = (Emax - Emin) / NBinsE * (m + 0.5);
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

      // Too much storage space needed, turn it off.
      // ttNeutrinoGrid->Fill();

      h3dNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, Neutrino_K40);
      h3dNeutrinoE_K40->Fill(CosTheta_earth, Phi_earth, E, NeutrinoE_K40);
      h3dNeutrinoX_K40->Fill(CosTheta_earth, Phi_earth, E, NeutrinoX_K40);
      h3dAntiNeutrino_K40->Fill(CosTheta_earth, Phi_earth, E, AntiNeutrino_K40);
      h3dAntiNeutrinoE_K40->Fill(CosTheta_earth, Phi_earth, E,
                                 AntiNeutrinoE_K40);
      h3dAntiNeutrinoX_K40->Fill(CosTheta_earth, Phi_earth, E,
                                 AntiNeutrinoX_K40);
      h3dAntiNeutrino_Th232->Fill(CosTheta_earth, Phi_earth, E,
                                  AntiNeutrino_Th232);
      h3dAntiNeutrinoE_Th232->Fill(CosTheta_earth, Phi_earth, E,
                                   AntiNeutrinoE_Th232);
      h3dAntiNeutrinoX_Th232->Fill(CosTheta_earth, Phi_earth, E,
                                   AntiNeutrinoX_Th232);
      h3dAntiNeutrino_U238->Fill(CosTheta_earth, Phi_earth, E,
                                 AntiNeutrino_U238);
      h3dAntiNeutrinoE_U238->Fill(CosTheta_earth, Phi_earth, E,
                                  AntiNeutrinoE_U238);
      h3dAntiNeutrinoX_U238->Fill(CosTheta_earth, Phi_earth, E,
                                  AntiNeutrinoX_U238);
    }
  }

  tfCalculateNeutrinoFlux->cd();

  ttNeutrinoFlux->Write();

  h3dNeutrino_K40->Write();
  h3dNeutrinoE_K40->Write();
  h3dNeutrinoX_K40->Write();
  h3dAntiNeutrino_K40->Write();
  h3dAntiNeutrinoE_K40->Write();
  h3dAntiNeutrinoX_K40->Write();
  h3dAntiNeutrino_Th232->Write();
  h3dAntiNeutrinoE_Th232->Write();
  h3dAntiNeutrinoX_Th232->Write();
  h3dAntiNeutrino_U238->Write();
  h3dAntiNeutrinoE_U238->Write();
  h3dAntiNeutrinoX_U238->Write();

  tfCalculateNeutrinoFlux->Close();

  tfFineCrust1->Close();

  return 0;
}
