#ifndef _NEUTRINOOSCILLATION_H_
#define _NEUTRINOOSCILLATION_H_

#include "ConstandUnit.h"
#include "Rootneed.h"

class NeutrinoOscillation {
public:
  NeutrinoOscillation();
  ~NeutrinoOscillation();

  static double Pee_vac(double E, double L);
  static double Pex_vac(double E, double L);
  static double Pee_MSW(double E, double L, double Ni, double Nf);
  static double Pex_MSW(double E, double L, double Ni, double Nf);
};

#endif
