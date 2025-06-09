#include <iostream>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/NeutrinoOscillation.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  jinpingStyle();

  TCanvas *cv = new TCanvas("cv", "", 700, 500);

  double E;
  double N = pow(10.0, 2.011) * Const::Na * Unit::mol / Unit::cm3;

  TH1D *h1dPee = new TH1D("h1dPee", "", 200, 0.0, 20.0);
  for (int i = 0; i < 200; ++i) {

    E = h1dPee->GetBinCenter(i + 1) * Unit::MeV;
    h1dPee->SetBinContent(i + 1, NeutrinoOscillation::Pee_MSW(E, N, 0.0));
  }

  cv->SetLogx(1);
  cv->SetLogy(1);
  h1dPee->GetXaxis()->SetRangeUser(1.0, 20.0);
  h1dPee->GetYaxis()->SetRangeUser(0.1, 0.9);
  h1dPee->Draw("HIST");
  cv->SaveAs("./data_out/h1dPee.png");

  return 0;
}
