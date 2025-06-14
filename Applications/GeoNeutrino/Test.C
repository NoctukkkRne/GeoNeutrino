#include "../Common/include/ConstandUnit.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  jinpingStyle();

  TFile *tfCalculateNeutrinoFlux =
      new TFile("./data_out/CalculateNeutrinoFlux.root");
  TH3D *h3dAntiNeutrinoE_K40 =
      (TH3D *)tfCalculateNeutrinoFlux->Get("h3dAntiNeutrinoE_K40");
  TH3D *h3dAntiNeutrinoE_Th232 =
      (TH3D *)tfCalculateNeutrinoFlux->Get("h3dAntiNeutrinoE_Th232");
  TH3D *h3dAntiNeutrinoE_U238 =
      (TH3D *)tfCalculateNeutrinoFlux->Get("h3dAntiNeutrinoE_U238");

  TCanvas *cv = new TCanvas("cv", "", 700, 500);
  TH1D *h1dPlot = new TH1D("h1dPlot", "", 1000, 0.0, 20.0);
  TH1D *h1dAntiNeutrinoE_K40 =
      new TH1D("h1dAntiNeutrinoE_K40", "", 1000, 0.0, 5.0);
  TH1D *h1dAntiNeutrinoE_Th232 =
      new TH1D("h1dAntiNeutrinoE_Th232", "", 1000, 0.0, 5.0);
  TH1D *h1dAntiNeutrinoE_U238 =
      new TH1D("h1dAntiNeutrinoE_U238", "", 1000, 0.0, 5.0);

  double E, F;

  for (int m = 0; m < 1000; ++m) {
    E = h1dAntiNeutrinoE_K40->GetXaxis()->GetBinCenter(m + 1);
    for (int i = 0; i < 100; ++i) {
      for (int j = 0; j < 100; ++j) {
        F = h3dAntiNeutrinoE_K40->GetBinContent(i, j, m);
        h1dAntiNeutrinoE_K40->Fill(E,
                                   F / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
        F = h3dAntiNeutrinoE_Th232->GetBinContent(i, j, m);
        h1dAntiNeutrinoE_Th232->Fill(
            E, F / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
        F = h3dAntiNeutrinoE_U238->GetBinContent(i, j, m);
        h1dAntiNeutrinoE_U238->Fill(E,
                                    F / (1.0 / Unit::m2 / Unit::s / Unit::MeV));
      }
    }
  }

  cv->SetLogx(1);
  cv->SetLogy(1);
  h1dPlot->GetXaxis()->SetRangeUser(0.1, 20.0);
  h1dPlot->GetYaxis()->SetRangeUser(1.0e4, 1.0e12);
  h1dPlot->Draw();
  h1dAntiNeutrinoE_K40->Draw("HIST;same");
  h1dAntiNeutrinoE_Th232->Draw("HIST;same");
  h1dAntiNeutrinoE_U238->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dTest.png");

  return 0;
}
