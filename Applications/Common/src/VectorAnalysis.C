#include "VectorAnalysis.h"

Vector3D::Vector3D() {}
Vector3D::~Vector3D() {}

void Vector3D::SetPolar(double r, double theta, double phi) {
  R = r;
  Theta = theta;
  Phi = phi;
  X = R * sin(Theta) * cos(Phi);
  Y = R * sin(Theta) * sin(Phi);
  Z = R * cos(Theta);
}

void Vector3D::SetXYZ(double x, double y, double z) {
  X = x;
  Y = y;
  Z = z;
  R = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  Theta = acos(z / R);
  if (R * sin(Theta) <= 0.0) {
    Phi = 0.0;
  } else {
    double CosPhi = x / (R * sin(Theta));
    double SinPhi = y / (R * sin(Theta));

    if (SinPhi > 0.0) {
      Phi = acos(CosPhi);
    } else {
      Phi = -acos(CosPhi);
    }
  }
}

void Vector3D::Scale(double r) { SetPolar(r, Theta, Phi); }

void Vector3D::RotateZ(double angle) {
  double x = X * cos(angle) - Y * sin(angle);
  double y = X * sin(angle) + Y * cos(angle);
  double z = Z;

  SetXYZ(x, y, z);
}

void Vector3D::RotateY(double angle) {
  double x = X * cos(angle) + Z * sin(angle);
  double y = Y;
  double z = -X * sin(angle) + Z * cos(angle);

  SetXYZ(x, y, z);
}

void Vector3D::Rotate(Vector3D *axis, double angle) {
  double theta_axis = axis->Theta;
  double phi_axis = axis->Phi;

  RotateZ(-phi_axis);
  RotateY(-theta_axis);
  RotateZ(angle);
  RotateY(theta_axis);
  RotateZ(phi_axis);
}

Vector3D *Vector3D::RotateGenerate(double theta, double phi) const {
  Vector3D *result = new Vector3D();

  result->SetPolar(R, Theta, Phi);
  result->RotateZ(-Phi);
  result->RotateY(-Theta);
  result->RotateY(theta);
  result->RotateZ(phi);
  result->RotateY(Theta);
  result->RotateZ(Phi);

  return result;
}

double Vector3D::GetR() const { return R; }

double Vector3D::GetTheta() const { return Theta; }

double Vector3D::GetPhi() const { return Phi; }

double Vector3D::GetX() const { return X; }

double Vector3D::GetY() const { return Y; }

double Vector3D::GetZ() const { return Z; }

Corrdinate3D::Corrdinate3D() {
  Xaxis = new Vector3D();
  Yaxis = new Vector3D();
  Zaxis = new Vector3D();
}
Corrdinate3D::~Corrdinate3D() {}

void Corrdinate3D::SetXYZ(Vector3D *xaxis, Vector3D *yaxis, Vector3D *zaxis) {
  Xaxis->SetPolar(xaxis->GetR(), xaxis->GetTheta(), xaxis->GetPhi());
  Yaxis->SetPolar(yaxis->GetR(), yaxis->GetTheta(), yaxis->GetPhi());
  Zaxis->SetPolar(zaxis->GetR(), zaxis->GetTheta(), zaxis->GetPhi());

  Xaxis->Scale(1.0);
  Yaxis->Scale(1.0);
  Zaxis->Scale(1.0);
}

double Vector3DDot(Vector3D *vec1, Vector3D *vec2) {
  return vec1->GetX() * vec2->GetX() + vec1->GetY() * vec2->GetY() +
         vec1->GetZ() * vec2->GetZ();
}

Vector3D *GetRelative(Vector3D *vec, Corrdinate3D *cor) {
  Vector3D *result = new Vector3D();
  double theta, phi;

  Vector3D *vvec = new Vector3D();
  Vector3D *zzaxis = new Vector3D();

  vvec->SetPolar(vec->GetR(), vec->GetTheta(), vec->GetPhi());
  zzaxis->SetPolar(cor->GetZaxis()->GetR(), cor->GetZaxis()->GetTheta(),
                   cor->GetZaxis()->GetPhi());

  zzaxis->Scale(1.0);
  vvec->Scale(1.0);

  double costheta = Vector3DDot(vvec, cor->GetZaxis());

  zzaxis->Scale(Vector3DDot(vvec, zzaxis));
  vvec->SetXYZ(vvec->GetX() - zzaxis->GetX(), vvec->GetY() - zzaxis->GetY(),
               vvec->GetZ() - zzaxis->GetZ());
  vvec->Scale(1.0);

  double cosphi = Vector3DDot(vvec, cor->GetXaxis());
  double sinphi = Vector3DDot(vvec, cor->GetYaxis());

  theta = acos(costheta);
  if (sinphi > 0) {
    phi = acos(cosphi);
  } else {
    phi = -acos(cosphi);
  }
  result->SetPolar(1.0, theta, phi);

  delete vvec;
  delete zzaxis;

  return result;
}
