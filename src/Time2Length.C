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
#endif
