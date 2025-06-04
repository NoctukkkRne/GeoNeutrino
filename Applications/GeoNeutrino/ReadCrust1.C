#define FineCrust1

#include <fstream>
#include <iostream>
#include <string>

#include "../Common/include/ConstandUnit.h"
#include "../Common/include/Rootneed.h"
#include "../Common/include/jinpingLocation.h"

int main() {
#ifdef FineCrust1
  std::cout << "Defined FineCrust1." << std::endl;
#endif

  const double jinpingX = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          cos(jinpingLocation::Phi);
  const double jinpingY = jinpingLocation::R * sin(jinpingLocation::Theta) *
                          sin(jinpingLocation::Phi);
  const double jinpingZ = jinpingLocation::R * cos(jinpingLocation::Theta);

  const double radius = 6371.0 * Unit::km;
  const double depthofCLM = 175.0 * Unit::km;
  const double rofEM = 6371.0 * Unit::km - 2891.0 * Unit::km;
  const double rofDM = rofEM + 710.0 * Unit::km;
  const double rhoofCLM = 4.66 * Unit::g / Unit::cm3;
  const double rhoofDM = 5.39 * Unit::g / Unit::cm3;
  const double rhoofEM = 5.39 * Unit::g / Unit::cm3;

#ifdef FineCrust1
  TFile *tf = new TFile("./data_out/FineCrust1.root", "recreate");
#else
  TFile *tf = new TFile("./data_out/Crust1.root", "recreate");
#endif
  TTree *ttEarthGrid = new TTree("EarthGrid", "");

  double R, Theta, Phi, D, r, theta, phi, d, rr, ttheta, pphi, dd, x, y, z, xx,
      yy, zz, Rho, vv, mm, L;
  int Type;
  // 0-OCWater 1-OCIce
  // 2-OCUpperSed 3-OCMiddleSed 4-OCLowerSed
  // 5-OCUpperCrust 6-OCMiddleCrust 7-OCLowerCrust
  // 8-CCWater 9-CCIce
  // 10-CCUpperSed 11-CCMiddleSed 12-CCLowerSed
  // 13-CCUpperCrust 14-CCMiddleCrust 15-CCLowerCrust
  // 16-CLM 17-DM 18-EM
  ttEarthGrid->Branch("R", &rr, "R/D");
  ttEarthGrid->Branch("Theta", &ttheta, "Theta/D");
  ttEarthGrid->Branch("Phi", &pphi, "Phi/D");
  ttEarthGrid->Branch("X", &xx, "X/D");
  ttEarthGrid->Branch("Y", &yy, "Y/D");
  ttEarthGrid->Branch("Z", &zz, "Z/D");
  ttEarthGrid->Branch("Rho", &Rho, "Rho/D");
  ttEarthGrid->Branch("V", &vv, "V/D");
  ttEarthGrid->Branch("M", &mm, "M/D");
  ttEarthGrid->Branch("Type", &Type, "Type/I");

  double dens[11];
  double bnd[12];
  std::string typ;

  std::ifstream inFile_Rho("./data_in/crust1.rho");
  std::ifstream inFile_Bnds("./data_in/crust1.bnds");
  std::ifstream inFile_Type("./data_in/CNtype1-1.txt");

  for (int i = 0; i < 180; ++i) {
    for (int j = 0; j < 360; ++j) {
      std::cout << "Loading, " << i * 360 + j << " / 64800" << std::endl;

      inFile_Type >> typ;
      for (int k = 0; k < 9; ++k) {
        inFile_Bnds >> bnd[k];
        bnd[k] *= Unit::km;
        inFile_Rho >> dens[k];
        dens[k] *= (Unit::g / Unit::cm3);
      }

      if (typ == "A1" || typ == "A0" || typ == "B-") { // Ocean
        bnd[9] = bnd[8] - 0.0;
        bnd[10] = rofDM - radius;
        bnd[11] = rofEM - radius;

        dens[8] = rhoofCLM;
        dens[9] = rhoofDM;
        dens[10] = rhoofEM;
      } else { // Land
        bnd[9] = bnd[8] - depthofCLM;
        bnd[10] = rofDM - radius;
        bnd[11] = rofEM - radius;

        dens[8] = rhoofCLM;
        dens[9] = rhoofDM;
        dens[10] = rhoofEM;
      }

      for (int k = 0; k < 11; ++k) {
        R = ((radius + bnd[k]) + (radius + bnd[k + 1])) / 2.0;
        D = (radius + bnd[k]) - (radius + bnd[k + 1]);
        Theta = (i + 0.5) * Unit::deg;
        Phi = (-179.5 + j) * Unit::deg;
        Rho = dens[k];

        if (k >= 8) { // CLM DM EM
          Type = k + 8;
        } else if (typ == "A1" || typ == "A0" || typ == "B-") { // Ocean
          Type = k;
        } else { // Land
          Type = k + 8;
        }

#ifdef FineCrust1                                             // Fine divided
        if ((i >= 58 && i <= 64) && (j >= 278 && j <= 284)) { // Near Jinping
          d = D / 10.0;
          for (int ii = 0; ii < 10; ++ii) {
            r = R + d * (ii - 4.5);
            for (int jj = 0; jj < 10; ++jj) {
              theta = Theta + 0.1 * Unit::deg * (jj - 4.5);
              for (int kk = 0; kk < 10; ++kk) {
                phi = Phi + 0.1 * Unit::deg * (kk - 4.5);

                x = r * sin(theta) * cos(phi);
                y = r * sin(theta) * sin(phi);
                z = r * cos(theta);

                L = sqrt(pow(x - jinpingX, 2) + pow(y - jinpingY, 2) +
                         pow(z - jinpingZ, 2));
                if (L < 30.0 * Unit::km) { // More fine divided
                  dd = d / 10.0;
                  for (int iii = 0; iii < 10; ++iii) {
                    rr = r + dd * (iii - 4.5);
                    for (int jjj = 0; jjj < 10; ++jjj) {
                      ttheta = theta + 0.01 * Unit::deg * (jjj - 4.5);
                      for (int kkk = 0; kkk < 10; ++kkk) {
                        pphi = phi + 0.01 * Unit::deg * (kkk - 4.5);

                        xx = rr * sin(ttheta) * cos(pphi);
                        yy = rr * sin(ttheta) * sin(pphi);
                        zz = rr * cos(ttheta);

                        vv = 1.0 / 3.0 *
                             (pow(rr + dd / 2.0, 3) - pow(rr - dd / 2.0, 3)) *
                             (cos(ttheta - 0.005 * Unit::deg) -
                              cos(ttheta + 0.005 * Unit::deg)) *
                             0.01 * Unit::deg;
                        mm = vv * Rho;

                        ttEarthGrid->Fill();
                      }
                    }
                  }
                  continue;
                }

                rr = r;
                ttheta = theta;
                pphi = phi;
                dd = d;
                xx = rr * sin(ttheta) * cos(pphi);
                yy = rr * sin(ttheta) * sin(pphi);
                zz = rr * cos(ttheta);
                vv = 1.0 / 3.0 *
                     (pow(rr + dd / 2.0, 3) - pow(rr - dd / 2.0, 3)) *
                     (cos(ttheta - 0.05 * Unit::deg) -
                      cos(ttheta + 0.05 * Unit::deg)) *
                     0.1 * Unit::deg;
                mm = vv * Rho;

                ttEarthGrid->Fill();
              }
            }
          }
          continue;
        }
#endif
        rr = R;
        ttheta = Theta;
        pphi = Phi;
        dd = D;
        xx = rr * sin(ttheta) * cos(pphi);
        yy = rr * sin(ttheta) * sin(pphi);
        zz = rr * cos(ttheta);
        vv = 1.0 / 3.0 * (pow(rr + dd / 2.0, 3) - pow(rr - dd / 2.0, 3)) *
             (cos(ttheta - 0.5 * Unit::deg) - cos(ttheta + 0.5 * Unit::deg)) *
             1.0 * Unit::deg;
        mm = vv * Rho;

        ttEarthGrid->Fill();
      }
    }
  }

  ttEarthGrid->Write();
  tf->Close();

  return 0;
}
