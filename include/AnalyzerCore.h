#ifndef AnalyzerCore_h
#define AnalyzerCore_h

#include "SNUDCTree.h"
#include "canvas_margin.h"
#include "TH2.h"
#include "TKey.h"
#include "TList.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include <fstream>

class AnalyzerCore : public SNUDCTree {
 public:
  //AnalyzerCore();
  //~AnalyzerCore();
  
  ofstream outfile;

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

  TH1 * GetHist(TString histname);
  void FillHist(TString histname, double value, double weight, int n_bin, double x_min, double x_max);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, bool YErrorZero=false);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left);
  TGraphAsymmErrors* hist_to_graph(TH1D* hist, int n_skip_x_left, int n_x_shift, int i_x_shift);
  TGraphAsymmErrors* GraphSubtract(TGraphAsymmErrors *a, TGraphAsymmErrors *b, bool Rel);
  void RemoveLargeError(TGraphAsymmErrors *a);
  void ScaleGraph(TGraphAsymmErrors *a, double c);
  double GetMaximum(TH1D* hist);
  double GetMaximum(TGraphAsymmErrors *a);
  TDirectory* MakeTemporaryDirectory();
  
};
#endif
