#ifndef _VECTORANALYSIS_H_
#define _VECTORANALYSIS_H_

#include <cmath>

class Vector3D {
public:
  Vector3D();
  ~Vector3D();

  void SetPolar(double r, double theta, double phi);
  void SetXYZ(double x, double y, double z);
  void Scale(double r);

  void RotateZ(double angle);
  void RotateY(double angle);
  void Rotate(Vector3D *axis, double angle);
  Vector3D *RotateGenerate(double theta, double phi) const;

  double GetR() const;
  double GetTheta() const;
  double GetPhi() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;

private:
  double R;
  double Theta;
  double Phi;
  double X;
  double Y;
  double Z;
};

class Corrdinate3D {
public:
  Corrdinate3D();
  ~Corrdinate3D();

  void SetXYZ(Vector3D *xaxis, Vector3D *yaxis, Vector3D *zaxis);

  Vector3D *GetXaxis() const;
  Vector3D *GetYaxis() const;
  Vector3D *GetZaxis() const;

private:
  Vector3D *Xaxis;
  Vector3D *Yaxis;
  Vector3D *Zaxis;
};

Vector3D *GetRelative(Vector3D *vec, Corrdinate3D *cor);
double Vector3DDot(Vector3D *vec1, Vector3D *vec2);

#endif
