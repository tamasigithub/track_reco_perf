#example of personal topOptions
#
# to use it  
# RecExCommon_links.sh  # once in a given directory
# athena >! athena.log
#  ( myTopOptions.py is defaulted through jobOptions.py soft link)
# 
# see RecExCommon/share/RecExCommon_flags.py for more available flags
# and https://twiki.cern.ch/twiki/bin/view/Atlas/RecExCommonFlags
# for more complete documentation.
#

from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
from RecExConfig.RecFlags import rec
from RecExConfig.RecAlgsFlags import recAlgs
from InDetRecExample.InDetJobProperties import InDetFlags
InDetFlags.doSecVertexFinder.set_Value_and_Lock(False)


athenaCommonFlags.FilesInput=["/nfs/dust/atlas/user/tkar/derivations/run/OUT1.AOD.combinedhh4b.pool.root"]
#athenaCommonFlags.FilesInput=["ESD.Fullhh4b.pool.root"]

#### Rubbish!!!
#from InDetSLHC_Example.SLHC_JobProperties import SLHC_Flags
#SLHC_Flags.doGMX.set_Value_and_Lock(True)
#SLHC_Flags.LayoutOption="InclinedDuals"
#include("InDetSLHC_Example/preInclude.SLHC_Setup_InclBrl_4.py")
#include("InDetSLHC_Example/preInclude.SLHC_Setup_Strip_GMX.py")
#include("InDetSLHC_Example/preInclude.SLHC_Calorimeter_mu0.py")
#include("InDetSLHC_Example/preInclude.SLHC.NoTRT_NoBCM_NoDBM.Reco.py")
#include("InDetSLHC_Example/SLHC_Setup_Reco_TrackingGeometry_GMX.py")
#DetDescrVersion = 'ATLAS-P2-ITK-20-00-00'
#include("RecExCond/AllDet_detDescr.py")

from RecExConfig import AutoConfiguration
AutoConfiguration.ConfigureSimulationOrRealData()
AutoConfiguration.ConfigureGeo()
AutoConfiguration.ConfigureConditionsTag()
# retrieving the PixelClusterContainer only requires the pixel detector description
from AthenaCommon.DetFlags import DetFlags
DetFlags.detdescr.all_setOff()
DetFlags.detdescr.pixel_setOn()
DetFlags.detdescr.SCT_setOn()
# preincludes
include("InDetSLHC_Example/preInclude.SLHC.py")
include('InDetSLHC_Example/preInclude.SLHC_Setup_Strip_GMX.py')
include('InDetSLHC_Example/preInclude.SLHC_Setup_InclBrl_4.py')
# Now load the description: 
include("RecExCond/AllDet_detDescr.py")
# postincludes
include("InDetSLHC_Example/postInclude.SLHC_Setup_InclBrl_4.py")
DetFlags.detdescr.TRT_setOff()
DetFlags.detdescr.AFP_setOff()
DetFlags.detdescr.ALFA_setOff()
DetFlags.detdescr.BCM_setOff()
DetFlags.detdescr.ZDC_setOff()
DetFlags.detdescr.Calo_setOn()
DetFlags.detdescr.Muon_setOff()



#set input file. Note that this triggers autoconfiguration automatically (see RecExCommonAutoConfiguration wiki)
# here a MC RDO is specified, but this can also be a data BS, an ESD AOD or TAG
#if athenaCommonFlags.FilesInput.isDefault(): # check if not already set upstream
#    athenaCommonFlags.FilesInput=["LFN:top_GEO-02-01-00_RDO_extract.pool"] 

athenaCommonFlags.EvtMax=-1   # number of events to process run on all file


# switch off detectors
rec.doForwardDet=False
rec.doInDet=True
rec.doCalo=True
rec.doMuon=False
rec.doEgamma=False
rec.doTrigger = False; recAlgs.doTrigger=False # disable trigger (maybe necessary if detectors switched of)
rec.doMuon=False
rec.doMuonCombined=False
rec.doWriteAOD=True
rec.doWriteESD=False
rec.doDPD=False
rec.doTruth=True

rec.doNameAuditor=True


# ** Turn PerfMon off for valgrind usage **
rec.doPerfMon.set_Value_and_Lock(False)
rec.doDetailedPerfMon.set_Value_and_Lock(False)
rec.doSemiDetailedPerfMon.set_Value_and_Lock(False)



