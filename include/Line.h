#ifndef Line_h
#define Line_h

#include "TVector3.h"
#include "TPolyLine3D.h"

class Line : public TVector3 {
 private:
  void Mag() = delete;
  void Mag2() = delete;
  void operator*=(int) = delete;
  void Perp() = delete;
  void Perp2() = delete;
  void SetMag() = delete;
  void SetMagThetaPhi() = delete;
  void SetPerp() =delete;
  void SetPtEtaPhi()=delete;
  void SetPtThetaPhi()=delete;
  
 public:
  double fTheta,fPhi;
  
  Line();
  Line(double x,double y,double z,double theta,double phi);
  Line(double x1,double y1,double z1,double x2,double y2,double z2);

  virtual double Angle(const TVector3& q) const { return Vector().Angle(q); }
  virtual double Angle(const Line& l) const { return Vector().Angle(l.Vector()); }
  virtual double CosTheta() const { return cos(fTheta); }
  virtual TVector3 Cross(const TVector3& q) const { return Vector().Cross(q); }
  virtual TVector3 Cross(const Line& l) const { return Vector().Cross(l.Vector()); }
  virtual double DeltaPhi(const TVector3& q) const { return Vector().DeltaPhi(q); }
  virtual double DeltaPhi(const Line& l) const { return Vector().DeltaPhi(l.Vector()); }  
  virtual double DeltaR(const TVector3& q) const { return Vector().DeltaR(q); }
  virtual double DeltaR(const Line& l) const { return Vector().DeltaR(l.Vector()); }  
  virtual double Distance(double x,double y,double z) const;
  virtual double Distance(const TVector3& p) const;
  virtual double Distance(const Line& line) const;
  virtual double Dot(const TVector3& q) const { return Vector().Dot(q); }
  virtual double Dot(const Line& l) const { return Vector().Dot(l.Vector()); }
  virtual TPolyLine3D* Draw();
  virtual double DrEtaPhi(const TVector3& q) const { return Vector().DrEtaPhi(q); }
  virtual double DrEtaPhi(const Line& l) const { return Vector().DrEtaPhi(l.Vector()); }
  virtual double Eta() const { return Vector().Eta(); }
  virtual TVector3 Point(double a=0) const { return TVector3(X(),Y(),Z())+a*Vector(); }
  virtual TVector3 PointWithX(double x) const;
  virtual TVector3 PointWithY(double y) const;
  virtual TVector3 PointWithZ(double z) const;
  virtual void SetPhi(double phi){fPhi=TMath::Sin(phi) > 0 ? TMath::ACos(TMath::Cos(phi)) : -TMath::ACos(TMath::Cos(phi));}
  virtual void SetTheta(double theta){fTheta=TMath::ACos(TMath::Cos(theta));}
  virtual double Theta() const { return fTheta; }
  virtual double Phi() const { return fPhi; }
  virtual TVector3 Vector() const { return TVector3(cos(fPhi)*sin(fTheta),sin(fPhi)*sin(fTheta),cos(fTheta)); }
  virtual void SetXYZXYZ(double x1,double y1,double z1,double x2,double y2,double z2);

  ClassDef(Line,1);
};
  
#endif
