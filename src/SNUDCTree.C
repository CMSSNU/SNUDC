#ifndef SNUDCTree_cxx
#define SNUDCTree_cxx

#include "SNUDCTree.h"

void SNUDCTree::Loop(){
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   }

   cout << "nentries : " << nentries << endl;
   cout << "nb : " << nb << endl;
}

SNUDCTree::SNUDCTree(){
  fChain=new TChain("SNUDC");
}

SNUDCTree::~SNUDCTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SNUDCTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
TString SNUDCTree::GetWireName(int n){
  if(n<0||n>=NWIRES) return "";
  int layer=n/48+1;
  int axis=(n%48)/16;
  int wire=n%16;
  TString axisname[3]={"x","u","v"};
  return axisname[axis]+Form("%d_%d",layer,wire);
}
int SNUDCTree::GetWireNumber(TString wirename){
  int wirenumber=0;
  if(wirename[0]=='x') wirenumber+=0;
  else if(wirename[0]=='u') wirenumber+=16;
  else if(wirename[0]=='v') wirenumber+=32;
  else return -1;
  
  TString slayer=wirename(1,1);
  if(!slayer.IsDigit()) return -1;
  int layer=slayer.Atoi()-1;
  if(layer<0||layer>3) return -1;
  wirenumber+=layer*48;

  if(wirename[2]!='_') return -1;
  
  TString swire=wirename(3,2);
  if(!swire.IsDigit()) return -1;
  int wire=swire.Atoi();
  if(wire<0||wire>15) return -1;
  wirenumber+=wire;
  return wirenumber;
}
Long64_t SNUDCTree::LoadTree(Long64_t entry)
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

void SNUDCTree::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
  
  for(int i=0;i<NWIRES;i++)
    if(wires[i]) delete wires[i];

  // Set branch addresses and branch pointers
  if (!fChain) return;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);

  for(int i=0;i<192;i++)
    fChain->SetBranchAddress(GetWireName(i),&wires[i],&b_wires[i]);

  Notify();
}

Bool_t SNUDCTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SNUDCTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SNUDCTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SNUDC_cxx
