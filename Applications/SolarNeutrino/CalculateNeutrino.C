#include <iostream>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingStyle.h"

#include "SolarModel.h"
#include "SolarNeutrinoFlux.h"

int main() {

  const int Nbins = 200000;
  const int NRebins = 10.0;
  const double Emin = 0.0;
  const double Emax = 20.0;
  const double DrawXmin = 0.1;
  const double DrawXmax = 20.0;
  const double DrawYmin = 1.0e-9;
  const double DrawYmax = 1.0e3;

  jinpingStyle();

  SolarNeutrinoFlux *snf = new SolarNeutrinoFlux();
  SolarModel *sm = new SolarModel();
  TCanvas *cv = new TCanvas("cv", "", 700, 500);
  cv->SetLogx(1);
  cv->SetLogy(1);

  TH1D *h1dPlot = new TH1D("h1dPlot", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_Be7 =
      new TH1D("h1dNeutrinoNoOsc_Be7", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_B8 =
      new TH1D("h1dNeutrinoNoOsc_B8", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_N13 =
      new TH1D("h1dNeutrinoNoOsc_N13", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_O15 =
      new TH1D("h1dNeutrinoNoOsc_O15", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_F17 =
      new TH1D("h1dNeutrinoNoOsc_F17", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_pp =
      new TH1D("h1dNeutrinoNoOsc_pp", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoNoOsc_hep =
      new TH1D("h1dNeutrinoNoOsc_hep", "", Nbins, Emin, Emax);

  TH1D *h1dNeutrinoOsc_Be7 =
      new TH1D("h1dNeutrinoOsc_Be7", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_B8 =
      new TH1D("h1dNeutrinoOsc_B8", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_N13 =
      new TH1D("h1dNeutrinoOsc_N13", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_O15 =
      new TH1D("h1dNeutrinoOsc_O15", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_F17 =
      new TH1D("h1dNeutrinoOsc_F17", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_pp =
      new TH1D("h1dNeutrinoOsc_pp", "", Nbins, Emin, Emax);
  TH1D *h1dNeutrinoOsc_hep =
      new TH1D("h1dNeutrinoOsc_hep", "", Nbins, Emin, Emax);

  for (int i = 0; i < Nbins; ++i) {
    double E = h1dPlot->GetBinCenter(i + 1) * Unit::MeV;

    h1dNeutrinoNoOsc_Be7->Fill(E / Unit::MeV,
                               snf->Neutrino_Be7(E) /
                                   (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoOsc_Be7->Fill(E / Unit::MeV,
                             snf->Neutrino_Be7(E) * sm->Pee_Be7(E) /
                                 (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_B8->Fill(E / Unit::MeV,
                              snf->Neutrino_B8(E) /
                                  (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_N13->Fill(E / Unit::MeV,
                               snf->Neutrino_N13(E) /
                                   (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_O15->Fill(E / Unit::MeV,
                               snf->Neutrino_O15(E) /
                                   (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_F17->Fill(E / Unit::MeV,
                               snf->Neutrino_F17(E) /
                                   (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_pp->Fill(E / Unit::MeV,
                              snf->Neutrino_pp(E) /
                                  (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
    h1dNeutrinoNoOsc_hep->Fill(E / Unit::MeV,
                               snf->Neutrino_hep(E) /
                                   (1.0e10 / Unit::MeV / Unit::s / Unit::cm2));
  }

  h1dPlot->Rebin(NRebins);
  h1dNeutrinoNoOsc_Be7->Rebin(NRebins);
  h1dNeutrinoNoOsc_B8->Rebin(NRebins);
  h1dNeutrinoNoOsc_N13->Rebin(NRebins);
  h1dNeutrinoNoOsc_O15->Rebin(NRebins);
  h1dNeutrinoNoOsc_F17->Rebin(NRebins);
  h1dNeutrinoNoOsc_pp->Rebin(NRebins);
  h1dNeutrinoNoOsc_hep->Rebin(NRebins);

  h1dPlot->GetXaxis()->SetRangeUser(DrawXmin, DrawXmax);
  h1dPlot->GetYaxis()->SetRangeUser(DrawYmin, DrawYmax);
  h1dPlot->Draw("HIST");
  h1dNeutrinoNoOsc_Be7->SetLineStyle(1);
  h1dNeutrinoNoOsc_Be7->SetLineColor(kBlue);
  h1dNeutrinoNoOsc_Be7->Draw("HIST;same");
  h1dNeutrinoNoOsc_B8->SetLineStyle(1);
  h1dNeutrinoNoOsc_B8->SetLineColor(kGreen);
  h1dNeutrinoNoOsc_B8->Draw("HIST;same");
  h1dNeutrinoNoOsc_N13->SetLineStyle(1);
  h1dNeutrinoNoOsc_N13->SetLineColor(kRed);
  h1dNeutrinoNoOsc_N13->Draw("HIST;same");
  h1dNeutrinoNoOsc_O15->SetLineStyle(1);
  h1dNeutrinoNoOsc_O15->SetLineColor(kMagenta);
  h1dNeutrinoNoOsc_O15->Draw("HIST;same");
  h1dNeutrinoNoOsc_F17->SetLineStyle(3);
  h1dNeutrinoNoOsc_F17->SetLineColor(kBlue);
  h1dNeutrinoNoOsc_F17->Draw("HIST;same");
  h1dNeutrinoNoOsc_pp->SetLineStyle(3);
  h1dNeutrinoNoOsc_pp->SetLineColor(kGreen);
  h1dNeutrinoNoOsc_pp->Draw("HIST;same");
  h1dNeutrinoNoOsc_hep->SetLineStyle(3);
  h1dNeutrinoNoOsc_hep->SetLineColor(kRed);
  h1dNeutrinoNoOsc_hep->Draw("HIST;same");
  cv->SaveAs("./data_out/h1dNeutrinoNoOsc.png");

  return 0;
}
