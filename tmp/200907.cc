{
  TCanvas* cc=NULL;
  TView3D* view=NULL;
  AnalyzerCore a;
  a.SetupConfig("runA");

  // chamber
  cc=a.DrawChamber();
  cc->SetWindowSize(1000,1000);
  a.DrawWires("all");
  view=(TView3D*)cc->GetView();
  view->RotateView(-30,-105);
  cc->SaveAs("chamber.png");
  view->RotateView(0,-180);
  cc->SaveAs("chamber_xy.png");
  view->RotateView(1,-91);
  cc->SaveAs("chamber_x.png");
  view->RotateView(45,-91);
  cc->SaveAs("chamber_u.png");
  view->RotateView(-45,-91);
  cc->SaveAs("chamber_v.png");
  view->ShowAxis();
  view->Zoom();
  view->Zoom();
  for(int i=0;i<60;i++){
    view->RotateView(6*i,-105);
    //cc->SaveAs(Form("chamber_gif%d.png",i));
  }
    

  // track example
  a.GetEntry(500);
  cc=a.DrawChamber();
  cc->SetWindowSize(1000,1000);
  a.DrawWires("");
  a.DrawTrack("TDC");
  view=(TView3D*)cc->GetView();
  view->RotateView(-30,-105);
  cc->SaveAs("event.png");
  view->RotateView(0,-180);
  cc->SaveAs("event_xy.png");
  view->RotateView(1,-91);
  cc->SaveAs("event_x.png");
  view->RotateView(45,-91);
  cc->SaveAs("event_u.png");
  view->RotateView(-45,-91);
  cc->SaveAs("event_v.png");
  view->ShowAxis();
  view->Zoom();
  view->Zoom();
  for(int i=0;i<60;i++){
    view->RotateView(6*i,-105);
    //cc->SaveAs(Form("event_gif%d.png",i));
  }

  TH1* hist=NULL;
  TPaveStats* stats=NULL;
  TFile f("output/ResolutionAnalyzer_runA.root");
  hist=(TH1*)f.Get("golden/WireOnly/x4_7");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("Events");
  hist->GetXaxis()->SetTitle("residue (y-y_{trk}) [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("wireonly.png");

  hist=(TH1*)f.Get("golden/TDC/x4_7");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("Events");
  hist->GetXaxis()->SetTitle("residue (y-y_{trk}) [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("tdc.png");

  hist=(TH1*)f.Get("golden/WireOnly_refTDC/x4_7");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("Events");
  hist->GetXaxis()->SetTitle("residue (y-y_{trk}) [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("wireonly_reftdc.png");

  hist=(TH1*)f.Get("scintillator1");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("y_{trk} [mm]");
  hist->GetXaxis()->SetTitle("x_{trk} [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("scintillator1.png");

  hist=(TH1*)f.Get("scintillator2");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("y_{trk} [mm]");
  hist->GetXaxis()->SetTitle("x_{trk} [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("scintillator2.png");

  hist=(TH1*)f.Get("golden/scintillator1");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("y_{trk} [mm]");
  hist->GetXaxis()->SetTitle("x_{trk} [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("scintillator1_gold.png");

  hist=(TH1*)f.Get("golden/scintillator2");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("y_{trk} [mm]");
  hist->GetXaxis()->SetTitle("x_{trk} [mm]");
  hist->Draw();
  cc->Update();
  stats=(TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  stats->SetX1NDC(0.65);
  stats->SetY1NDC(0.65);
  cc->Modified();
  cc->SaveAs("scintillator2_gold.png");

  TFile ff("output/Time2Length_runA.root");

  hist=(TH1*)ff.Get("x4_7");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("Events");
  hist->GetXaxis()->SetTitle("TDC time [ns]");
  hist->SetStats(0);
  hist->Draw();
  cc->SaveAs("time2length.png");

  hist=(TH1*)ff.Get("x4_7_cumulative");
  cc=new TCanvas;
  cc->SetLeftMargin(0.15);
  cc->SetBottomMargin(0.15);
  cc->SetWindowSize(600,600);
  hist->GetYaxis()->SetTitle("Drift length / Maximum drift length");
  hist->GetXaxis()->SetTitle("TDC time [ns]");
  hist->SetStats(0);
  hist->Draw();  
  cc->SaveAs("time2length_cumulative.png");
  
}
