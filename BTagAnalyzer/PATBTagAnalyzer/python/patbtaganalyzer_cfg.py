import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
#'file:/afs/cern.ch/work/n/nitish/LPCBTaggingHATS/CMSSW_5_3_13/src/BTagAnalyzer/PATBTagAnalyzer/16D5D599-F129-E211-AB60-00261894390B.root'
'file:/afs/cern.ch/work/n/nitish/LPCBTaggingHATS/CMSSW_5_3_13/src/BTagAnalyzer/PATBTagAnalyzer/patTuple_addBTagging.root'

    )
)

process.demo = cms.EDAnalyzer('PATBTagAnalyzer')
process.demo.RecoJetSource = cms.InputTag('selectedPatJets')

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("analysis.root")
                              )


process.p = cms.Path(process.demo)
