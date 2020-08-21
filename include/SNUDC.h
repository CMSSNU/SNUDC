//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 21 14:40:50 2020 by ROOT version 6.12/06
// from TTree SNUDC/SNUCD
// found on file: runA_partial.root
//////////////////////////////////////////////////////////

#ifndef SNUDC_h
#define SNUDC_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class SNUDC {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   vector<int>     *x1_0;
   vector<int>     *x1_1;
   vector<int>     *x1_2;
   vector<int>     *x1_3;
   vector<int>     *x1_4;
   vector<int>     *x1_5;
   vector<int>     *x1_6;
   vector<int>     *x1_7;
   vector<int>     *x1_8;
   vector<int>     *x1_9;
   vector<int>     *x1_10;
   vector<int>     *x1_11;
   vector<int>     *x1_12;
   vector<int>     *x1_13;
   vector<int>     *x1_14;
   vector<int>     *x1_15;
   vector<int>     *u1_0;
   vector<int>     *u1_1;
   vector<int>     *u1_2;
   vector<int>     *u1_3;
   vector<int>     *u1_4;
   vector<int>     *u1_5;
   vector<int>     *u1_6;
   vector<int>     *u1_7;
   vector<int>     *u1_8;
   vector<int>     *u1_9;
   vector<int>     *u1_10;
   vector<int>     *u1_11;
   vector<int>     *u1_12;
   vector<int>     *u1_13;
   vector<int>     *u1_14;
   vector<int>     *u1_15;
   vector<int>     *v1_0;
   vector<int>     *v1_1;
   vector<int>     *v1_2;
   vector<int>     *v1_3;
   vector<int>     *v1_4;
   vector<int>     *v1_5;
   vector<int>     *v1_6;
   vector<int>     *v1_7;
   vector<int>     *v1_8;
   vector<int>     *v1_9;
   vector<int>     *v1_10;
   vector<int>     *v1_11;
   vector<int>     *v1_12;
   vector<int>     *v1_13;
   vector<int>     *v1_14;
   vector<int>     *v1_15;
   vector<int>     *x2_0;
   vector<int>     *x2_1;
   vector<int>     *x2_2;
   vector<int>     *x2_3;
   vector<int>     *x2_4;
   vector<int>     *x2_5;
   vector<int>     *x2_6;
   vector<int>     *x2_7;
   vector<int>     *x2_8;
   vector<int>     *x2_9;
   vector<int>     *x2_10;
   vector<int>     *x2_11;
   vector<int>     *x2_12;
   vector<int>     *x2_13;
   vector<int>     *x2_14;
   vector<int>     *x2_15;
   vector<int>     *u2_0;
   vector<int>     *u2_1;
   vector<int>     *u2_2;
   vector<int>     *u2_3;
   vector<int>     *u2_4;
   vector<int>     *u2_5;
   vector<int>     *u2_6;
   vector<int>     *u2_7;
   vector<int>     *u2_8;
   vector<int>     *u2_9;
   vector<int>     *u2_10;
   vector<int>     *u2_11;
   vector<int>     *u2_12;
   vector<int>     *u2_13;
   vector<int>     *u2_14;
   vector<int>     *u2_15;
   vector<int>     *v2_0;
   vector<int>     *v2_1;
   vector<int>     *v2_2;
   vector<int>     *v2_3;
   vector<int>     *v2_4;
   vector<int>     *v2_5;
   vector<int>     *v2_6;
   vector<int>     *v2_7;
   vector<int>     *v2_8;
   vector<int>     *v2_9;
   vector<int>     *v2_10;
   vector<int>     *v2_11;
   vector<int>     *v2_12;
   vector<int>     *v2_13;
   vector<int>     *v2_14;
   vector<int>     *v2_15;
   vector<int>     *x3_0;
   vector<int>     *x3_1;
   vector<int>     *x3_2;
   vector<int>     *x3_3;
   vector<int>     *x3_4;
   vector<int>     *x3_5;
   vector<int>     *x3_6;
   vector<int>     *x3_7;
   vector<int>     *x3_8;
   vector<int>     *x3_9;
   vector<int>     *x3_10;
   vector<int>     *x3_11;
   vector<int>     *x3_12;
   vector<int>     *x3_13;
   vector<int>     *x3_14;
   vector<int>     *x3_15;
   vector<int>     *u3_0;
   vector<int>     *u3_1;
   vector<int>     *u3_2;
   vector<int>     *u3_3;
   vector<int>     *u3_4;
   vector<int>     *u3_5;
   vector<int>     *u3_6;
   vector<int>     *u3_7;
   vector<int>     *u3_8;
   vector<int>     *u3_9;
   vector<int>     *u3_10;
   vector<int>     *u3_11;
   vector<int>     *u3_12;
   vector<int>     *u3_13;
   vector<int>     *u3_14;
   vector<int>     *u3_15;
   vector<int>     *v3_0;
   vector<int>     *v3_1;
   vector<int>     *v3_2;
   vector<int>     *v3_3;
   vector<int>     *v3_4;
   vector<int>     *v3_5;
   vector<int>     *v3_6;
   vector<int>     *v3_7;
   vector<int>     *v3_8;
   vector<int>     *v3_9;
   vector<int>     *v3_10;
   vector<int>     *v3_11;
   vector<int>     *v3_12;
   vector<int>     *v3_13;
   vector<int>     *v3_14;
   vector<int>     *v3_15;
   vector<int>     *x4_0;
   vector<int>     *x4_1;
   vector<int>     *x4_2;
   vector<int>     *x4_3;
   vector<int>     *x4_4;
   vector<int>     *x4_5;
   vector<int>     *x4_6;
   vector<int>     *x4_7;
   vector<int>     *x4_8;
   vector<int>     *x4_9;
   vector<int>     *x4_10;
   vector<int>     *x4_11;
   vector<int>     *x4_12;
   vector<int>     *x4_13;
   vector<int>     *x4_14;
   vector<int>     *x4_15;
   vector<int>     *u4_0;
   vector<int>     *u4_1;
   vector<int>     *u4_2;
   vector<int>     *u4_3;
   vector<int>     *u4_4;
   vector<int>     *u4_5;
   vector<int>     *u4_6;
   vector<int>     *u4_7;
   vector<int>     *u4_8;
   vector<int>     *u4_9;
   vector<int>     *u4_10;
   vector<int>     *u4_11;
   vector<int>     *u4_12;
   vector<int>     *u4_13;
   vector<int>     *u4_14;
   vector<int>     *u4_15;
   vector<int>     *v4_0;
   vector<int>     *v4_1;
   vector<int>     *v4_2;
   vector<int>     *v4_3;
   vector<int>     *v4_4;
   vector<int>     *v4_5;
   vector<int>     *v4_6;
   vector<int>     *v4_7;
   vector<int>     *v4_8;
   vector<int>     *v4_9;
   vector<int>     *v4_10;
   vector<int>     *v4_11;
   vector<int>     *v4_12;
   vector<int>     *v4_13;
   vector<int>     *v4_14;
   vector<int>     *v4_15;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_x1_0;   //!
   TBranch        *b_x1_1;   //!
   TBranch        *b_x1_2;   //!
   TBranch        *b_x1_3;   //!
   TBranch        *b_x1_4;   //!
   TBranch        *b_x1_5;   //!
   TBranch        *b_x1_6;   //!
   TBranch        *b_x1_7;   //!
   TBranch        *b_x1_8;   //!
   TBranch        *b_x1_9;   //!
   TBranch        *b_x1_10;   //!
   TBranch        *b_x1_11;   //!
   TBranch        *b_x1_12;   //!
   TBranch        *b_x1_13;   //!
   TBranch        *b_x1_14;   //!
   TBranch        *b_x1_15;   //!
   TBranch        *b_u1_0;   //!
   TBranch        *b_u1_1;   //!
   TBranch        *b_u1_2;   //!
   TBranch        *b_u1_3;   //!
   TBranch        *b_u1_4;   //!
   TBranch        *b_u1_5;   //!
   TBranch        *b_u1_6;   //!
   TBranch        *b_u1_7;   //!
   TBranch        *b_u1_8;   //!
   TBranch        *b_u1_9;   //!
   TBranch        *b_u1_10;   //!
   TBranch        *b_u1_11;   //!
   TBranch        *b_u1_12;   //!
   TBranch        *b_u1_13;   //!
   TBranch        *b_u1_14;   //!
   TBranch        *b_u1_15;   //!
   TBranch        *b_v1_0;   //!
   TBranch        *b_v1_1;   //!
   TBranch        *b_v1_2;   //!
   TBranch        *b_v1_3;   //!
   TBranch        *b_v1_4;   //!
   TBranch        *b_v1_5;   //!
   TBranch        *b_v1_6;   //!
   TBranch        *b_v1_7;   //!
   TBranch        *b_v1_8;   //!
   TBranch        *b_v1_9;   //!
   TBranch        *b_v1_10;   //!
   TBranch        *b_v1_11;   //!
   TBranch        *b_v1_12;   //!
   TBranch        *b_v1_13;   //!
   TBranch        *b_v1_14;   //!
   TBranch        *b_v1_15;   //!
   TBranch        *b_x2_0;   //!
   TBranch        *b_x2_1;   //!
   TBranch        *b_x2_2;   //!
   TBranch        *b_x2_3;   //!
   TBranch        *b_x2_4;   //!
   TBranch        *b_x2_5;   //!
   TBranch        *b_x2_6;   //!
   TBranch        *b_x2_7;   //!
   TBranch        *b_x2_8;   //!
   TBranch        *b_x2_9;   //!
   TBranch        *b_x2_10;   //!
   TBranch        *b_x2_11;   //!
   TBranch        *b_x2_12;   //!
   TBranch        *b_x2_13;   //!
   TBranch        *b_x2_14;   //!
   TBranch        *b_x2_15;   //!
   TBranch        *b_u2_0;   //!
   TBranch        *b_u2_1;   //!
   TBranch        *b_u2_2;   //!
   TBranch        *b_u2_3;   //!
   TBranch        *b_u2_4;   //!
   TBranch        *b_u2_5;   //!
   TBranch        *b_u2_6;   //!
   TBranch        *b_u2_7;   //!
   TBranch        *b_u2_8;   //!
   TBranch        *b_u2_9;   //!
   TBranch        *b_u2_10;   //!
   TBranch        *b_u2_11;   //!
   TBranch        *b_u2_12;   //!
   TBranch        *b_u2_13;   //!
   TBranch        *b_u2_14;   //!
   TBranch        *b_u2_15;   //!
   TBranch        *b_v2_0;   //!
   TBranch        *b_v2_1;   //!
   TBranch        *b_v2_2;   //!
   TBranch        *b_v2_3;   //!
   TBranch        *b_v2_4;   //!
   TBranch        *b_v2_5;   //!
   TBranch        *b_v2_6;   //!
   TBranch        *b_v2_7;   //!
   TBranch        *b_v2_8;   //!
   TBranch        *b_v2_9;   //!
   TBranch        *b_v2_10;   //!
   TBranch        *b_v2_11;   //!
   TBranch        *b_v2_12;   //!
   TBranch        *b_v2_13;   //!
   TBranch        *b_v2_14;   //!
   TBranch        *b_v2_15;   //!
   TBranch        *b_x3_0;   //!
   TBranch        *b_x3_1;   //!
   TBranch        *b_x3_2;   //!
   TBranch        *b_x3_3;   //!
   TBranch        *b_x3_4;   //!
   TBranch        *b_x3_5;   //!
   TBranch        *b_x3_6;   //!
   TBranch        *b_x3_7;   //!
   TBranch        *b_x3_8;   //!
   TBranch        *b_x3_9;   //!
   TBranch        *b_x3_10;   //!
   TBranch        *b_x3_11;   //!
   TBranch        *b_x3_12;   //!
   TBranch        *b_x3_13;   //!
   TBranch        *b_x3_14;   //!
   TBranch        *b_x3_15;   //!
   TBranch        *b_u3_0;   //!
   TBranch        *b_u3_1;   //!
   TBranch        *b_u3_2;   //!
   TBranch        *b_u3_3;   //!
   TBranch        *b_u3_4;   //!
   TBranch        *b_u3_5;   //!
   TBranch        *b_u3_6;   //!
   TBranch        *b_u3_7;   //!
   TBranch        *b_u3_8;   //!
   TBranch        *b_u3_9;   //!
   TBranch        *b_u3_10;   //!
   TBranch        *b_u3_11;   //!
   TBranch        *b_u3_12;   //!
   TBranch        *b_u3_13;   //!
   TBranch        *b_u3_14;   //!
   TBranch        *b_u3_15;   //!
   TBranch        *b_v3_0;   //!
   TBranch        *b_v3_1;   //!
   TBranch        *b_v3_2;   //!
   TBranch        *b_v3_3;   //!
   TBranch        *b_v3_4;   //!
   TBranch        *b_v3_5;   //!
   TBranch        *b_v3_6;   //!
   TBranch        *b_v3_7;   //!
   TBranch        *b_v3_8;   //!
   TBranch        *b_v3_9;   //!
   TBranch        *b_v3_10;   //!
   TBranch        *b_v3_11;   //!
   TBranch        *b_v3_12;   //!
   TBranch        *b_v3_13;   //!
   TBranch        *b_v3_14;   //!
   TBranch        *b_v3_15;   //!
   TBranch        *b_x4_0;   //!
   TBranch        *b_x4_1;   //!
   TBranch        *b_x4_2;   //!
   TBranch        *b_x4_3;   //!
   TBranch        *b_x4_4;   //!
   TBranch        *b_x4_5;   //!
   TBranch        *b_x4_6;   //!
   TBranch        *b_x4_7;   //!
   TBranch        *b_x4_8;   //!
   TBranch        *b_x4_9;   //!
   TBranch        *b_x4_10;   //!
   TBranch        *b_x4_11;   //!
   TBranch        *b_x4_12;   //!
   TBranch        *b_x4_13;   //!
   TBranch        *b_x4_14;   //!
   TBranch        *b_x4_15;   //!
   TBranch        *b_u4_0;   //!
   TBranch        *b_u4_1;   //!
   TBranch        *b_u4_2;   //!
   TBranch        *b_u4_3;   //!
   TBranch        *b_u4_4;   //!
   TBranch        *b_u4_5;   //!
   TBranch        *b_u4_6;   //!
   TBranch        *b_u4_7;   //!
   TBranch        *b_u4_8;   //!
   TBranch        *b_u4_9;   //!
   TBranch        *b_u4_10;   //!
   TBranch        *b_u4_11;   //!
   TBranch        *b_u4_12;   //!
   TBranch        *b_u4_13;   //!
   TBranch        *b_u4_14;   //!
   TBranch        *b_u4_15;   //!
   TBranch        *b_v4_0;   //!
   TBranch        *b_v4_1;   //!
   TBranch        *b_v4_2;   //!
   TBranch        *b_v4_3;   //!
   TBranch        *b_v4_4;   //!
   TBranch        *b_v4_5;   //!
   TBranch        *b_v4_6;   //!
   TBranch        *b_v4_7;   //!
   TBranch        *b_v4_8;   //!
   TBranch        *b_v4_9;   //!
   TBranch        *b_v4_10;   //!
   TBranch        *b_v4_11;   //!
   TBranch        *b_v4_12;   //!
   TBranch        *b_v4_13;   //!
   TBranch        *b_v4_14;   //!
   TBranch        *b_v4_15;   //!

   SNUDC(TTree *tree=0);
   virtual ~SNUDC();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SNUDC_cxx
