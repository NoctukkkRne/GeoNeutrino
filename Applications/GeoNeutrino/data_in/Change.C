#include <fstream>
#include <iostream>

int Change() {
  std::ofstream outFile;
  outFile.open("X.dat", std::ios::out);

  TFile *tf = new TFile("X.root", "read");
  TH1D *h1dNeutrino = (TH1D *)tf->Get("Neutrino");
  TH1D *h1dAntiNeutrino = (TH1D *)tf->Get("AntiNeutrino");

  outFile << 0.0 << "    " << 0.0 << "    " << 0.0 << std::endl;
  for (int i = 0; i < 500; ++i) {
    outFile << h1dNeutrino->GetXaxis()->GetBinCenter(i + 1) << "    ";
    outFile << h1dNeutrino->GetBinContent(i + 1) << "    ";
    outFile << h1dAntiNeutrino->GetBinContent(i + 1) << std::endl;
  }

  outFile.close();

  return 0;
}
