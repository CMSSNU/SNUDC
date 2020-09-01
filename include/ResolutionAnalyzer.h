#ifndef ResolutionAnalyzer_h
#define ResolutionAnalyzer_h

#include "AnalyzerCore.h"

class ResolutionAnalyzer : public AnalyzerCore {
 public:
  virtual void ExecuteEvent();
  virtual bool IsGolden() const;
  virtual void RemoveInvalidHit();
};

#endif