# include my own algorithm(s). These jobo will be included at the end of topSequence configuration
# rec.UserAlgs=[ "MyPackage/MyAlgorithm_jobOptions.py" ]
# these lines will be executed at the end of topSequence configuration
# rec.UserExecs=[ "from MyPackage.myAlgConf import myAlg","topSequence+=myAlg()" ]
# these lines will be executed after RecExCommon_flags.py has been imported, last chance for flag modification
# note that flag locking mechanism has a better chance to yield consistent configuration
# see https://twiki.cern.ch/twiki/bin/view/Atlas/TriggerFlags
# see https://twiki.cern.ch/twiki/bin/view/Atlas/UserAnalysisTest#The_AOD_Production_Flags
# rec.UserFlags=[ "AODFlags.FastSimulation=False" ] 


# autoconfiguration might trigger undesired feature
rec.doESD.set_Value_and_Lock(False) # uncomment if do not run ESD making algorithms
rec.doWriteESD.set_Value_and_Lock(False) # uncomment if do not write ESD
rec.doAOD.set_Value_and_Lock(False) # uncomment if do not run AOD making algorithms
rec.doWriteAOD.set_Value_and_Lock(True) # uncomment if do not write AOD
rec.doWriteTAG.set_Value_and_Lock(False) # uncomment if do not write TAG


#rec.doDumpTES=True

from AthenaCommon.AlgSequence import AlgSequence
from AthenaCommon.AppMgr import ToolSvc,theApp,ServiceMgr
from AthenaCommon.AthenaCommonFlags  import athenaCommonFlags
from AthenaCommon.GlobalFlags  import globalflags
from AthenaCommon.BeamFlags import jobproperties
from RecExConfig.RecFlags import rec
from AthenaCommon.Resilience import treatException,protectedInclude
topSequence = AlgSequence()

from JetRec.JetRecStandard import jtm
jtm.useTracks = True
from JetRec.JetRecConf import PseudoJetGetter
from JetRecTools.JetRecToolsConf import TrackPseudoJetGetter

from JetRecTools.JetRecToolsConf import JetTrackSelectionTool
from JetRecTools.JetRecToolsConf import SimpleJetTrackSelectionTool
from JetRecTools.JetRecToolsConf import TrackVertexAssociationTool
from JetRec.JetRecConf import JetSorter
from JetMomentTools.JetMomentToolsConf import JetVertexFractionTool
from JetMomentTools.JetMomentToolsConf import JetVertexTaggerTool

from InDetTrackSelectionTool.InDetTrackSelectionToolConf import InDet__InDetTrackSelectionTool

from MyAnalysis.MyAnalysisConf import MyPVAnalysis
topSequence += MyPVAnalysis("MyPVAnalysis")
topSequence.MyPVAnalysis.NumberOfVertexBins = 40
topSequence.MyPVAnalysis.RangeOfZVertex = 200. #mm
topSequence.MyPVAnalysis.MinimumPtJet = 5000. # MeV
topSequence.MyPVAnalysis.MaximumNumberJets = 10

jtm += InDet__InDetTrackSelectionTool(
  "trk_ttttrackselloose",
  minPt                   = 500,
  maxAbsEta               = 1.5,
  CutLevel                = "",
)

jtm += JetTrackSelectionTool(
  "stdtracksel",
  InputContainer  = "InDetTrackParticles",
  OutputContainer = "JetSelectedStdTracks",
  Selector        = jtm.trk_trackselloose
)
jtm += JetTrackSelectionTool(
  "stdtrackselloose",
  InputContainer  = "InDetTrackParticles",
  OutputContainer = "JetSelectedStdTracks",
  Selector        = jtm.trk_trackselloose
)
jtm += JetTrackSelectionTool(
  "ttttracksel",
  InputContainer  = "TTTParticles",
  OutputContainer = "JetSelectedTTTTracks",
  Selector        = jtm.trk_ttttrackselloose
)
jtm += JetTrackSelectionTool(
  "ttttrackselloose",
  InputContainer  = "TTTParticles",
  OutputContainer = "JetSelectedTTTLooseTracks",
  Selector        = jtm.trk_ttttrackselloose
)
jtm += TrackVertexAssociationTool(
  "stdtvassoc",
  TrackParticleContainer  = "InDetTrackParticles",
  TrackVertexAssociation  = "JetStdTrackVtxAssoc",
  VertexContainer         = "PrimaryVertices",
  TrackVertexAssoTool     = jtm.jetTighTVAtool,
)

