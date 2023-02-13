void ana_reso(int evno, int dirno){
	std::string dir, f_r0, f_l0, f_r1, f_l1, ofile;	//0:cnc 1:cdh
	dir = "data" + std::to_string(dirno);
	f_r0 = "../" + dir + "/reso_r" + std::to_string(evno) + "_cnc.dat";
	f_l0 = "../" + dir + "/reso_l" + std::to_string(evno) + "_cnc.dat";
	f_r1 = "../" + dir + "/reso_r" + std::to_string(evno) + "_cdh.dat";
	f_l1 = "../" + dir + "/reso_l" + std::to_string(evno) + "_cdh.dat";

	std::ifstream inf_r0(f_r0.c_str());
	std::ifstream inf_l0(f_l0.c_str());
	std::ifstream inf_r1(f_r1.c_str());
	std::ifstream inf_l1(f_l1.c_str());

	ofile = "../" + dir + "/" + dir + "_reso.root";
	TFile *file = new TFile(ofile.c_str(), "UPDATE");
	
	TH1D *h_r0[6], *h_l0[6], *h_r1[6], *h_l1[6];
	std::string hname;
	for(int i = 0; i<6; i++){
		hname = "reso_r_" + std::to_string(evno) + "_cnc_" + std::to_string((i+1)*100);
		h_r0[i] = new TH1D(hname.c_str(),hname.c_str(),3000,9.5,13.5);
		hname = "reso_l_" + std::to_string(evno) + "_cnc_" + std::to_string((i+1)*100);
		h_l0[i] = new TH1D(hname.c_str(),hname.c_str(),3000,9.5,13.5);
		hname = "reso_r_" + std::to_string(evno) + "_cdh_" + std::to_string((i+1)*100);
		h_r1[i] = new TH1D(hname.c_str(),hname.c_str(),3000,9.5,13.5);
		hname = "reso_l_" + std::to_string(evno) + "_cdh_" + std::to_string((i+1)*100);
		h_l1[i] = new TH1D(hname.c_str(),hname.c_str(),3000,9.5,13.5);
	}
	
	int ev;
	double reso[6];
	while (inf_r0 >> ev >> reso[0] >> reso[1] >> reso[2] >> reso[3] >> reso[4] >> reso[5]){
		for(int i = 0; i<6; i++){
			h_r0[i]->Fill(reso[i]);
		}
	}
	while (inf_l0 >> ev >> reso[0] >> reso[1] >> reso[2] >> reso[3] >> reso[4] >> reso[5]){
		for(int i = 0; i<6; i++){
			h_l0[i]->Fill(reso[i]);
		}
	}
	while (inf_r1 >> ev >> reso[0] >> reso[1] >> reso[2] >> reso[3] >> reso[4] >> reso[5]){
		for(int i = 0; i<6; i++){
			h_r1[i]->Fill(reso[i]);
		}
	}
	while (inf_l1 >> ev >> reso[0] >> reso[1] >> reso[2] >> reso[3] >> reso[4] >> reso[5]){
		for(int i = 0; i<6; i++){
			h_l1[i]->Fill(reso[i]);
		}
	}
	
	for(int i=0; i<6; i++){
		h_r0[i]->Write();
		h_l0[i]->Write();
		h_r1[i]->Write();
		h_l1[i]->Write();
	}
}
