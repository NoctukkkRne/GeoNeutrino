#ifndef _CROSSSECTION_H_
#define _CROSSSECTION_H_

#include "ConstandUnit.h"

class CrossSection {
public:
  CrossSection();
  ~CrossSection();

  static double TCS_IBD(double E_nu);

  static double DCS_Scat_NuE(double E_nu, double T_e);
  static double DCS_Scat_AntiNuE(double E_nu, double T_e);
  static double DCS_Scat_NuX(double E_nu, double T_e);
  static double DCS_Scat_AntiNuX(double E_nu, double T_e);

  static double TCS_Scat_NuE(double E_nu);
  static double TCS_Scat_AntiNuE(double E_nu);
  static double TCS_Scat_NuX(double E_nu);
  static double TCS_Scat_AntiNuX(double E_nu);
};

#endif
