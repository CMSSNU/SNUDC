#ifndef Line_cxx
#define Line_cxx

#include "Line.h"

ClassImp(Line);

Line::Line(){
  SetXYZ(0,0,0);
  fTheta=0; fPhi=0;
}
  
Line::Line(double x,double y,double z,double theta,double phi){
  SetXYZ(x,y,z);
  fTheta=theta; fPhi=phi;
}
Line::Line(double x1,double y1,double z1,double x2,double y2,double z2){
  SetXYZXYZ(x1,y1,z1,x2,y2,z2);
}
void Line::Draw(){
  TPolyLine3D* a=new TPolyLine3D(2);
  TVector3 start=Point(-1000);
  TVector3 end=Point(1000);
  a->SetPoint(0,start.X(),start.Y(),start.Z());
  a->SetPoint(1,end.X(),end.Y(),end.Z());
  a->Draw();
}
double Line::Distance(double x,double y,double z) const {
  return Distance(TVector3(x,y,z));
} 
double Line::Distance(const TVector3& p) const {
  TVector3 bridge=Point()-p;
  TVector3 axis=Cross(bridge).Cross(Vector());
  axis.SetMag(1);
  return fabs(bridge.Dot(axis));
} 
double Line::Distance(const Line& line) const {
  TVector3 bridge=Point()-line.Point();
  TVector3 axis=Cross(line);
  if(axis.Mag()==0) return Distance(line.Point());
  axis.SetMag(1);
  return fabs(bridge.Dot(axis));
}
TVector3 Line::PointWithX(double x) const {
  TVector3 p=Point();
  TVector3 v=Vector();
  if(v.X()==0) return p;
  return p+(x-p.X())/v.X()*v;
}
TVector3 Line::PointWithY(double y) const {
  TVector3 p=Point();
  TVector3 v=Vector();
  if(v.Y()==0) return p;
  return p+(y-p.Y())/v.Y()*v;
}
TVector3 Line::PointWithZ(double z) const {
  TVector3 p=Point();
  TVector3 v=Vector();
  if(v.Z()==0) return p;
  return p+(z-p.Z())/v.Z()*v;
}
void Line::SetXYZXYZ(double x1,double y1,double z1,double x2,double y2,double z2){
  SetX(x1); SetY(y1); SetZ(z1);
  TVector3 t(x2-x1,y2-y1,z2-z1);
  t.SetMag(1);
  fTheta=t.Theta(); fPhi=t.Phi();
}
#endif
