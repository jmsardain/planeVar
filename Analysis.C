#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/tools/Recluster.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/PseudoJet.hh"
#include <TVector2.h>
#include <TVector3.h>

using namespace fastjet;

void Analysis::Loop(TString Label){
   if (fChain == 0) return;
 
   TFile*fOut = new TFile("plots/"+Label+".root", "RECREATE");
   TH2F *h2 = new TH2F("h2","h2",10,0, 5,10,-1,6);
   TH1F *h_plane_angle = new TH1F("h_plane_angle","Angle between consecutive planes",50,-5,5);
   TH1F *h_pt_ratio = new TH1F("h_pt_ratio","pT ratio between consecutive splittings",50,0,10);
   TH2F *h_angle_vs_pt_ratio = new TH2F("h_angle_vs_pt_ratio","Angle vs pT ratio",100,0.5,1,100,0,0.5);

   Long64_t nentries = fChain->GetEntriesFast();
   int label = -1;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
    
      if(Label=="QCD") {
         label = label_QCD;
      } else if(Label=="W") {
         label = label_Wqq;
      } else if(Label=="Z") {
         label = label_Zqq;
      } else if(Label=="Hbb") {
         label = label_Hbb;
      } else {
         cout << " check argument! Exiting ... " << endl;
         return;
      }
      if(label!=1) continue;
      vector<PseudoJet> particles;
      for (unsigned int i=0; i<part_px->size(); i++){
         particles.push_back(PseudoJet(part_px->at(i), part_py->at(i), part_pz->at(i), part_energy->at(i)));
      }
      // std::cout << "particles.size() = " << particles.size() << std::endl;
      JetDefinition jet_def(cambridge_algorithm, 1.0);
      ClusterSequence cs(particles, jet_def);
      vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());
      cout << "jets.size() = " << jets.size() << endl;
      fastjet::PseudoJet j = jets.at(0);
      fastjet::PseudoJet jj, j1, j2;
      jj = j;
      
      TVector2 prev_normal(0,0);
      bool first_plane = true;
      double prev_hardest_pt = 0.0;
      bool first_splitting = true;
      double prev_angle = 0.0;
      
      while (jj.has_parents(j1,j2)) {
         if (j1.pt2() < j2.pt2()) 	{
            fastjet::PseudoJet jTemp;
            jTemp = j1;
            j1 = j2;
            j2 = jTemp;
         }
         
         // Calculate Lund variables
         double deltaR = std::log(1/j1.delta_R(j2)); 
         double kt = std::log(j2.pt() * j1.delta_R(j2));
         h2->Fill(deltaR, kt);
         
         // Get the hardest pseudojet at current level 
         double current_hardest_pt = j1.pt();
         
         TVector3 v1(j1.pt(), j1.eta(), j1.phi());
         TVector3 v2(j2.pt(), j2.eta(), j2.phi());
         TVector2 current_normal(-v1.Y(), v1.X()); 
         current_normal = current_normal.Unit(); // take unit vector 
         
         // Calculate angle between consecutive planes
         if (!first_plane) {
            double cos_angle = prev_normal * current_normal / (prev_normal.Mod() * current_normal.Mod());

            if (cos_angle > 1.0) cos_angle = 1.0;
            if (cos_angle < -1.0) cos_angle = -1.0;
    
            double angle = std::acos(cos_angle);
            h_plane_angle->Fill(angle);
            prev_angle = angle;
         }
         
         // Calculate pT ratio between hardest pseudojets for consecutive splittings
         if (!first_splitting) {
            double pt_ratio = current_hardest_pt / prev_hardest_pt ;
            h_pt_ratio->Fill(pt_ratio);
            h_angle_vs_pt_ratio->Fill(pt_ratio, prev_angle);
         }
         
         prev_normal = current_normal;
         prev_hardest_pt = current_hardest_pt;
         first_plane = false;
         first_splitting = false;
         jj = j1;
      }
   }

   
   h2->Write("lundPlane_"+Label);
   h_plane_angle->Write("planeAngles_"+Label);
   h_pt_ratio->Write("ptRatios_"+Label);
   h_angle_vs_pt_ratio->Write("angle_vs_pt_ratio_"+Label);
   fOut->Close();

}
