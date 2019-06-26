// clean up

#include <TFile.h>
#include <TCanvas.h>
#include <fstream>
#include <string>
#include <sstream>
#include "test_dashboard_analysis.h"

void Analysis_FastEfficiencyTable(int run_num){

  ifstream fin;
  string dir, line, entry;
  int row_count = 0;
  float data;

  TH1 *FastEfficiencyTable = new TH1F("FastEfficiencyTable","No. of Chambers vs Efficiency",100,0,100); // efficiency distribution
  dir = "QC8Test/src/Analysis/GEMQC8/data/Dashboard/FastEfficiencyTables/FastEfficiencyTable_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,",")){
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
}

void Analysis_VFATEfficiencyTable(int run_num){

  ifstream fin;
  string dir, line, entry;
  int row_count = 0;
  float data;

  TH1 *VFATEfficiencyTable = new TH1F("VFATEfficiencyTable","No. of VFATs vs Efficiency",100,0,100); // efficiency distribution
  dir = "QC8Test/src/Analysis/GEMQC8/data/Dashboard/VFATEfficiencyTables/VFATEfficiencyTable_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,",")){
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

}







///

ch_count += 1; // count number of times chamber name appears in ch_ID, auto-count ch_ID[i = 0]
name = ch_ID.at(i);
if(i==ch_ID.size()-1){ // handle last element
  if(name == ch_ID.at(i-1) ){
    ch_count+=1;
    cout<<ch_count<<endl;
    break;
  }
  else if(name == ch_ID.at(i-1))
}
if(name != ch_ID.at(i-1)){
  cout<<ch_count<<endl;
  ch_count = 0; // reset count when ch_ID[i] != ch_ID[i-1]
}
}
