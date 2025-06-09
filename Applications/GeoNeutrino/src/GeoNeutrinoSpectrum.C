#include "GeoNeutrinoSpectrum.h"

GeoNeutrinoSpectrum::GeoNeutrinoSpectrum() {
  std::ifstream inFile;
  std::vector<double> temp_E;
  std::vector<double> temp_Neutrino;
  std::vector<double> temp_AntiNeutrino;
  std::string sline;
  std::istringstream isstream;
  double E, Neutrino, AntiNeutrino;

  // K40
  inFile.open("./data_in/K40.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_Neutrino.clear();
  temp_AntiNeutrino.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> Neutrino >> AntiNeutrino;
    E *= Unit::MeV;
    Neutrino *= (1.0 / Unit::MeV);
    AntiNeutrino *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_Neutrino.emplace_back(Neutrino);
    temp_AntiNeutrino.emplace_back(AntiNeutrino);
  }
  K40.emplace_back(temp_E);
  K40.emplace_back(temp_Neutrino);
  K40.emplace_back(temp_AntiNeutrino);
  inFile.close();

  // K40
  inFile.open("./data_in/K40.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_Neutrino.clear();
  temp_AntiNeutrino.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> Neutrino >> AntiNeutrino;
    E *= Unit::MeV;
    Neutrino *= (1.0 / Unit::MeV);
    AntiNeutrino *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_Neutrino.emplace_back(Neutrino);
    temp_AntiNeutrino.emplace_back(AntiNeutrino);
  }
  K40.emplace_back(temp_E);
  K40.emplace_back(temp_Neutrino);
  K40.emplace_back(temp_AntiNeutrino);
  inFile.close();

  // Th232
  inFile.open("./data_in/Th232.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_Neutrino.clear();
  temp_AntiNeutrino.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> Neutrino >> AntiNeutrino;
    E *= Unit::MeV;
    Neutrino *= (1.0 / Unit::MeV);
    AntiNeutrino *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_Neutrino.emplace_back(Neutrino);
    temp_AntiNeutrino.emplace_back(AntiNeutrino);
  }
  Th232.emplace_back(temp_E);
  Th232.emplace_back(temp_Neutrino);
  Th232.emplace_back(temp_AntiNeutrino);
  inFile.close();

  // U238
  inFile.open("./data_in/U238.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  temp_E.clear();
  temp_Neutrino.clear();
  temp_AntiNeutrino.clear();
  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> E >> Neutrino >> AntiNeutrino;
    E *= Unit::MeV;
    Neutrino *= (1.0 / Unit::MeV);
    AntiNeutrino *= (1.0 / Unit::MeV);
    temp_E.emplace_back(E);
    temp_Neutrino.emplace_back(Neutrino);
    temp_AntiNeutrino.emplace_back(AntiNeutrino);
  }
  U238.emplace_back(temp_E);
  U238.emplace_back(temp_Neutrino);
  U238.emplace_back(temp_AntiNeutrino);
  inFile.close();
}

GeoNeutrinoSpectrum::~GeoNeutrinoSpectrum() {}

double GeoNeutrinoSpectrum::Neutrino_K40(double E) const {
  double result;

  auto iter = std::lower_bound(K40[0].begin(), K40[0].end(), E);
  if (iter == K40[0].begin() || iter == K40[0].end()) {
    result = 0.0;
  } else {
    int id = iter - K40[0].begin();
    double x1 = K40[0][id - 1];
    double x2 = K40[0][id];
    double y1 = K40[1][id - 1];
    double y2 = K40[1][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double GeoNeutrinoSpectrum::AntiNeutrino_K40(double E) const {
  double result;

  auto iter = std::lower_bound(K40[0].begin(), K40[0].end(), E);
  if (iter == K40[0].begin() || iter == K40[0].end()) {
    result = 0.0;
  } else {
    int id = iter - K40[0].begin();
    double x1 = K40[0][id - 1];
    double x2 = K40[0][id];
    double y1 = K40[2][id - 1];
    double y2 = K40[2][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double GeoNeutrinoSpectrum::AntiNeutrino_Th232(double E) const {
  double result;

  auto iter = std::lower_bound(Th232[0].begin(), Th232[0].end(), E);
  if (iter == Th232[0].begin() || iter == Th232[0].end()) {
    result = 0.0;
  } else {
    int id = iter - Th232[0].begin();
    double x1 = Th232[0][id - 1];
    double x2 = Th232[0][id];
    double y1 = Th232[2][id - 1];
    double y2 = Th232[2][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}

double GeoNeutrinoSpectrum::AntiNeutrino_U238(double E) const {
  double result;

  auto iter = std::lower_bound(U238[0].begin(), U238[0].end(), E);
  if (iter == U238[0].begin() || iter == U238[0].end()) {
    result = 0.0;
  } else {
    int id = iter - U238[0].begin();
    double x1 = U238[0][id - 1];
    double x2 = U238[0][id];
    double y1 = U238[2][id - 1];
    double y2 = U238[2][id];
    result = y1 + (y2 - y1) * (E - x1) / (x2 - x1);
  }

  return result;
}
