#ifndef _JINPINGLOCATION_H_
#define _JINPINGLOCATION_H_

#include "ConstandUnit.h"
#include "VectorAnalysis.h"

class jinpingLocation {
public:
  jinpingLocation();
  ~jinpingLocation();

  static double Theta;
  static double Phi;
  static double R;

  Vector3D *jinpingZaxis;
  Vector3D *jinpingXaxis;
  Vector3D *jinpingYaxis;
};

#endif
