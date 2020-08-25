// Test program of TDC64M 
// Usgage :  ROOT> .L tdc64m_test.C
//           ROOT> run_tdc64m(1000) //for 1000 events data case


#include "tdc64m_test.h"

int run_tdc64m(int Nevent = 1000) {

  // check setting variable
  cout << "Total evt number for data taking= "<< Nevent <<endl;

  // get NKHOME enviernment
  TString mypath = gSystem->Getenv("NKHOME");
  cout<<"NKHOME pass : "<<mypath<<endl;
  TString myvme  = mypath + TString("/lib/libNotice6UVME_root.so");  
  TString mytdc = mypath + TString("/lib/libNoticeTDC64M_root.so");
  
  // Loading VME & TDC lib.
  gSystem->Load(myvme);
  gSystem->Load(mytdc);

  // local variable
  int gmode;          // gate mode, 0 for common start, 1 for common stop
  int emode;          // edge mode, 0 for leading edge only, 1 for both leading and trailing edge
  int rmode;          // run mode,  0 for L1 buffer mode, 1 for L2 buffer mode
  int ch[0x40000];    // TDC channel number array
  int nevt[0x40000];  // event number array
  int nhit[0x40000];  // hit number array
  int edge[0x40000];  // edge flag array, 0 for trailing edge, 1 for leading edge
  int data[0x40000];  // TDC data array, ns unit
  unsigned long value;
  int i;
  int bufnum =0;
  int evt = 0;
  int flag = 1;
  int IsFill=1;
  int dnum;
  int sevt, eevt, aevt;
  int ich, ievt;

  int mid = 0x0;      // Module ID --> Set by DIP switch on the board

  // open Fadc next
  int nkusb =0;       // nkvmeusb driver id

  // Class
  NKTDC64M kadc;
  
  //VME open  
  kadc.VMEopen(nkusb);
  
  //tree class
  fadc fadc1;
  head head1;

  c1 = new TCanvas("c1", "TDC64M", 800, 800);
  c1->Divide(1,2);
  
  TFile *hfile=new TFile("tdc64m.root","RECREATE");
  TTree *tdc64m=new TTree("tdc64m","tdc64m file");
  TTree *head=new TTree("head","Head of Run");
  TString bfadc = TString("tdc/I:edge/I:hitnum/I:evtnum/I:ch/I");  
  cout<<"bfadc = "<<bfadc<<endl;  
  tdc64m->Branch("fadc",&fadc1,bfadc);
  TString bhead = TString("gmode/I:emode/I:rmode/I:range/I:delay/I:mask[64]/I");
  cout<<"head = "<<bhead<<endl;  
  head->Branch("head1",&head1,bhead);
  TH1F *hoscd1 = new TH1F("hoscd1", "Channel1", 65536, 0, 65536);
  TH1F *hoscd2 = new TH1F("hoscd2", "Channel2", 65536, 0, 65536);

  // open TDC64M
  kadc.TDC64Mopen(nkusb, mid);

  // set mode
  gmode = 0;        // common start
  emode = 1;        // measure both edge
  rmode = 1;        // run L1 buffer mode
  kadc.TDC64Mwrite_MODE(nkusb, mid, gmode, emode, rmode);
  value = kadc.TDC64Mread_MODE(nkusb, mid);
  head1.gmode = value & 0x1;
  head1.emode = (value >> 1) & 0x1;
  head1.rmode = (value >> 2) & 0x1;

  // set dynamic range (set in us unit, 1, 2, 4, 8, 16, 32 and 64 are available)
  kadc.TDC64Mwrite_RANGE(nkusb, mid, 64);
  head1.range = kadc.TDC64Mread_RANGE(nkusb, mid);

  // set TDC input delay (set in ns)
  kadc.TDC64Mwrite_DLY(nkusb, mid, 0);
  head1.delay = kadc.TDC64Mread_DLY(nkusb, mid);

  // set TDC input mask (for unconnected inputs or abnormally noise channels)
  kadc.TDC64Mwrite_TMASK(nkusb, mid, 0, 0x0000);            // for channel 1 ~ 16
  kadc.TDC64Mwrite_TMASK(nkusb, mid, 1, 0xFFFF);            // for channel 17 ~ 32
  kadc.TDC64Mwrite_TMASK(nkusb, mid, 2, 0xFFFF);            // for channel 33 ~ 48
  kadc.TDC64Mwrite_TMASK(nkusb, mid, 3, 0xFFFF);            // for channel 49 ~ 64
  value = kadc.TDC64Mread_TMASK(nkusb, mid, 0);
  for (i = 0; i < 16; i++) 
    head1.mask[i] = (value >> i) & 0x1;
  value = kadc.TDC64Mread_TMASK(nkusb, mid, 1);
  for (i = 0; i < 16; i++) 
    head1.mask[16 + i] = (value >> i) & 0x1;
  value = kadc.TDC64Mread_TMASK(nkusb, mid, 2);
  for (i = 0; i < 16; i++) 
    head1.mask[32 + i] = (value >> i) & 0x1;
  value = kadc.TDC64Mread_TMASK(nkusb, mid, 3);
  for (i = 0; i < 16; i++) 
    head1.mask[48 + i] = (value >> i) & 0x1;

  head->Fill();

  // reset TDC
  kadc.TDC64Mreset(nkusb, mid);

  // Start TDC DAQ ( Start buffer page 0 and 1 )
  kadc.TDC64MstartL(nkusb, mid); 
  kadc.TDC64MstartH(nkusb, mid);

  while(flag) {

    while(1) {
      if(bufnum == 0) 
	IsFill = !(kadc.TDC64Mread_RunL(nkusb, mid));
      else if(bufnum ==1)
	IsFill = !(kadc.TDC64Mread_RunH(nkusb, mid)); // Read event number, Flag =0 :all fill

      if(IsFill) break;
    }

    // read data
    // in case of L2 buffer mode
    if (rmode) {
      // read data
      dnum = kadc.TDC64Mread_TDCL2(nkusb, mid, bufnum, data, edge, nhit, nevt, ch);
	
      // save data;
      for (i = 0; i < dnum; i++) {
	fadc1.tdc = data[i];
	fadc1.edge = edge[i];
	fadc1.hitnum = nhit[i];
	fadc1.evtnum = nevt[i];
	fadc1.ch = ch[i];
	
	printf("ch = %d\n", ch[i]);

	// fill histogram
	if (fadc1.ch == 1)
	  hoscd1->Fill(fadc1.tdc);	
	if (fadc1.ch == 2)
	  hoscd2->Fill(fadc1.tdc);	
	
	// get event numbers taken
	if (i == 0)
	  sevt = fadc1.evtnum;
	if (i == (dnum - 1))
	  eevt = fadc1.evtnum;
	
	aevt = eevt - sevt +1;
	if (aevt < 0)
	  aevt = aevt + 0x1000000;

	// fill root file
	tdc64m->Fill();
      }
    }
    // in case of L1 buffer mode
    else {
      // read data			
      kadc.TDC64Mread_TDCL1(nkusb, mid, bufnum, emode, nhit, data, edge);

      // save data
      for (ievt = 0; ievt < 16; ievt++) {
	for (ich = 0; ich < 64; ich++) {
	  for (i = 0; i < nhit[ich * 16 + ievt]; i++) {
	    fadc1.tdc = data[ich * 512 + ievt * 32 + i];
	    fadc1.edge = edge[ich * 512 + ievt * 32 + i];
	    fadc1.hitnum = i +1;
	    fadc1.evtnum = ievt;
	    fadc1.ch = ich + 1;

	    // fill histogram
	    if (fadc1.ch == 1)
	      hoscd1->Fill(fadc1.tdc);	
	    if (fadc1.ch == 2)
	      hoscd2->Fill(fadc1.tdc);	

	    // fill root file
	    tdc64m->Fill();
	  }
	}
      }

      aevt = 16;
    }
 
    evt = evt + aevt;

    if(evt >= Nevent) 
      flag = 0;

    c1->cd(1);
    hoscd1->Draw();
    c1->cd(2);
    hoscd2->Draw();
    c1->Modified();
    c1->Update();
    printf("evt number = %d\n",evt);
    gSystem->Exec("date");

    if (flag) {
      if(bufnum == 0 ) { 
	bufnum = 1;
	kadc.TDC64MstartL(nkusb, mid); 
      }
      else if(bufnum == 1) { 
	bufnum =0; 
	kadc.TDC64MstartH(nkusb, mid);
      }
    }
  
    tdc64m->AutoSave();
    FILE *fp = fopen("KILLME","r");
    if(fp) {
      fclose(fp);
      printf(" KILLME file exist  BYE \n");
      gSystem->Exec("rm -f KILLME");
      break;
    }
  }

  printf("finished!!\n");
  gSystem->Exec("date");
  hfile->Write();
 
  return 0;
}


  
  

