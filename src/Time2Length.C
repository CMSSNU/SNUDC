#ifndef Time2Length_cxx
#define Time2Length_cxx

#include "Time2Length.h"

void Time2Length::ExecuteEvent(){
  for(int iw=0;iw<NWIRES;iw++){
    if(GetTDC(iw)->size()){
      FillHist(GetWireName(iw),GetTDC(iw)->at(0),1,1100,900,2000);
    }
  }
}
void Time2Length::ProcessHist(){
  for(auto& it:maphist){
    TH1* hist=it.second;
    TH1* chist=hist->GetCumulative(true,"");
    chist->Scale(1/chist->GetMaximum());
    chist->SetDirectory(0);
    it.second=chist;
    delete hist;
  }
}
#endif
