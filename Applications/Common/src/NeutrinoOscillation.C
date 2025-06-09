#include "NeutrinoOscillation.h"

NeutrinoOscillation::NeutrinoOscillation() {}
NeutrinoOscillation::~NeutrinoOscillation() {}

double NeutrinoOscillation::Pee_vac(double E, double L) {

  double delta21 = 1.267 * (Const::deltamsquare21 / Unit::eV2) * (L / Unit::m) /
                   (E / Unit::MeV);
  double delta32 = 1.267 * (Const::deltamsquare32 / Unit::eV2) * (L / Unit::m) /
                   (E / Unit::MeV);
  double delta31 = 1.267 * (Const::deltamsquare31 / Unit::eV2) * (L / Unit::m) /
                   (E / Unit::MeV);
  double y1 = pow(cos(Const::theta_13), 4) *
              pow(sin(2.0 * Const::theta_12), 2) * pow(sin(delta21), 2);
  double y2 = pow(sin(2.0 * Const::theta_13), 2) *
              pow(cos(Const::theta_12), 2) * pow(sin(delta31), 2);
  double y3 = pow(sin(2.0 * Const::theta_13), 2) *
              pow(sin(Const::theta_12), 2) * pow(sin(delta32), 2);

  return 1.0 - y1 - y2 - y3;
}

double NeutrinoOscillation::Pex_vac(double E, double L) {
  return 1.0 - Pee_vac(E, L);
}

double NeutrinoOscillation::Pee_MSW(double E, double Ni, double Nf) {
  double Ai = sqrt(2.0) / 2.0 * Const::Gf * Ni;
  double tan2theta_12Mi =
      Const::deltamsquare21 / (4.0 * E) * sin(2.0 * Const::theta_12) /
      (Const::deltamsquare21 / (4.0 * E) * cos(2.0 * Const::theta_12) - Ai);
  double cos2theta_12Mi = 1.0 / sqrt(1.0 + pow(tan2theta_12Mi, 2));
  if (tan2theta_12Mi < 0.0) {
    cos2theta_12Mi *= -1.0;
  }

  double Af = sqrt(2.0) / 2.0 * Const::Gf * Nf;
  double tan2theta_12Mf =
      Const::deltamsquare21 / (4.0 * E) * sin(2.0 * Const::theta_12) /
      (Const::deltamsquare21 / (4.0 * E) * cos(2.0 * Const::theta_12) - Af);
  double cos2theta_12Mf = 1.0 / sqrt(1.0 + pow(tan2theta_12Mf, 2));
  if (tan2theta_12Mf < 0.0) {
    cos2theta_12Mf *= -1.0;
  }

  return pow(cos(Const::theta_13), 4) *
         (1.0 + cos2theta_12Mi * cos2theta_12Mf) / 2.0;
}

double NeutrinoOscillation::Pex_MSW(double E, double Ni, double Nf) {
  return 1.0 - Pee_MSW(E, Ni, Nf);
}