from TrackVertexAssociationTool.TrackVertexAssociationToolConf import CP__TightTrackVertexAssociationTool
jtm += CP__TightTrackVertexAssociationTool("jetTighTVAtoolTTT", dzSinTheta_cut=5.0, doPV=True)

jtm += TrackVertexAssociationTool(
  "ttttvassoc",
  TrackParticleContainer  = "TTTParticles",
  TrackVertexAssociation  = "JetTTTTrackVtxAssoc",
  ####VertexContainer         = "PrimaryVertices",
  VertexContainer         = "MyPrimaryVertices",        # Change this to use the standard offline PV
  TrackVertexAssoTool     = jtm.jetTighTVAtoolTTT,
)

# Jet vertex fraction with selection.
#jtm += JetVertexFractionTool(
#  "jvf",
#  VertexContainer = jtm.vertexContainer,
#  AssociatedTracks = "GhostTrack",
#  TrackVertexAssociation = jtm.tvassoc.TrackVertexAssociation,
#  TrackSelector = jtm.trackselloose,
#  JVFName = "JVF"
#)

# Jet vertex tagger.
jtm += JetVertexTaggerTool(
  "jvtTTT",
  ####VertexContainer = "PrimaryVertices",
  VertexContainer         = "MyPrimaryVertices",        # Change this to use the standard offline PV
  TrackParticleContainer  = "TTTParticles",
  AssociatedTracks = "GhostTTTTrack",
  TrackVertexAssociation = "JetTTTTrackVtxAssoc",
  TrackSelector = jtm.ttttrackselloose,
  JVTName = "JvtTTT",
  K_JVFCorrScale = 0.01,
  Z0Cut = 3.0,
  PUTrkPtCut = 30000.0
)
jtm += JetVertexTaggerTool(
  "jvtStd",
  VertexContainer = "PrimaryVertices",
  TrackParticleContainer  = "InDetTrackParticles",
  AssociatedTracks = "GhostStdTrack",
  TrackVertexAssociation = "JetStdTrackVtxAssoc",
  TrackSelector = jtm.stdtrackselloose,
  JVTName = "JvtStd",
  K_JVFCorrScale = 0.01,
  Z0Cut = 3.0,
  PUTrkPtCut = 30000.0
)

jtm += JetVertexFractionTool(
  "jvfTTT",
  ####VertexContainer = "PrimaryVertices",
  VertexContainer         = "MyPrimaryVertices",        # Change this to use the standard offline PV
  AssociatedTracks = "GhostTTTTrack",
  TrackVertexAssociation = "JetTTTTrackVtxAssoc",
  TrackSelector = jtm.ttttrackselloose,
  JVFName = "JVFTTT"
)

jtm += JetVertexFractionTool(
  "jvfStd",
  VertexContainer = "PrimaryVertices",
  AssociatedTracks = "GhostStdTrack",
  TrackVertexAssociation = "JetStdTrackVtxAssoc",
  TrackSelector = jtm.stdtrackselloose,
  JVFName = "JVFStd"
)

####
#common_ungroomed_modifiers = [
#  jtm.width,
#  jtm.jetisol,
#  jtm.ktdr,
#  jtm.nsubjettiness,
#  jtm.ktsplitter,
#  jtm.angularity,
#  jtm.dipolarity,
#  jtm.planarflow,
#  jtm.ktmassdrop,
#  jtm.encorr,
#  jtm.comshapes
#]
#
## Add parton truth labels and truth jet modifiers.
#if jetFlags.useTruth():
#  if jtm.haveParticleJetTools:
#    common_ungroomed_modifiers += [jtm.partontruthlabel]
#    common_ungroomed_modifiers += [jtm.truthpartondr]
#
#  # Modifiers for truth jets.
#  truth_ungroomed_modifiers = list(common_ungroomed_modifiers)
#  if jtm.haveParticleJetTools:
#    truth_ungroomed_modifiers += [jtm.jetdrlabeler]
#
## Modifiers for track jets.
#track_ungroomed_modifiers = list(common_ungroomed_modifiers)
#if jetFlags.useTruth() and jtm.haveParticleJetTools:
#  track_ungroomed_modifiers += [jtm.trackjetdrlabeler]
#
## Modifiers for topo (and pflow) jets.
#topo_ungroomed_modifiers = ["jetfilter"]
#topo_ungroomed_modifiers += common_ungroomed_modifiers
#topo_ungroomed_modifiers += [jtm.jetens]
#topo_ungroomed_modifiers += [jtm.larhvcorr]
#if jetFlags.useCaloQualityTool():
#  topo_ungroomed_modifiers += [jtm.caloqual_cluster]
#if jetFlags.useTracks():
#  topo_ungroomed_modifiers += [jtm.jvf]
####

