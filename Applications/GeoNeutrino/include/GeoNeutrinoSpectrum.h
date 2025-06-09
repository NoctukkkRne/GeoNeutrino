#ifndef _GEONEUTRINOAPECTRUM_H_
#define _GEONEUTRINOAPECTRUM_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Common/include/ConstandUnit.h"

class GeoNeutrinoSpectrum {
public:
  GeoNeutrinoSpectrum();
  ~GeoNeutrinoSpectrum();

  double Neutrino_K40(double E) const;
  double AntiNeutrino_K40(double E) const;
  double AntiNeutrino_Th232(double E) const;
  double AntiNeutrino_U238(double E) const;

private:
  std::vector<std::vector<double>> K40;
  std::vector<std::vector<double>> Th232;
  std::vector<std::vector<double>> U238;
};

#endif
