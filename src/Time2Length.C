#ifndef Time2Length_cxx
#define Time2Length_cxx

#include "Time2Length.h"

void Time2Length::Loop(){
  SetupConfig("runA");
  int entries=GetEntries();
  for(int ientry=0;ientry<entries;ientry++){
    GetEntry(ientry);
    for(int iw=0;iw<NWIRES;iw++){
      if(GetTDC(iw)->size()){
	FillHist(GetWireName(iw),GetTDC(iw)->at(0),1,1100,900,2000);
      }
    }
  }
  TFile f("time2length.root","recreate");
  for(auto it:maphist){
    TH1* hist=it.second;
    TH1* chist=hist->GetCumulative(true,"");
    chist->Scale(1/chist->GetMaximum());
    chist->Write();
  }
}

#endif
