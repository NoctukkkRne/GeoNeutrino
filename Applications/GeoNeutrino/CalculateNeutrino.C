#define FineCrust1

#include <fstream>
#include <iostream>
#include <string>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/CrossSection.h"
#include "../Common/include/NeutrinoOscillation.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingLocation.h"
#include "../Common/include/jinpingStyle.h"

int main() {
#ifdef FineCrust1
  std::cout << "Define FineCrust1" << std::endl;
#endif

  const double jinpingX = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          cos(jinpingLocation::Phi);
  const double jinpingY = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          sin(jinpingLocation::Phi);
  const double jinpingZ = jinpingLocation::R * cos(jinpingLocation::Theta);

  jinpingStyle();

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

  double R, Theta, Phi, X, Y, Z, Rho, V, M;
  int Type;
  double DecayRate_K40, DecayRate_Th232, DecayRate_U238;
  double E, L, P, N_Spectrum, N_Flux;
  double TNUTotal_K40 = 0.0, TNUCrust_K40 = 0.0, TNUMantle_K40 = 0.0;
  double TNUTotal_Th232 = 0.0, TNUCrust_Th232 = 0.0, TNUMantle_Th232 = 0.0;
  double TNUTotal_U238 = 0.0, TNUCrust_U238 = 0.0, TNUMantle_U238 = 0.0;
  int GridID = -1;
  double TNU_Grid[49] = {0.0};

  TFile *tfNeutrinoGrid =
      new TFile("./data_out/CalculateNeutrinoGrid.root", "recreate");
  TTree *ttNeutrinoGrid = new TTree("NeutrinoGrid", "");
  ttNeutrinoGrid->Branch("R", &R, "R/D");
  ttNeutrinoGrid->Branch("Theta", &Theta, "Theta/D");
  ttNeutrinoGrid->Branch("Phi", &Phi, "Phi/D");
  ttNeutrinoGrid->Branch("X", &X, "X/D");
  ttNeutrinoGrid->Branch("Y", &Y, "Y/D");
  ttNeutrinoGrid->Branch("Z", &Z, "Z/D");
  ttNeutrinoGrid->Branch("DecayRate_K40", &DecayRate_K40, "DecayRate_K40/D");
  ttNeutrinoGrid->Branch("DecayRate_Th232", &DecayRate_Th232,
                         "DecayRate_Th232/D");
  ttNeutrinoGrid->Branch("DecayRate_U238", &DecayRate_U238, "DecayRate_U238/D");

#ifdef FineCrust1
  TFile *tfFineCrust1 = new TFile("./data_out/FineCrust1.root");
#else
  TFile *tfFineCrust1 = new TFile("./data_out/Crust1.root");
#endif
  TTree *ttGrid = (TTree *)tfFineCrust1->Get("EarthGrid");
  ttGrid->SetBranchAddress("R", &R);
  ttGrid->SetBranchAddress("Theta", &Theta);
  ttGrid->SetBranchAddress("Phi", &Phi);
  ttGrid->SetBranchAddress("X", &X);
  ttGrid->SetBranchAddress("Y", &Y);
  ttGrid->SetBranchAddress("Z", &Z);
  ttGrid->SetBranchAddress("Rho", &Rho);
  ttGrid->SetBranchAddress("V", &V);
  ttGrid->SetBranchAddress("M", &M);
  ttGrid->SetBranchAddress("Type", &Type);

  TFile *tfDecay_K40 = new TFile("./data_in/K40.root");
  TH1D *h1dDecayNeutrino_K40 = (TH1D *)tfDecay_K40->Get("Neutrino");
  TH1D *h1dDecayAntiNeutrino_K40 = (TH1D *)tfDecay_K40->Get("AntiNeutrino");
  TFile *tfDecay_Th232 = new TFile("./data_in/Th232.root");
  TH1D *h1dDecayAntiNeutrino_Th232 = (TH1D *)tfDecay_Th232->Get("AntiNeutrino");
  TFile *tfDecay_U238 = new TFile("./data_in/U238.root");
  TH1D *h1dDecayAntiNeutrino_U238 = (TH1D *)tfDecay_U238->Get("AntiNeutrino");

  TCanvas *cv = new TCanvas("cv", "", 700, 500);

  TH1D *h1dNeutrinoNoOsc_K40 =
      new TH1D("h1dNeutrinoNoOsc_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dNeutrinoOsc_K40 =
      new TH1D("h1dNeutrinoOsc_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoNoOsc_K40 =
      new TH1D("h1dAntiNeutrinoNoOsc_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoOsc_K40 =
      new TH1D("h1dAntiNeutrinoOsc_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoNoOsc_Th232 =
      new TH1D("h1dAntiNeutrinoNoOsc_Th232", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoOsc_Th232 =
      new TH1D("h1dAntiNeutrinoOsc_Th232", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoNoOsc_U238 =
      new TH1D("h1dAntiNeutrinoNoOsc_U238", "", 2000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoOsc_U238 =
      new TH1D("h1dAntiNeutrinoOsc_U238", "", 2000, 0.0, 20.0);

  for (int i = 0; i < ttGrid->GetEntries(); ++i) {
    if (i % 1000 == 0) {
      std::cout << "Processing " << i << "/" << ttGrid->GetEntries()
                << std::endl;
    }
    ttGrid->GetEntry(i);

    L = sqrt(pow(X - jinpingX, 2) + pow(Y - jinpingY, 2) +
             pow(Z - jinpingZ, 2));
    GridID = -1;
    if (Theta / Unit::deg > 58 && Theta / Unit::deg < 65 &&
        Phi / Unit::deg > 98 && Phi / Unit::deg < 105) {
      GridID = int(Theta / Unit::deg - 58) * 7 + int(Phi / Unit::deg - 98);
    }

    // K40 Decay
    DecayRate_K40 = M * N_K[Type] * Const::x_K40 / Const::mr_K40 * Const::Na *
                    Const::lambda_K40;
    // K40 Neutrino
    for (int m = 0; m < 400; ++m) {
      E = h1dDecayNeutrino_K40->GetBinCenter(m + 1) * Unit::MeV;
      N_Spectrum = h1dDecayNeutrino_K40->GetBinContent(m + 1) / Unit::MeV;
      P = NeutrinoOscillation::Pee_vac(E, L);

      N_Flux = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_K40 * N_Spectrum;

      h1dNeutrinoNoOsc_K40->Fill(
          E / Unit::MeV, N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      h1dNeutrinoOsc_K40->Fill(
          E / Unit::MeV, P * N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
    }
    // K40 AntiNeutrino
    for (int m = 0; m < 400; ++m) {
      E = h1dDecayAntiNeutrino_K40->GetBinCenter(m + 1) * Unit::MeV;
      N_Spectrum = h1dDecayAntiNeutrino_K40->GetBinContent(m + 1) / Unit::MeV;
      P = NeutrinoOscillation::Pee_vac(E, L);

      N_Flux = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_K40 * N_Spectrum;
      TNUTotal_K40 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                      P * 0.01 * Unit::MeV;

      h1dAntiNeutrinoNoOsc_K40->Fill(
          E / Unit::MeV, N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      h1dAntiNeutrinoOsc_K40->Fill(
          E / Unit::MeV, P * N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      if ((Type >= 2 && Type <= 7) || (Type >= 10 && Type <= 15)) {
        TNUCrust_K40 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                        P * 0.01 * Unit::MeV;
      } else if (Type >= 16 && Type <= 18) {
        TNUMantle_K40 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                         P * 0.01 * Unit::MeV;
      }
    }

    // Th232 Decay
    DecayRate_Th232 = M * N_Th[Type] * Const::x_Th232 / Const::mr_Th232 *
                      Const::Na * Const::lambda_Th232;
    for (int m = 0; m < 400; ++m) {
      E = h1dDecayAntiNeutrino_Th232->GetBinCenter(m + 1) * Unit::MeV;
      N_Spectrum = h1dDecayAntiNeutrino_Th232->GetBinContent(m + 1) / Unit::MeV;
      P = NeutrinoOscillation::Pee_vac(E, L);

      N_Flux = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_Th232 * N_Spectrum;
      TNUTotal_Th232 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                        P * 0.01 * Unit::MeV;
      if (GridID >= 0 && GridID < 49) {
        TNU_Grid[GridID] += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 *
                            Unit::yr * P * 0.01 * Unit::MeV;
      }

      h1dAntiNeutrinoNoOsc_Th232->Fill(
          E / Unit::MeV, N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      h1dAntiNeutrinoOsc_Th232->Fill(
          E / Unit::MeV, P * N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      if ((Type >= 2 && Type <= 7) || (Type >= 10 && Type <= 15)) {
        TNUCrust_Th232 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 *
                          Unit::yr * P * 0.01 * Unit::MeV;
      } else if (Type >= 16 && Type <= 18) {
        TNUMantle_Th232 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 *
                           Unit::yr * P * 0.01 * Unit::MeV;
      }
    }

    // U238 Decay
    DecayRate_U238 = M * N_U[Type] * Const::x_U238 / Const::mr_U238 *
                     Const::Na * Const::lambda_U238;
    for (int m = 0; m < 400; ++m) {
      E = h1dDecayAntiNeutrino_U238->GetBinCenter(m + 1) * Unit::MeV;
      N_Spectrum = h1dDecayAntiNeutrino_U238->GetBinContent(m + 1) / Unit::MeV;
      P = NeutrinoOscillation::Pee_vac(E, L);

      N_Flux = 1.0 / (4.0 * Const::pi * L * L) * DecayRate_U238 * N_Spectrum;
      TNUTotal_U238 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                       P * 0.01 * Unit::MeV;
      if (GridID >= 0 && GridID < 49) {
        TNU_Grid[GridID] += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 *
                            Unit::yr * P * 0.01 * Unit::MeV;
      }

      h1dAntiNeutrinoNoOsc_U238->Fill(
          E / Unit::MeV, N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      h1dAntiNeutrinoOsc_U238->Fill(
          E / Unit::MeV, P * N_Flux / (1.0 / Unit::m2 / Unit::s / Unit::MeV));

      if ((Type >= 2 && Type <= 7) || (Type >= 10 && Type <= 15)) {
        TNUCrust_U238 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 * Unit::yr *
                         P * 0.01 * Unit::MeV;
      } else if (Type >= 16 && Type <= 18) {
        TNUMantle_U238 += N_Flux * CrossSection::TCS_IBD(E) * 1.0e32 *
                          Unit::yr * P * 0.01 * Unit::MeV;
      }
    }

    ttNeutrinoGrid->Fill();
  }

  cv->SetLogx(1);
  cv->SetLogy(1);
  TH1D *h1dPlot = new TH1D("h1dPlot", "", 2000, 0.0, 20.0);
  h1dPlot->GetXaxis()->SetRangeUser(0.1, 20.0);
  h1dPlot->GetYaxis()->SetRangeUser(1.0e4, 1.0e12);
  h1dPlot->GetXaxis()->SetTitle("NeutrinoEnergy [MeV]");
  h1dPlot->GetYaxis()->SetTitle("NeutrinoFlux [m^{-2}s^{-1}MeV^{-1}]");

  h1dPlot->Draw("HIST");
  h1dAntiNeutrinoNoOsc_K40->SetLineColor(kRed);
  h1dAntiNeutrinoNoOsc_K40->SetLineStyle(3);
  h1dAntiNeutrinoNoOsc_K40->Draw("HIST;same");
  h1dAntiNeutrinoOsc_K40->SetLineColor(kRed);
  h1dAntiNeutrinoOsc_K40->SetLineStyle(1);
  h1dAntiNeutrinoOsc_K40->Draw("HIST;same");
  h1dAntiNeutrinoNoOsc_Th232->SetLineColor(kGreen);
  h1dAntiNeutrinoNoOsc_Th232->SetLineStyle(3);
  h1dAntiNeutrinoNoOsc_Th232->Draw("HIST;same");
  h1dAntiNeutrinoOsc_Th232->SetLineColor(kGreen);
  h1dAntiNeutrinoOsc_Th232->SetLineStyle(1);
  h1dAntiNeutrinoOsc_Th232->Draw("HIST;same");
  h1dAntiNeutrinoNoOsc_U238->SetLineColor(kBlue);
  h1dAntiNeutrinoNoOsc_U238->SetLineStyle(3);
  h1dAntiNeutrinoNoOsc_U238->Draw("HIST;same");
  h1dAntiNeutrinoOsc_U238->SetLineColor(kBlue);
  h1dAntiNeutrinoOsc_U238->SetLineStyle(1);
  h1dAntiNeutrinoOsc_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dNeutrino.png");

  cv->SetLogx(1);
  cv->SetLogy(1);
  h1dPlot->Draw("HIST");
  h1dAntiNeutrinoNoOsc_K40->SetLineColor(kRed);
  h1dAntiNeutrinoNoOsc_K40->SetLineStyle(1);
  h1dAntiNeutrinoNoOsc_K40->Draw("HIST;same");
  h1dAntiNeutrinoNoOsc_Th232->SetLineColor(kGreen);
  h1dAntiNeutrinoNoOsc_Th232->SetLineStyle(1);
  h1dAntiNeutrinoNoOsc_Th232->Draw("HIST;same");
  h1dAntiNeutrinoNoOsc_U238->SetLineColor(kBlue);
  h1dAntiNeutrinoNoOsc_U238->SetLineStyle(1);
  h1dAntiNeutrinoNoOsc_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dNeutrinoNoOsc.png");

  cv->SetLogx(1);
  cv->SetLogy(1);
  h1dPlot->Draw("HIST");
  h1dAntiNeutrinoOsc_K40->SetLineColor(kRed);
  h1dAntiNeutrinoOsc_K40->SetLineStyle(1);
  h1dAntiNeutrinoOsc_K40->Draw("HIST;same");
  h1dAntiNeutrinoOsc_Th232->SetLineColor(kGreen);
  h1dAntiNeutrinoOsc_Th232->SetLineStyle(1);
  h1dAntiNeutrinoOsc_Th232->Draw("HIST;same");
  h1dAntiNeutrinoOsc_U238->SetLineColor(kBlue);
  h1dAntiNeutrinoOsc_U238->SetLineStyle(1);
  h1dAntiNeutrinoOsc_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dNeutrinoOsc.png");

  cv->SetLogx(0);
  cv->SetLogy(0);
  TH1D *h1dPee_K40 = new TH1D("h1dPee_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dPee_Th232 = new TH1D("h1dPee_Th232", "", 2000, 0.0, 20.0);
  TH1D *h1dPee_U238 = new TH1D("h1dPee_U238", "", 2000, 0.0, 20.0);
  for (int m = 0; m < 2000; ++m) {
    if (h1dAntiNeutrinoNoOsc_K40->GetBinContent(m + 1) > 0.0) {
      h1dPee_K40->SetBinContent(
          m + 1, h1dAntiNeutrinoOsc_K40->GetBinContent(m + 1) /
                     h1dAntiNeutrinoNoOsc_K40->GetBinContent(m + 1));
    }
    if (h1dAntiNeutrinoNoOsc_Th232->GetBinContent(m + 1) > 0.0) {
      h1dPee_Th232->SetBinContent(
          m + 1, h1dAntiNeutrinoOsc_Th232->GetBinContent(m + 1) /
                     h1dAntiNeutrinoNoOsc_Th232->GetBinContent(m + 1));
    }
    if (h1dAntiNeutrinoNoOsc_U238->GetBinContent(m + 1) > 0.0) {
      h1dPee_U238->SetBinContent(
          m + 1, h1dAntiNeutrinoOsc_U238->GetBinContent(m + 1) /
                     h1dAntiNeutrinoNoOsc_U238->GetBinContent(m + 1));
    }
  }
  h1dPlot->GetXaxis()->SetTitle("NeutrinoEnergy [MeV]");
  h1dPlot->GetXaxis()->SetRangeUser(0.0, 3.5);
  h1dPlot->GetYaxis()->SetTitle("P_{ee}^{i}");
  h1dPlot->GetYaxis()->SetRangeUser(0.525, 0.585);
  h1dPlot->Draw("HIST");
  h1dPee_K40->SetLineColor(kRed);
  h1dPee_K40->Draw("HIST;same");
  h1dPee_Th232->SetLineColor(kGreen);
  h1dPee_Th232->Draw("HIST;same");
  h1dPee_U238->SetLineColor(kBlue);
  h1dPee_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dPee.png");

  tfNeutrinoGrid->cd();
  ttNeutrinoGrid->Write();
  h1dNeutrinoNoOsc_K40->Write();
  h1dNeutrinoOsc_K40->Write();
  h1dAntiNeutrinoNoOsc_K40->Write();
  h1dAntiNeutrinoOsc_K40->Write();
  h1dAntiNeutrinoNoOsc_Th232->Write();
  h1dAntiNeutrinoOsc_Th232->Write();
  h1dAntiNeutrinoNoOsc_U238->Write();
  h1dAntiNeutrinoOsc_U238->Write();
  h1dPee_K40->Write();
  h1dPee_Th232->Write();
  h1dPee_U238->Write();
  tfNeutrinoGrid->Close();

  tfFineCrust1->Close();
  tfDecay_K40->Close();
  tfDecay_Th232->Close();
  tfDecay_U238->Close();

  std::cout << "K40 TNU  :" << TNUTotal_K40 << "  " << TNUCrust_K40 << "  "
            << TNUMantle_K40 << std::endl;
  std::cout << "Th232 TNU:" << TNUTotal_Th232 << "  " << TNUCrust_Th232 << "  "
            << TNUMantle_Th232 << std::endl;
  std::cout << "U238 TNU :" << TNUTotal_U238 << "  " << TNUCrust_U238 << "  "
            << TNUMantle_U238 << std::endl;
  std::cout << "Near Grid TNU:" << std::endl;
  for (int pp = 0; pp < 7; ++pp) {
    for (int qq = 0; qq < 7; ++qq) {
      std::cout << TNU_Grid[pp * 7 + qq] << "  ";
    }
    std::cout << std::endl;
  }

  return 0;
}
