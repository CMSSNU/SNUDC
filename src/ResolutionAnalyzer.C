#ifndef ResolutionAnalyzer_cxx
#define ResolutionAnalyzer_cxx

#include "ResolutionAnalyzer.h"

void ResolutionAnalyzer::Loop(){
  long nentries=GetEntries();
  for(long ientry=0;ientry<nentries;ientry++){
    if(ientry%1000==0) cout<<ientry<<"/"<<nentries<<endl;
    if(ientry>10000) break;
    GetEntry(ientry);
    Line* track=NULL;
    track=GetTrack("TDC");
    if(track){
      for(int i=0;i<NWIRES;i++){
	if(GetTDC(i)->size()){
	  double length=GetDriftLength(i,GetTDC(i)->at(0));
	  double z=GetWire(i)->Z();
	  double length0=GetWire(i)->Distance(track->PointWithZ(z));
	  FillHist("TDC/"+GetWireName(i),length-length0,1,150,-15,15);
	}
      }
    }
    track=GetTrack("WireOnly");
    if(track){
      for(int i=0;i<NWIRES;i++){
	if(GetTDC(i)->size()){
	  double length=GetDriftLength(i,GetTDC(i)->at(0));
	  double z=GetWire(i)->Z();
	  double length0=GetWire(i)->Distance(track->PointWithZ(z));
	  FillHist("WireOnly/"+GetWireName(i),length-length0,1,150,-15,15);
	}
      }
    }
  }

  TFile f("resolution.root","recreate");
  WriteHist();
}
    
#endif
