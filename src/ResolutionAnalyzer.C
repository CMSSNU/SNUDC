#ifndef ResolutionAnalyzer_cxx
#define ResolutionAnalyzer_cxx

#include "ResolutionAnalyzer.h"

void ResolutionAnalyzer::Loop(){
  long nentries=GetEntries();
  for(long ientry=0;ientry<nentries;ientry++){
    if(ientry%1000==0) cout<<ientry<<"/"<<nentries<<endl;
    //if(ientry>50000) break;
    GetEntry(ientry);
    Line* track=NULL;
    track=GetTrack("TDC");
    bool golden=IsGolden();
    if(track){
      for(int i=0;i<NWIRES;i++){
	if(GetTDC(i)->size()){
	  double maxdriftlength=6;
	  double scale=1;
	  if(GetWireName(i).BeginsWith("x")) scale=8.5/6;

	  double z=GetWire(i)->Z();
	  TVector3 track_point=track->PointWithZ(z);	
	  double x0=track_point.X();
	  double y0=track_point.Y();

	  TVector3 wire_point=GetWire(i)->PointWithX(x0);
	  double y1=wire_point.Y()+GetDriftLength(i,GetTDC(i)->at(0))*maxdriftlength*scale;
	  double y2=wire_point.Y()-GetDriftLength(i,GetTDC(i)->at(0))*maxdriftlength*scale;
	  if(fabs(y1-y0)<fabs(y2-y0)) FillHist("TDC/"+GetWireName(i),(y1-y0)/scale,1,100,-20,20);
	  else FillHist("TDC/"+GetWireName(i),(y2-y0)/scale,1,100,-20,20);
	  if(golden){
	    if(fabs(y1-y0)<fabs(y2-y0)) FillHist("TDC/golden/"+GetWireName(i),(y1-y0)/scale,1,100,-20,20);
	    else FillHist("TDC/golden/"+GetWireName(i),(y2-y0)/scale,1,100,-20,20);
	  }
	}
      }
    }
    track=GetTrack("WireOnly");
    if(track){
      for(int i=0;i<NWIRES;i++){
	if(GetTDC(i)->size()){
	  double scale=1;
	  if(GetWireName(i).BeginsWith("x")) scale=8.5/6;

	  double z=GetWire(i)->Z();
	  TVector3 track_point=track->PointWithZ(z);	
	  double x0=track_point.X();
	  double y0=track_point.Y();

	  TVector3 wire_point=GetWire(i)->PointWithX(x0);
	  double y=wire_point.Y();
	  FillHist("WireOnly/"+GetWireName(i),(y-y0)/scale,1,100,-20,20);
	  if(golden){
	    FillHist("WireOnly/golden/"+GetWireName(i),(y-y0)/scale,1,100,-20,20);
	  }
	}
      }
    }
  }

  TFile f("resolution.root","recreate");
  WriteHist();
}

bool ResolutionAnalyzer::IsGolden() const {
  vector<TString> layers={"x3","u3","v3","x4","u4","v4"};
  for(const auto& layer:layers)
    if(GetTDCCount(layer)!=1) return false;
  return true;
}
#endif