/*
SNUDC::SNUDC(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("runA_partial.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("runA_partial.root");
      }
      f->GetObject("SNUDC",tree);

   }
   Init(tree);
}
*/
SNUDC::~SNUDC()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SNUDC::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SNUDC::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SNUDC::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   x1_0 = 0;
   x1_1 = 0;
   x1_2 = 0;
   x1_3 = 0;
   x1_4 = 0;
   x1_5 = 0;
   x1_6 = 0;
   x1_7 = 0;
   x1_8 = 0;
   x1_9 = 0;
   x1_10 = 0;
   x1_11 = 0;
   x1_12 = 0;
   x1_13 = 0;
   x1_14 = 0;
   x1_15 = 0;
   u1_0 = 0;
   u1_1 = 0;
   u1_2 = 0;
   u1_3 = 0;
   u1_4 = 0;
   u1_5 = 0;
   u1_6 = 0;
   u1_7 = 0;
   u1_8 = 0;
   u1_9 = 0;
   u1_10 = 0;
   u1_11 = 0;
   u1_12 = 0;
   u1_13 = 0;
   u1_14 = 0;
   u1_15 = 0;
   v1_0 = 0;
   v1_1 = 0;
   v1_2 = 0;
   v1_3 = 0;
   v1_4 = 0;
   v1_5 = 0;
   v1_6 = 0;
   v1_7 = 0;
   v1_8 = 0;
   v1_9 = 0;
   v1_10 = 0;
   v1_11 = 0;
   v1_12 = 0;
   v1_13 = 0;
   v1_14 = 0;
   v1_15 = 0;
   x2_0 = 0;
   x2_1 = 0;
   x2_2 = 0;
   x2_3 = 0;
   x2_4 = 0;
   x2_5 = 0;
   x2_6 = 0;
   x2_7 = 0;
   x2_8 = 0;
   x2_9 = 0;
   x2_10 = 0;
   x2_11 = 0;
   x2_12 = 0;
   x2_13 = 0;
   x2_14 = 0;
   x2_15 = 0;
   u2_0 = 0;
   u2_1 = 0;
   u2_2 = 0;
   u2_3 = 0;
   u2_4 = 0;
   u2_5 = 0;
   u2_6 = 0;
   u2_7 = 0;
   u2_8 = 0;
   u2_9 = 0;
   u2_10 = 0;
   u2_11 = 0;
   u2_12 = 0;
   u2_13 = 0;
   u2_14 = 0;
   u2_15 = 0;
   v2_0 = 0;
   v2_1 = 0;
   v2_2 = 0;
   v2_3 = 0;
   v2_4 = 0;
   v2_5 = 0;
   v2_6 = 0;
   v2_7 = 0;
   v2_8 = 0;
   v2_9 = 0;
   v2_10 = 0;
   v2_11 = 0;
   v2_12 = 0;
   v2_13 = 0;
   v2_14 = 0;
   v2_15 = 0;
   x3_0 = 0;
   x3_1 = 0;
   x3_2 = 0;
   x3_3 = 0;
   x3_4 = 0;
   x3_5 = 0;
   x3_6 = 0;
   x3_7 = 0;
   x3_8 = 0;
   x3_9 = 0;
   x3_10 = 0;
   x3_11 = 0;
   x3_12 = 0;
   x3_13 = 0;
   x3_14 = 0;
   x3_15 = 0;
   u3_0 = 0;
   u3_1 = 0;
   u3_2 = 0;
   u3_3 = 0;
   u3_4 = 0;
   u3_5 = 0;
   u3_6 = 0;
   u3_7 = 0;
   u3_8 = 0;
   u3_9 = 0;
   u3_10 = 0;
   u3_11 = 0;
   u3_12 = 0;
   u3_13 = 0;
   u3_14 = 0;
   u3_15 = 0;
   v3_0 = 0;
   v3_1 = 0;
   v3_2 = 0;
   v3_3 = 0;
   v3_4 = 0;
   v3_5 = 0;
   v3_6 = 0;
   v3_7 = 0;
   v3_8 = 0;
   v3_9 = 0;
   v3_10 = 0;
   v3_11 = 0;
   v3_12 = 0;
   v3_13 = 0;
   v3_14 = 0;
   v3_15 = 0;
   x4_0 = 0;
   x4_1 = 0;
   x4_2 = 0;
   x4_3 = 0;
   x4_4 = 0;
   x4_5 = 0;
   x4_6 = 0;
   x4_7 = 0;
   x4_8 = 0;
   x4_9 = 0;
   x4_10 = 0;
   x4_11 = 0;
   x4_12 = 0;
   x4_13 = 0;
   x4_14 = 0;
   x4_15 = 0;
   u4_0 = 0;
   u4_1 = 0;
   u4_2 = 0;
   u4_3 = 0;
   u4_4 = 0;
   u4_5 = 0;
   u4_6 = 0;
   u4_7 = 0;
   u4_8 = 0;
   u4_9 = 0;
   u4_10 = 0;
   u4_11 = 0;
   u4_12 = 0;
   u4_13 = 0;
   u4_14 = 0;
   u4_15 = 0;
   v4_0 = 0;
   v4_1 = 0;
   v4_2 = 0;
   v4_3 = 0;
   v4_4 = 0;
   v4_5 = 0;
   v4_6 = 0;
   v4_7 = 0;
   v4_8 = 0;
   v4_9 = 0;
   v4_10 = 0;
   v4_11 = 0;
   v4_12 = 0;
   v4_13 = 0;
   v4_14 = 0;
   v4_15 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("x1_0", &x1_0, &b_x1_0);
   fChain->SetBranchAddress("x1_1", &x1_1, &b_x1_1);
   fChain->SetBranchAddress("x1_2", &x1_2, &b_x1_2);
   fChain->SetBranchAddress("x1_3", &x1_3, &b_x1_3);
   fChain->SetBranchAddress("x1_4", &x1_4, &b_x1_4);
   fChain->SetBranchAddress("x1_5", &x1_5, &b_x1_5);
   fChain->SetBranchAddress("x1_6", &x1_6, &b_x1_6);
   fChain->SetBranchAddress("x1_7", &x1_7, &b_x1_7);
   fChain->SetBranchAddress("x1_8", &x1_8, &b_x1_8);
   fChain->SetBranchAddress("x1_9", &x1_9, &b_x1_9);
   fChain->SetBranchAddress("x1_10", &x1_10, &b_x1_10);
   fChain->SetBranchAddress("x1_11", &x1_11, &b_x1_11);
   fChain->SetBranchAddress("x1_12", &x1_12, &b_x1_12);
   fChain->SetBranchAddress("x1_13", &x1_13, &b_x1_13);
   fChain->SetBranchAddress("x1_14", &x1_14, &b_x1_14);
   fChain->SetBranchAddress("x1_15", &x1_15, &b_x1_15);
   fChain->SetBranchAddress("u1_0", &u1_0, &b_u1_0);
   fChain->SetBranchAddress("u1_1", &u1_1, &b_u1_1);
   fChain->SetBranchAddress("u1_2", &u1_2, &b_u1_2);
   fChain->SetBranchAddress("u1_3", &u1_3, &b_u1_3);
   fChain->SetBranchAddress("u1_4", &u1_4, &b_u1_4);
   fChain->SetBranchAddress("u1_5", &u1_5, &b_u1_5);
   fChain->SetBranchAddress("u1_6", &u1_6, &b_u1_6);
   fChain->SetBranchAddress("u1_7", &u1_7, &b_u1_7);
   fChain->SetBranchAddress("u1_8", &u1_8, &b_u1_8);
   fChain->SetBranchAddress("u1_9", &u1_9, &b_u1_9);
   fChain->SetBranchAddress("u1_10", &u1_10, &b_u1_10);
   fChain->SetBranchAddress("u1_11", &u1_11, &b_u1_11);
   fChain->SetBranchAddress("u1_12", &u1_12, &b_u1_12);
   fChain->SetBranchAddress("u1_13", &u1_13, &b_u1_13);
   fChain->SetBranchAddress("u1_14", &u1_14, &b_u1_14);
   fChain->SetBranchAddress("u1_15", &u1_15, &b_u1_15);
   fChain->SetBranchAddress("v1_0", &v1_0, &b_v1_0);
   fChain->SetBranchAddress("v1_1", &v1_1, &b_v1_1);
   fChain->SetBranchAddress("v1_2", &v1_2, &b_v1_2);
   fChain->SetBranchAddress("v1_3", &v1_3, &b_v1_3);
   fChain->SetBranchAddress("v1_4", &v1_4, &b_v1_4);
   fChain->SetBranchAddress("v1_5", &v1_5, &b_v1_5);
   fChain->SetBranchAddress("v1_6", &v1_6, &b_v1_6);
   fChain->SetBranchAddress("v1_7", &v1_7, &b_v1_7);
   fChain->SetBranchAddress("v1_8", &v1_8, &b_v1_8);
   fChain->SetBranchAddress("v1_9", &v1_9, &b_v1_9);
   fChain->SetBranchAddress("v1_10", &v1_10, &b_v1_10);
   fChain->SetBranchAddress("v1_11", &v1_11, &b_v1_11);
   fChain->SetBranchAddress("v1_12", &v1_12, &b_v1_12);
   fChain->SetBranchAddress("v1_13", &v1_13, &b_v1_13);
   fChain->SetBranchAddress("v1_14", &v1_14, &b_v1_14);
   fChain->SetBranchAddress("v1_15", &v1_15, &b_v1_15);
   fChain->SetBranchAddress("x2_0", &x2_0, &b_x2_0);
   fChain->SetBranchAddress("x2_1", &x2_1, &b_x2_1);
   fChain->SetBranchAddress("x2_2", &x2_2, &b_x2_2);
   fChain->SetBranchAddress("x2_3", &x2_3, &b_x2_3);
   fChain->SetBranchAddress("x2_4", &x2_4, &b_x2_4);
   fChain->SetBranchAddress("x2_5", &x2_5, &b_x2_5);
   fChain->SetBranchAddress("x2_6", &x2_6, &b_x2_6);
   fChain->SetBranchAddress("x2_7", &x2_7, &b_x2_7);
   fChain->SetBranchAddress("x2_8", &x2_8, &b_x2_8);
   fChain->SetBranchAddress("x2_9", &x2_9, &b_x2_9);
   fChain->SetBranchAddress("x2_10", &x2_10, &b_x2_10);
   fChain->SetBranchAddress("x2_11", &x2_11, &b_x2_11);
   fChain->SetBranchAddress("x2_12", &x2_12, &b_x2_12);
   fChain->SetBranchAddress("x2_13", &x2_13, &b_x2_13);
   fChain->SetBranchAddress("x2_14", &x2_14, &b_x2_14);
   fChain->SetBranchAddress("x2_15", &x2_15, &b_x2_15);
   fChain->SetBranchAddress("u2_0", &u2_0, &b_u2_0);
   fChain->SetBranchAddress("u2_1", &u2_1, &b_u2_1);
   fChain->SetBranchAddress("u2_2", &u2_2, &b_u2_2);
   fChain->SetBranchAddress("u2_3", &u2_3, &b_u2_3);
   fChain->SetBranchAddress("u2_4", &u2_4, &b_u2_4);
   fChain->SetBranchAddress("u2_5", &u2_5, &b_u2_5);
   fChain->SetBranchAddress("u2_6", &u2_6, &b_u2_6);
   fChain->SetBranchAddress("u2_7", &u2_7, &b_u2_7);
   fChain->SetBranchAddress("u2_8", &u2_8, &b_u2_8);
   fChain->SetBranchAddress("u2_9", &u2_9, &b_u2_9);
   fChain->SetBranchAddress("u2_10", &u2_10, &b_u2_10);
   fChain->SetBranchAddress("u2_11", &u2_11, &b_u2_11);
   fChain->SetBranchAddress("u2_12", &u2_12, &b_u2_12);
   fChain->SetBranchAddress("u2_13", &u2_13, &b_u2_13);
   fChain->SetBranchAddress("u2_14", &u2_14, &b_u2_14);
   fChain->SetBranchAddress("u2_15", &u2_15, &b_u2_15);
   fChain->SetBranchAddress("v2_0", &v2_0, &b_v2_0);
   fChain->SetBranchAddress("v2_1", &v2_1, &b_v2_1);
   fChain->SetBranchAddress("v2_2", &v2_2, &b_v2_2);
   fChain->SetBranchAddress("v2_3", &v2_3, &b_v2_3);
   fChain->SetBranchAddress("v2_4", &v2_4, &b_v2_4);
   fChain->SetBranchAddress("v2_5", &v2_5, &b_v2_5);
   fChain->SetBranchAddress("v2_6", &v2_6, &b_v2_6);
   fChain->SetBranchAddress("v2_7", &v2_7, &b_v2_7);
   fChain->SetBranchAddress("v2_8", &v2_8, &b_v2_8);
   fChain->SetBranchAddress("v2_9", &v2_9, &b_v2_9);
   fChain->SetBranchAddress("v2_10", &v2_10, &b_v2_10);
   fChain->SetBranchAddress("v2_11", &v2_11, &b_v2_11);
   fChain->SetBranchAddress("v2_12", &v2_12, &b_v2_12);
   fChain->SetBranchAddress("v2_13", &v2_13, &b_v2_13);
   fChain->SetBranchAddress("v2_14", &v2_14, &b_v2_14);
   fChain->SetBranchAddress("v2_15", &v2_15, &b_v2_15);
   fChain->SetBranchAddress("x3_0", &x3_0, &b_x3_0);
   fChain->SetBranchAddress("x3_1", &x3_1, &b_x3_1);
   fChain->SetBranchAddress("x3_2", &x3_2, &b_x3_2);
   fChain->SetBranchAddress("x3_3", &x3_3, &b_x3_3);
   fChain->SetBranchAddress("x3_4", &x3_4, &b_x3_4);
   fChain->SetBranchAddress("x3_5", &x3_5, &b_x3_5);
   fChain->SetBranchAddress("x3_6", &x3_6, &b_x3_6);
   fChain->SetBranchAddress("x3_7", &x3_7, &b_x3_7);
   fChain->SetBranchAddress("x3_8", &x3_8, &b_x3_8);
   fChain->SetBranchAddress("x3_9", &x3_9, &b_x3_9);
   fChain->SetBranchAddress("x3_10", &x3_10, &b_x3_10);
   fChain->SetBranchAddress("x3_11", &x3_11, &b_x3_11);
   fChain->SetBranchAddress("x3_12", &x3_12, &b_x3_12);
   fChain->SetBranchAddress("x3_13", &x3_13, &b_x3_13);
   fChain->SetBranchAddress("x3_14", &x3_14, &b_x3_14);
   fChain->SetBranchAddress("x3_15", &x3_15, &b_x3_15);
   fChain->SetBranchAddress("u3_0", &u3_0, &b_u3_0);
   fChain->SetBranchAddress("u3_1", &u3_1, &b_u3_1);
   fChain->SetBranchAddress("u3_2", &u3_2, &b_u3_2);
   fChain->SetBranchAddress("u3_3", &u3_3, &b_u3_3);
   fChain->SetBranchAddress("u3_4", &u3_4, &b_u3_4);
   fChain->SetBranchAddress("u3_5", &u3_5, &b_u3_5);
   fChain->SetBranchAddress("u3_6", &u3_6, &b_u3_6);
   fChain->SetBranchAddress("u3_7", &u3_7, &b_u3_7);
   fChain->SetBranchAddress("u3_8", &u3_8, &b_u3_8);
   fChain->SetBranchAddress("u3_9", &u3_9, &b_u3_9);
   fChain->SetBranchAddress("u3_10", &u3_10, &b_u3_10);
   fChain->SetBranchAddress("u3_11", &u3_11, &b_u3_11);
   fChain->SetBranchAddress("u3_12", &u3_12, &b_u3_12);
   fChain->SetBranchAddress("u3_13", &u3_13, &b_u3_13);
   fChain->SetBranchAddress("u3_14", &u3_14, &b_u3_14);
   fChain->SetBranchAddress("u3_15", &u3_15, &b_u3_15);
   fChain->SetBranchAddress("v3_0", &v3_0, &b_v3_0);
   fChain->SetBranchAddress("v3_1", &v3_1, &b_v3_1);
   fChain->SetBranchAddress("v3_2", &v3_2, &b_v3_2);
   fChain->SetBranchAddress("v3_3", &v3_3, &b_v3_3);
   fChain->SetBranchAddress("v3_4", &v3_4, &b_v3_4);
   fChain->SetBranchAddress("v3_5", &v3_5, &b_v3_5);
   fChain->SetBranchAddress("v3_6", &v3_6, &b_v3_6);
   fChain->SetBranchAddress("v3_7", &v3_7, &b_v3_7);
   fChain->SetBranchAddress("v3_8", &v3_8, &b_v3_8);
   fChain->SetBranchAddress("v3_9", &v3_9, &b_v3_9);
   fChain->SetBranchAddress("v3_10", &v3_10, &b_v3_10);
   fChain->SetBranchAddress("v3_11", &v3_11, &b_v3_11);
   fChain->SetBranchAddress("v3_12", &v3_12, &b_v3_12);
   fChain->SetBranchAddress("v3_13", &v3_13, &b_v3_13);
   fChain->SetBranchAddress("v3_14", &v3_14, &b_v3_14);
   fChain->SetBranchAddress("v3_15", &v3_15, &b_v3_15);
   fChain->SetBranchAddress("x4_0", &x4_0, &b_x4_0);
   fChain->SetBranchAddress("x4_1", &x4_1, &b_x4_1);
   fChain->SetBranchAddress("x4_2", &x4_2, &b_x4_2);
   fChain->SetBranchAddress("x4_3", &x4_3, &b_x4_3);
   fChain->SetBranchAddress("x4_4", &x4_4, &b_x4_4);
   fChain->SetBranchAddress("x4_5", &x4_5, &b_x4_5);
   fChain->SetBranchAddress("x4_6", &x4_6, &b_x4_6);
   fChain->SetBranchAddress("x4_7", &x4_7, &b_x4_7);
   fChain->SetBranchAddress("x4_8", &x4_8, &b_x4_8);
   fChain->SetBranchAddress("x4_9", &x4_9, &b_x4_9);
   fChain->SetBranchAddress("x4_10", &x4_10, &b_x4_10);
   fChain->SetBranchAddress("x4_11", &x4_11, &b_x4_11);
   fChain->SetBranchAddress("x4_12", &x4_12, &b_x4_12);
   fChain->SetBranchAddress("x4_13", &x4_13, &b_x4_13);
   fChain->SetBranchAddress("x4_14", &x4_14, &b_x4_14);
   fChain->SetBranchAddress("x4_15", &x4_15, &b_x4_15);
   fChain->SetBranchAddress("u4_0", &u4_0, &b_u4_0);
   fChain->SetBranchAddress("u4_1", &u4_1, &b_u4_1);
   fChain->SetBranchAddress("u4_2", &u4_2, &b_u4_2);
   fChain->SetBranchAddress("u4_3", &u4_3, &b_u4_3);
   fChain->SetBranchAddress("u4_4", &u4_4, &b_u4_4);
   fChain->SetBranchAddress("u4_5", &u4_5, &b_u4_5);
   fChain->SetBranchAddress("u4_6", &u4_6, &b_u4_6);
   fChain->SetBranchAddress("u4_7", &u4_7, &b_u4_7);
   fChain->SetBranchAddress("u4_8", &u4_8, &b_u4_8);
   fChain->SetBranchAddress("u4_9", &u4_9, &b_u4_9);
   fChain->SetBranchAddress("u4_10", &u4_10, &b_u4_10);
   fChain->SetBranchAddress("u4_11", &u4_11, &b_u4_11);
   fChain->SetBranchAddress("u4_12", &u4_12, &b_u4_12);
   fChain->SetBranchAddress("u4_13", &u4_13, &b_u4_13);
   fChain->SetBranchAddress("u4_14", &u4_14, &b_u4_14);
   fChain->SetBranchAddress("u4_15", &u4_15, &b_u4_15);
   fChain->SetBranchAddress("v4_0", &v4_0, &b_v4_0);
   fChain->SetBranchAddress("v4_1", &v4_1, &b_v4_1);
   fChain->SetBranchAddress("v4_2", &v4_2, &b_v4_2);
   fChain->SetBranchAddress("v4_3", &v4_3, &b_v4_3);
   fChain->SetBranchAddress("v4_4", &v4_4, &b_v4_4);
   fChain->SetBranchAddress("v4_5", &v4_5, &b_v4_5);
   fChain->SetBranchAddress("v4_6", &v4_6, &b_v4_6);
   fChain->SetBranchAddress("v4_7", &v4_7, &b_v4_7);
   fChain->SetBranchAddress("v4_8", &v4_8, &b_v4_8);
   fChain->SetBranchAddress("v4_9", &v4_9, &b_v4_9);
   fChain->SetBranchAddress("v4_10", &v4_10, &b_v4_10);
   fChain->SetBranchAddress("v4_11", &v4_11, &b_v4_11);
   fChain->SetBranchAddress("v4_12", &v4_12, &b_v4_12);
   fChain->SetBranchAddress("v4_13", &v4_13, &b_v4_13);
   fChain->SetBranchAddress("v4_14", &v4_14, &b_v4_14);
   fChain->SetBranchAddress("v4_15", &v4_15, &b_v4_15);
   Notify();
}

Bool_t SNUDC::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SNUDC::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SNUDC::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SNUDC_cxx
