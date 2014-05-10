//===========================================================================  
// Description:  An example code to access b-tagging information in PAT
//
// Authors: Nitish Dhingra, Alexander Schmidt
//
// Event: BTaggingHATS@Fermiab-LPC on 12 May, 2014
//===========================================================================  


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/Handle.h"

#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <TH1.h>
#include <TH2.h>

using namespace std;
using namespace reco;
using namespace edm;

// class declaration

class PATBTagAnalyzer : public edm::EDAnalyzer {
	public:
		explicit PATBTagAnalyzer(const edm::ParameterSet&);
		~PATBTagAnalyzer();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


	private:
		virtual void beginJob() ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob() ;

		TH1F *hBJetDiscrByTrackCountingHighEff;
		TH1F *hBJetDiscrByTrackCountingHighPur;
		TH1F *hBJetDiscrBySimpleSecondaryVertexHighEff;
		TH1F *hBJetDiscrByCombinedSecondaryVertexHighEff;
		TH1F *hBJetDiscrByCombinedSecondaryVertexMVA;
		TH1F *hBJetDiscrByjetProbabilityBJetTags;
		TH1F *hBJetDiscrByjetBProbabilityBJetTags; 
		TH1F *hTrueBJetPt;
		TH1F *hTrueBJetEta;
		TH1F *hTrueBJetPtPassingCSVM;
		TH1F *hTrueBJetEtaPassingCSVM;
		TH1F *hTrueBJetPtPassingCSVT;
		TH1F *hTrueBJetEtaPassingCSVT;
		TH1F *hJetPartonFlavor;
		TH1F *hNonBJetPt;
		TH1F *hNonBJetEta;
		TH1F *hNonBJetPtPassingCSVM;
		TH1F *hNonBJetEtaPassingCSVM;
		TH1F *hNonBJetPtPassingCSVT;
		TH1F *hNonBJetEtaPassingCSVT;
		TH1F *hTrueBJetPtPassingTCHP;
		TH1F *hTrueBJetEtaPassingTCHP;
		TH1F *hNonBJetPtPassingTCHP;
		TH1F *hNonBJetEtaPassingTCHP;
		InputTag _RecoJetSource;
		double   _RecoJetEtaMaxCut;
		double   _RecoJetPtMinCut;  
		int NBJets, NBJetsPassingCSVM, NBJetsPassingCSVT, NnonBJets, NnonBJetsPassingCSVM, NnonBJetsPassingCSVT, NBJetsPassingTCHP, NnonBJetsPassingTCHP;
		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
};

// constructors and destructor

PATBTagAnalyzer::PATBTagAnalyzer(const edm::ParameterSet& iConfig)

