#include <iostream>

#include "../Common/include/Const.h"
#include "../Common/include/CrossSection.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  jinpingStyle();

  TCanvas *cv = new TCanvas("cv", "", 700, 500);

  double E;

  TH1D *h1dCS_AntiNuE_1MeV = new TH1D("h1dCS_AntiNuE_1MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_AntiNuX_1MeV = new TH1D("h1dCS_AntiNuX_1MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_NuE_1MeV = new TH1D("h1dCS_NuE_1MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_NuX_1MeV = new TH1D("h1dCS_NuX_1MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_AntiNuE_2MeV = new TH1D("h1dCS_AntiNuE_2MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_AntiNuX_2MeV = new TH1D("h1dCS_AntiNuX_2MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_NuE_2MeV = new TH1D("h1dCS_NuE_2MeV", "", 200, 0.0, 2.0);
  TH1D *h1dCS_NuX_2MeV = new TH1D("h1dCS_NuX_2MeV", "", 200, 0.0, 2.0);

  for (int m = 0; m < 200; ++m) {

    E = h1dCS_NuE_1MeV->GetBinCenter(m + 1);
    h1dCS_NuE_1MeV->SetBinContent(m + 1, CrossSection::DCS_Scat_NuE(1.0, E) /
                                             (cm2 / MeV));

    E = h1dCS_NuX_1MeV->GetBinCenter(m + 1);
    h1dCS_NuX_1MeV->SetBinContent(m + 1, CrossSection::DCS_Scat_NuX(1.0, E) /
                                             (cm2 / MeV));

    E = h1dCS_AntiNuE_1MeV->GetBinCenter(m + 1);
    h1dCS_AntiNuE_1MeV->SetBinContent(
        m + 1, CrossSection::DCS_Scat_AntiNuE(1.0, E) / (cm2 / MeV));

    E = h1dCS_AntiNuX_1MeV->GetBinCenter(m + 1);
    h1dCS_AntiNuX_1MeV->SetBinContent(
        m + 1, CrossSection::DCS_Scat_AntiNuX(1.0, E) / (cm2 / MeV));

    E = h1dCS_NuE_2MeV->GetBinCenter(m + 1);
    h1dCS_NuE_2MeV->SetBinContent(m + 1, CrossSection::DCS_Scat_NuE(2.0, E) /
                                             (cm2 / MeV));

    E = h1dCS_NuX_2MeV->GetBinCenter(m + 1);
    h1dCS_NuX_2MeV->SetBinContent(m + 1, CrossSection::DCS_Scat_NuX(2.0, E) /
                                             (cm2 / MeV));

    E = h1dCS_AntiNuE_2MeV->GetBinCenter(m + 1);
    h1dCS_AntiNuE_2MeV->SetBinContent(
        m + 1, CrossSection::DCS_Scat_AntiNuE(2.0, E) / (cm2 / MeV));

    E = h1dCS_AntiNuX_2MeV->GetBinCenter(m + 1);
    h1dCS_AntiNuX_2MeV->SetBinContent(
        m + 1, CrossSection::DCS_Scat_AntiNuX(2.0, E) / (cm2 / MeV));
  }

  TH1D *h1dPlot = new TH1D("h1dPlot", "", 200, 0.0, 2.0);
  h1dPlot->GetXaxis()->SetTitle("ElectronKineticEnergy [MeV]");
  h1dPlot->GetXaxis()->SetRangeUser(0.0, 2.0);
  h1dPlot->GetYaxis()->SetTitle("CrossSection [cm^{2}MeV^{-1}]");
  h1dPlot->GetYaxis()->SetRangeUser(0.0, 14.0e-45);

  h1dCS_AntiNuE_1MeV->SetLineColor(kRed);
  h1dCS_AntiNuE_1MeV->SetLineStyle(1);
  h1dCS_AntiNuX_1MeV->SetLineColor(kGreen);
  h1dCS_AntiNuX_1MeV->SetLineStyle(1);
  h1dCS_NuE_1MeV->SetLineColor(kBlue);
  h1dCS_NuE_1MeV->SetLineStyle(1);
  h1dCS_NuX_1MeV->SetLineColor(kPink);
  h1dCS_NuX_1MeV->SetLineStyle(1);
  h1dCS_AntiNuE_2MeV->SetLineColor(kRed);
  h1dCS_AntiNuE_2MeV->SetLineStyle(3);
  h1dCS_AntiNuX_2MeV->SetLineColor(kGreen);
  h1dCS_AntiNuX_2MeV->SetLineStyle(3);
  h1dCS_NuE_2MeV->SetLineColor(kBlue);
  h1dCS_NuE_2MeV->SetLineStyle(3);
  h1dCS_NuX_2MeV->SetLineColor(kMagenta);
  h1dCS_NuX_2MeV->SetLineStyle(3);
  TLegend *tl = new TLegend(0.5, 0.7, 0.8, 0.9);
  tl->SetNColumns(2);
  tl->AddEntry(h1dCS_AntiNuE_1MeV, "#bar{#nu}_{e} 1MeV", "l");
  tl->AddEntry(h1dCS_AntiNuX_1MeV, "#bar{#nu}_{#mu,#tau} 1MeV", "l");
  tl->AddEntry(h1dCS_NuE_1MeV, "#nu_{e} 1MeV", "l");
  tl->AddEntry(h1dCS_NuX_1MeV, "#nu_{#mu,#tau} 1MeV", "l");
  tl->AddEntry(h1dCS_AntiNuE_2MeV, "#bar{#nu}_{e} 2MeV", "l");
  tl->AddEntry(h1dCS_AntiNuX_2MeV, "#bar{#nu}_{#mu,#tau} 2MeV", "l");
  tl->AddEntry(h1dCS_NuE_2MeV, "#nu_{e} 2MeV", "l");
  tl->AddEntry(h1dCS_NuX_2MeV, "#nu_{#mu,#tau} 2MeV", "l");

  h1dPlot->Draw("HIST");
  h1dCS_AntiNuE_1MeV->Draw("same");
  h1dCS_AntiNuX_1MeV->Draw("same");
  h1dCS_NuE_1MeV->Draw("same");
  h1dCS_NuX_1MeV->Draw("same");
  h1dCS_AntiNuE_2MeV->Draw("same");
  h1dCS_AntiNuX_2MeV->Draw("same");
  h1dCS_NuE_2MeV->Draw("same");
  h1dCS_NuX_2MeV->Draw("same");
  tl->Draw("same");
  cv->SaveAs("./data_out/h1dDCS.png");

  return 0;
}
