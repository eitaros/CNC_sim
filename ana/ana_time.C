void ana_time(int evno, int dirno){
	std::string dir, f_r0, f_l0, f_r1, f_l1, ofile;	//0:cnc 1:cdh
	dir = "data" + std::to_string(dirno);
	f_r0 = "../" + dir + "/time_r_" + std::to_string(evno) + "_cnc.dat";
	f_l0 = "../" + dir + "/time_l_" + std::to_string(evno) + "_cnc.dat";
	f_r1 = "../" + dir + "/time_r_" + std::to_string(evno) + "_cdh.dat";
	f_l1 = "../" + dir + "/time_l_" + std::to_string(evno) + "_cdh.dat";

	std::ifstream inf_r0(f_r0.c_str());
	std::ifstream inf_l0(f_l0.c_str());
	std::ifstream inf_r1(f_r1.c_str());
	std::ifstream inf_l1(f_l1.c_str());

	ofile = "../" + dir + "/" + dir + "_time.root";
	TFile *file = new TFile(ofile.c_str(), "UPDATE");
	
	TH1D *h_r0, *h_l0, *h_r1, *h_l1;
	std::string hname;
	hname = "time_r_" + std::to_string(evno) + "_cnc";
	h_r0 = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
	hname = "reso_l_" + std::to_string(evno) + "_cnc";
	h_l0 = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
	hname = "reso_r_" + std::to_string(evno) + "_cdh";
	h_r1 = new TH1D(hname.c_str(),hname.c_str(),100,0,100);
	hname = "reso_l_" + std::to_string(evno) + "_cdh";
	h_l1 = new TH1D(hname.c_str(),hname.c_str(),100,0,100);

	
	int ev;
	double time;
	while (inf_r0 >> ev >> time){
		h_r0->Fill(time);
	}
	while (inf_l0 >> ev >> time){
		h_l0->Fill(time);
	}
	while (inf_r1 >> ev >> time){
		h_r1->Fill(time);
	}
	while (inf_l1 >> ev >> time){
		h_l1->Fill(time);
	}
	
	h_r0->Write();
	h_l0->Write();
	h_r1->Write();
	h_l1->Write();
}
