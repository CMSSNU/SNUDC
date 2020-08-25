#define SNUDC_cxx
#include "SNUDC.h"
#include "mylib.h"
#include "canvas_margin.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TString WORKING_DIR = getenv("SNUDC_WORKING_DIR");
TString root_file_path = WORKING_DIR+"/rootfiles/data/";
TString root_filename = "runA_partial.root";
TString filename = root_file_path + root_filename;

SNUDC::SNUDC(TTree *tree) : fChain(0)
{
  if (tree == 0) {
    TFile *current_file = new TFile ((filename)) ;
    if (!current_file || !current_file->IsOpen()) {
      current_file = new TFile(filename);
    }
    current_file->GetObject("SNUDC",tree);
    
  }
  Init(tree);
}

void Draw_Hist(TString histname){

  TString ENV_PLOT_PATH = getenv("SNUDC_PLOT_PATH");
  TString base_plotpath = ENV_PLOT_PATH + "/";

  TCanvas *c1 = new TCanvas(histname, histname, 600, 600);
  gStyle -> SetOptStat(1111);
  canvas_margin(c1);
  c1->cd();

  maphist_TH1D[histname] -> Draw("hist");

  c1 -> SaveAs(base_plotpath + "/" + histname + ".pdf");
}

void Draw_Hist_Cumulative(TString histname){

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
  TH1* hc =maphist_TH1D[histname] ->GetCumulative();
  hc -> Draw("hist");
  c2 -> SaveAs(base_plotpath + "/" + histname + "_Cumulative.pdf");

}


void SNUDC::Loop()
{
//   In a ROOT session, you can do:
//      root> .L SNUDC.C
//      root> SNUDC t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //Long64_t nentries = 2;
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if(jentry%2000 == 0) cout << jentry << "/" << nentries << " done" << endl;

      for(int i = 0; i < 192; i++){
	if(wires.at(i)->size() > 0){
	  if(i < 16) FillHist("x1_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=16 && i < 32) FillHist("u1_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=32 && i < 48) FillHist("v1_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=48 && i < 64) FillHist("x2_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=64 && i < 80) FillHist("u2_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=80 && i < 96) FillHist("v2_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=96 && i < 112) FillHist("x3_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=112 && i < 128) FillHist("u3_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=128 && i < 144) FillHist("v3_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=144 && i < 160) FillHist("x4_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=160 && i < 176) FillHist("u4_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else if(i >=176 && i < 192) FillHist("v4_TDC", wires.at(i)->at(0), 1., 3000, 0., 3000.);
	  else continue;
	}
      }
   }
 
   TString layers[12] = {"x1", "u1", "v1", "x2", "u2", "v2", "x3", "u3", "v3", "x4", "u4", "v4"};
   for(int i_layer = 0; i_layer < 12; i_layer++){
     Draw_Hist(layers[i_layer] + "_TDC");
     Draw_Hist_Cumulative(layers[i_layer] + "_TDC");
   }

   cout << "nentries : " << nentries << endl;
   cout << "nb : " << nb << endl;
}
