#include "ConstandUnit.h"

double Unit::deg = TMath::Pi() / 180.0;
double Unit::eV = 1.0;
double Unit::keV = 1.0e3 * eV;
double Unit::MeV = 1.0e6 * eV;
double Unit::GeV = 1.0e9 * eV;
double Unit::J = 1.0 / TMath::Qe() * eV;
double Unit::eV2 = eV * eV;
double Unit::GeV2 = GeV * GeV;
double Unit::s = 1.0 / TMath::Hbar() / J;
double Unit::day = 24.0 * 3600.0 * s;
double Unit::yr = 365.0 * day;
double Unit::m = 1.0 / TMath::C() * s;
double Unit::cm = 1.0e-2 * m;
double Unit::km = 1.0e3 * m;
double Unit::m2 = m * m;
double Unit::cm2 = cm * cm;
double Unit::km2 = km * km;
double Unit::m3 = m * m * m;
double Unit::cm3 = cm * cm * cm;
double Unit::km3 = km * km * km;
double Unit::kg = J / pow(m / s, 2);
double Unit::g = 1.0e-3 * kg;
double Unit::ton = 1.0e3 * kg;
double Unit::mol = 1.0;

double Const::pi = TMath::Pi();
double Const::Gf = 1.166e-5 / Unit::GeV2;
double Const::me = 0.511 * Unit::MeV;
double Const::mp = 938.27 * Unit::MeV;
double Const::mn = 939.57 * Unit::MeV;
double Const::theta_12 = 0.584;
double Const::theta_13 = 0.149;
double Const::theta_23 = 0.785;
double Const::deltamsquare21 = 7.53e-5 * Unit::eV2;
double Const::deltamsquare32 = 2.51e-3 * Unit::eV2;
double Const::deltamsquare31 = deltamsquare32 - deltamsquare21;
double Const::mr_K40 = 39.10 * Unit::g / Unit::mol;
double Const::mr_Th232 = 232.04 * Unit::g / Unit::mol;
double Const::mr_U238 = 238.03 * Unit::g / Unit::mol;
double Const::x_K40 = 1.17e-4;
double Const::x_Th232 = 1.000;
double Const::x_U238 = 0.993;
double Const::lambda_K40 = log(2.0) / (1.248e9 * Unit::yr);
double Const::lambda_Th232 = log(2.0) / (1.401e10 * Unit::yr);
double Const::lambda_U238 = log(2.0) / (4.469e9 * Unit::yr);
double Const::Na = 6.02e23 / Unit::mol;
