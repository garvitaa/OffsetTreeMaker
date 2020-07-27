#ifndef __jetVetoMap_C__
#define __jetVetoMap_C__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

#include "TFile.h"
#include "TH2D.h"
#include "TMath.h"
#include "TString.h"

using namespace std;

vector<float> eta_low, eta_high, phi_low, phi_high;

float getVetoMap() {
  return eta_low, eta_high, phi_low, phi_high;
}

void jetVetoMap(TString filename="jetveto.root", TString map_name = "h2hot_ul18_plus_hem1516_and_hbp2m1" ) {
  TDirectory *curdir = gDirectory;

  TFile *f0 = new TFile(filename,"READ");
  assert(f0 && !f0->IsZombie());
  curdir->cd();

  TH2D *h2 = (TH2D*)f0->Get(map_name);
  assert(h2);

  for (int i = 1; i != h2->GetNbinsX()+1; ++i) {
    for (int j = 1; j !=  h2->GetNbinsY()+1; ++j) {
      if (h2->GetBinContent(i,j) >0){
        eta_low.push_back(h2->GetXaxis()->GetBinLowEdge(i)); 
        eta_high.push_back(h2->GetXaxis()->GetBinLowEdge(i) + h2->GetXaxis()->GetBinWidth(i));
        phi_low.push_back(h2->GetYaxis()->GetBinLowEdge(j));
        phi_high.push_back(h2->GetYaxis()->GetBinLowEdge(j) + h2->GetYaxis()->GetBinWidth(j));

        // std::cout<< "eta_low: " << h2->GetXaxis()->GetBinLowEdge(i) << " eta_high: " << (h2->GetXaxis()->GetBinLowEdge(i) + h2->GetXaxis()->GetBinWidth(i))
        //          << " phi_low: " << h2->GetYaxis()->GetBinLowEdge(j) << " phi_high: " << (h2->GetYaxis()->GetBinLowEdge(j) + h2->GetYaxis()->GetBinWidth(j))
        //          << "\t" <<h2->GetBinContent(i,j)<<std::endl;

      }
    }
  }
}

#endif //__jetVetoMap_C__