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

double NeutrinoOscillation::Pee_MSW(double E, double L, double Ni, double Nf) {

  return 0.0;
}

double NeutrinoOscillation::Pex_MSW(double E, double L, double Ni, double Nf) {

  return 0.0;
}
