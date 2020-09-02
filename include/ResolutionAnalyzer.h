#ifndef ResolutionAnalyzer_h
#define ResolutionAnalyzer_h

#include "AnalyzerCore.h"

class ResolutionAnalyzer : public AnalyzerCore {
 public:
  ResolutionAnalyzer(){ fReportEvery=100; }
  virtual Line* ReconstructTrack(TString algorithm);
  virtual void ExecuteEvent();
  virtual bool IsGolden() const;
  virtual void RemoveInvalidHit();
};

#endif
