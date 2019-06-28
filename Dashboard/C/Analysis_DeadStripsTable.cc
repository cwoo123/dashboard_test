// Running this as a macro to test its functionality

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

void Analysis_DeadStripsTable(int run_num){ // test before adding analysis_dead

  ifstream fin;
  string dir, line, entry, name;
  int row_count = 0;
  int ch_count = -900;
  vector<string> ch_ID, replic;
  TH1F *h[15]; // declare 15 element array for each s-chamber histo
  char *chamber = new char[100]; // for histo names
  char *description = new char[100]; // human readable name to the histograms
  string ch_name;
  int data;

  TH1F *DeadStripsTable = new TH1F("DeadStripsTable","No. of Chambers vs Number of Dead Strips",15,0.5,15.5);
  dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_DeadStrips_run" + to_string(run_num) + ".csv";
  fin.open(dir);

  // get chamber s/n,
  while(getline(fin, line)){
    int column_count = 0;
    row_count+=1;
    stringstream s(line);
    while(getline(s,entry,',')){
      if(row_count==1) // skips loop when entries are column names
        break;
      column_count+=1;
      if(column_count==1) // get chamber names into vector
        ch_ID.push_back(entry);
    }
  }

  row_count=0; //reset
  fin.close();

  //draw summary plot for No. of VFAT vs No. of Deads
  for(int i = 0;i<ch_ID.size();i++){
    replic.push_back(ch_ID.at(i));
    name = ch_ID.at(i);
    if( count(replic.begin(), replic.end(), name) > 1 ){ // if replic has > 1 instance of "name", next iteration.
      replic.pop_back();
      continue;
    }
    ch_count = count(ch_ID.begin(), ch_ID.end(), name); // no. of time chamber name appears = no. of Dead strips in chamber
    DeadStripsTable->Fill(ch_count);
    }
    TCanvas *c3=new TCanvas();
    DeadStripsTable->Draw();


  // create and fill eta histograms for each chamber
  fin.open(dir);
  for(int i = 0; i<replic.size(); i++ ){
    strcpy(chamber, replic.at(i).c_str());
    strcpy(description, (replic.at(i) + ": Number of Dead Strips per Eta").c_str());
    h[i] = new TH1F(chamber, description, 8, 0.5, 8.5);

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
        if(column_count==4){
          if(ch_name==replic.at(i)){ // if row corresponds to chamber, read data
            data = stoi(entry);
            data = 8-data%8; // obtain eta_ID
            h[i]->Fill(data); // fill with eta_IDs
          }
        }
      }
    }

    fin.close();
    TCanvas *c1 = new TCanvas();
    h[i]->Draw();
    fin.open(dir);  // re-open
    row_count=0; // reset row_count
  }

}
