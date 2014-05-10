import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('PATBTagAnalyzer',
RecoJetSource = cms.InputTag('selectedPatJets')
)
#process.demo = cms.EDAnalyzer('PATBTagAnalyzer')
#process.demo.RecoJetSource = cms.InputTag('selectedPatJets')


