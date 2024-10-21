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
#include "TColor.h"
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

  // vector<vector<TH2F*> > l_Reac_LBL_Eloss_vec;
  // for(int i=0; i<simd->GetNLayers(); i++){
  //   for(int j=0;j<=1;j++) {
  //   l_Reac_LBL_Eloss_vec[i][j] = new TH2F(Form("l_Reac_LBL_Eloss_%d_%d",i,j),Form("l_Reac_LBL_Eloss_%d_%d",i,j),1000,2900,3400,1000,2900,3400);hlist->Add(l_Reac_LBL_Eloss_vec[i][j]);
  //   } 
  // }
  
  TH2F* l_Reac_LBL_Eloss00 = new TH2F("l_Reac_LBL_Eloss00","l_Reac_LBL_Eloss00",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss00);
  TH2F* l_Reac_LBL_Eloss01 = new TH2F("l_Reac_LBL_Eloss01","l_Reac_LBL_Eloss01",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss01);
  TH2F* l_Reac_LBL_Eloss10 = new TH2F("l_Reac_LBL_Eloss10","l_Reac_LBL_Eloss10",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss10);
  TH2F* l_Reac_LBL_Eloss11 = new TH2F("l_Reac_LBL_Eloss11","l_Reac_LBL_Eloss11",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss11);
  TH2F* l_Reac_LBL_Eloss20 = new TH2F("l_Reac_LBL_Eloss20","l_Reac_LBL_Eloss20",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss20);
  TH2F* l_Reac_LBL_Eloss21 = new TH2F("l_Reac_LBL_Eloss21","l_Reac_LBL_Eloss21",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss21);
  TH2F* l_Reac_LBL_Eloss30 = new TH2F("l_Reac_LBL_Eloss30","l_Reac_LBL_Eloss30",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss30);
  TH2F* l_Reac_LBL_Eloss31 = new TH2F("l_Reac_LBL_Eloss31","l_Reac_LBL_Eloss31",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss31);
  TH2F* l_Reac_LBL_Eloss40 = new TH2F("l_Reac_LBL_Eloss40","l_Reac_LBL_Eloss40",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss40);
  TH2F* l_Reac_LBL_Eloss41 = new TH2F("l_Reac_LBL_Eloss41","l_Reac_LBL_Eloss41",100,0,5,200,300,500);hlist->Add(l_Reac_LBL_Eloss41);
  vector<TH2F*> plots_vec ; 
  int max_cont = 0 ;
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
    
    
    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      l_Edep_layer->Fill(lisa->GetLayerID(j), lisa->GetEnergyDetected(j));
      
    }


    //creating LBL reacted vs unreacted beam plots



    //bool cond = 1;


    // for(int sz = 0;sz<simd->GetNLayers();sz++){
    //   cond=1;
    //   for(int k = 0;k<simd->GetNLayers();k++){
    //     cout<<cond<<"cond"<<simd->GetReactionLayer()<<"  iteration = "<<k<<"   "<<sz<<endl;;
    //     if(cond == true && lisa->GetLayerID(sz+1) == k+1 && (simd->GetReactionLayer()== k || simd->GetReactionLayer() == k+1)){
    //       cond = 1 ; 

    //     cout<<simd->GetReactionLayer()<<"  iteration = "<<k<<"   "<<sz<<endl;
    //     }
    //     else cond = 0;
    //   }
    // }


    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 0 && simd->GetReactionLayer() == 0 ){
         
         l_Reac_LBL_Eloss01->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
    l_Reac_LBL_Eloss01->SetLineColor(kRed);

    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 0 && simd->GetReactionLayer() != 0 ){
         
         l_Reac_LBL_Eloss00->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }

   Int_t MaxBin = l_Reac_LBL_Eloss00->GetMaximumBin();
   Int_t x,y,z;
   l_Reac_LBL_Eloss00->GetBinXYZ(MaxBin, x, y, z);
   max_cont = l_Reac_LBL_Eloss00->GetBinContent(MaxBin);
   


    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 1 && (simd->GetReactionLayer() == 0 || simd->GetReactionLayer() == 1)){
         
         l_Reac_LBL_Eloss11->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
     l_Reac_LBL_Eloss11->SetLineColor(kRed);


    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 1 && (simd->GetReactionLayer() != 0 && simd->GetReactionLayer() != 1)){
         
         l_Reac_LBL_Eloss10->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }




    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 2 && (simd->GetReactionLayer() == 0 || simd->GetReactionLayer() == 1 || simd->GetReactionLayer() == 2 )){
         
         l_Reac_LBL_Eloss21->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
     l_Reac_LBL_Eloss21->SetLineColor(kRed);

    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 2 && (simd->GetReactionLayer() != 0 && simd->GetReactionLayer() != 1 && simd->GetReactionLayer() != 2)){
         
         l_Reac_LBL_Eloss20->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }




    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 3 && (simd->GetReactionLayer() == 0 || simd->GetReactionLayer() == 1 || simd->GetReactionLayer() == 2 || simd->GetReactionLayer() == 3)){
         
         l_Reac_LBL_Eloss31->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
     l_Reac_LBL_Eloss31->SetLineColor(kRed);

    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 3 && (simd->GetReactionLayer() != 0 && simd->GetReactionLayer() != 1 && simd->GetReactionLayer() != 2 && simd->GetReactionLayer() != 3)){
         
         l_Reac_LBL_Eloss30->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }


    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 4 && (simd->GetReactionLayer() == 0 || simd->GetReactionLayer() == 1 || simd->GetReactionLayer() == 2 || simd->GetReactionLayer() == 3 || simd->GetReactionLayer() == 4 ) ){
         
         l_Reac_LBL_Eloss41->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
     l_Reac_LBL_Eloss41->SetLineColor(kRed);

    for(UShort_t j=0;j<lisa->GetLayers().size();j++){
      if(lisa->GetLayerID(j) == 4 && (simd->GetReactionLayer() != 0 && simd->GetReactionLayer() != 1 && simd->GetReactionLayer() != 2 && simd->GetReactionLayer() != 3 && simd->GetReactionLayer() != 4)){
         
         l_Reac_LBL_Eloss40->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j));
         
       }
     }
    

    





    
    //   for(UShort_t j=0;j<lisa->GetLayers().size();j++){
    //   if(lisa->GetLayerID(j) = 0 && simd->GetReactionLayer() != 0 ){

    //     l_Reac_LBL_Eloss_vec[0][0]->Fill(lisa->GetLayerID(j),lisa->GetEnergyDetected(j)); 

    //   }
    // }
    
    if(i%10000 == 0){
      double time_end = get_time();
      cout<<setw(5)<<setiosflags(ios::fixed)<<setprecision(1)<<(100.*i)/nentries<<" % done\t"<<(Float_t)i/(time_end - time_start)<<" events/s " << (nentries-i)*(time_end - time_start)/(Float_t)i<<"s to go \r"<<flush;
    }

  } //end of hits loop







    l_Reac_LBL_Eloss00->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss00);
    l_Reac_LBL_Eloss01->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss01);
    l_Reac_LBL_Eloss10->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss10);
    l_Reac_LBL_Eloss11->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss11);
    l_Reac_LBL_Eloss20->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss20);
    l_Reac_LBL_Eloss21->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss21);
    l_Reac_LBL_Eloss30->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss30);
    l_Reac_LBL_Eloss31->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss31);
    l_Reac_LBL_Eloss40->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss40);
    l_Reac_LBL_Eloss41->SetBinContent(1,200,max_cont);
    plots_vec.push_back(l_Reac_LBL_Eloss41);

 
 

  double red[2] = { 51, 231};
  double gre[2] = { 66,  68};
  double blu[2] = {155,  56};


    for(UShort_t i=0;i<plots_vec.size();i++){
    double sred = red[0]+i*(red[1]-red[0])/(plots_vec.size()-1);
    double sgre = gre[0]+i*(gre[1]-gre[0])/(plots_vec.size()-1);
    double sblu = blu[0]+i*(blu[1]-blu[0])/(plots_vec.size()-1);
    Int_t ci = TColor::GetFreeColorIndex(); // color index
    //auto color = new TColor(ci, sred/256, sgre/256, sblu/256);
    auto color = new TColor(ci, 223./256., 255./256., 11./256.);
    //color->SetRGB(223./256., 255./256., 11./256.);
    //cout<<"red:  "<<sred/256<<" green:  "<<sgre/256<<"  blue:  "<<sblu/256<<endl;
    //plots_vec[i]->SetFillColor(color);
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
