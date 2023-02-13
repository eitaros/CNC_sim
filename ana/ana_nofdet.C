void ana_nofdet(int evno, int dirno){
	std::string dir, f_s0, f_s1, ofile;	//0:cnc 1:cdh
	dir = "data" + std::to_string(dirno);
	f_s0 = "../" + dir + "/nofdet_r_" + std::to_string(evno) + "_cnc.dat";
	f_s1 = "../" + dir + "/nofdet_l_" + std::to_string(evno) + "_cdh.dat";

	std::ifstream inf_s0(f_s0.c_str());
	std::ifstream inf_s1(f_s1.c_str());

	ofile = "../" + dir + "/" + dir + "_nofdet.root";
	TFile *file = new TFile(ofile.c_str(), "UPDATE");
	
	TH1D *h_r0[5], *h_l0[5], *h_r1[5], *h_l1[5];
	std::string hname;
	for(int i = 0; i<5; i++){
		hname = "reso_r_" + std::to_string(evno) + "_cnc_" + std::to_string((i+1)*100);
		h_r0[i] = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
		hname = "reso_l_" + std::to_string(evno) + "_cnc_" + std::to_string((i+1)*100);
		h_l0[i] = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
		hname = "reso_r_" + std::to_string(evno) + "_cdh_" + std::to_string((i+1)*100);
		h_r1[i] = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
		hname = "reso_l_" + std::to_string(evno) + "_cdh_" + std::to_string((i+1)*100);
		h_l1[i] = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
	}

	int ev;
	double resor0[5],resol0[5],resor1[5],resol1[5];
	hname = "reso_" + std::to_string(evno);
	TTree *tree = new TTree(hname, hname);
	tree->Branch("cnc_r",&resor0, "resor0[5]/D");
	tree->Branch("cnc_l",&resol0, "resol0[5]/D");
	tree->Branch("cdh_r",&resor1, "resor1[5]/D");
	tree->Branch("cdh_l",&resol1, "resol1[5]/D");
	
	while (inf_r0 >> ev >> resor0[0] >> resor0[1] >> resor0[2] >> resor0[3] >> resor0[4]){
		for(int i = 0; i<5; i++){
			h_r0[i]->Fill(resor0[i]);
		}
		tree->Fill();
	}
	while (inf_l0 >> ev >> resol0[0] >> resol0[1] >> resol0[2] >> resol0[3] >> resol0[4]){
		for(int i = 0; i<5; i++){
			h_l0[i]->Fill(resol0[i]);
		}
		tree->Fill();
	}
	while (inf_r1 >> ev >> resor1[0] >> resor1[1] >> resor1[2] >> resor1[3] >> resor1[4]){
		for(int i = 0; i<5; i++){
			h_r1[i]->Fill(resor1[i]);
		}
		tree->Fill();
	}
	while (inf_l1 >> ev >> resol1[0] >> resol1[1] >> resol1[2] >> resol1[3] >> resol1[4]){
		for(int i = 0; i<5; i++){
			h_l1[i]->Fill(resol1[i]);
		}
		tree->Fill();
	}
	
	for(int i=0; i<5; i++){
		h_r0[i]->Write();
		h_l0[i]->Write();
		h_r1[i]->Write();
		h_l1[i]->Write();
	}
	tree->Write();
}
