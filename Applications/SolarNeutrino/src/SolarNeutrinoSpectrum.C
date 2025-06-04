#include "SolarNeutrinoSpectrum.h"

SolarNeutrinoSpectrum::SolarNeutrinoSpectrum() {
  std::ifstream inFile;
  std::vector<double> temp_E;
  std::vector<double> temp_N;
  std::string sline;
  std::istringstream isstream;
  double E, N;

  inFile.open("./data_in/B8.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_N.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> N;
    E *= Unit::MeV;
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  B8.emplace_back(temp_E);
  B8.emplace_back(temp_N);

  inFile.close();
}

SolarNeutrinoSpectrum::~SolarNeutrinoSpectrum() {}

double SolarNeutrinoSpectrum::Spectrum_B8(double E) const {
  double result;

  auto iter = std::lower_bound(B8[0].begin(), B8[0].end(), E);
  int id = iter - B8[0].begin();
  if (id == 0) {
    result = 0.0;
  } else {
    double x1 = B8[0][id - 1];
    double x2 = B8[0][id];
    double y1 = B8[1][id - 1];
    double y2 = B8[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}
