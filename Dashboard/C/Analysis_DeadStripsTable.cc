// Running this as a macro to test its functionality

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include <stdio.h>
#include "Dashboard_Analysis.h"

void Analysis_DeadStripsTable(int run_num){ // test before adding analysis_dead

  ifstream fin;
  string dir, line, entry, name;
  int row_count = 0;
  int ch_count = -900;
  int run = -1;
  Int_t runmax = -1;
  vector<string> ch_ID, replic;
  vector<int> runvec; //stores run numbers
  TH1F *h[15]; // declare 15 element array for each s-chamber histo; 15 is max num of s-chambers in cosmic stand
  TH2 *h2[15]; // declare 15 element array for 2D histos per chamber
  char *chamber = new char[100]; // for histo names
  char *description = new char[100]; // human readable name to the histograms
  char *description2d = new char[100]; // human readable name to the histograms
  string ch_name, outfile;
  TH1F *DeadStripsTable;
  int data, datay;

  if(run_num==-1){
    cout<<"Analysing all runs"<<endl;
    outfile = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/Roots/DeadStripsTable_allruns.root";

    DeadStripsTable = new TH1F("All runs: DeadStripsTable","No. of Chambers vs Number of Dead Strips (summed over all runs)",15,0.5,15.5);
    dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_DeadStrips_allruns.csv";
    fin.open(dir);
  }
  else{
    outfile = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/Roots/DeadStripsTable_run" + to_string(run_num) +".root";

    DeadStripsTable = new TH1F("DeadStripsTable","No. of Chambers vs Number of Dead Strips",15,0.5,15.5);
    dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_DeadStrips_run" + to_string(run_num) + ".csv";
    fin.open(dir);
  }

  TFile f(outfile.c_str(), "NEW");

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
      if(column_count==7){ // get run numbers into vector
        run=stoi(entry);
        runvec.push_back(run);
      }
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

  DeadStripsTable->Write("DeadStripsTable");
  runmax = *max_element(runvec.begin(), runvec.end());
  Double_t maxedge = runmax+0.5;

  // create and fill eta histograms for each chamber
  fin.open(dir);
  for(int i = 0; i<replic.size(); i++ ){
    strcpy(chamber, replic.at(i).c_str());
    strcpy(description, (replic.at(i) + ": Number of Dead Strips per Eta").c_str());
    h[i] = new TH1F(chamber, description, 8, 0.5, 8.5);
    strcpy(description2d, (replic.at(i) + ": Number of Dead Strips per Eta, per Run").c_str());
    h2[i] = new TH2F(chamber, description2d, 8, 0.5, 8.5,runmax,0.5,maxedge); // error, fill in numofbins line 93

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
            if(run_num!=-1)
              h[i]->Fill(data); // fill with eta_IDs
          }
        }
        if(column_count==7 && run_num==-1){
          if(ch_name==replic.at(i)){ // if row corresponds to chamber, read data
            datay = stoi(entry); // run number
            h2[i]->Fill(data,datay);
          }
        }
      }
    }
    fin.close();
    if(run_num==-1){
      h2[i]->SetOption("lego");
      h2[i]->SetXTitle("Eta");
      h2[i]->SetYTitle("Run Number");
      h2[i]->SetZTitle("Dead Strip Count");
      h2[i]->Write(chamber);
    }
    else
      h[i]->Write(chamber);
    fin.open(dir);  // re-open
    row_count=0; // reset row_count
  }
  f.Close();
  if(run_num==-1)
    cout<<"DeadStripsTable_allruns.root created."<<endl;
  else
    cout<<"DeadStripsTable_run" + to_string(run_num) +".root created."<<endl;
}
