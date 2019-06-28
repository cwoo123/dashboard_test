// test saving histo to root file


#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <stdio.h>
#include "Dashboard_Analysis.h"

void Analysis_VFATEfficiencyTable(int run_num){

  ifstream fin;
  string dir, line, entry;
  vector <string> replic,ch_ID;
  int row_count = 0;
  float data;
  string ch_name, name;
  TH1F *v[15]; // declare 15 element array for each s-chamber histo
  char *chamber = new char[100]; // for histo names
  char *description = new char[100]; // human readable name to the histograms

  string outfile = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/Roots/VFATEfficiencyTable_run" + to_string(run_num) +".root";
  TFile f(outfile.c_str(), "NEW");

  TH1F *VFATEfficiencyTable = new TH1F("VFATEfficiencyTable","No. of VFATs vs Efficiency",10000,0,1);
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
      if(column_count==1){ // get chamber names into vector
        ch_ID.push_back(entry);
        break;
      }
    }
  }
  row_count=0; //reset
  fin.close();

  for(int i = 0;i<ch_ID.size();i++){
    replic.push_back(ch_ID.at(i));
    name = ch_ID.at(i);
    if( count(replic.begin(), replic.end(), name) > 1 ) // if replic has > 1 instance of "name",
      replic.pop_back(); // ensures that replic entries are unique
  }

  fin.open(dir);

  for(int i = 0; i<replic.size(); i++ ){
    strcpy(chamber, replic.at(i).c_str());
    strcpy(description, (replic.at(i) + ": No. VFAT vs Efficiency").c_str());
    v[i] = new TH1F(chamber, description, 10000, 0, 1);

    while(getline(fin, line)){
      int column_count = 0;
      row_count+=1; // call values r
      stringstream s(line);

      while(getline(s,entry,',')){

        if(row_count==1) // skips loop when entries are column names
          break;
        column_count+=1; // call values c

        if(column_count==1){
          if(entry==replic.at(i)){
            ch_name = entry; // stores "entry" as ch_name for comparison if entry(r,1) == replic[i]
          }
          if(entry!=replic.at(i)){
            ch_name = " "; // assign some other string if entry(r,1) doesn't correspond
          }
        }
        if(column_count==3){
          if(i==0){ // fill over summary histo only once.
            data = stof(entry);
            VFATEfficiencyTable->Fill(data); // stores data for summary plot at every Efficiency column
          }
          if(ch_name==replic.at(i)){
            data = stof(entry);
            v[i]->Fill(data); // fills this chamber specific histo only if entry is also == replic[i]
          }
        }
      }
    }

    fin.close();
    v[i]->Write(chamber);
    fin.open(dir);  // re-open
    row_count=0; // reset row_count
  }

  VFATEfficiencyTable->Write("VFATEfficiencyTable");
  f.Close();
  cout<<"VFATEfficiencyTable_run" + to_string(run_num) +".root created."<<endl;
}
