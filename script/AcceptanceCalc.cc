#include <iostream>
#include <stdlib.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TMath.h>
#include "map"
#include "TString.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <TF1.h>
#include <TLine.h>
#include <TH2F.h>
#include <TGraphErrors.h>
#include <TPaveStats.h>
#include <iostream>
#include <fstream>

double X=29.; //scintillator X-length
double Y=15.; //scintillator Y-length
double HEIGHT=50.; //distance of two scintillator

double GetAcceptanceByMC(double h=50.,double x=29.,double y=15.);
double GetAcceptanceByIntegral(double h=50.,double x=29.,double y=15.);

/////////////////////// Monte-Calro method ////////////////////////////
//calculate passing point at bellow plane and check if muon passes bellow scintillator
bool trigger(double x1, double y1, double theta, double phi){
  
  double current_r = HEIGHT * tan(theta);
  
  double current_x2 = x1 + current_r * cos(phi);
  double current_y2 = y1 + current_r * sin(phi);
   
  if(current_x2 > 0 && current_x2 < X && current_y2 > 0 && current_y2 < Y){
    
    return true;
  }
  else return false;
  

}

//main function
double GetAcceptanceByMC(double h,double x,double y){
  HEIGHT=h;
  X=x;
  Y=y;
  
  int cycle = 10000000; //number of experiments
  
  
  double event_weighted = 0;
  double event_trigged = 0;
  

  ////for 
  for(int i = 0; i < cycle; i ++){
    //call random point on above plane
    double current_x1 = gRandom->Rndm()*X;
    double current_y1 = gRandom->Rndm()*Y;
    //call random theta and phi of passing cosmic ray
    double current_theta = TMath::Pi()/2 * ( gRandom->Rndm());
    double current_phi= 2.0 * TMath::Pi() * ( gRandom->Rndm());
    
    bool trigged = trigger(current_x1, current_y1, current_theta, current_phi);
    
    event_weighted = event_weighted + pow(cos(current_theta), 2)*sin(current_theta);
    //event_weighted+=sin(current_theta);
    if(trigged) {
      event_trigged = event_trigged + pow(cos(current_theta), 2)*sin(current_theta);
      //event_trigged+=sin(current_theta);
    }

  }
  ///end for loop
  
  double ratio = (event_trigged + 0.) / (event_weighted + 0.);
  cout << "ratio is : " << ratio << endl;

  double rate = X * Y * ratio / 60.0 ;
  rate = rate * 0.88;
  cout << "rate is : " << rate << " Hz" << endl;

  return ratio;
}

/////////////////////// Integral method ////////////////////////////
double term(double x1,double y1, double x2,double y2){
  TVector3 r(x2-x1,y2-y1,-1.*HEIGHT);
  TVector3 n(0,0,-1);
  //return r.Dot(n)/pow(r.Mag(),3);
  return 3*pow(r.Dot(n)/r.Mag(),2)*(r.Dot(n)/pow(r.Mag(),3));
}
double func_term(double *x,double *par){
  return term(par[0],par[1],x[0],x[1]);
}
  
double pointEff(double x,double y){
  TF2 f("f",&func_term,0,X,0,Y,2);
  f.SetParameters(x,y);
  return f.Integral(0,X,0,Y)/(2*TMath::Pi());
}
double func_pointEff(double *x,double *par){
  return pointEff(x[0],x[1]);
}
double GetAcceptanceByIntegral(double h,double x,double y){
  HEIGHT=h;
  X=x;
  Y=y;
  TF2 f("f",&func_pointEff,0,X,0,Y);
  return f.Integral(0,X,0,Y)/X/Y;
}  
