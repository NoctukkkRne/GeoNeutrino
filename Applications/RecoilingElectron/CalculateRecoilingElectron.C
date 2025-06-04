#include <iostream>

#include "../Common/include/CrossSection.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  jinpingStyle();

  TCanvas *cv = new TCanvas("cv", "", 700, 500);
  TH1D *h1dPolt = new TH1D("h1dPolt", "", 2000, 0.0, 20.0);
  h1dPolt->GetXaxis()->SetTitle("ElectronKineticEnergy [MeV]");
  h1dPolt->GetYaxis()->SetTitle("Rate [/100ton*day*MeV]");

  TFile *tfNeutrinoGrid =
      new TFile("../GeoNeutrino/data_out/CalculateNeutrinoGrid.root", "read");
  TH1D *h1dAntiNeutrinoOsc_K40 =
      (TH1D *)tfNeutrinoGrid->Get("h1dAntiNeutrinoOsc_K40");
  TH1D *h1dAntiNeutrinoOsc_Th232 =
      (TH1D *)tfNeutrinoGrid->Get("h1dAntiNeutrinoOsc_Th232");
  TH1D *h1dAntiNeutrinoOsc_U238 =
      (TH1D *)tfNeutrinoGrid->Get("h1dAntiNeutrinoOsc_U238");

  TFile *tfElectronSpectrum =
      new TFile("./data_out/CalculateRecoilingElectron.root", "recreate");
  TH1D *h1dElectron_K40 = new TH1D("h1dElectron_K40", "", 2000, 0.0, 20.0);
  TH1D *h1dElectron_Th232 = new TH1D("h1dElectron_Th232", "", 2000, 0.0, 20.0);
  TH1D *h1dElectron_U238 = new TH1D("h1dElectron_U238", "", 2000, 0.0, 20.0);

  double F, E_nu, E_e;

  for (int i = 0; i < 2000; ++i) {
    E_nu = h1dAntiNeutrinoOsc_K40->GetBinCenter(i + 1);
    F = h1dAntiNeutrinoOsc_K40->GetBinContent(i + 1);

    for (int j = 0; j < 2000; ++j) {
      E_e = h1dElectron_K40->GetBinCenter(j + 1);

      h1dElectron_K40->Fill(E_e, F * CrossSection::DCS_Scat_AntiNuE(E_nu, E_e) /
                                     100.0 * day * 100.0 * ton / g / 2.0 * na);
    }
  }
  for (int i = 0; i < 2000; ++i) {
    E_nu = h1dAntiNeutrinoOsc_Th232->GetBinCenter(i + 1);
    F = h1dAntiNeutrinoOsc_Th232->GetBinContent(i + 1);

    for (int j = 0; j < 2000; ++j) {
      E_e = h1dElectron_Th232->GetBinCenter(j + 1);

      h1dElectron_Th232->Fill(E_e,
                              F * CrossSection::DCS_Scat_AntiNuE(E_nu, E_e) /
                                  100.0 * day * 100.0 * ton / g / 2.0 * na);
    }
  }
  for (int i = 0; i < 2000; ++i) {
    E_nu = h1dAntiNeutrinoOsc_U238->GetBinCenter(i + 1);
    F = h1dAntiNeutrinoOsc_U238->GetBinContent(i + 1);

    for (int j = 0; j < 2000; ++j) {
      E_e = h1dElectron_U238->GetBinCenter(j + 1);

      h1dElectron_U238->Fill(E_e,
                             F * CrossSection::DCS_Scat_AntiNuE(E_nu, E_e) /
                                 100.0 * day * 100.0 * ton / g / 2.0 * na);
    }
  }

  tfElectronSpectrum->cd();
  h1dElectron_K40->Write();
  h1dElectron_Th232->Write();
  h1dElectron_U238->Write();

  cv->SetLogx(1);
  cv->SetLogy(1);
  h1dPolt->GetXaxis()->SetRangeUser(0.1, 20.0);
  h1dPolt->GetYaxis()->SetRangeUser(1.0e-4, 0.5);
  h1dPolt->Draw("HIST");
  h1dElectron_K40->SetLineColor(kRed);
  h1dElectron_K40->Draw("HIST;same");
  h1dElectron_Th232->SetLineColor(kGreen);
  h1dElectron_Th232->Draw("HIST;same");
  h1dElectron_U238->SetLineColor(kBlue);
  h1dElectron_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dElectron.png");

  tfElectronSpectrum->Close();
  tfNeutrinoGrid->Close();

  return 0;
}
