void ana_reso3(int th){
	std::string fname20, fname21, hname;	//0:cnc 1:cdh
	fname20 = "../data20/data20_reso.root";
	fname21 = "../data21/data21_reso.root";

	TFile *f0 = new TFile(fname20.c_str());
	TFile *f1 = new TFile(fname21.c_str());

	std::vector<int> length = {1, 60, 115, 230, 345, 460, 155, 190, 270, 305};
	std::vector<TH1D*> h_cnc_r, h_cnc_l, h_cdh_r, h_cdh_l;
	TH1D *h;
	for (int i = 0; i < length.size(); i++){
		if(i<6){
			hname = "reso_r_" + std::to_string(length.at(i)) + "_cnc_" + std::to_string(th);
			h = (TH1D*)f0->Get(hname.c_str());
			h_cnc_r.push_back(h);

			hname = "reso_l_" + std::to_string(length.at(i)) + "_cnc_" + std::to_string(th);
			h = (TH1D*)f0->Get(hname.c_str());
			h_cnc_l.push_back(h);

			/* hname = "reso_r_" + std::to_string(length.at(i)) + "_cdh_" + std::to_string(th);
			h = (TH1D*)f0->Get(hname.c_str());
			h_cdh_r.push_back(h);

			hname = "reso_l_" + std::to_string(length.at(i)) + "_cdh_" + std::to_string(th);
			h = (TH1D*)f0->Get(hname.c_str());
			h_cdh_l.push_back(h); */
		} else {
			hname = "reso_r_" + std::to_string(length.at(i)) + "_cnc_" + std::to_string(th);
			h = (TH1D*)f1->Get(hname.c_str());
			h_cnc_r.push_back(h);

			hname = "reso_l_" + std::to_string(length.at(i)) + "_cnc_" + std::to_string(th);
			h = (TH1D*)f1->Get(hname.c_str());
			h_cnc_l.push_back(h);

			/* hname = "reso_r_" + std::to_string(length.at(i)) + "_cdh_" + std::to_string(th);
			h = (TH1D*)f1->Get(hname.c_str());
			h_cdh_r.push_back(h);

			hname = "reso_l_" + std::to_string(length.at(i)) + "_cdh_" + std::to_string(th);
			h = (TH1D*)f1->Get(hname.c_str());
			h_cdh_l.push_back(h); */
		}
	}
	
	const Int_t n = length.size();
	TFitResultPtr results;
	Double_t sig_cnc_r[n], sig_cnc_l[n], sig_cdh_r[n], sig_cdh_l[n];
	Double_t err_cnc_r[n], err_cnc_l[n], err_cdh_r[n], err_cdh_l[n];
	Double_t x[n], x_err[n];
	for(int i = 0; i < n; i++){
		/* results = h_cnc_r->Fit("gaus", "S");
		sig_cnc_r.push_back(results->Parameter(2));
		err_cnc_r.push_back(results->ParError(2));

		results = h_cnc_l->Fit("gaus", "S");
		sig_cnc_l.push_back(results->Parameter(2));
		err_cnc_l.push_back(results->ParError(2));

		results = h_cdh_r->Fit("gaus", "S");
		sig_cnc_r.push_back(results->Parameter(2));
		err_cdh_r.push_back(results->ParError(2));

		results = h_cdh_l->Fit("gaus", "S");
		sig_cdh_l.push_back(results->Parameter(2));
		err_cdh_l.push_back(results->ParError(2)); */
		results = h_cnc_r.at(i)->Fit("gaus", "S");
		sig_cnc_r[i] = results->Parameter(2) * 1000;
		err_cnc_r[i] = results->ParError(2) * 1000;

		results = h_cnc_l.at(i)->Fit("gaus", "S");
		sig_cnc_l[i] = results->Parameter(2) * 1000;
		err_cnc_l[i] = results->ParError(2) * 1000;

		/* results = h_cdh_r.at(i)->Fit("gaus", "S");
		sig_cdh_r[i] = results->Parameter(2);
		err_cdh_r[i] = results->ParError(2);

		results = h_cdh_l.at(i)->Fit("gaus", "S");
		sig_cdh_l[i] = results->Parameter(2);
		err_cdh_l[i] = results->ParError(2); */

		x[i] = (Double_t)length.at(i);
		x_err[i] = 0.;
	}

	std::string fname;
	fname = "txt/cnc_" + std::to_string(th) + ".txt";
	std::ofstream ofile(fname.c_str(), std::ios::app);
	for(int i = 0; i<n; i++){
		ofile << x[i] << " " << sig_cnc_r[i] << " " << x_err[i] << " " << err_cnc_r[i] << " " << sig_cnc_l[i] << " " << x_err[i] << " " << err_cnc_l[i] << std::endl;
	}

	
	TGraphErrors *g_cnc_r = new TGraphErrors(n, x, sig_cnc_r, x_err, err_cnc_r);
	g_cnc_r->SetMarkerColor(kRed);
	g_cnc_r->SetLineColor(kRed);
	/*TGraphErrors *g_cnc_l = new TGraphErrors(n, x, sig_cnc_l, x_err, err_cnc_l);
	g_cnc_l->SetMarkerColor(kOrange);
	TGraphErrors *g_cdh_r = new TGraphErrors(n, x, sig_cdh_r, x_err, err_cdh_r);
	g_cdh_r->SetMarkerColor(kBlue);
	TGraphErrors *g_cdh_l = new TGraphErrors(n, x, sig_cdh_l, x_err, err_cdh_l);
	g_cdh_l->SetMarkerColor(kGreen); */
	std::string title = "threshold : " + std::to_string(th) + " photons; length(mm); sigma(ns)";
	char ti[64];
	sprintf(ti,"threshold : %d photons; length(mm); sigma(ns)",th);
	TMultiGraph *mg = new TMultiGraph();
	mg->Add(g_cnc_r);
	/*mg->Add(g_cnc_l);
	mg->Add(g_cdh_r);
	mg->Add(g_cdh_l); */

	/* TCanvas *c1 = new TCanvas("c1","c1");
	mg->Draw("AP");
	std::string pdfname = "pdf/th_" + std::to_string(th) + ".pdf";
	c1->Print(pdfname.c_str()); */
}
