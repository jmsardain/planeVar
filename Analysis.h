//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 29 20:46:32 2025 by ROOT version 6.34.04
// from TTree tree/tree
// found on file: data/ZToQQ_123.root
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TString.h>
#include <TChain.h>
#include <vector>
// Header file for the classes stored in the TTree if any.
using namespace std;


class Analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float> *part_px;
   vector<float> *part_py;
   vector<float> *part_pz;
   vector<float> *part_energy;
   vector<float> *part_deta;
   vector<float> *part_dphi;
   vector<float> *part_d0val;
   vector<float> *part_d0err;
   vector<float> *part_dzval;
   vector<float> *part_dzerr;
   vector<float> *part_charge;
   vector<int> *part_isChargedHadron;
   vector<int> *part_isNeutralHadron;
   vector<int> *part_isPhoton;
   vector<int> *part_isElectron;
   vector<int> *part_isMuon;
   Float_t         label_QCD;
   Bool_t          label_Hbb;
   Bool_t          label_Hcc;
   Bool_t          label_Hgg;
   Bool_t          label_H4q;
   Bool_t          label_Hqql;
   Int_t           label_Zqq;
   Int_t           label_Wqq;
   Int_t           label_Tbqq;
   Int_t           label_Tbl;
   Float_t         jet_pt;
   Float_t         jet_eta;
   Float_t         jet_phi;
   Float_t         jet_energy;
   Float_t         jet_nparticles;
   Float_t         jet_sdmass;
   Float_t         jet_tau1;
   Float_t         jet_tau2;
   Float_t         jet_tau3;
   Float_t         jet_tau4;
   Float_t         aux_genpart_eta;
   Float_t         aux_genpart_phi;
   Float_t         aux_genpart_pid;
   Float_t         aux_genpart_pt;
   Float_t         aux_truth_match;

   // List of branches
   TBranch        *b_part_px;   //!
   TBranch        *b_part_py;   //!
   TBranch        *b_part_pz;   //!
   TBranch        *b_part_energy;   //!
   TBranch        *b_part_deta;   //!
   TBranch        *b_part_dphi;   //!
   TBranch        *b_part_d0val;   //!
   TBranch        *b_part_d0err;   //!
   TBranch        *b_part_dzval;   //!
   TBranch        *b_part_dzerr;   //!
   TBranch        *b_part_charge;   //!
   TBranch        *b_part_isChargedHadron;   //!
   TBranch        *b_part_isNeutralHadron;   //!
   TBranch        *b_part_isPhoton;   //!
   TBranch        *b_part_isElectron;   //!
   TBranch        *b_part_isMuon;   //!
   TBranch        *b_label_QCD;   //!
   TBranch        *b_label_Hbb;   //!
   TBranch        *b_label_Hcc;   //!
   TBranch        *b_label_Hgg;   //!
   TBranch        *b_label_H4q;   //!
   TBranch        *b_label_Hqql;   //!
   TBranch        *b_label_Zqq;   //!
   TBranch        *b_label_Wqq;   //!
   TBranch        *b_label_Tbqq;   //!
   TBranch        *b_label_Tbl;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_energy;   //!
   TBranch        *b_jet_nparticles;   //!
   TBranch        *b_jet_sdmass;   //!
   TBranch        *b_jet_tau1;   //!
   TBranch        *b_jet_tau2;   //!
   TBranch        *b_jet_tau3;   //!
   TBranch        *b_jet_tau4;   //!
   TBranch        *b_aux_genpart_eta;   //!
   TBranch        *b_aux_genpart_phi;   //!
   TBranch        *b_aux_genpart_pid;   //!
   TBranch        *b_aux_genpart_pt;   //!
   TBranch        *b_aux_truth_match;   //!

   Analysis(TTree *tree=0);
   virtual ~Analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString Label);
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data/ZToQQ_123.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data/ZToQQ_123.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Analysis::~Analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   part_px = 0;
   part_py = 0;
   part_pz = 0;
   part_energy = 0;
   part_deta = 0;
   part_dphi = 0;
   part_d0val = 0;
   part_d0err = 0;
   part_dzval = 0;
   part_dzerr = 0;
   part_charge = 0;
   part_isChargedHadron = 0;
   part_isNeutralHadron = 0;
   part_isPhoton = 0;
   part_isElectron = 0;
   part_isMuon = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("part_px", &part_px, &b_part_px);
   fChain->SetBranchAddress("part_py", &part_py, &b_part_py);
   fChain->SetBranchAddress("part_pz", &part_pz, &b_part_pz);
   fChain->SetBranchAddress("part_energy", &part_energy, &b_part_energy);
   fChain->SetBranchAddress("part_deta", &part_deta, &b_part_deta);
   fChain->SetBranchAddress("part_dphi", &part_dphi, &b_part_dphi);
   fChain->SetBranchAddress("part_d0val", &part_d0val, &b_part_d0val);
   fChain->SetBranchAddress("part_d0err", &part_d0err, &b_part_d0err);
   fChain->SetBranchAddress("part_dzval", &part_dzval, &b_part_dzval);
   fChain->SetBranchAddress("part_dzerr", &part_dzerr, &b_part_dzerr);
   fChain->SetBranchAddress("part_charge", &part_charge, &b_part_charge);
   fChain->SetBranchAddress("part_isChargedHadron", &part_isChargedHadron, &b_part_isChargedHadron);
   fChain->SetBranchAddress("part_isNeutralHadron", &part_isNeutralHadron, &b_part_isNeutralHadron);
   fChain->SetBranchAddress("part_isPhoton", &part_isPhoton, &b_part_isPhoton);
   fChain->SetBranchAddress("part_isElectron", &part_isElectron, &b_part_isElectron);
   fChain->SetBranchAddress("part_isMuon", &part_isMuon, &b_part_isMuon);
   fChain->SetBranchAddress("label_QCD", &label_QCD, &b_label_QCD);
   fChain->SetBranchAddress("label_Hbb", &label_Hbb, &b_label_Hbb);
   fChain->SetBranchAddress("label_Hcc", &label_Hcc, &b_label_Hcc);
   fChain->SetBranchAddress("label_Hgg", &label_Hgg, &b_label_Hgg);
   fChain->SetBranchAddress("label_H4q", &label_H4q, &b_label_H4q);
   fChain->SetBranchAddress("label_Hqql", &label_Hqql, &b_label_Hqql);
   fChain->SetBranchAddress("label_Zqq", &label_Zqq, &b_label_Zqq);
   fChain->SetBranchAddress("label_Wqq", &label_Wqq, &b_label_Wqq);
   fChain->SetBranchAddress("label_Tbqq", &label_Tbqq, &b_label_Tbqq);
   fChain->SetBranchAddress("label_Tbl", &label_Tbl, &b_label_Tbl);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_energy", &jet_energy, &b_jet_energy);
   fChain->SetBranchAddress("jet_nparticles", &jet_nparticles, &b_jet_nparticles);
   fChain->SetBranchAddress("jet_sdmass", &jet_sdmass, &b_jet_sdmass);
   fChain->SetBranchAddress("jet_tau1", &jet_tau1, &b_jet_tau1);
   fChain->SetBranchAddress("jet_tau2", &jet_tau2, &b_jet_tau2);
   fChain->SetBranchAddress("jet_tau3", &jet_tau3, &b_jet_tau3);
   fChain->SetBranchAddress("jet_tau4", &jet_tau4, &b_jet_tau4);
   fChain->SetBranchAddress("aux_genpart_eta", &aux_genpart_eta, &b_aux_genpart_eta);
   fChain->SetBranchAddress("aux_genpart_phi", &aux_genpart_phi, &b_aux_genpart_phi);
   fChain->SetBranchAddress("aux_genpart_pid", &aux_genpart_pid, &b_aux_genpart_pid);
   fChain->SetBranchAddress("aux_genpart_pt", &aux_genpart_pt, &b_aux_genpart_pt);
   fChain->SetBranchAddress("aux_truth_match", &aux_truth_match, &b_aux_truth_match);
   Notify();
}

bool Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void Analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis_cxx
