#ifndef _CONSTANDUNIT_H_
#define _CONSTANDUNIT_H_

#include <TMath.h>

class Unit {
public:
  Unit();
  ~Unit();

  // Geometry
  static double deg;

  // Energy
  static double eV;
  static double keV;
  static double MeV;
  static double J;
  static double eV2;

  // Length
  static double m;
  static double m2;
  static double m3;
  static double cm;
  static double cm2;
  static double cm3;
  static double km;
  static double km2;
  static double km3;

  // Mass
  static double kg;
  static double g;
  static double ton;

  // Time
  static double s;
  static double day;
  static double yr;

  // Chemistry
  static double mol;
};

class Const {
public:
  Const();
  ~Const();

  // Geometry const
  static double pi;

  // Physical const
  // static double c;
  // static double hbar;
  // static double qe;

  // Particle parameters
  static double me;
  static double mp;
  static double mn;

  // Neutrino oscillation parameters
  static double theta_12;
  static double theta_13;
  static double theta_23;
  static double deltamsquare21;
  static double deltamsquare32;
  static double deltamsquare31;

  // Element parameters
  static double mr_K40;
  static double mr_Th232;
  static double mr_U238;
  static double x_K40;
  static double x_Th232;
  static double x_U238;
  static double lambda_K40;
  static double lambda_Th232;
  static double lambda_U238;

  // Chemistry const
  static double Na;
};

#endif