{
	Service<TFileService> fs; 
	_RecoJetSource = iConfig.getParameter<InputTag>("RecoJetSource");
	_RecoJetEtaMaxCut = iConfig.getParameter<double>("RecoJetEtaMaxCut");
	_RecoJetPtMinCut = iConfig.getParameter<double>("RecoJetPtMinCut");

	// Define Histograms 
	hBJetDiscrByTrackCountingHighEff = fs->make<TH1F>("BJetDiscrByTrackCountingHighEff", "BJetDiscrByTrackCountingHighEff", 400, -20, 20);
	hBJetDiscrByTrackCountingHighPur = fs->make<TH1F>("BJetDiscrByTrackCountingHighPur", "BJetDiscrByTrackCountingHighPur", 400, -20, 20);
	hBJetDiscrBySimpleSecondaryVertexHighEff = fs->make<TH1F>("BJetDiscrBySimpleSecondaryVertexHighEff", "BJetDiscrBySimpleSecondaryVertexHighEff", 400, -20, 20);
	hBJetDiscrByCombinedSecondaryVertexHighEff = fs->make<TH1F>("BJetDiscrByCombinedSecondaryVertexHighEff", "BJetDiscrByCombinedSecondaryVertexHighEff", 400, -20, 20);
	hBJetDiscrByCombinedSecondaryVertexMVA = fs->make<TH1F>("BJetDiscrByCombinedSecondaryVertexMVA", "BJetDiscrByCombinedSecondaryVertexMVA", 400, -20, 20);                
	hBJetDiscrByjetProbabilityBJetTags = fs->make<TH1F>("BJetDiscrByjetProbabilityBJetTags", "jetProbabilityBJetTags", 25, 0., 2.5);
	hBJetDiscrByjetBProbabilityBJetTags = fs->make<TH1F>("BJetDiscrByjetBProbabilityBJetTags", "jetBProbabilityBJetTags", 25, 0., 2.5);

	hTrueBJetPt = fs->make<TH1F>("TrueBJetPt", "TrueBJetPt", 100,0., 200.);
	hTrueBJetEta = fs->make<TH1F>("TrueBJetEta", "TrueBJetEta", 160, -4.0, 4.0);
	hTrueBJetPtPassingCSVM = fs->make<TH1F>("TrueBJetPtPassingCSVM","TrueBJetPtPassingCSVM", 100,0., 200.);
	hTrueBJetEtaPassingCSVM = fs->make<TH1F>("TrueBJetEtaPassingCSVM","TrueBJetEtaPassingCSVM", 160, -4.0, 4.0);
	hTrueBJetPtPassingCSVT = fs->make<TH1F>("TrueBJetPtPassingCSVT","TrueBJetPtPassingCSVT", 100,0., 200.);
	hTrueBJetEtaPassingCSVT = fs->make<TH1F>("TrueBJetEtaPassingCSVT","TrueBJetEtaPassingCSVT", 160, -4.0, 4.0);
	hJetPartonFlavor = fs->make<TH1F>("JetPartonFlavor", "JetPartonFlavor", 30, 0, 30);            
	hNonBJetPt = fs->make<TH1F>("NonBJetPt", "NonBJetPt", 100,0., 200.);
	hNonBJetEta = fs->make<TH1F>("NonBJetEta", "NonBJetEta", 160, -4.0, 4.0);
	hNonBJetPtPassingCSVM = fs->make<TH1F>("NonBJetPtPassingCSVM","NonBJetPtPassingCSVM", 100,0., 200.);
	hNonBJetEtaPassingCSVM = fs->make<TH1F>("NonBJetEtaPassingCSVM","NonBJetEtaPassingCSVM", 160, -4.0, 4.0);
	hNonBJetPtPassingCSVT = fs->make<TH1F>("NonBJetPtPassingCSVT","NonBJetPtPassingCSVT", 100,0., 200.);
	hNonBJetEtaPassingCSVT = fs->make<TH1F>("NonBJetEtaPassingCSVT","NonBJetEtaPassingCSVT", 160, -4.0, 4.0);	
	hTrueBJetPtPassingTCHP = fs->make<TH1F>("TrueBJetPtPassingTCHP", "TrueBJetPtPassingTCHP", 100, 0., 200.);
	hTrueBJetEtaPassingTCHP = fs->make<TH1F>("TrueBJetEtaPassingTCHP", "TrueBJetEtaPassingTCHP", 160, -4.0, 4.0);
	hNonBJetPtPassingTCHP = fs->make<TH1F>("NonBJetPtPassingTCHP", "NonBJetPtPassingTCHP", 100,0., 200.);
	hNonBJetEtaPassingTCHP = fs->make<TH1F>("NonBJetEtaPassingTCHP", "NonBJetEtaPassingTCHP", 160, -4.0, 4.0);
}


PATBTagAnalyzer::~PATBTagAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


// ------------ method called once each job just before starting event loop  ------------
void PATBTagAnalyzer::beginJob()
{

	NBJets=0;
	NBJetsPassingCSVM=0;
	NBJetsPassingCSVT=0; 
	NnonBJets=0; 
	NnonBJetsPassingCSVM=0;
	NnonBJetsPassingCSVT=0;
	NBJetsPassingTCHP=0;
	NnonBJetsPassingTCHP=0;

}
                                                                 

