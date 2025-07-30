#include <iostream>
#include "TString.h"
#include "Analysis.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(int argc, char* argv[]){
// int main(){
	std::string label(argv[1]);
	

	TString Label  = TString(label.c_str());
	TString theLink = "./data/*root";

	
	TString treeName = "tree";
	TChain * myChain = new TChain( treeName ) ;

	cout << theLink << endl ;

	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;


	Analysis * myAnalysis ;
	myAnalysis =  new Analysis( myChain ) ;
	myAnalysis->Loop(Label);
	return 0;

}
