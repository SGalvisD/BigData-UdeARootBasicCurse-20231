#ifndef classtoy_h
#define classtoy_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class classtoy {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Nspull;
   Double_t        Nsdif;
   Double_t        Nbpull;
   Double_t        Mupull;
   Double_t        Nsig;
   Double_t        NsigE;
   Double_t        Nbkg;
   Double_t        NbkgE;
   Double_t        mu;
   Double_t        muE;
   Double_t        g1;
   Double_t        g1E;
   Double_t        conscheb;
   Double_t        conschebE;
   Double_t        edm;
   Double_t        llh;
   Int_t           status;
   Int_t           covQual;
   Int_t           badNll;

   // List of branches
   TBranch        *b_Nspull;   //!
   TBranch        *b_Nsdif;   //!
   TBranch        *b_Nbpull;   //!
   TBranch        *b_Mupull;   //!
   TBranch        *b_Nsig;   //!
   TBranch        *b_NsigE;   //!
   TBranch        *b_Nbkg;   //!
   TBranch        *b_NbkgE;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_muE;   //!
   TBranch        *b_g1;   //!
   TBranch        *b_g1E;   //!
   TBranch        *b_conscheb;   //!
   TBranch        *b_conschebE;   //!
   TBranch        *b_edm;   //!
   TBranch        *b_llh;   //!
   TBranch        *b_status;   //!
   TBranch        *b_covQual;   //!
   TBranch        *b_badNll;   //!

   classtoy(TTree *tree=0);
   virtual ~classtoy();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef classtoy_cxx
classtoy::classtoy(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ToyMC_Par2.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ToyMC_Par2.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

classtoy::~classtoy()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t classtoy::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t classtoy::LoadTree(Long64_t entry)
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

void classtoy::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Nspull", &Nspull, &b_Nspull);
   fChain->SetBranchAddress("Nsdif", &Nsdif, &b_Nsdif);
   fChain->SetBranchAddress("Nbpull", &Nbpull, &b_Nbpull);
   fChain->SetBranchAddress("Mupull", &Mupull, &b_Mupull);
   fChain->SetBranchAddress("Nsig", &Nsig, &b_Nsig);
   fChain->SetBranchAddress("NsigE", &NsigE, &b_NsigE);
   fChain->SetBranchAddress("Nbkg", &Nbkg, &b_Nbkg);
   fChain->SetBranchAddress("NbkgE", &NbkgE, &b_NbkgE);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("muE", &muE, &b_muE);
   fChain->SetBranchAddress("g1", &g1, &b_g1);
   fChain->SetBranchAddress("g1E", &g1E, &b_g1E);
   fChain->SetBranchAddress("conscheb", &conscheb, &b_conscheb);
   fChain->SetBranchAddress("conschebE", &conschebE, &b_conschebE);
   fChain->SetBranchAddress("edm", &edm, &b_edm);
   fChain->SetBranchAddress("llh", &llh, &b_llh);
   fChain->SetBranchAddress("status", &status, &b_status);
   fChain->SetBranchAddress("covQual", &covQual, &b_covQual);
   fChain->SetBranchAddress("badNll", &badNll, &b_badNll);
   Notify();
}

Bool_t classtoy::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void classtoy::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t classtoy::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef classtoy_cxx
