// Running this as a macro to test its functionality

#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <fstream>
#include <string>
#include <sstream>
#include <TH1.h>
#include "test_dashboard_analysis.h"

void Analysis_VFATEfficiencyTable(int run_num){

  ifstream fin;
  string dir, line, entry;
  int row_count = 0;
  float data;

  TH1F *VFATEfficiencyTable = new TH1F("VFATEfficiencyTable","No. of VFATs vs Efficiency",100,0,1);
  dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_VFATEfficiencyTable_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,',')){
      if(row_count==1) // skips loop when entries are column names
        break;
      column_count+=1;
      if(column_count==3){
        data = stof(entry);
        VFATEfficiencyTable->Fill(data);
        break;
      }
    }
  }
  fin.close();
  VFATEfficiencyTable->Draw();
}
