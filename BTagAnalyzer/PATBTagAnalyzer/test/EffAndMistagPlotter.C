{
	gStyle->SetOptStat(0);

	TFile *f = TFile::Open("analysis.root");
	TH1F *h1 = (TH1F*)f->Get("demo/TrueBJetPtPassingCSVM");
	TH1F *h2 = (TH1F*)f->Get("demo/TrueBJetPt");
	TH1F *h3 = (TH1F*)f->Get("demo/NonBJetPtPassingCSVM");
	TH1F *h4 = (TH1F*)f->Get("demo/NonBJetPt");
        h1->Rebin(5);
	h2->Rebin(5);
	h3->Rebin(5);
	h4->Rebin(5);
	TH1F *BTagEff = h1->Clone(); 
	TH1F *MisTagEff = h1->Clone();

	TCanvas *c1 = new TCanvas("c1","n1",400,400);
	c1->cd();
	BTagEff->GetXaxis()->SetTitle("p_{T} [GeV]");
	BTagEff->GetYaxis()->SetTitle("b-tagging Efficiency");
	BTagEff->SetTitle("CSV Medium");
	BTagEff->Sumw2();
	BTagEff->Divide(h1,h2);
	BTagEff->SetMaximum(1.0);
	BTagEff->GetYaxis()->SetTitleOffset(1.5);
	BTagEff->SetMarkerStyle(20);
	BTagEff->SetMarkerColor(kRed);
	BTagEff->Draw("p0E1");
	c1->Print("bTagEff_CSVM.png");

	TCanvas *c2 = new TCanvas("c2","n2",400,400);
	c2->cd();
	MisTagEff->GetXaxis()->SetTitle("p_{T} [GeV]");
	MisTagEff->GetYaxis()->SetTitle("Light jet Mis-tagging Efficiency");
	MisTagEff->SetTitle("CSV Medium");
	MisTagEff->Sumw2();
	MisTagEff->Divide(h3,h4);
	MisTagEff->GetYaxis()->SetTitleOffset(1.5);
	MisTagEff->SetMarkerStyle(20);
	MisTagEff->SetMarkerColor(kRed);
	MisTagEff->Draw("p0E1");
	c2->Print("LightJetMisTag_CSVM.png");

}

