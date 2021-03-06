#ifndef AnalyzerCore_cxx
#define AnalyzerCore_cxx

#include "AnalyzerCore.h"

AnalyzerCore::AnalyzerCore(){
  for(int i=0;i<NWIRES;i++){
    fWires[i]=new Line(0,0,0,0,0);
    fTime2Length[i]=NULL;
  }
}
AnalyzerCore::~AnalyzerCore(){
  for(int i=0;i<NWIRES;i++){
    if(fWires[i]) delete fWires[i];
    if(fTime2Length[i]) delete fTime2Length[i];
  }
  for(auto& track:fTracks)
    if(track.second) delete track.second;
  fTracks.clear();
}

TCanvas* AnalyzerCore::DrawChamber() const {
  TCanvas *c=new TCanvas;
  double rmin[]={-300,-300,-300};
  double rmax[]={300,300,300};
  TView3D* view=new TView3D(1,rmin,rmax);
  view->ShowAxis();
  TBRIK* chamber=new TBRIK(Form("chamber_run%d_event%d",run,event),"chamber","",fChamber_dx,fChamber_dy,fChamber_dz);
  chamber->Draw();
  return c;
}
TPolyLine3D* AnalyzerCore::DrawTrack(TString algorithm) {
  Line* track=GetTrack(algorithm);
  TPolyLine3D* line=track->Draw();
  line->SetLineColor(3);
  return line;
}
void AnalyzerCore::DrawWires(TString option) const {
  option.ToLower();
  for(int i=0;i<NWIRES;i++){
    bool draw=false;
    TPolyLine3D* l=new TPolyLine3D(2);
    TVector3 start=GetWire(i)->PointWithX(-95);
    TVector3 end=GetWire(i)->PointWithX(95);
    l->SetPoint(0,start.X(),start.Y(),start.Z());
    l->SetPoint(1,end.X(),end.Y(),end.Z());
    if(option.Contains("all")) draw=true;
    if(fChain->GetBranchStatus(GetWireName(i))){
      if(option.Contains("on")) draw=true;
      l->SetLineColor(kBlack);
      if(GetTDC(i)->size()){
	draw=true;
	l->SetLineColor(kRed);
	l->SetLineWidth(2);
      }
    }else{
      l->SetLineStyle(2);
      l->SetLineColor(kGray);
    }
    if(draw) l->Draw();
  }
}
void AnalyzerCore::ExecuteEvent(){  
}
void AnalyzerCore::FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max){
  TH1 *this_hist = GetHist(histname);
  if( !this_hist ){
    this_hist = new TH1D(histname, "", n_bin, x_min, x_max);
    this_hist->SetDirectory(NULL);
    maphist[histname] = this_hist;
  }

  this_hist->Fill(value, weight);
}
void AnalyzerCore::FillHist(TString histname, double value_x, double value_y, double weight, int n_bin_x, double x_min, double x_max, int n_bin_y, double y_min, double y_max){
  TH1 *this_hist = GetHist(histname);
  if( !this_hist ){
    this_hist = new TH2D(histname, "", n_bin_y, x_min, x_max, n_bin_y, y_min, y_max);
    this_hist->SetDirectory(NULL);
    maphist[histname] = this_hist;
  }
  if(!this_hist->InheritsFrom("TH2")){
    cout<<"[AnalyzerCore::FillHist] "<<histname<<" already exist with different class"<<endl;
    return;
  }
  ((TH2*)this_hist)->Fill(value_x, value_y, weight);
}

double AnalyzerCore::FunctionQuick(const double *par) const{
  Line track(par[0],par[1],-fChamber_dz,par[2],par[3],fChamber_dz);
  double chi2=0;
  for(int i=0;i<NWIRES;i++){
    if(GetTDC(i)->size()){
      chi2+=pow(track.Distance(*GetWire(i)),2);
    }
  }
  return chi2;
}
double AnalyzerCore::FunctionWireOnly(const double *par) const{
  Line track(par[0],par[1],-fChamber_dz,par[2],par[3],fChamber_dz);
  double chi2=0;
  int layercount[12]={};
  for(int l=0;l<12;l++)
    for(int w=0;w<16;w++)
      if(GetTDC(w+16*l)->size()) layercount[l]++;
      
  for(int i=0;i<NWIRES;i++){
    if(GetTDC(i)->size()){
      chi2+=pow(track.Distance(*GetWire(i))/sqrt(12)*12,2);
    }
  }
  return chi2;
}