// ------------ method called for each event  ------------
void
PATBTagAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	edm::Handle< pat::JetCollection > _patJets;
	iEvent.getByLabel(_RecoJetSource, _patJets);

	for ( pat::JetCollection::const_iterator patJet = _patJets->begin(); patJet != _patJets->end(); ++patJet ) {

		// Only look at jets that pass jet pt and eta cuts
		if(patJet->pt() < _RecoJetPtMinCut || fabs(patJet->eta()) > _RecoJetEtaMaxCut) continue;

		hBJetDiscrByTrackCountingHighEff->Fill(patJet->bDiscriminator("trackCountingHighEffBJetTags"));
		hBJetDiscrByTrackCountingHighPur->Fill(patJet->bDiscriminator("trackCountingHighPurBJetTags"));
		hBJetDiscrBySimpleSecondaryVertexHighEff->Fill(patJet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
		hBJetDiscrByCombinedSecondaryVertexHighEff->Fill(patJet->bDiscriminator("combinedSecondaryVertexBJetTags"));
		hBJetDiscrByCombinedSecondaryVertexMVA->Fill(patJet->bDiscriminator("combinedSecondaryVertexMVABJetTags"));
		hBJetDiscrByjetProbabilityBJetTags->Fill(patJet->bDiscriminator("jetProbabilityBJetTags")); 
		hBJetDiscrByjetBProbabilityBJetTags->Fill(patJet->bDiscriminator("jetBProbabilityBJetTags"));
		hJetPartonFlavor->Fill(fabs(patJet->partonFlavour()));
		if(fabs(patJet->partonFlavour()) == 5) { hTrueBJetPt->Fill(patJet->pt()); hTrueBJetEta->Fill(patJet->eta()); NBJets++;
			if(patJet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679) { 
				hTrueBJetPtPassingCSVM->Fill(patJet->pt()); 
				hTrueBJetEtaPassingCSVM->Fill(patJet->eta());
				NBJetsPassingCSVM++;
			} 
			if(patJet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.898) {
				hTrueBJetPtPassingCSVT->Fill(patJet->pt());
				hTrueBJetEtaPassingCSVT->Fill(patJet->eta());
				NBJetsPassingCSVT++;
			} 
			if(patJet->bDiscriminator("trackCountingHighPurBJetTags") > 3.41) {
				hTrueBJetPtPassingTCHP->Fill(patJet->pt());
				hTrueBJetEtaPassingTCHP->Fill(patJet->eta());
				NBJetsPassingTCHP++;
			}

		} else if ((fabs(patJet->partonFlavour()) == 1) || (fabs(patJet->partonFlavour()) == 2) || (fabs(patJet->partonFlavour()) == 3) || (fabs(patJet->partonFlavour()) == 21)) {
			hNonBJetPt->Fill(patJet->pt()); 
			hNonBJetEta->Fill(patJet->eta());
			NnonBJets++;
			if(patJet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679) {
				hNonBJetPtPassingCSVM->Fill(patJet->pt());
				hNonBJetEtaPassingCSVM->Fill(patJet->eta());       
				NnonBJetsPassingCSVM++;                         
			} 
			if(patJet->bDiscriminator("combinedSecondaryVertexBJetTags") > 0.898) {
				hNonBJetPtPassingCSVT->Fill(patJet->pt());
				hNonBJetEtaPassingCSVT->Fill(patJet->eta());
				NnonBJetsPassingCSVT++;
			}
			if(patJet->bDiscriminator("trackCountingHighPurBJetTags") > 3.41) {
				hNonBJetPtPassingTCHP->Fill(patJet->pt());
				hNonBJetEtaPassingTCHP->Fill(patJet->eta());
				NnonBJetsPassingTCHP++;
			}
		}

	}

}


// ------------ method called once each job just after ending the event loop  ------------
void 
PATBTagAnalyzer::endJob() 
{
cout<<"\033[1;31m ==================================================================\033[0m\n";
cout<<"\033[1;31m              Results for CSV medium tagger                 \033[0m\n";
cout<<"\033[1;31m ==================================================================\033[0m\n";
cout<<"\033[2;32m B-tagging Efficiency (by simple counting) : "<<100.0*double(NBJetsPassingCSVM)/double(NBJets)<<"% \033[0m\n";
cout<<"\033[2;32m Mistag rate (by simple counting) : "<<100.0*double(NnonBJetsPassingCSVM)/double(NnonBJets)<<"% \033[0m\n"; 
cout<<"\033[1;31m ==================================================================\033[0m\n";

}

// ------------ method called when starting to processes a run  ------------
void 
PATBTagAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
PATBTagAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
PATBTagAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
PATBTagAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PATBTagAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PATBTagAnalyzer);
