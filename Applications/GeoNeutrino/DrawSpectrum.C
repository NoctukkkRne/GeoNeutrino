#include <iostream>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

#include "GeoNeutrinoSpectrum.h"

int main() {

  jinpingStyle();

  GeoNeutrinoSpectrum *gns = new GeoNeutrinoSpectrum();

  TCanvas *cv = new TCanvas("cv", "", 700, 500);
  cv->SetLogx(0);
  cv->SetLogy(1);

  TH1D *h1dPlot = new TH1D("h1dPlot", "", 5000, 0.0, 5.0);
  h1dPlot->GetXaxis()->SetTitle("NeutrinoEnergy [MeV]");
  h1dPlot->GetXaxis()->SetRangeUser(0.2, 3.7);
  h1dPlot->GetYaxis()->SetTitle("NeutrinoNumber [MeV^{-1}decay^{-1}]");
  h1dPlot->GetYaxis()->SetRangeUser(1.0e-2, 2.0e1);
  h1dPlot->Draw();

  double E;

  TH1D *h1dNeutrino_K40 = new TH1D("h1dNeutrino_K40", "", 5000, 0.0, 5.0);
  TH1D *h1dAntiNeutrino_K40 =
      new TH1D("h1dAntiNeutrino_K40", "", 5000, 0.0, 5.0);
  TH1D *h1dAntiNeutrino_Th232 =
      new TH1D("h1dAntiNeutrino_Th232", "", 5000, 0.0, 5.0);
  TH1D *h1dAntiNeutrino_U238 =
      new TH1D("h1dAntiNeutrino_U238", "", 5000, 0.0, 5.0);
  for (int i = 0; i < 5000; ++i) {
    E = (0.001 * i + 0.0005) * Unit::MeV;
    h1dNeutrino_K40->SetBinContent(i + 1,
                                   gns->Neutrino_K40(E) / (1.0 / Unit::MeV));
    h1dAntiNeutrino_K40->SetBinContent(i + 1, gns->AntiNeutrino_K40(E) /
                                                  (1.0 / Unit::MeV));
    h1dAntiNeutrino_Th232->SetBinContent(i + 1, gns->AntiNeutrino_Th232(E) /
                                                    (1.0 / Unit::MeV));
    h1dAntiNeutrino_U238->SetBinContent(i + 1, gns->AntiNeutrino_U238(E) /
                                                   (1.0 / Unit::MeV));
  }
  h1dNeutrino_K40->Draw("HIST;same");
  h1dAntiNeutrino_K40->Draw("HIST;same");
  h1dAntiNeutrino_Th232->Draw("HIST;same");
  h1dAntiNeutrino_U238->Draw("HIST;same");

  cv->SaveAs("./data_out/NeutrinoSpectrum.png");

  return 0;
}
