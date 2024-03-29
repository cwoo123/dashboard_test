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

void Analysis_HotStripsTable(int run_num){ // test before adding analysis_Hot

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
  TH1F *HotStripsTable;
  int data, datay;

  if(run_num==-1){
    cout<<"Analysing all runs"<<endl;
    outfile = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/Roots/HotStripsTable_allruns.root";

    HotStripsTable = new TH1F("All runs: HotStripsTable","No. of Chambers vs Number of Hot Strips (summed over all runs)",15,0.5,15.5);
    dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_HotStrips_allruns.csv";
    fin.open(dir);
  }
  else{
    outfile = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/Roots/HotStripsTable_run" + to_string(run_num) +".root";

    HotStripsTable = new TH1F("HotStripsTable","No. of Chambers vs Number of Hot Strips",15,0.5,15.5);
    dir = "/afs/cern.ch/user/c/cwoo/dashboard_test/Dashboard/Data/CSVs/Test_HotStrips_run" + to_string(run_num) + ".csv";
    fin.open(dir);
  }

  TFile f(outfile.c_str(), "NEW");

  // get chamber s/n and run numbers in the DB
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

  row_count=0; //reset for use below
  fin.close();

  //draw summary plot for No. of VFAT vs No. of Hots
  for(int i = 0;i<ch_ID.size();i++){
    replic.push_back(ch_ID.at(i));
    name = ch_ID.at(i);
    if( count(replic.begin(), replic.end(), name) > 1 ){ // if replic has > 1 instance of "name", next iteration.
      replic.pop_back();
      continue;
    }
    ch_count = count(ch_ID.begin(), ch_ID.end(), name); // no. of time chamber name appears = no. of Hot strips in chamber
    HotStripsTable->Fill(ch_count);
    }

  HotStripsTable->Write("HotStripsTable");

  runmax = *max_element(runvec.begin(), runvec.end()); // sets num bins to the max run in the entire DB; try set to max run per CHAMBER instead
  Double_t maxedge = runmax+0.5; // sets edge to max run +0.5 in the entire DB; try set to max run per CHAMBER instead

  // create and fill eta histograms for each chamber
  fin.open(dir);
  for(int i = 0; i<replic.size(); i++ ){

    strcpy(chamber, replic.at(i).c_str());
    strcpy(description, (replic.at(i) + ": Number of Hot Strips per Eta").c_str());
    h[i] = new TH1F(chamber, description, 8, 0.5, 8.5);

    strcpy(description2d, (replic.at(i) + ": Number of Hot Strips per Eta, per Run").c_str());
    h2[i] = new TH2F(chamber, description2d, 8, 0.5, 8.5,runmax,0.5,maxedge); // error, fill in numofbins line 93

    while(getline(fin, line)){
      int column_count = 0;
      row_count+=1;
      stringstream s(line);

      while(getline(s,entry,',')){

        if(row_count==1) // skips loop when entries are column names
          break;
        column_count+=1;

        if(column_count==1){ // column for chamber names
          if(entry==replic.at(i)){
            ch_name = entry; // stores "entry" as ch_name for comparison if entry(row_count,1) == replic[i]
          }
          if(entry!=replic.at(i)){
            ch_name = " "; // assign some other string if entry(row_count,1) doesn't correspond
          }
        }
        if(column_count==4){
          if(ch_name==replic.at(i)){ // if row corresponds to right chamber, read data
            data = stoi(entry);
            data = 8-data%8; // obtain eta_ID
            if(run_num!=-1)
              h[i]->Fill(data); // fill with eta_IDs
          }
        }
        if(column_count==7 && run_num==-1){ // for analysis of all runs
          if(ch_name==replic.at(i)){ // if row corresponds to right chamber, read data
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
      h2[i]->SetZTitle("Hot Strip Count");
      h2[i]->Write(chamber);
    }
    else
      h[i]->Write(chamber);
    fin.open(dir);  // re-open
    row_count=0; // reset row_count
  }
  f.Close();

  if(run_num==-1)
    cout<<"HotStripsTable_allruns.root created."<<endl;
  else
    cout<<"HotStripsTable_run" + to_string(run_num) +".root created."<<endl;
}