double AnalyzerCore::FunctionTDC(const double *par) const{
  Line track(par[0],par[1],-fChamber_dz,par[2],par[3],fChamber_dz);
  double chi2=0;
  for(int l=0;l<12;l++){
    double this_chi2=99999;
    for(int w=0;w<16;w++){
      int i=16*l+w;
      if(GetTDC(i)->size()){
	Line l1=*GetWire(i);
	Line l2=*GetWire(i);
	TString axis=GetWireName(i)(0);
	double length=GetDriftLength(i,GetTDC(i)->at(0));
	if(axis=="x"){
	  l1.SetY(l1.Y()+6*length);
	  l2.SetY(l2.Y()-6*length);
	}else{
	  l1.SetY(l1.Y()+8.5*length);
	  l2.SetY(l2.Y()-8.5*length);
	}
	TVector3 track_point=track.PointWithZ(GetWire(i)->Z());
	double val1=pow(l1.Distance(track_point),2);
	double val2=pow(l2.Distance(track_point),2);
	double val=TMath::Min(val1,val2);
	if(val<this_chi2) this_chi2=val;
      }
    }
    if(this_chi2!=99999) chi2+=this_chi2;
  }

  return chi2;
}
double AnalyzerCore::GetDriftLength(int n,double time) const {
  if(n<0||n>=NWIRES) return -999;
  if(!fTime2Length[n]){
    cout<<"[AnalyzerCore::GetDriftLength] no Time2Length histogram"<<endl;
    return -999;
  }
  int ibin=fTime2Length[n]->FindBin(time);
  int first=fTime2Length[n]->GetXaxis()->GetFirst();
  if(ibin<first) ibin=first;
  int last=fTime2Length[n]->GetXaxis()->GetLast();
  if(ibin>last) ibin=last;
  return fTime2Length[n]->GetBinContent(ibin);
}

int AnalyzerCore::GetEntry(long entry){
  for(auto& track:fTracks)
    if(track.second) delete track.second;
  fTracks.clear();  
  return SNUDCTree::GetEntry(entry);
}
TH1 * AnalyzerCore::GetHist(TString histname) const{

  TH1 *h = NULL;
  std::map<TString, TH1*>::const_iterator mapit = maphist.find(histname);
  if(mapit != maphist.end()) return mapit->second;

  return h;

}
double AnalyzerCore::GetMaximum(TH1D* hist){

  TAxis *xaxis = hist->GetXaxis();

  double maxval(-1.);
  for(int i=1; i<=xaxis->GetNbins(); i++){
    if( hist->GetBinContent(i) + hist->GetBinError(i) > maxval ){
      maxval = hist->GetBinContent(i) + hist->GetBinError(i);
    }
  }

  return maxval;

}

double AnalyzerCore::GetMaximum(TGraphAsymmErrors *a){

  int NX = a->GetN();

  double maxval(-9999.);
  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if( y+yerr_high > maxval ){
      maxval = y+yerr_high;
    }

  }

  return maxval;

}
int AnalyzerCore::GetTDCCount(TString substr) const {
  int count=0;
  for(int i=0;i<NWIRES;i++)
    if(GetTDC(i)->size())
      if(GetWireName(i).Contains(substr))
	count+=GetTDC(i)->size();
  return count;
} 

Line* AnalyzerCore::GetTrack(TString algorithm){
  Line* track=NULL;
  auto it=fTracks.find(algorithm);
  if(it!=fTracks.end()) track=it->second;
  else{
    track=ReconstructTrack(algorithm);
    if(track) fTracks[algorithm]=track;
  }
  return track;
}

Line* AnalyzerCore::GetWire(int n) const {
  if(n<0||n>=NWIRES) return NULL;
  else return fWires[n];
}

Line* AnalyzerCore::GetWire(TString wirename) const {
  return GetWire(GetWireNumber(wirename));
}

