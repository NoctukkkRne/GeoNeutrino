#include "CrossSection.h"

CrossSection::CrossSection() {}
CrossSection::~CrossSection() {}

// Total CrossSection for IBD
double CrossSection::TCS_IBD(double E_nu) {
  double result = 0.0;

  double Ee = E_nu - (Const::mn - Const::mp);
  if (Ee < Const::me) {
    result = 0.0;
  } else {
    double pe = sqrt(Ee * Ee - Const::me * Const::me);
    result = 0.0952 * (Ee / Unit::MeV) * (pe / Unit::MeV) * 1.0e-42 * Unit::cm2;
  }

  return result;
}

// Differential CrossSection for Nu_e Electron Scattering
double CrossSection::DCS_Scat_NuE(double E_nu, double T_e) {
  double result;

  const double temax = 2.0 * E_nu * E_nu / (2.0 * E_nu + Const::me);
  if (T_e > temax) {
    result = 0.0;
  } else {
    const double g1 = 0.73;
    const double g2 = 0.23;
    const double sigma0 = 88.06e-46 * Unit::cm2;

    double A = sigma0 / Const::me;
    double y1 = pow(g1, 2);
    double y2 = pow(g2, 2) * pow(1.0 - T_e / E_nu, 2);
    double y3 = g1 * g2 * Const::me * T_e / pow(E_nu, 2);

    result = A * (y1 + y2 - y3);
  }
  return result;
}

// Differential CrossSection for Nu_x Electron Scattering
double CrossSection::DCS_Scat_NuX(double E_nu, double T_e) {
  double result;

  const double temax = 2.0 * E_nu * E_nu / (2.0 * E_nu + Const::me);
  if (T_e > temax) {
    result = 0.0;
  } else {
    const double g1 = -0.27;
    const double g2 = 0.23;
    const double sigma0 = 88.06e-46 * Unit::cm2;

    double A = sigma0 / Const::me;
    double y1 = pow(g1, 2);
    double y2 = pow(g2, 2) * pow(1.0 - T_e / E_nu, 2);
    double y3 = g1 * g2 * Const::me * T_e / pow(E_nu, 2);

    result = A * (y1 + y2 - y3);
  }
  return result;
}

// Differential CrossSection for AntiNu_e Electron Scattering
double CrossSection::DCS_Scat_AntiNuE(double E_nu, double T_e) {
  double result;

  const double temax = 2.0 * E_nu * E_nu / (2.0 * E_nu + Const::me);
  if (T_e > temax) {
    result = 0.0;
  } else {
    const double g1 = 0.23;
    const double g2 = 0.73;
    const double sigma0 = 88.06e-46 * Unit::cm2;

    double A = sigma0 / Const::me;
    double y1 = pow(g1, 2);
    double y2 = pow(g2, 2) * pow(1.0 - T_e / E_nu, 2);
    double y3 = g1 * g2 * Const::me * T_e / pow(E_nu, 2);

    result = A * (y1 + y2 - y3);
  }
  return result;
}

// Differential CrossSection for AntiNu_x Electron Scattering
double CrossSection::DCS_Scat_AntiNuX(double E_nu, double T_e) {
  double result;

  const double temax = 2.0 * E_nu * E_nu / (2.0 * E_nu + Const::me);
  if (T_e > temax) {
    result = 0.0;
  } else {
    const double g1 = 0.23;
    const double g2 = -0.27;
    const double sigma0 = 88.06e-46 * Unit::cm2;

    double A = sigma0 / Const::me;
    double y1 = pow(g1, 2);
    double y2 = pow(g2, 2) * pow(1.0 - T_e / E_nu, 2);
    double y3 = g1 * g2 * Const::me * T_e / pow(E_nu, 2);

    result = A * (y1 + y2 - y3);
  }
  return result;
}

// Scattering Angle for Nu Electron Scattering
double CrossSection::Theta_Scat(double E_nu, double T_e) {
  double result;

  const double temax = 2.0 * E_nu * E_nu / (2.0 * E_nu + Const::me);
  if (T_e > temax) {
    result = 0.0;
  } else {
    result = acos((1.0 + Const::me / E_nu) / sqrt(1.0 + 2.0 * Const::me / T_e));
  }
  return result;
}
