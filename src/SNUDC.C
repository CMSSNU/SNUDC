#define SNUDC_cxx
#include "SNUDC.h"
#include "mylib.h"
#include "canvas_margin.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
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

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }

   cout << "nentries : " << nentries << endl;
   cout << "nb : " << nb << endl;
}