TGraphAsymmErrors* AnalyzerCore::GraphSubtract(TGraphAsymmErrors *a, TGraphAsymmErrors *b, bool Rel){

  //==== do a-b

  int NX = a->GetN();
  TGraphAsymmErrors* gr_out = (TGraphAsymmErrors*)a->Clone();

  for(int i=0; i<NX; i++){

    double a_x, a_y, b_x, b_y;

    a->GetPoint(i, a_x, a_y);
    b->GetPoint(i, b_x, b_y);

    if(Rel==true){
      gr_out->SetPoint( i, a_x, (a_y-b_y)/b_y );
    }
    else{
      gr_out->SetPoint( i, a_x, a_y-b_y );
    }

  }

  return gr_out;

}

TGraphAsymmErrors* AnalyzerCore::hist_to_graph(TH1D* hist, bool YErrorZero){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=0; i<Nbins; i++){
    x[i] = xaxis->GetBinCenter(i+1);
    y[i] = hist->GetBinContent(i+1);
    xlow[i] = xaxis->GetBinCenter(i+1)-xaxis->GetBinLowEdge(i+1);
    xup[i] = xaxis->GetBinUpEdge(i+1)-xaxis->GetBinCenter(i+1);
    ylow[i] = hist->GetBinError(i+1);
    yup[i] = hist->GetBinError(i+1);
    if(YErrorZero){
      ylow[i] = 0;
      yup[i] = 0;
    }
    //ylow[i] = 0;
    //yup[i] = 0;
    //cout << "x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}

TGraphAsymmErrors* AnalyzerCore::hist_to_graph(TH1D* hist, int n_skip_x_left){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);
    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}

