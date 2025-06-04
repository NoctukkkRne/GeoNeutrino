#include <iostream>

#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  jinpingStyle();

  TCanvas *cv = new TCanvas("cv", "", 700, 500);
  cv->SetLogx(0);
  cv->SetLogy(1);

  TH1D *h1dPlot = new TH1D("h1dPlot", "", 400, 0.0, 4.0);
  h1dPlot->GetXaxis()->SetTitle("NeutrinoEnergy [MeV]");
  h1dPlot->GetXaxis()->SetRangeUser(0.2, 3.7);
  h1dPlot->GetYaxis()->SetTitle("NeutrinoNumber [MeV^{-1}decay^{-1}]");
  h1dPlot->GetYaxis()->SetRangeUser(1.0e-2, 2.0e1);
  h1dPlot->Draw();

  TFile *tf_K40 = new TFile("./data_in/K40.root", "read");
  TH1D *h1dNeutrino_K40 = (TH1D *)tf_K40->Get("2");
  h1dNeutrino_K40->SetLineColor(kBlue);
  for (int i = 0; i < 100; ++i) {
    h1dNeutrino_K40->SetBinContent(
        i + 1, h1dNeutrino_K40->GetBinContent(i + 1) * 100 / 100);
  }
  h1dNeutrino_K40->Draw("HIST;same");

  TFile *tf_Th232 = new TFile("./data_in/Th232.root", "read");
  TH1D *h1dNeutrino_Th232 = (TH1D *)tf_Th232->Get("2");
  h1dNeutrino_Th232->SetLineColor(kGreen);
  for (int i = 0; i < 100; ++i) {
    h1dNeutrino_Th232->SetBinContent(
        i + 1, h1dNeutrino_Th232->GetBinContent(i + 1) * 100 / 100);
  }
  h1dNeutrino_Th232->Draw("HIST;same");

  TFile *tf_U238 = new TFile("./data_in/U238.root", "read");
  TH1D *h1dNeutrino_U238 = (TH1D *)tf_U238->Get("2");
  h1dNeutrino_U238->SetLineColor(kRed);
  for (int i = 0; i < 100; ++i) {
    h1dNeutrino_U238->SetBinContent(
        i + 1, h1dNeutrino_U238->GetBinContent(i + 1) * 100 / 100);
  }
  h1dNeutrino_U238->Draw("HIST;same");

  cv->SaveAs("./data_out/NeutrinoSpectrum.png");

  return 0;
}
