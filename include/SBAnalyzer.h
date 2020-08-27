#ifndef SBAnalyzer_h
#define SBAnalyzer_h

#include "AnalyzerCore.h"

class SBAnalyzer : public AnalyzerCore {
public :
  SBAnalyzer();

  virtual void     Loop();
  void Draw_Hist(TString histname);
  void Draw_Hist_Cumulative(TString histname);
  
};

#endif

