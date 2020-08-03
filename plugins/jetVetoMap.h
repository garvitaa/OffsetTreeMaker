#ifndef __jetVetoMap_C__
#define __jetVetoMap_C__

#include <iostream>
#include <vector>
#include <utility>

#include "TFile.h"
#include "TH2D.h"

using namespace std;

vector<vector<float>> jetVetoMap(TString filename="jetvetoinput.root", TString map_name = "h2hot_ul18_plus_hem1516_and_hbp2m1" ) {
  vector<vector<float>> m_JetVetoMap(4);
  TFile *f0 = TFile::Open(filename);
  if (!f0->IsOpen()){cout << "Jet Veto File not open .." <<endl;}

  TH2D *h2 = (TH2D*)f0->Get(map_name);
  m_JetVetoMap.clear();
  for (int i = 1; i != h2->GetNbinsX()+1; ++i) {
    for (int j = 1; j !=  h2->GetNbinsY()+1; ++j) {
      if (h2->GetBinContent(i,j) >0){
        m_JetVetoMap[0].push_back(h2->GetXaxis()->GetBinLowEdge(i)); 
        m_JetVetoMap[1].push_back(h2->GetXaxis()->GetBinLowEdge(i) + h2->GetXaxis()->GetBinWidth(i));
        m_JetVetoMap[2].push_back(h2->GetYaxis()->GetBinLowEdge(j));
        m_JetVetoMap[3].push_back(h2->GetYaxis()->GetBinLowEdge(j) + h2->GetYaxis()->GetBinWidth(j));
      }
    }
  }
  f0->Close();
  return m_JetVetoMap;
}

#endif //__jetVetoMap_C__
