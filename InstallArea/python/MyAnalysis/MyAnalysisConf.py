#Tue Feb 19 13:03:05 2019"""Automatically generated. DO NOT EDIT please"""
from GaudiKernel.GaudiHandles import *
from GaudiKernel.Proxy.Configurable import *

class MyAnalysis( ConfigurableAlgorithm ) :
  __slots__ = { 
    'OutputLevel' : 0, # int
    'Enable' : True, # bool
    'ErrorMax' : 1, # int
    'ErrorCounter' : 0, # int
    'AuditAlgorithms' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditReinitialize' : False, # bool
    'AuditRestart' : False, # bool
    'AuditExecute' : False, # bool
    'AuditFinalize' : False, # bool
    'AuditBeginRun' : False, # bool
    'AuditEndRun' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'MonitorService' : 'MonitorSvc', # str
    'RegisterForContextService' : False, # bool
    'EvtStore' : ServiceHandle('StoreGateSvc'), # GaudiHandle
    'DetStore' : ServiceHandle('StoreGateSvc/DetectorStore'), # GaudiHandle
    'UserStore' : ServiceHandle('UserDataSvc/UserDataSvc'), # GaudiHandle
    'Debug' : False, # bool
    'McEventInfoKey' : 'EventInfo', # str
    'TruthEventKey' : 'TruthParticles', # str
    'TrackPcleContainerKey' : 'InDetTrackParticles', # str
    'TTTPcleContainerKey' : 'TTTParticles', # str
    'AntiKt4EMJetKey' : 'AntiKt4EMTopoJets', # str
    'AntiKt4StdEMJetKey' : 'AntiKt4StdEMTopoJets', # str
    'AntiKt4TTTEMJetKey' : 'AntiKt4TTTEMTopoJets', # str
    'StdAntiKt4TrackJetKey' : 'AntiKt4StdTrackJets', # str
    'StdAntiKt2TrackJetKey' : 'AntiKt2StdTrackJets', # str
    'TTTAntiKt4TrackJetKey' : 'AntiKt4TTTTrackJets', # str
    'TTTAntiKt2TrackJetKey' : 'AntiKt2TTTTrackJets', # str
    'TruthJetKey' : 'AntiKt4TruthJets', # str
    'StdAntiKt4PV0TrackJetkey' : 'AntiKt4PV0StdTrackJets', # str
    'StdAntiKt2PV0TrackJetkey' : 'AntiKt2PV0StdTrackJets', # str
    'TTTAntiKt4PV0TrackJetkey' : 'AntiKt4PV0TTTTrackJets', # str
    'TTTAntiKt2PV0TrackJetkey' : 'AntiKt2PV0TTTTrackJets', # str
  }
  _propertyDocDct = { 
    'DetStore' : """ Handle to a StoreGateSvc/DetectorStore instance: it will be used to retrieve data during the course of the job """,
    'RegisterForContextService' : """ The flag to enforce the registration for Algorithm Context Service """,
    'UserStore' : """ Handle to a UserDataSvc/UserDataSvc instance: it will be used to retrieve user data during the course of the job """,
    'EvtStore' : """ Handle to a StoreGateSvc instance: it will be used to retrieve data during the course of the job """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(MyAnalysis, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'MyAnalysis'
  def getType( self ):
      return 'MyAnalysis'
  pass # class MyAnalysis

class MyPVAnalysis( ConfigurableAlgorithm ) :
  __slots__ = { 
    'OutputLevel' : 0, # int
    'Enable' : True, # bool
    'ErrorMax' : 1, # int
    'ErrorCounter' : 0, # int
    'AuditAlgorithms' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditReinitialize' : False, # bool
    'AuditRestart' : False, # bool
    'AuditExecute' : False, # bool
    'AuditFinalize' : False, # bool
    'AuditBeginRun' : False, # bool
    'AuditEndRun' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'MonitorService' : 'MonitorSvc', # str
    'RegisterForContextService' : False, # bool
    'EvtStore' : ServiceHandle('StoreGateSvc'), # GaudiHandle
    'DetStore' : ServiceHandle('StoreGateSvc/DetectorStore'), # GaudiHandle
    'UserStore' : ServiceHandle('UserDataSvc/UserDataSvc'), # GaudiHandle
    'Debug' : False, # bool
    'McEventInfoKey' : 'EventInfo', # str
    'TTTPcleContainerKey' : 'TTTParticles', # str
    'VertexKey' : 'MyPrimaryVertices', # str
    'R' : 0.40000000, # float
    'NumberOfVertexBins' : 40, # int
    'RangeOfZVertex' : 200.00000, # float
    'MinimumPtJet' : 5000.0000, # float
    'MaximumNumberJets' : 10, # int
  }
  _propertyDocDct = { 
    'DetStore' : """ Handle to a StoreGateSvc/DetectorStore instance: it will be used to retrieve data during the course of the job """,
    'RegisterForContextService' : """ The flag to enforce the registration for Algorithm Context Service """,
    'UserStore' : """ Handle to a UserDataSvc/UserDataSvc instance: it will be used to retrieve user data during the course of the job """,
    'EvtStore' : """ Handle to a StoreGateSvc instance: it will be used to retrieve data during the course of the job """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(MyPVAnalysis, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'MyAnalysis'
  def getType( self ):
      return 'MyPVAnalysis'
  pass # class MyPVAnalysis
