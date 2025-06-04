#ifndef _SOLARNEUTRINOAPECTRUM_H_
#define _SOLARNEUTRINOAPECTRUM_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Common/include/ConstandUnit.h"

class SolarNeutrinoSpectrum {
public:
  SolarNeutrinoSpectrum();
  ~SolarNeutrinoSpectrum();

  double Spectrum_B8(double E) const;
  double Spectrum_Be7(double E) const;

private:
  std::vector<std::vector<double>> B8;
  std::vector<std::vector<double>> Be7;
};

#endif
