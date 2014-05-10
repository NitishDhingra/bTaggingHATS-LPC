## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

##from PhysicsTools.PatAlgos.tools.coreTools import *
##removeMCMatching(process, ['All'])

## uncomment the following line to add tcMET to the event content
#from PhysicsTools.PatAlgos.tools.metTools import *
#addTcMET(process, 'TC')
#addPfMET(process, 'PF')

## Add different b-taggers collections to the event content
from PhysicsTools.PatAlgos.tools.jetTools import *

process.patJets.addTagInfos = True

# uncomment the following lines to add ak5PFJets with new b-tags to your PAT output
addJetCollection(process,cms.InputTag('ak5PFJets'),
                 'AK5', 'PF',
                 doJTA        = True,
                 doBTagging   = True,
                 btagInfo           = cms.vstring('impactParameterTagInfos','secondaryVertexTagInfos','secondaryVertexNegativeTagInfos','inclusiveSecondaryVertexFinderTagInfos'),
                 btagdiscriminators = cms.vstring('jetBProbabilityBJetTags','jetProbabilityBJetTags','trackCountingHighPurBJetTags','trackCountingHighEffBJetTags','simpleSecondaryVertexHighEffBJetTags','simpleSecondaryVertexHighPurBJetTags','combinedSecondaryVertexBJetTags','combinedInclusiveSecondaryVertexBJetTags'),
                 jetCorrLabel = ('AK5PF', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])),
                 doType1MET   = True,
                 doL1Cleaning = True,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("ak5GenJets"),
                 doJetID      = True,
                 jetIdLabel   = "ak5"
                 )
process.patJetsAK5PF.addTagInfos = True

## EDAnalyzer to apply selections & fill the histograms
process.demo = cms.EDAnalyzer('PATBTagAnalyzer', 
		RecoJetSource = cms.InputTag('cleanPatJetsAK5PF'),
		RecoJetEtaMaxCut = cms.double(2.5),
		RecoJetPtMinCut = cms.double(20.0)

		)

## Output root file containing the histograms
process.TFileService = cms.Service("TFileService",
		fileName = cms.string("analysis.root")
		)

## Message Logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100


## let it run
process.p = cms.Path( process.patDefaultSequence + process.demo )

## ------------------------------------------------------
#  In addition you usually want to change the following
#  parameters:
## ------------------------------------------------------
#
#   process.GlobalTag.globaltag =  ...    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
#                                         ##
## switch to RECO input
#from PhysicsTools.PatAlgos.patInputFiles_cff import filesRelValProdTTbarAODSIM
#process.source.fileNames = filesRelValProdTTbarAODSIM
#                                         ##
process.maxEvents.input = 2000
#                                         ##
#   process.out.outputCommands = [ ... ]  ##  (e.g. taken from PhysicsTools/PatAlgos/python/patEventContent_cff.py)
#                                         ##

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
'file:/eos/uscms/store/user/nitish/LPCBTaggingHATS/RelValTTbar_536/16D5D599-F129-E211-AB60-00261894390B.root' 

    )
)

process.out.fileName = 'patTuple_addBTagging.root'
process.options.wantSummary = False   ##  (to suppress the long output at the end of the job)
