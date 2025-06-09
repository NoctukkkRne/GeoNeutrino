#include "SolarModel.h"

SolarModel::SolarModel() {
  std::ifstream inFile;
  double Rfrac, ne, Be7frac, B8frac, N13frac, O15frac, F17frac, ppfrac, hepfrac,
      useless;
  std::string sline;
  std::istringstream isstream;

  inFile.open("./data_in/bs2005agsopflux.dat", std::ios::in);
  if (!inFile.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }

  while (std::getline(inFile, sline)) {
    isstream.clear();
    isstream.str(sline);
    isstream >> Rfrac >> useless >> ne >> useless >> useless >> ppfrac >>
        B8frac >> N13frac >> O15frac >> F17frac >> Be7frac >> useless >>
        hepfrac;

    ne *= Const::Na * Unit::mol / Unit::cm3;

    R.emplace_back(Rfrac);
    Be7.emplace_back(Be7frac);
    B8.emplace_back(B8frac);
    N13.emplace_back(N13frac);
    O15.emplace_back(O15frac);
    F17.emplace_back(F17frac);
    pp.emplace_back(ppfrac);
    hep.emplace_back(hepfrac);
  }
};

SolarModel::~SolarModel(){};

double SolarModel::Pee_Be7(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += Be7[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_B8(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += B8[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_N13(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += N13[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_O15(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += O15[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_F17(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += F17[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_pp(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += pp[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pee_hep(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += hep[id] * NeutrinoOscillation::Pee_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_Be7(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += Be7[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_B8(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += B8[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_N13(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += N13[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_O15(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += O15[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_F17(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += F17[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_pp(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += pp[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}

double SolarModel::Pex_hep(double E) const {
  double result = 0.0;
  for (int id = 0; id < R.size(); ++id) {
    result += hep[id] * NeutrinoOscillation::Pex_MSW(E, Ne[id], 0);
  }
  return result;
}
