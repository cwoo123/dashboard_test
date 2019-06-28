// Running this as a macro to test its functionality

#include <TFile.h>
#include <TCanvas.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <TH1.h>
#include "Dashboard_Analysis.h"

using namespace std;

void Analysis_FastEfficiencyTable(int run_num){

  ifstream fin;
  string dir, line, entry;
  int row_count = 0;
  float data;

  TH1F *FastEfficiencyTable = new TH1F("FastEfficiencyTable","No. of Chambers vs Efficiency",100,0,100); // efficiency distribution
  dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_FastEfficiencyTable_run" + to_string(run_num) + ".csv";
  fin.open(dir);
  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,',')){
      if(row_count==1) // skips loop when entries are column names
        break;
      column_count+=1;
      if(column_count==2){
        data = stof(entry);
        FastEfficiencyTable->Fill(data);
        break;
      }
    }
  }
  fin.close();
  TCanvas *c1=new TCanvas();
  FastEfficiencyTable->Draw();
}
