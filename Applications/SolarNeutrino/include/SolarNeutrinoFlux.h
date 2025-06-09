#ifndef _SOLARNEUTRINOFLUX_H_
#define _SOLARNEUTRINOFLUX_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Common/include/ConstandUnit.h"

class SolarNeutrinoFlux {
public:
  SolarNeutrinoFlux();
  ~SolarNeutrinoFlux();

  double Neutrino_Be7(double E) const;
  double Neutrino_B8(double E) const;
  double Neutrino_N13(double E) const;
  double Neutrino_O15(double E) const;
  double Neutrino_F17(double E) const;
  double Neutrino_pp(double E) const;
  double Neutrino_hep(double E) const;

private:
  double flux_Be7;
  double flux_B8;
  double flux_N13;
  double flux_O15;
  double flux_F17;
  double flux_pp;
  double flux_hep;
  std::vector<std::vector<double>> Be7_862;
  std::vector<std::vector<double>> Be7_384;
  std::vector<std::vector<double>> B8;
  std::vector<std::vector<double>> N13;
  std::vector<std::vector<double>> O15;
  std::vector<std::vector<double>> F17;
  std::vector<std::vector<double>> pp;
  std::vector<std::vector<double>> hep;

  double Spectrum_Be7(double E) const;
  double Spectrum_B8(double E) const;
  double Spectrum_N13(double E) const;
  double Spectrum_O15(double E) const;
  double Spectrum_F17(double E) const;
  double Spectrum_pp(double E) const;
  double Spectrum_hep(double E) const;
};

#endif