TGraphAsymmErrors* AnalyzerCore::hist_to_graph(TH1D* hist, int n_skip_x_left, int n_x_shift, int i_x_shift){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins()-n_skip_x_left;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=1; i<=Nbins; i++){
    x[i-1] = xaxis->GetBinCenter(i+n_skip_x_left);
    y[i-1] = hist->GetBinContent(i+n_skip_x_left);
    xlow[i-1] = xaxis->GetBinCenter(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left);
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinCenter(i+n_skip_x_left);
    ylow[i-1] = hist->GetBinError(i+n_skip_x_left);
    yup[i-1] = hist->GetBinError(i+n_skip_x_left);

    double dx = (xaxis->GetBinUpEdge(i+n_skip_x_left)-xaxis->GetBinLowEdge(i+n_skip_x_left))/double(n_x_shift+1);
    x[i-1] = xaxis->GetBinLowEdge(i+n_skip_x_left) + double(i_x_shift+1) * dx;
    xlow[i-1] = double(i_x_shift+1) * dx;
    xup[i-1] = xaxis->GetBinUpEdge(i+n_skip_x_left)-x[i-1];

    //ylow[i-1] = 0;
    //yup[i-1] = 0;
    //cout << "x = " << x[i-1] << ", y = " << y[i-1] << ", x_low = " << xlow[i-1] << ", xup = " << xup[i-1] << ", ylow = " << ylow[i-1] << ", yup = " << yup[i-1] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}
void AnalyzerCore::LoadHist(TString filename){
  TFile *f=new TFile(filename);
  LoadHist(f);
  f->Close();
}

void AnalyzerCore::LoadHist(TDirectory* dir){
  for(const auto& key:*dir->GetListOfKeys()){
    TObject* obj=((TKey*)key)->ReadObj();
    if(obj->InheritsFrom("TDirectory")) LoadHist((TDirectory*)obj);
    else if(obj->InheritsFrom("TH1")){
      TH1* hist=(TH1*)obj;
      hist->SetDirectory(0);
      maphist[hist->GetName()]=hist;
    }
  } 
}

void AnalyzerCore::Loop(int nskip,int nevent,bool doProcessHist){
  if (fChain == 0) return;
  Long64_t nentries = GetEntries();
  if(nevent>-1){
    if(nentries>nskip+nevent) nentries=nskip+nevent;
  }

  for (Long64_t jentry=nskip; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if((jentry-nskip)%fReportEvery==0) cout<<jentry-nskip<<"/"<<nentries-nskip<<endl;
    GetEntry(jentry);
    ExecuteEvent();
  }
  if(doProcessHist) ProcessHist();
  WriteHist();
}
void AnalyzerCore::PrintTDCCount() const {
  for(int l=0;l<12;l++){
    cout<<GetWireName(16*l)(0,2)<<" ";
    for(int w=0;w<16;w++){
      cout<<GetTDC(16*l+w)->size()<<" ";
    }
    cout<<endl;
  }
}
void AnalyzerCore::ProcessHist(){
}

TDirectory* AnalyzerCore::MakeTemporaryDirectory(){

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    TString dirname=Form("HNCommonLeptonFakes_%d",counter);
    if (gROOT->GetDirectory(dirname) ){
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir(dirname);

  }

  return tempDir;

}

Line* AnalyzerCore::ReconstructTrack(TString algorithm){
  Line* track=NULL;
  ROOT::Math::Minimizer* minimizer=ROOT::Math::Factory::CreateMinimizer("Minuit2","Migrad");
  if(algorithm=="Quick"){
    ROOT::Math::Functor f(this,&AnalyzerCore::FunctionQuick,4);
    minimizer->SetFunction(f);
    minimizer->SetLimitedVariable(0,"x1",0,0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(1,"y1",0,0.1,-fChamber_dy,fChamber_dy);
    minimizer->SetLimitedVariable(2,"x2",0,0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(3,"y2",0,0.1,-fChamber_dy,fChamber_dy);
    minimizer->Minimize();
    const double *minimum=minimizer->X();
    track=new Line(minimum[0],minimum[1],-fChamber_dz,minimum[2],minimum[3],fChamber_dz);    
  }else if(algorithm=="WireOnly"){
    Line* initial=GetTrack("Quick");
    ROOT::Math::Functor f(this,&AnalyzerCore::FunctionWireOnly,4);
    minimizer->SetFunction(f);
    minimizer->SetLimitedVariable(0,"x1",initial->PointWithZ(-fChamber_dz).X(),0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(1,"y1",initial->PointWithZ(-fChamber_dz).Y(),0.1,-fChamber_dy,fChamber_dy);
    minimizer->SetLimitedVariable(2,"x2",initial->PointWithZ(+fChamber_dz).X(),0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(3,"y2",initial->PointWithZ(+fChamber_dz).Y(),0.1,-fChamber_dy,fChamber_dy);
    minimizer->Minimize();
    const double *minimum=minimizer->X();
    track=new Line(minimum[0],minimum[1],-fChamber_dz,minimum[2],minimum[3],fChamber_dz);    
  }else if(algorithm=="TDC"){
    Line* initial=GetTrack("Quick");
    ROOT::Math::Functor f(this,&AnalyzerCore::FunctionTDC,4);
    minimizer->SetFunction(f);
    minimizer->SetLimitedVariable(0,"x1",initial->PointWithZ(-fChamber_dz).X(),0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(1,"y1",initial->PointWithZ(-fChamber_dz).Y(),0.1,-fChamber_dy,fChamber_dy);
    minimizer->SetLimitedVariable(2,"x2",initial->PointWithZ(+fChamber_dz).X(),0.1,-fChamber_dx,fChamber_dx);
    minimizer->SetLimitedVariable(3,"y2",initial->PointWithZ(+fChamber_dz).Y(),0.1,-fChamber_dy,fChamber_dy);
    minimizer->Minimize();
    const double *minimum=minimizer->X();
    track=new Line(minimum[0],minimum[1],-fChamber_dz,minimum[2],minimum[3],fChamber_dz);    
  }else{
    cout<<"[AnalyzerCore::ReconstructTrack] Unknown algorithm "<<algorithm<<endl;
  }
  delete minimizer;
  return track;
}

void AnalyzerCore::RemoveLargeError(TGraphAsymmErrors *a){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    if(y+yerr_high==1.){
      a->SetPointEYhigh( i, yerr_low );
    }

  }

}

TString AnalyzerCore::Replace(TString str,TString reg,TString repl){
  if(reg=="") return str;
  int extent;
  int start=str.Index(TRegexp(reg),&extent);
  if(start>=0) return str.Replace(start,extent,repl);
  else return str;
}

void AnalyzerCore::ScaleGraph(TGraphAsymmErrors *a, double c){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    a->SetPoint(i, x, c*y);
    a->SetPointEYlow(i, c*yerr_low);
    a->SetPointEYhigh(i, c*yerr_high);

  }

}

int AnalyzerCore::SetupConfig(TString configname){
  TString configpath=getenv("SNUDC_WORKING_DIR")+TString("/config/")+configname;
  cout<<"[AnalyzerCore::SetupConfig] using config directory "<<configpath<<endl;

  // Setup input data files
  ifstream fdata(configpath+"/datapath.txt");
  if(fdata.is_open()){
    while(!fdata.eof()){
      TString line;
      line.ReadLine(fdata);
      if(line==""||line.Contains(TRegexp("^[ \t]*#"))) continue;
      vector<TString> files=Split(gSystem->GetFromPipe("find "+line+" -type f -name '*.root'| sort -V"),"\n");
      for(const auto& file:files) fChain->Add(file);
    }
  }else{
    cout<<"[AnalyzerCore::SetupConfig] No datapath.txt in "<<configpath<<endl;
    return -1;
  }
  fdata.close();
  TObjArray* listoffiles=fChain->GetListOfFiles();
  cout<<"[AnalyzerCore::SetupConfig] "<<listoffiles->GetEntries()<<" files are loaded"<<endl;
  cout<<"  "<<listoffiles->First()->GetTitle()<<endl;
  cout<<"  ..."<<endl;
  cout<<"  "<<listoffiles->Last()->GetTitle()<<endl;
  Init();

  //setup wires
  ifstream fwire(configpath+"/wire.txt");
  if(fwire.is_open()){
    while(!fwire.eof()){
      TString s;
      s.ReadLine(fwire);
      s.ReplaceAll("\t"," ");
      if(s==""||s.Contains(TRegexp("^[\t ]*#"))) continue;
      vector<TString> num=Split(s," ");
      if(num.size()<7){
	cout<<"[AnalyzerCore::SetupConfig] Wrong wire.txt format"<<endl;
	return -1;
      }
      GetWire(num[0].Atoi())->SetXYZXYZ(num[1].Atof(),num[2].Atof(),num[3].Atof(),num[4].Atof(),num[5].Atof(),num[6].Atof());
      if(num.size()>7){
	TString onoff=num[7];
	onoff.ToUpper();
	if(onoff=="OFF"||onoff=="0"||onoff=="FALSE")
	  fChain->SetBranchStatus(GetWireName(num[0].Atoi()),false);
      }
    }
    cout<<"[AnalyzerCore::SetupConfig] Setup wire alignment"<<endl;    
  }else{
    cout<<"[AnalyzerCore::SetupConfig] No wire.txt in "<<configpath<<endl;
    return -1;
  }
  fwire.close();

  //setup time2length
  TFile *f=new TFile(configpath+"/time2length.root");
  if(f->IsZombie()){
    cout<<"[AnalyzerCore::SetupConfig] No time2length.root in "<<configpath<<endl;
  }else{
    cout<<"[AnalyzerCore::SetupConfig] Setup time2length histograms"<<endl;
    for(int i=0;i<NWIRES;i++){
      fTime2Length[i]=(TH1*)f->Get(GetWireName(i)+"_cumulative");
      fTime2Length[i]->Scale(1/fTime2Length[i]->GetMaximum());
      fTime2Length[i]->SetDirectory(0);
    }
  } 
  delete f;
  
  return 1;
}

vector<TString> AnalyzerCore::Split(TString s,TString del){
  TObjArray* array=s.Tokenize(del);
  vector<TString> out;
  for(const auto& obj:*array){
    out.push_back(((TObjString*)obj)->String());
  }
  array->Delete();
  return out;
}

void AnalyzerCore::WriteHist(){
  TFile *f=NULL;
  if(fOutFileName=="") f=new TFile("hist.root","recreate");
  else f=new TFile(fOutFileName,"recreate");

  for(const auto& it:maphist){
    TString this_fullname=it.second->GetName();
    TString this_name=this_fullname(this_fullname.Last('/')+1,this_fullname.Length());
    TString this_prefix=this_fullname(0,this_fullname.Last('/'));
    TDirectory *dir = f->GetDirectory(this_prefix);
    if(!dir){
      f->mkdir(this_prefix);
    }
    f->cd(this_prefix);
    it.second->Write(this_name);
    f->cd();
  }
  f->Close();
}
#endif
