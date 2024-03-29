// script to analyse all performance data at once.

#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <fstream>
#include <string>
#include <sstream>
#include <TH1.h>
#include "Dashboard_Analysis.h"


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
}


/////// below: not being tested


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
}

void Analysis_HotStripsTable(int run_num){ // test before adding analysis_dead

  ifstream fin;
  string dir, line, entry, name;
  int row_count = 0;
  int ch_count = -900;
  vector<string> ch_ID, replic;

  TH1F *HotStripsTable = new TH1F("HotStripsTable","No. of Chambers vs Number of Hot Strips",15,1,15);
  dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_HotStrips_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,',')){
      if(row_count==1) // skips loop when entries are column names
        break;
      column_count+=1;
      if(column_count==1){ // get chamber names into vector
        ch_ID.push_back(entry);
        break;
      }
    }
  }
  fin.close();

  for(int i = 0;i<ch_ID.size();i++){
    replic.push_back(ch_ID.at(i));
    name = ch_ID.at(i);
    if( count(replic.begin(), replic.end(), name) > 1 ) // if replic has > 1 instance of "name", next iteration.
      continue;
    ch_count = count(ch_ID.begin(), ch_ID.end(), name); // no. of time chamber name appears = no. of hot strips in chamber
    HotStripsTable->Fill(ch_count);

    }

}


void Analysis_DeadStripsTable(int run_num){ // test before adding analysis_dead

  ifstream fin;
  string dir, line, entry, name;
  int row_count = 0;
  int ch_count = -900;
  vector<string> ch_ID, replic;

  TH1F *DeadStripsTable = new TH1F("DeadStripsTable","No. of Chambers vs Number of Dead Strips",15,1,15);
  dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_DeadStrips_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,',')){
      if(row_count==1) // skips loop when entries are column names
        break;
      column_count+=1;
      if(column_count==1){ // get chamber names into vector
        ch_ID.push_back(entry);
        break;
      }
    }
  }
  fin.close();

  for(int i = 0;i<ch_ID.size();i++){
    replic.push_back(ch_ID.at(i));
    name = ch_ID.at(i);
    if( count(replic.begin(), replic.end(), name) > 1 ) // if replic has > 1 instance of "name", next iteration.
      continue;
    ch_count = count(ch_ID.begin(), ch_ID.end(), name); // no. of time chamber name appears = no. of Dead strips in chamber
    DeadStripsTable->Fill(ch_count);

    }

}
