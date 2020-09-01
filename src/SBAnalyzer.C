#ifndef SBAnalyzer_cxx
#define SBAnalyzer_cxx

#include "SBAnalyzer.h"

void SBAnalyzer::Draw_Hist(TString histname){

  TString ENV_PLOT_PATH = getenv("SNUDC_PLOT_PATH");
  TString base_plotpath = ENV_PLOT_PATH + "/";

  TCanvas *c1 = new TCanvas(histname, histname, 600, 600);
  gStyle -> SetOptStat(1111);
  canvas_margin(c1);
  c1->cd();

  TH1* hist=GetHist(histname);
  if(hist) hist->Draw("hist");

  c1 -> SaveAs(base_plotpath + "/" + histname + ".pdf");
}

void SBAnalyzer::Draw_Hist_Cumulative(TString histname){

  TString ENV_PLOT_PATH = getenv("SNUDC_PLOT_PATH");
  TString base_plotpath = ENV_PLOT_PATH + "/";

  TCanvas *c2 = new TCanvas(histname + "_Cumulative", histname + "_Cumulative", 600, 600);
  gStyle -> SetOptStat(1111);
  gStyle->SetStatX(0.3);
  gStyle->SetStatY(0.9);
  gStyle->SetStatW(0.1);
  gStyle->SetStatH(0.1);
  canvas_margin(c2);
  c2->cd();
  TH1* hist=GetHist(histname);
  if(hist){
    TH1* hc =hist->GetCumulative();
    hc -> Draw("hist");
  }
  c2 -> SaveAs(base_plotpath + "/" + histname + "_Cumulative.pdf");

}


void SBAnalyzer::ExecuteEvent()
{
  for(int i = 0; i < NWIRES; i++){
    if(GetTDC(i)->size() > 0){
      FillHist(GetWireName(i)(0,2)+"_TDC", GetTDC(i)->at(0), 1., 3000, 0., 3000.);
    }
  }
}
void SBAnalyzer::WriteHist(){
  TString layers[12] = {"x1", "u1", "v1", "x2", "u2", "v2", "x3", "u3", "v3", "x4", "u4", "v4"};
  for(int i_layer = 0; i_layer < 12; i_layer++){
    Draw_Hist(layers[i_layer] + "_TDC");
    Draw_Hist_Cumulative(layers[i_layer] + "_TDC");
  }
}
#endif
