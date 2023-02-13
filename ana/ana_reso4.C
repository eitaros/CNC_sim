void ana_reso4(int th){
	char fname[64];
	sprintf(fname,"txt/cnc_%d.txt",th);

	TGraphErrors *g_cnc_r = new TGraphErrors(fname,"%lg %lg %lg %lg %*s %*s %*s");
	g_cnc_r->SetMarkerColor(kRed);
	g_cnc_r->SetLineColor(kRed);
	TGraphErrors *g_cnc_l = new TGraphErrors(fname,"%lg %*s %*s %*s %lg %lg %lg");
	g_cnc_l->SetMarkerColor(kBlue);
	g_cnc_l->SetLineColor(kBlue);

	g_cnc_r->GetXaxis()->SetTitle("length(mm)");
	g_cnc_r->GetXaxis()->SetTitle("resolution(ps)");

	TMultiGraph *mg = new TMultiGraph();
	mg->Add(g_cnc_r);
	mg->Add(g_cnc_l);

	TCanvas *c1 = new TCanvas("c1","c1");
	mg->Draw("AP");


	std::string pdfname = "pdf/th2_" + std::to_string(th) + ".pdf";
	c1->Print(pdfname.c_str());
}
