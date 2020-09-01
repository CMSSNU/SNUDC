double Vp0=-2500;
double Vc0=-2500;
double Va0=0;
double hc=1;
double SingleWire(double x,double y,double V){
  double r=sqrt(x*x+y*y);
  if(r<0.03) r=0.03;
  return V*(2-log(r/0.03));
}
double GetTotalV(double x,double y,double Vp,double Va,vector<double> parVc){
  double Vtot=0;
  for(int l=0;l<1;l++){
    double y0=l*16;
    for(int i=0;i<16;i++){
      double x0=(i-7.5)*12;
      Vtot+=SingleWire(x-x0,y-y0,Va);
    }
    for(int i=0;i<17;i++){
      double x0=(i-8)*12;
      Vtot+=SingleWire(x-x0,y-y0,Vp);
    }
    for(double x0=-200;x0<200;x0+=hc){
      int npar=parVc.size();
      double Vc=parVc[0];
      for(int i=1;i<npar;i++)
	Vc+=parVc[i]*cos(i*2*TMath::Pi()/12*x0);
      Vtot+=SingleWire(x-x0,y-(y0-8),Vc);
      if(l==0) Vtot+=SingleWire(x-x0,y-(y0+8),Vc);
    }
  }
  return Vtot;
}
double func(double *xx,double *par){
  vector<double> parVc(&par[3],&par[3]+(int)par[2]);
  return GetTotalV(xx[0],xx[1],par[0],par[1],parVc);
}
double GetChiSquare(const double *par){
  double chi=0;
  double Vp=par[0];
  double Va=par[1];
  vector<double> parVc(&par[3],&par[3]+int(par[2]));
  for(int i=0;i<6;i++){
    double x=(i-2.5)*12;
    chi+=pow(GetTotalV(x,0,Vp,Va,parVc)-Va0,2)*2;
  }
  for(int i=0;i<7;i++){
    double x=(i-3)*12;
    chi+=pow(GetTotalV(x,0,Vp,Va,parVc)-Vp0,2);
  }
  for(double x=-30;x<30;x+=hc){
    chi+=pow(GetTotalV(x,8,Vp,Va,parVc)-Vc0,2);
    chi+=pow(GetTotalV(x,-8,Vp,Va,parVc)-Vc0,2);
  }
  cout<<Vp<<" "<<Va<<" "<<parVc[0]<<" "<<parVc[1]<<endl;
  cout<<"chi="<<chi<<endl;
  return chi;
}
double Fit(){
  int npar=15;
  vector<double> par={2000,0,6,5,0,0,0,0,0,0,0,0,0,0,0};

  TF2 *finit=new TF2("initial",&func,-20,20,-10,10,npar);
  finit->SetParameters(&par[0]);
  TCanvas *cinit=new TCanvas;
  finit->Draw("colz");
  
  ROOT::Math::Minimizer* minimum = ROOT::Math::Factory::CreateMinimizer("Minuit2","Migrad");
  ROOT::Math::Functor f(&GetChiSquare,npar);
  minimum->SetFunction(f);
  for(int i=0;i<par.size();i++){
    minimum->SetVariable(i,Form("par%d",i),par[i],.1);
  }
  minimum->FixVariable(2);
  
  minimum->Minimize();
  cout<<"Minimum="<<minimum->MinValue()<<endl;
  const double *result=minimum->X();

  TF2 *fresult=new TF2("result",&func,-20,20,-10,10,npar);
  fresult->SetParameters(result);
  cout<<"(0,0): "<<fresult->Eval(0,0)<<endl;
  cout<<"(6,0): "<<fresult->Eval(6,0)<<endl;
  cout<<"(0,8): "<<fresult->Eval(0,8)<<endl;
  cout<<"(6,8): "<<fresult->Eval(6,8)<<endl;
  TCanvas *cresult=new TCanvas;
  fresult->SetNpx(100);
  fresult->SetNpy(100);
  fresult->DrawClone("colz");
  TCanvas *cgrad=new TCanvas;
  fresult->SetNpx(20);
  fresult->SetNpy(10);
  fresult->Draw("ARR");

  return 0;
}
