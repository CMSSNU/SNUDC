{
  gROOT->LoadMacro("tdc64m_test.h");
  TFile *a=new TFile("tdc64m.root");
  TTree *tdc64m = (TTree*)a->Get("tdc64m");

  Int_t hch;

  printf("Enter channel number to show : ");
  scanf("%d", &hch);

  Int_t nevent=tdc64m->GetEntries();
  printf(" Total event %d \n", nevent);
  TH1F *hoscd1 = new TH1F("hoscd1", "TDC", 65536, 0, 65536);
  TCanvas *c1 = new TCanvas("c1", "KIMS", 1000, 800);
  //  c1->Divide(1,1);
  c1->Draw();
  fadc fadc1;
  char temp[255];
  TObjArray *leaves=tdc64m->GetBranch("fadc")->GetListOfLeaves();
  TLeaf *l_leafa  = (TLeaf*)leaves->At(0);   l_leafa->SetAddress(&fadc1.tdc);
  TLeaf *l_leafb  = (TLeaf*)leaves->At(1);   l_leafb->SetAddress(&fadc1.edge);
  TLeaf *l_leafc  = (TLeaf*)leaves->At(2);   l_leafc->SetAddress(&fadc1.hitnum);
  TLeaf *l_leafd  = (TLeaf*)leaves->At(3);   l_leafd->SetAddress(&fadc1.evtnum);
  TLeaf *l_leafe  = (TLeaf*)leaves->At(4);   l_leafe->SetAddress(&fadc1.ch);

  Int_t nbytes = 0;

  hoscd1->Reset();

  for(int j=0;j<nevent;j++){
    nbytes +=tdc64m->GetEvent(j);

    if (fadc1.ch == hch)
      hoscd1->Fill(fadc1.tdc);

    if (!((j + 1) % 1000))
      printf("%d / %d processed\n", j + 1, nevent);
  }
  
  hoscd1->Draw();
  c1->Modified();
  c1->Update();
}
