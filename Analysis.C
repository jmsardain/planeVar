#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
using namespace fastjet;

void Analysis::Loop(TString Label){
   if (fChain == 0) return;
 

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (jentry>2) break;
      vector<PseudoJet> particles;
      for (unsigned int i=0; i<part_px->size(); i++){
         particles.push_back(PseudoJet(part_px->at(i), part_py->at(i), part_pz->at(i), part_energy->at(i)));
      }
      JetDefinition jet_def(antikt_algorithm, 1.0);
      ClusterSequence cs(particles, jet_def);
      vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
      cout << "jets.size() = " << jets.size() << endl;
      
      // Now we can access the jets
      // implement the Lund plane analysis
      // define a plane from the pseudojets


   }
}
