#include <iostream>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/CrossSection.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/VectorAnalysis.h"
#include "../Common/include/jinpingStyle.h"

int main() {

  TRandom *rnd = new TRandom(1);

  const double Exposion =
      1.5e5 * Unit::ton * Unit::yr / Unit::g / 2.0 * Unit::mol * Const::Na;

  TFile *tfCalculateGeoNeutrinoFlux =
      new TFile("../GeoNeutrino/data_out/CalculateNeutrinoFlux.root", "read");

  TH3D *h3dNeutrinoE_K40 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dNeutrinoE_K40");
  TH3D *h3dNeutrinoX_K40 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dNeutrinoX_K40");
  TH3D *h3dAntiNeutrinoE_K40 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoE_K40");
  TH3D *h3dAntiNeutrinoX_K40 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoX_K40");
  TH3D *h3dAntiNeutrinoE_Th232 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoE_Th232");
  TH3D *h3dAntiNeutrinoX_Th232 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoX_Th232");
  TH3D *h3dAntiNeutrinoE_U238 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoE_U238");
  TH3D *h3dAntiNeutrinoX_U238 =
      (TH3D *)tfCalculateGeoNeutrinoFlux->Get("h3dAntiNeutrinoX_U238");

  double E_nu, T_e, Theta, Phi;

  TH1D *h1dTCSNeutrinoE =
      new TH1D("h1dTCSNeutrinoE", "", 1000, 0.0, 5.0 * Unit::MeV);
  TH1D *h1dTCSNeutrinoX =
      new TH1D("h1dTCSNeutrinoX", "", 1000, 0.0, 5.0 * Unit::MeV);
  TH1D *h1dTCSAntiNeutrinoE =
      new TH1D("h1dTCSAntiNeutrinoE", "", 1000, 0.0, 5.0 * Unit::MeV);
  TH1D *h1dTCSAntiNeutrinoX =
      new TH1D("h1dTCSAntiNeutrinoX", "", 1000, 0.0, 5.0 * Unit::MeV);

  TH1D *h1dDCSNeutrinoE[1000] = {nullptr};
  TH1D *h1dDCSNeutrinoX[1000] = {nullptr};
  TH1D *h1dDCSAntiNeutrinoE[1000] = {nullptr};
  TH1D *h1dDCSAntiNeutrinoX[1000] = {nullptr};
  Vector3D *Direction_Neutrino = new Vector3D();
  Vector3D *Direction_Electron = nullptr;

  double EE;

  TFile *tfGeoSignal = new TFile("./data_out/GeoSignal.root", "recreate");

  TTree *ttNeutrinoE_K40 = new TTree("NeutrinoE_K40", "");
  ttNeutrinoE_K40->Branch("Theta", &Theta, "Theta/D");
  ttNeutrinoE_K40->Branch("Phi", &Phi, "Phi/D");
  ttNeutrinoE_K40->Branch("E", &T_e, "E/D");
  TTree *ttNeutrinoX_K40 = new TTree("NeutrinoX_K40", "");
  ttNeutrinoX_K40->Branch("Theta", &Theta, "Theta/D");
  ttNeutrinoX_K40->Branch("Phi", &Phi, "Phi/D");
  ttNeutrinoX_K40->Branch("E", &T_e, "E/D");

  TTree *ttAntiNeutrinoE_K40 = new TTree("AntiNeutrinoE_K40", "");
  ttAntiNeutrinoE_K40->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoE_K40->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoE_K40->Branch("E", &T_e, "E/D");
  TTree *ttAntiNeutrinoX_K40 = new TTree("AntiNeutrinoX_K40", "");
  ttAntiNeutrinoX_K40->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoX_K40->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoX_K40->Branch("E", &T_e, "E/D");

  TTree *ttAntiNeutrinoE_Th232 = new TTree("AntiNeutrinoE_Th232", "");
  ttAntiNeutrinoE_Th232->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoE_Th232->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoE_Th232->Branch("E", &T_e, "E/D");
  TTree *ttAntiNeutrinoX_Th232 = new TTree("AntiNeutrinoX_Th232", "");
  ttAntiNeutrinoX_Th232->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoX_Th232->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoX_Th232->Branch("E", &T_e, "E/D");

  TTree *ttAntiNeutrinoE_U238 = new TTree("AntiNeutrinoE_U238", "");
  ttAntiNeutrinoE_U238->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoE_U238->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoE_U238->Branch("E", &T_e, "E/D");
  TTree *ttAntiNeutrinoX_U238 = new TTree("AntiNeutrinoX_U238", "");
  ttAntiNeutrinoX_U238->Branch("Theta", &Theta, "Theta/D");
  ttAntiNeutrinoX_U238->Branch("Phi", &Phi, "Phi/D");
  ttAntiNeutrinoX_U238->Branch("E", &T_e, "E/D");

  double binwidth = 5.0 * Unit::keV;

  for (int m = 0; m < 1000; ++m) {
    std::cout << "Processing " << m << "/1000" << std::endl;

    E_nu = h3dNeutrinoE_K40->GetZaxis()->GetBinCenter(m + 1);
    h1dDCSNeutrinoE[m] = new TH1D(TString::Format("h1dDCSNeutrinoE_%04d", m),
                                  "", 1000, 0.0, 5.0 * Unit::MeV);
    h1dDCSNeutrinoX[m] = new TH1D(TString::Format("h1dDCSNeutrinoX_%04d", m),
                                  "", 1000, 0.0, 5.0 * Unit::MeV);
    h1dDCSAntiNeutrinoE[m] =
        new TH1D(TString::Format("h1dDCSAntiNeutrinoE_%04d", m), "", 1000, 0.0,
                 5.0 * Unit::MeV);
    h1dDCSAntiNeutrinoX[m] =
        new TH1D(TString::Format("h1dDCSAntiNeutrinoX_%04d", m), "", 1000, 0.0,
                 5.0 * Unit::MeV);

    for (int mm = 0; mm < 1000; ++mm) {
      EE = h1dDCSNeutrinoE[m]->GetXaxis()->GetBinCenter(mm + 1);
      h1dDCSNeutrinoE[m]->SetBinContent(mm + 1,
                                        CrossSection::DCS_Scat_NuE(E_nu, EE));
      h1dDCSNeutrinoX[m]->SetBinContent(mm + 1,
                                        CrossSection::DCS_Scat_NuX(E_nu, EE));
      h1dDCSAntiNeutrinoE[m]->SetBinContent(
          mm + 1, CrossSection::DCS_Scat_AntiNuE(E_nu, EE));
      h1dDCSAntiNeutrinoX[m]->SetBinContent(
          mm + 1, CrossSection::DCS_Scat_AntiNuX(E_nu, EE));
    }

    h1dTCSNeutrinoE->SetBinContent(
        m + 1, h1dDCSNeutrinoE[m]->Integral(1, 1000) * binwidth);
    h1dTCSNeutrinoX->SetBinContent(
        m + 1, h1dDCSNeutrinoX[m]->Integral(1, 1000) * binwidth);
    h1dTCSAntiNeutrinoE->SetBinContent(
        m + 1, h1dDCSAntiNeutrinoE[m]->Integral(1, 1000) * binwidth);
    h1dTCSAntiNeutrinoX->SetBinContent(
        m + 1, h1dDCSAntiNeutrinoX[m]->Integral(1, 1000) * binwidth);
  }

  double flux, tcs, theta, phi, ttheta, pphi, lambda;
  int n;

  for (int m = 0; m < 1000; ++m) {
    E_nu = h3dNeutrinoE_K40->GetZaxis()->GetBinCenter(m + 1);
    for (int i = 0; i < 100; ++i) {
      theta = acos(h3dNeutrinoE_K40->GetXaxis()->GetBinCenter(i + 1));
      for (int j = 0; j < 100; ++j) {
        phi = h3dNeutrinoE_K40->GetYaxis()->GetBinCenter(j + 1);
        Direction_Neutrino->SetPolar(1.0, theta, phi);

        // NeutrinoE_K40
        tcs = h1dTCSNeutrinoE->GetBinContent(m + 1);
        flux = h3dNeutrinoE_K40->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSNeutrinoE[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttNeutrinoE_K40->Fill();
        }

        // NeutrinoX_K40
        tcs = h1dTCSNeutrinoX->GetBinContent(m + 1);
        flux = h3dNeutrinoX_K40->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSNeutrinoX[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttNeutrinoX_K40->Fill();
        }

        // AntiNeutrinoE_K40
        tcs = h1dTCSAntiNeutrinoE->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoE_K40->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoE[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoE_K40->Fill();
        }

        // AntiNeutrinoX_K40
        tcs = h1dTCSAntiNeutrinoX->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoX_K40->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoX[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoX_K40->Fill();
        }

        // AntiNeutrinoE_Th232
        tcs = h1dTCSAntiNeutrinoE->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoE_Th232->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoE[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoE_Th232->Fill();
        }

        // AntiNeutrinoX_Th232
        tcs = h1dTCSAntiNeutrinoX->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoX_Th232->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoX[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoX_Th232->Fill();
        }

        // AntiNeutrinoE_U238
        tcs = h1dTCSAntiNeutrinoE->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoE_U238->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoE[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoE_U238->Fill();
        }

        // AntiNeutrinoX_U238
        tcs = h1dTCSAntiNeutrinoX->GetBinContent(m + 1);
        flux = h3dAntiNeutrinoX_U238->GetBinContent(i, j, m);
        lambda = flux * tcs * binwidth * Exposion;
        n = rnd->Poisson(lambda);

        for (int k = 0; k < n; ++k) {
          ttheta = CrossSection::Theta_Scat(E_nu, T_e);
          pphi = rnd->Uniform(-Const::pi, Const::pi);
          delete Direction_Electron;
          Direction_Electron = Direction_Neutrino->RotateGenerate(ttheta, pphi);

          T_e = h1dDCSAntiNeutrinoX[m]->GetRandom(rnd);
          Theta = Direction_Electron->GetTheta();
          Phi = Direction_Electron->GetPhi();

          ttAntiNeutrinoX_U238->Fill();
        }
      }
    }
  }

  tfGeoSignal->cd();
  ttNeutrinoE_K40->Write();
  ttNeutrinoX_K40->Write();
  ttAntiNeutrinoE_K40->Write();
  ttAntiNeutrinoX_K40->Write();
  ttAntiNeutrinoE_Th232->Write();
  ttAntiNeutrinoX_Th232->Write();
  ttAntiNeutrinoE_U238->Write();
  ttAntiNeutrinoX_U238->Write();
  tfGeoSignal->Close();
  tfCalculateGeoNeutrinoFlux->Close();

  return 0;
}
