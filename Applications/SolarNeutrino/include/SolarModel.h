#ifndef _SOLARMODEL_H_
#define _SOLARMODEL_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Common/include/ConstandUnit.h"
#include "../../Common/include/NeutrinoOscillation.h"

class SolarModel {
public:
  SolarModel();
  ~SolarModel();

  double Pee_Be7(double E) const;
  double Pee_B8(double E) const;
  double Pee_N13(double E) const;
  double Pee_O15(double E) const;
  double Pee_F17(double E) const;
  double Pee_pp(double E) const;
  double Pee_hep(double E) const;

  double Pex_Be7(double E) const;
  double Pex_B8(double E) const;
  double Pex_N13(double E) const;
  double Pex_O15(double E) const;
  double Pex_F17(double E) const;
  double Pex_pp(double E) const;
  double Pex_hep(double E) const;

private:
  std::vector<double> R;
  std::vector<double> Ne;
  std::vector<double> Be7;
  std::vector<double> B8;
  std::vector<double> N13;
  std::vector<double> O15;
  std::vector<double> F17;
  std::vector<double> pp;
  std::vector<double> hep;
};

#endif
