#include "SolarNeutrinoFlux.h"

SolarNeutrinoFlux::SolarNeutrinoFlux() {
  std::ifstream inFile;
  std::vector<double> temp_E;
  std::vector<double> temp_N;
  std::string sline;
  std::istringstream isstream;
  double E, N;

  // Be7
  flux_Be7 = 0.500 * 1.0e10 / Unit::s / Unit::cm2;
  // Be7_862
  inFile.open("./data_in/Be7_862.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_N.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> N;
    E = 861.3 * Unit::keV + E * Unit::keV;
    N = 0.897 * N * (1.0 / Unit::keV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  Be7_862.emplace_back(temp_E);
  Be7_862.emplace_back(temp_N);
  inFile.close();
  // Be7_384
  inFile.open("./data_in/Be7_384.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_N.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> N;
    E = 384.3 * Unit::keV + E * Unit::keV;
    N = 0.103 * N * (1.0 / Unit::keV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  Be7_384.emplace_back(temp_E);
  Be7_384.emplace_back(temp_N);
  inFile.close();

  // B8
  flux_B8 = 5.58e-4 * 1.0e10 / Unit::s / Unit::cm2;
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
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  B8.emplace_back(temp_E);
  B8.emplace_back(temp_N);
  inFile.close();

  // N13
  flux_N13 = 0.0296 * 1.0e10 / Unit::s / Unit::cm2;
  inFile.open("./data_in/N13.dat", std::ios::in);
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
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  N13.emplace_back(temp_E);
  N13.emplace_back(temp_N);
  inFile.close();

  // O15
  flux_O15 = 0.0223 * 1.0e10 / Unit::s / Unit::cm2;
  inFile.open("./data_in/O15.dat", std::ios::in);
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
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  O15.emplace_back(temp_E);
  O15.emplace_back(temp_N);
  inFile.close();

  // F17
  flux_F17 = 5.52e-4 * 1.0e10 / Unit::s / Unit::cm2;
  inFile.open("./data_in/F17.dat", std::ios::in);
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
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  F17.emplace_back(temp_E);
  F17.emplace_back(temp_N);
  inFile.close();

  // pp
  flux_pp = 5.98 * 1.0e10 / Unit::s / Unit::cm2;
  inFile.open("./data_in/pp.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_N.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> N;
    E = 5.0406 * Unit::keV + E * Unit::MeV;
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  pp.emplace_back(temp_E);
  pp.emplace_back(temp_N);
  inFile.close();

  // hep
  flux_hep = 8.04e-7 * 1.0e10 / Unit::s / Unit::cm2;
  inFile.open("./data_in/hep.dat", std::ios::in);
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
    N *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_N.emplace_back(N);
  }
  hep.emplace_back(temp_E);
  hep.emplace_back(temp_N);
  inFile.close();
}

SolarNeutrinoFlux::~SolarNeutrinoFlux() {}

double SolarNeutrinoFlux::Neutrino_Be7(double E) const {
  return flux_Be7 * Spectrum_Be7(E);
}

double SolarNeutrinoFlux::Neutrino_B8(double E) const {
  return flux_B8 * Spectrum_B8(E);
}

double SolarNeutrinoFlux::Neutrino_N13(double E) const {
  return flux_N13 * Spectrum_N13(E);
}

double SolarNeutrinoFlux::Neutrino_O15(double E) const {
  return flux_O15 * Spectrum_O15(E);
}

double SolarNeutrinoFlux::Neutrino_F17(double E) const {
  return flux_F17 * Spectrum_F17(E);
}

double SolarNeutrinoFlux::Neutrino_pp(double E) const {
  return flux_pp * Spectrum_pp(E);
}

double SolarNeutrinoFlux::Neutrino_hep(double E) const {
  return flux_hep * Spectrum_hep(E);
}

double SolarNeutrinoFlux::Spectrum_Be7(double E) const {
  double result_862, result_384;

  auto iter_862 = std::lower_bound(Be7_862[0].begin(), Be7_862[0].end(), E);
  if (iter_862 == Be7_862[0].begin() || iter_862 == Be7_862[0].end()) {
    result_862 = 0.0;
  } else {
    int id_862 = iter_862 - Be7_862[0].begin();
    double x1_862 = Be7_862[0][id_862 - 1];
    double x2_862 = Be7_862[0][id_862];
    double y1_862 = Be7_862[1][id_862 - 1];
    double y2_862 = Be7_862[1][id_862];
    result_862 = y1_862 + (y2_862 - y1_862) * (E - x1_862) / (x2_862 - x1_862);
  }

  auto iter_384 = std::lower_bound(Be7_384[0].begin(), Be7_384[0].end(), E);
  if (iter_384 == Be7_384[0].begin() || iter_384 == Be7_384[0].end()) {
    result_384 = 0.0;
  } else {
    int id_384 = iter_384 - Be7_384[0].begin();
    double x1_384 = Be7_384[0][id_384 - 1];
    double x2_384 = Be7_384[0][id_384];
    double y1_384 = Be7_384[1][id_384 - 1];
    double y2_384 = Be7_384[1][id_384];
    result_384 = y1_384 + (y2_384 - y1_384) * (E - x1_384) / (x2_384 - x1_384);
  }

  return result_862 + result_384;
}

double SolarNeutrinoFlux::Spectrum_B8(double E) const {
  double result;

  auto iter = std::lower_bound(B8[0].begin(), B8[0].end(), E);
  if (iter == B8[0].begin() || iter == B8[0].end()) {
    result = 0.0;
  } else {
    int id = iter - B8[0].begin();
    double x1 = B8[0][id - 1];
    double x2 = B8[0][id];
    double y1 = B8[1][id - 1];
    double y2 = B8[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double SolarNeutrinoFlux::Spectrum_N13(double E) const {
  double result;

  auto iter = std::lower_bound(N13[0].begin(), N13[0].end(), E);
  if (iter == N13[0].begin() || iter == N13[0].end()) {
    result = 0.0;
  } else {
    int id = iter - N13[0].begin();
    double x1 = N13[0][id - 1];
    double x2 = N13[0][id];
    double y1 = N13[1][id - 1];
    double y2 = N13[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double SolarNeutrinoFlux::Spectrum_O15(double E) const {
  double result;

  auto iter = std::lower_bound(O15[0].begin(), O15[0].end(), E);
  if (iter == O15[0].begin() || iter == O15[0].end()) {
    result = 0.0;
  } else {
    int id = iter - O15[0].begin();
    double x1 = O15[0][id - 1];
    double x2 = O15[0][id];
    double y1 = O15[1][id - 1];
    double y2 = O15[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double SolarNeutrinoFlux::Spectrum_F17(double E) const {
  double result;

  auto iter = std::lower_bound(F17[0].begin(), F17[0].end(), E);
  if (iter == F17[0].begin() || iter == F17[0].end()) {
    result = 0.0;
  } else {
    int id = iter - F17[0].begin();
    double x1 = F17[0][id - 1];
    double x2 = F17[0][id];
    double y1 = F17[1][id - 1];
    double y2 = F17[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double SolarNeutrinoFlux::Spectrum_pp(double E) const {
  double result;

  auto iter = std::lower_bound(pp[0].begin(), pp[0].end(), E);
  if (iter == pp[0].begin() || iter == pp[0].end()) {
    result = 0.0;
  } else {
    int id = iter - pp[0].begin();
    double x1 = pp[0][id - 1];
    double x2 = pp[0][id];
    double y1 = pp[1][id - 1];
    double y2 = pp[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double SolarNeutrinoFlux::Spectrum_hep(double E) const {
  double result;

  auto iter = std::lower_bound(hep[0].begin(), hep[0].end(), E);
  if (iter == hep[0].begin() || iter == hep[0].end()) {
    result = 0.0;
  } else {
    int id = iter - hep[0].begin();
    double x1 = hep[0][id - 1];
    double x2 = hep[0][id];
    double y1 = hep[1][id - 1];
    double y2 = hep[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}