# Ghost tracks.
jtm += TrackPseudoJetGetter(
  "GTTTTrackGetter",
  InputContainer = "JetSelectedTTTTracks",
  Label = "GhostTTTTrack",
  OutputContainer = "PseudoJetGhostTTTTracks",
  TrackVertexAssociation = "JetTTTTrackVtxAssoc",
  SkipNegativeEnergy = True,
  GhostScale = 1e-40,
)
jtm += TrackPseudoJetGetter(
  "GStdTrackGetter",
  InputContainer = "JetSelectedStdTracks",
  Label = "GhostStdTrack",
  OutputContainer = "PseudoJetGhostStdTracks",
  TrackVertexAssociation = "JetStdTrackVtxAssoc",
  SkipNegativeEnergy = True,
  GhostScale = 1e-40,
)

# now make the input objects list for the AntiKt4EMTopo
# jet using the set of topoclusters
# that came in the output of the subtraction above
jtm += PseudoJetGetter(
   "CaloGetter",
   InputContainer = 'CaloCalTopoClusters',
   Label = "EMTopo",
   OutputContainer = 'CaloCalTopoClustersPseudoJet',
   SkipNegativeEnergy = True,
   GhostScale = 0.0
   )
# associate tracks to the jets to calculate track-dependent variables
jtm += TrackPseudoJetGetter(
   "TrackGetter",
   #InputContainer = 'InDetTrackParticles',
   InputContainer = 'JetSelectedStdTracks',
   Label = "Track",
   OutputContainer = 'InDetTrackParticlesPseudoJet',
   TrackVertexAssociation = "JetStdTrackVtxAssoc",
   SkipNegativeEnergy = True,
   GhostScale = 0.0
   )
jtm += TrackPseudoJetGetter(
   "TTTTrackGetter",
   #InputContainer = 'TTTParticles',
   InputContainer = 'JetSelectedTTTTracks',
   Label = "Track",
   OutputContainer = 'TTTParticlesPseudoJet',
   TrackVertexAssociation = "JetTTTTrackVtxAssoc",
   SkipNegativeEnergy = True,
   GhostScale = 0.0
   )

#from MCTruthClassifier.MCTruthClassifierConf import MCTruthClassifier
#truthClassifier = MCTruthClassifier(name = "JetMCTruthClassifier")
#from ParticleJetTools.ParticleJetToolsConf import CopyTruthJetParticles
#jtm += CopyTruthJetParticles("TruthParticleCopy", OutputName="MyJetInputTruthParticles",
#                             MCTruthClassifier=truthClassifier,
#                             IncludePromptLeptons=False,
#                             IncludeMuons=False,IncludeNeutrinos=False)
#jtm += PseudoJetGetter(
#     "TruthGetter",
#      Label = "Truth",
#      InputContainer = jtm.truthpartcopy.OutputName,
#      OutputContainer = "PseudoJetTruth",
#      GhostScale = 0.0,
#      SkipNegativeEnergy = True,
#      )

#jtm.gettersMap["CaloGetter"]=[jtm.CaloGetter]
#jtm.gettersMap["TruthGetter"] = [jtm.TruthGetter]
jtm.gettersMap["TrackGetter"]=[jtm.TrackGetter]
jtm.gettersMap["TTTTrackGetter"]=[jtm.TTTTrackGetter]
jtm.gettersMap["TTTCaloGetter"]=[jtm.CaloGetter, jtm.GTTTTrackGetter]
jtm.gettersMap["StdCaloGetter"]=[jtm.CaloGetter, jtm.GStdTrackGetter]

