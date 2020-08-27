//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 21 14:40:50 2020 by ROOT version 6.12/06
// from TTree SNUDC/SNUCD
// found on file: runA_partial.root
//////////////////////////////////////////////////////////

#ifndef SNUDCTree_h
#define SNUDCTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>
using namespace std;

class SNUDCTree {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   static const int NWIRES=192;
   vector<int>* wires[NWIRES];
   TBranch*     b_wires[NWIRES];

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!

   SNUDCTree();
   virtual ~SNUDCTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   static TString GetWireName(int n);
   static int GetWireNumber(TString wirename);
     
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif
