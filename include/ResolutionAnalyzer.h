#ifndef ResolutionAnalyzer_h
#define ResolutionAnalyzer_h

#include "AnalyzerCore.h"

class ResolutionAnalyzer : public AnalyzerCore {
 public:
  virtual void Loop();
  virtual bool IsGolden() const;
};

#endif