jtm.modifiersMap["truth"] = [jtm.jetsorter]
jtm.modifiersMap["tttcalo"] = [jtm.jvfTTT, jtm.jvtTTT]
jtm.modifiersMap["stdcalo"] = [jtm.jvfStd, jtm.jvtStd]
madeJet = []
def makeJetAlg(jetName, mods, inGetter, R = 0.4, ivtx = None):
  finderArgs = dict( modifiersin = mods, consumers = [])
  finderArgs['ptmin'] = 10e3
  finderArgs['ptminFilter'] = 10e3
  finderArgs['ghostArea'] = 0.0
  finderArgs['calibOpt'] = ""
  finderArgs['ivtxin'] = ivtx
  # create the finder for the temporary collection
  finderTool = jtm.addJetFinder(jetName, "AntiKt", R, inGetter,
                                        **finderArgs   # pass the prepared arguments
                                        )
  from JetRec.JetRecConf import JetAlgorithm
  if "TTTTrack" in jetName:
    if not "TTTTrack" in madeJet:
      alg = JetAlgorithm("jetalg%s" % jetName, Tools = [jtm.ttttracksel, jtm.ttttvassoc] + [finderTool])
      madeJet.append("TTTTrack")
    else:
      alg = JetAlgorithm("jetalg%s" % jetName, Tools = [] + [finderTool])
  elif "Track" in jetName:
    if not "Track" in madeJet:
      alg = JetAlgorithm("jetalg%s" % jetName, Tools = [jtm.stdtracksel, jtm.stdtvassoc] + [finderTool])
      madeJet.append("Track")
    else:
      alg = JetAlgorithm("jetalg%s" % jetName, Tools = [] + [finderTool])
  elif "StdEMTopo":
    alg = JetAlgorithm("jetalg%s" % jetName, Tools = [finderTool])
  elif "TTTEMTopo":
    alg = JetAlgorithm("jetalg%s" % jetName, Tools = [finderTool])
  else:
    alg = JetAlgorithm("jetalg%s" % jetName, Tools = [finderTool])
  return alg
topSequence += makeJetAlg("AntiKt4StdTrackJets", mods = [], inGetter = "TrackGetter")
topSequence += makeJetAlg("AntiKt4TTTTrackJets", mods = [], inGetter = "TTTTrackGetter")

topSequence += makeJetAlg("AntiKt2StdTrackJets", mods = [], R=0.2, inGetter = "TrackGetter")
topSequence += makeJetAlg("AntiKt2TTTTrackJets", mods = [], R=0.2, inGetter = "TTTTrackGetter")

topSequence += makeJetAlg("AntiKt4PV0StdTrackJets", mods = [], R = 0.4, ivtx = 0, inGetter = "TrackGetter")
topSequence += makeJetAlg("AntiKt4PV0TTTTrackJets", mods = [], R = 0.4, ivtx = 0, inGetter = "TTTTrackGetter")

topSequence += makeJetAlg("AntiKt2PV0StdTrackJets", mods = [], R = 0.2, ivtx = 0, inGetter = "TrackGetter")
topSequence += makeJetAlg("AntiKt2PV0TTTTrackJets", mods = [], R = 0.2, ivtx = 0, inGetter = "TTTTrackGetter")

topSequence += makeJetAlg("AntiKt4TTTEMTopoJets", mods = "tttcalo", inGetter = "TTTCaloGetter")
topSequence += makeJetAlg("AntiKt4StdEMTopoJets", mods = "stdcalo", inGetter = "StdCaloGetter")
#topSequence += makeJetAlg("AntiKt4StdEMTopoJets", mods = [], inGetter = "CaloGetter")
#topSequence += makeJetAlg("AntiKt4StdTruthJets", mods = [], inGetter = "TruthGetter")

# TODO
from MyAnalysis.MyAnalysisConf import MyAnalysis
topSequence += MyAnalysis()
#svcMgr.MessageSvc.OutputLevel=VERBOSE

svcMgr += CfgMgr.THistSvc()
svcMgr.THistSvc.Output += ["MYSTREAM DATAFILE='%out_ntuple.root' OPT='RECREATE'"]

# main jobOption
include ("RecExCommon/RecExCommon_topOptions.py")


StreamAOD.ItemList += ['xAOD::JetContainer#*']
StreamAOD.ItemList += ['xAOD::JetAuxContainer#*']
#svcMgr.StoreGateSvc.Dump=True
#print(topSequence)
print("Dumping track selectors")
print(jtm.stdtracksel)
print(jtm.ttttracksel)
print(jtm.ttttrackselloose)
print("The juice!")
print(jtm.trk_trackselloose)
print(jtm.trk_ttttrackselloose)

theApp.EvtMax = -1
