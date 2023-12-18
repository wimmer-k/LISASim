#include <iostream>
#include <iomanip>
#include <string>
#include <sys/time.h>
#include <signal.h>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCutG.h"
#include "TStopwatch.h"

#include "CommandLineInterface.hh"
#include "EventInfo.hh"

using namespace TMath;
using namespace std;

bool signal_received = false;
void signalhandler(int sig);
double get_time();

int main(int argc, char* argv[]){
  double time_start = get_time();  
  TStopwatch timer;
  timer.Start();
  signal(SIGINT,signalhandler);
  vector<char*> InputFiles;
  char* OutputFile = NULL;
  int nmax =0;
  int vl =0;
  CommandLineInterface* interface = new CommandLineInterface();

  interface->Add("-i", "inputfiles", &InputFiles);
  interface->Add("-o", "outputfile", &OutputFile);
  interface->Add("-n", "nmax", &nmax);
  interface->Add("-v", "verbose", &vl);
  interface->CheckFlags(argc, argv);
  if(InputFiles.size() == 0 || OutputFile == NULL){
    cerr<<"You have to provide at least one input file and the output file!"<<endl;
    exit(1);
  }
  cout<<"input file(s):"<<endl;
  for(unsigned int i=0; i<InputFiles.size(); i++){
    cout<<InputFiles[i]<<endl;
  }
  cout<<"output file: "<<OutputFile<< endl;
  
  TChain* tr;
  tr = new TChain("str");
  for(unsigned int i=0; i<InputFiles.size(); i++){
    tr->Add(InputFiles[i]);
  }
  if(tr == NULL){
    cout << "could not find tree build in file " << endl;
    for(unsigned int i=0; i<InputFiles.size(); i++){
      cout<<InputFiles[i]<<endl;
    }
    return 3;
  }
  // branches in roofile
  SimEvent* simd = new SimEvent;
  tr->SetBranchAddress("simData",&simd);
  LISAEvent* lisa = new LISAEvent;
  tr->SetBranchAddress("lisaData",&lisa);

  // create the output file
  TFile* ofile = new TFile(OutputFile,"recreate");
  ofile->cd();

  // list of histograms
  TList *hlist = new TList();

  // LISA histos
  TH1F* l_hitpattern = new TH1F("l_hitpattern","l_hitpattern",125,0,125);hlist->Add(l_hitpattern);
  TH2F* l_Edep_layer = new TH2F("l_Edep_layer","l_Edep_layer",5,0,5,1000,0,5000);hlist->Add(l_Edep_layer);

  // simData histos
  TH2F* s_beta_layer = new TH2F("l_beta_layer","l_beta_layer",5,0,5,1000,0,1);hlist->Add(s_beta_layer);

  

  
  Double_t nentries = tr->GetEntries();
  if(nmax>0){
    nentries = nmax;
  }
  Int_t nbytes = 0;
  Int_t status;
  for(int i=0; i<nentries;i++){
    if(signal_received){
      break;
    }
    simd->Clear();
    lisa->Clear();


    // read the tree
    if(vl>2)
      cout << "getting entry " << i << endl;
    status = tr->GetEvent(i);
    if(vl>2)
      cout << "status " << status << endl;
    if(status == -1){
      cerr<<"Error occured, couldn't read entry "<<i<<" from tree "<<tr->GetName()<<" in file "<<tr->GetFile()->GetName()<<endl;
      return 5;
    }
    else if(status == 0){
      cerr<<"Error occured, entry "<<i<<" in tree "<<tr->GetName()<<" in file "<<tr->GetFile()->GetName()<<" doesn't exist"<<endl;
      return 6;
    }
    nbytes += status;

    for(UShort_t j=0;j< simd->GetNLayers();j++){
      s_beta_layer->Fill(j,simd->GetOutGoingBeta(j));
    }
    
    
    for(UShort_t j=0;j<lisa->GetNLayers();j++){
      l_Edep_layer->Fill(lisa->GetLayerID(j), lisa->GetEnergyDetected(j));
    }
    
    
    if(i%10000 == 0){
      double time_end = get_time();
      cout<<setw(5)<<setiosflags(ios::fixed)<<setprecision(1)<<(100.*i)/nentries<<" % done\t"<<(Float_t)i/(time_end - time_start)<<" events/s " << (nentries-i)*(time_end - time_start)/(Float_t)i<<"s to go \r"<<flush;
    }

  }
  cout << endl;

    
  cout << "writing to file" << endl;
  cout << endl;
  ofile->cd();
  TH1F* h1;
  TH2F* h2;
  TIter next(hlist);
  while( (h1 = (TH1F*)next()) ){
    if(h1->GetEntries()>0)
      h1->Write("",TObject::kOverwrite);
  }
  while( (h2 = (TH2F*)next()) ){
    if(h2->GetEntries()>0)
      h2->Write("",TObject::kOverwrite);
  }
  ofile->Close();
    
  double time_end = get_time();
  cout << "Run time " << time_end - time_start << " s." << endl;

  return 0;
}
void signalhandler(int sig){
  if (sig == SIGINT){
    signal_received = true;
  }
}

double get_time(){
    struct timeval t;
    gettimeofday(&t, NULL);
    double d = t.tv_sec + (double) t.tv_usec/1000000;
    return d;
}
