#ifndef AnalyzerCore_h
#define AnalyzerCore_h

#include "TH2.h"
#include "TKey.h"
#include "TList.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TRegexp.h"
#include "TObjString.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TBRIK.h"

#include <fstream>

#include "SNUDCTree.h"
#include "Line.h"
#include "canvas_margin.h"

class AnalyzerCore : public SNUDCTree {
 public:
  AnalyzerCore();
  ~AnalyzerCore();
  
  Line *fWires[NWIRES];
  TH1 *fTime2Length[NWIRES];
  map<TString,Line*> fTracks;
  TString fOutFileName;
  
  // == Debugging Mode
  bool debug = true;
  TString Cycle_name;
  // == Call all needed maps
  map<TString, TH1*> maphist;
  map<TString, TGraph*> mapgraph;
  map<TString, TFile*> mapfile;
  map<TString, TCanvas*> mapcanvas;
  map<TString, TPad*> mappad;
  map<TString, THStack*> maphstack;
  map<TString, TLegend*> maplegend;
  map<TString, TH1F*> mapfunc;
  map<TString, double> map_overflow;
  map<TString, TLine*> mapline;
  map<TString, TKey*> maphistcheck;
  map<TString, TList*> maplist;
  map<TString, std::vector<double> > map_bin_vector;
  map<TString, std::vector<TString> > map_sample_names;
  map<TString, std::vector<double> > map_syst_array;
  map<TString, std::vector<double> > map_syst_table;

  virtual void DrawChamber() const;
  virtual void DrawWires(TString option="") const;
  virtual void ExecuteEvent();
  virtual void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  virtual double FunctionWireOnly(const double* par) const;
  virtual double FunctionTDC(const double* par) const;
  virtual double GetDriftLength(int n,double time) const;
  virtual int GetEntry(long entry);
  virtual TH1 * GetHist(TString histname) const;
  double GetMaximum(TH1D* hist);
  double GetMaximum(TGraphAsymmErrors *a);
  virtual int GetTDCCount(TString substr) const;
  virtual Line* GetTrack(TString algorithm="");
  virtual Line* GetWire(int n) const;
  virtual Line* GetWire(TString wirename) const;
  TGraphAsymmErrors* GraphSubtract(TGraphAsymmErrors *a, TGraphAsymmErrors *b, bool Rel);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, bool YErrorZero=false);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left, int n_x_shift, int i_x_shift);
  virtual void Loop(int nskip,int nevent);
  TDirectory* MakeTemporaryDirectory();
  virtual Line* ReconstructTrack(TString algorithm);
  void RemoveLargeError(TGraphAsymmErrors *a);
  static TString Replace(TString str,TString reg,TString repl);
  void ScaleGraph(TGraphAsymmErrors *a, double c);
  virtual void SetOutFileName(TString outfilename) { fOutFileName=outfilename; }
  virtual TString GetOutFileName() const { return fOutFileName; }
  virtual int SetupConfig(TString configname);
  static vector<TString> Split(TString s,TString del);
  virtual void WriteHist();
};
#endif
