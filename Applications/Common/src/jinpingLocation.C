#include "jinpingLocation.h"

jinpingLocation::jinpingLocation() {}
jinpingLocation::~jinpingLocation() {}

double jinpingLocation::Theta = (90.0 - 28.15323) * Unit::deg;
double jinpingLocation::Phi = 101.7114 * Unit::deg;
// const double jinpingR = 6374.42 * Unit::km - 2.4 * Unit::km;
double jinpingLocation::R = 6371.0 * Unit::km + 1.5 * Unit::km;
// const double R = 6371.0 * Unit::km - 2.4 * Unit::km;
