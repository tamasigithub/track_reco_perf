#include "MyAnalysis/MyAnalysis.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/ServiceHandle.h"
#include "StoreGate/StoreGateSvc.h"

//#include "EventInfo/EventInfo.h"
//#include "EventInfo/EventType.h"
//#include "EventInfo/EventID.h"
#include "xAODEventInfo/EventInfo.h"

#include "xAODTruth/TruthParticleContainer.h"

#include "xAODTracking/VertexContainer.h"
#include "xAODTracking/Vertex.h"

#include "AthContainers/AuxElement.h"

#include "CxxUtils/make_unique.h"
#include <algorithm>
#include <iterator>

/////////////////////////////////////////////////////////
/*******************************************************
 * Constructor with parameters
 *******************************************************/
MyAnalysis::MyAnalysis(const std::string& name, ISvcLocator* pSvcLocator):
AthAlgorithm(name, pSvcLocator),
m_associator(0),
vec_jetPars(0),m_collectionTree(0),m_event(0), 
m_weight(0),
m_truthM(0), m_truthPt(0), m_truthEta(0), m_truthPhi(0), m_truthPdg(0), m_truthStatus(0), m_truthBarcode(0),
m_truthjetEta(0),m_truthjetPhi(0),m_truthjetE(0),m_truthjetM(0),m_truthjetPt(0),m_truthjetPx(0),m_truthjetPy(0),m_truthjetPz(0),
m_StdPVx(0), m_StdPVy(0), m_StdPVz(0), m_TTTPVz(0),
m_InDetd0(0),m_InDetz0(0),m_InDetphi0(0),m_InDettheta(0),m_InDetqOverP(0), m_InDetTBarcode(0), m_InDetTPt(0), m_InDetTEta(0), m_InDetTPhi(0),
m_TTTd0(0),m_TTTz0(0),m_TTTphi0(0),m_TTTtheta(0),m_TTTqOverP(0), m_TTTPt(0), m_TTTTBarcode(0), m_TTTTPt(0), m_TTTTEta(0), m_TTTTPhi(0),
m_calojetJVF(0), m_calojetJVT(0), m_calojetEta(0),m_calojetPhi(0),m_calojetE(0),m_calojetM(0),m_calojetPt(0),m_calojetPx(0),m_calojetPy(0),m_calojetPz(0),
m_caloTTTjetJVF(0), m_caloTTTjetJVT(0), m_caloTTTjetEta(0),m_caloTTTjetPhi(0),m_caloTTTjetE(0),m_caloTTTjetM(0),m_caloTTTjetPt(0),m_caloTTTjetPx(0),m_caloTTTjetPy(0),m_caloTTTjetPz(0),
m_caloStdjetJVF(0), m_caloStdjetJVT(0), m_caloStdjetEta(0),m_caloStdjetPhi(0),m_caloStdjetE(0),m_caloStdjetM(0),m_caloStdjetPt(0),m_caloStdjetPx(0),m_caloStdjetPy(0),m_caloStdjetPz(0),
m_std4trkjetEta(0),m_std4trkjetPhi(0),m_std4trkjetE(0),m_std4trkjetM(0),m_std4trkjetPt(0),m_std4trkjetPx(0),m_std4trkjetPy(0),m_std4trkjetPz(0),
m_std2trkjetEta(0),m_std2trkjetPhi(0),m_std2trkjetE(0),m_std2trkjetM(0),m_std2trkjetPt(0),m_std2trkjetPx(0),m_std2trkjetPy(0),m_std2trkjetPz(0),
m_ttt4trkjetEta(0),m_ttt4trkjetPhi(0),m_ttt4trkjetE(0),m_ttt4trkjetM(0),m_ttt4trkjetPt(0),m_ttt4trkjetPx(0),m_ttt4trkjetPy(0),m_ttt4trkjetPz(0),
m_ttt2trkjetEta(0),m_ttt2trkjetPhi(0),m_ttt2trkjetE(0),m_ttt2trkjetM(0),m_ttt2trkjetPt(0),m_ttt2trkjetPx(0),m_ttt2trkjetPy(0),m_ttt2trkjetPz(0)
{
  //add constructor properties
  //Configuration keys
  declareProperty("Debug",			m_debug = false);
  declareProperty("McEventInfoKey", 		m_infokey= "EventInfo");
  declareProperty("TruthEventKey", 		m_truthkey= "TruthParticles");
  declareProperty("TrackPcleContainerKey", 	m_tpContainer= "InDetTrackParticles");
  declareProperty("TTTPcleContainerKey", 	m_tttContainer= "TTTParticles");
  declareProperty("AntiKt4EMJetKey", 		m_jetSGkey= "AntiKt4EMTopoJets");
  declareProperty("AntiKt4StdEMJetKey", 	m_jetStdSGkey= "AntiKt4StdEMTopoJets");
  declareProperty("AntiKt4TTTEMJetKey", 	m_jetTTTSGkey= "AntiKt4TTTEMTopoJets");
  declareProperty("StdAntiKt4TrackJetKey", 	m_trkjet4key= "AntiKt4StdTrackJets");
  declareProperty("StdAntiKt2TrackJetKey", 	m_trkjet2key= "AntiKt2StdTrackJets");
  declareProperty("TTTAntiKt4TrackJetKey", 	m_ttttrkjet4key= "AntiKt4TTTTrackJets");
  declareProperty("TTTAntiKt2TrackJetKey", 	m_ttttrkjet2key= "AntiKt2TTTTrackJets");
  declareProperty("TruthJetKey", 		m_truthjetkey= "AntiKt4TruthJets");
  declareProperty("StdAntiKt4PV0TrackJetkey",	m_stdPV0trkjet4key= "AntiKt4PV0StdTrackJets");
  declareProperty("StdAntiKt2PV0TrackJetkey",	m_stdPV0trkjet2key= "AntiKt2PV0StdTrackJets");
  declareProperty("TTTAntiKt4PV0TrackJetkey",	m_tttPV0trkjet4key= "AntiKt4PV0TTTTrackJets");
  declareProperty("TTTAntiKt2PV0TrackJetkey",	m_tttPV0trkjet2key= "AntiKt2PV0TTTTrackJets");
}

//! Destructor
MyAnalysis::~MyAnalysis()
{
  if (m_associator) delete m_associator;
}

//! Print track particle parameters
void MyAnalysis::printTrackPcle(const xAOD::TrackParticle &tp)
{
	std::cout << "d0 = " << tp.d0() << ", z0 = " << tp.z0() << ", phi0 = " << tp.phi0() << ", theta = " << tp.theta() << ", qOverP = " << tp.qOverP() << std::endl;
	return;
}

//! Print jet parameters
void MyAnalysis::printJet(const xAOD::Jet &tj)
{
	std::cout<<"printing jet parameters : eta = " << tj.eta() << ", phi = " << tj.phi() << ", e = " << tj.e() << ", m = " << tj.m() << ", pt = " << tj.pt() << ", px = " << tj.px() << ", py = " << tj.py() << ", pz = " << tj.pz() <<std::endl;
	return; 
}

//! Get Jet parameters
std::vector<float> MyAnalysis::GetJetParameters(const xAOD::Jet &tj, int isStd)
{
	vec_jetPars.clear();
	vec_jetPars.resize(10);
	vec_jetPars[0] = tj.eta();
	vec_jetPars[1] = tj.phi();
	vec_jetPars[2] = tj.e();
	vec_jetPars[3] = tj.m();
	vec_jetPars[4] = tj.pt();
	vec_jetPars[5] = tj.px();
	vec_jetPars[6] = tj.py();
	vec_jetPars[7] = tj.pz();
	if (isStd == 0) { // pre-recorded
		vec_jetPars[8] = tj.auxdata<std::vector<float> >("JVF")[0];
		vec_jetPars[9] = tj.auxdata<float>("Jvt");
	} else if (isStd == 1) { //standard tracks, but remade
		vec_jetPars[8] = tj.auxdata<std::vector<float> >("JVFStd")[0];
		vec_jetPars[9] = tj.auxdata<float>("JvtStd");
	} else if (isStd == 2) { // triplet tracks
		vec_jetPars[8] = tj.auxdata<std::vector<float> >("JVFTTT")[0];
		vec_jetPars[9] = tj.auxdata<float>("JvtTTT");
	}
	return vec_jetPars;
}
/*******************************************************
 * Initialize method :
 *******************************************************/
StatusCode MyAnalysis::initialize()
{
  // Print where you are
  ATH_MSG_INFO ("initialize()");

  if (!m_associator)
    m_associator = new DeltaRAssociator("DeltaRAssociator", 0.01);
  
  // Get the Storegate collection
  StatusCode sc = service("StoreGateSvc", m_sgSvc);
  if (sc.isFailure()) {
    ATH_MSG_ERROR( "Could not find StoreGateSvc" );
    return sc;
  }
  //! Check if you can get a handle over the Histogram Service
  ServiceHandle<ITHistSvc> histSvc("THistSvc",name());
  CHECK( histSvc.retrieve() );
  //! Collection Tree
  m_collectionTree = new TTree("m_collectionTree", "collectionTree");
  CHECK(histSvc->regTree("/MYSTREAM/truthTree", m_collectionTree));
  m_collectionTree->Branch("event",        &m_event);        
  m_collectionTree->Branch("weight",       &m_weight);        

  m_collectionTree->Branch("truthM",       &m_truthM);   
  m_collectionTree->Branch("truthPt",      &m_truthPt);   
  m_collectionTree->Branch("truthEta",     &m_truthEta);     
  m_collectionTree->Branch("truthPhi",     &m_truthPhi);     
  m_collectionTree->Branch("truthPdg",     &m_truthPdg);     
  m_collectionTree->Branch("truthStatus",  &m_truthStatus);     
  m_collectionTree->Branch("truthBarcode", &m_truthBarcode);     

  m_collectionTree->Branch("truthjetEta",   &m_truthjetEta);   
  m_collectionTree->Branch("truthjetPhi",   &m_truthjetPhi);   
  m_collectionTree->Branch("truthjetE",     &m_truthjetE);     
  m_collectionTree->Branch("truthjetM",     &m_truthjetM);     
  m_collectionTree->Branch("truthjetPt",    &m_truthjetPt);    
  m_collectionTree->Branch("truthjetPx",    &m_truthjetPx);   
  m_collectionTree->Branch("truthjetPy",    &m_truthjetPy);    
  m_collectionTree->Branch("truthjetPz",    &m_truthjetPz);    

  m_collectionTree->Branch("StdPVx",        &m_StdPVx);      
  m_collectionTree->Branch("StdPVy",        &m_StdPVy);      
  m_collectionTree->Branch("StdPVz",        &m_StdPVz);      

  m_collectionTree->Branch("TTTPVz",        &m_TTTPVz);      

  m_collectionTree->Branch("InDetd0",      &m_InDetd0);      
  m_collectionTree->Branch("InDetz0",      &m_InDetz0);      
  m_collectionTree->Branch("InDetphi0",    &m_InDetphi0);    
  m_collectionTree->Branch("InDettheta",   &m_InDettheta);   
  m_collectionTree->Branch("InDetqOverP",  &m_InDetqOverP);  
  m_collectionTree->Branch("InDetTBarcode",&m_InDetTBarcode);
  m_collectionTree->Branch("InDetTPt",     &m_InDetTPt);
  m_collectionTree->Branch("InDetTEta",    &m_InDetTEta);
  m_collectionTree->Branch("InDetTPhi",    &m_InDetTPhi);

  m_collectionTree->Branch("TTTd0",        &m_TTTd0);        
  m_collectionTree->Branch("TTTz0",        &m_TTTz0);        
  m_collectionTree->Branch("TTTphi0",      &m_TTTphi0);      
  m_collectionTree->Branch("TTTtheta",     &m_TTTtheta);     
  m_collectionTree->Branch("TTTqOverP",    &m_TTTqOverP);    
  m_collectionTree->Branch("TTTPt",        &m_TTTPt);    
  m_collectionTree->Branch("TTTTBarcode",  &m_TTTTBarcode);
  m_collectionTree->Branch("TTTTPt",       &m_TTTTPt);
  m_collectionTree->Branch("TTTTEta",      &m_TTTTEta);
  m_collectionTree->Branch("TTTTPhi",      &m_TTTTPhi);

  m_collectionTree->Branch("calojetJVF",   &m_calojetJVF);   
  m_collectionTree->Branch("calojetJVT",   &m_calojetJVT);   
  m_collectionTree->Branch("calojetEta",   &m_calojetEta);   
  m_collectionTree->Branch("calojetPhi",   &m_calojetPhi);   
  m_collectionTree->Branch("calojetE",     &m_calojetE);     
  m_collectionTree->Branch("calojetM",     &m_calojetM);     
  m_collectionTree->Branch("calojetPt",    &m_calojetPt);    
  m_collectionTree->Branch("calojetPx",    &m_calojetPx);   
  m_collectionTree->Branch("calojetPy",    &m_calojetPy);    
  m_collectionTree->Branch("calojetPz",    &m_calojetPz);    

  m_collectionTree->Branch("caloTTTjetJVF",   &m_caloTTTjetJVF);   
  m_collectionTree->Branch("caloTTTjetJVT",   &m_caloTTTjetJVT);   
  m_collectionTree->Branch("caloTTTjetEta",   &m_caloTTTjetEta);   
  m_collectionTree->Branch("caloTTTjetPhi",   &m_caloTTTjetPhi);   
  m_collectionTree->Branch("caloTTTjetE",     &m_caloTTTjetE);     
  m_collectionTree->Branch("caloTTTjetM",     &m_caloTTTjetM);     
  m_collectionTree->Branch("caloTTTjetPt",    &m_caloTTTjetPt);    
  m_collectionTree->Branch("caloTTTjetPx",    &m_caloTTTjetPx);   
  m_collectionTree->Branch("caloTTTjetPy",    &m_caloTTTjetPy);    
  m_collectionTree->Branch("caloTTTjetPz",    &m_caloTTTjetPz);    

  m_collectionTree->Branch("caloStdjetJVF",   &m_caloStdjetJVF);   
  m_collectionTree->Branch("caloStdjetJVT",   &m_caloStdjetJVT);   
  m_collectionTree->Branch("caloStdjetEta",   &m_caloStdjetEta);   
  m_collectionTree->Branch("caloStdjetPhi",   &m_caloStdjetPhi);   
  m_collectionTree->Branch("caloStdjetE",     &m_caloStdjetE);     
  m_collectionTree->Branch("caloStdjetM",     &m_caloStdjetM);     
  m_collectionTree->Branch("caloStdjetPt",    &m_caloStdjetPt);    
  m_collectionTree->Branch("caloStdjetPx",    &m_caloStdjetPx);   
  m_collectionTree->Branch("caloStdjetPy",    &m_caloStdjetPy);    
  m_collectionTree->Branch("caloStdjetPz",    &m_caloStdjetPz);    

  m_collectionTree->Branch("std4trkjetEta",&m_std4trkjetEta);
  m_collectionTree->Branch("std4trkjetPhi",&m_std4trkjetPhi);
  m_collectionTree->Branch("std4trkjetE",  &m_std4trkjetE);
  m_collectionTree->Branch("std4trkjetM",  &m_std4trkjetM);
  m_collectionTree->Branch("std4trkjetPt", &m_std4trkjetPt); 
  m_collectionTree->Branch("std4trkjetPx", &m_std4trkjetPx); 
  m_collectionTree->Branch("std4trkjetPy", &m_std4trkjetPy); 
  m_collectionTree->Branch("std4trkjetPz", &m_std4trkjetPz); 
  m_collectionTree->Branch("std2trkjetEta",&m_std2trkjetEta);;
  m_collectionTree->Branch("std2trkjetPhi",&m_std2trkjetPhi);
  m_collectionTree->Branch("std2trkjetE",  &m_std2trkjetE);  
  m_collectionTree->Branch("std2trkjetM",  &m_std2trkjetM);  
  m_collectionTree->Branch("std2trkjetPt", &m_std2trkjetPt); 
  m_collectionTree->Branch("std2trkjetPx", &m_std2trkjetPx); ;
  m_collectionTree->Branch("std2trkjetPy", &m_std2trkjetPy); ;
  m_collectionTree->Branch("std2trkjetPz", &m_std2trkjetPz); 
  m_collectionTree->Branch("ttt4trkjetEta",&m_ttt4trkjetEta);
  m_collectionTree->Branch("ttt4trkjetPhi",&m_ttt4trkjetPhi);
  m_collectionTree->Branch("ttt4trkjetE",  &m_ttt4trkjetE);  
  m_collectionTree->Branch("ttt4trkjetM",  &m_ttt4trkjetM);  
  m_collectionTree->Branch("ttt4trkjetPt", &m_ttt4trkjetPt); 
  m_collectionTree->Branch("ttt4trkjetPx", &m_ttt4trkjetPx);
  m_collectionTree->Branch("ttt4trkjetPy", &m_ttt4trkjetPy);
  m_collectionTree->Branch("ttt4trkjetPz", &m_ttt4trkjetPz);
  m_collectionTree->Branch("ttt2trkjetEta",&m_ttt2trkjetEta);
  m_collectionTree->Branch("ttt2trkjetPhi",&m_ttt2trkjetPhi);
  m_collectionTree->Branch("ttt2trkjetE",  &m_ttt2trkjetE);
  m_collectionTree->Branch("ttt2trkjetM",  &m_ttt2trkjetM);  
  m_collectionTree->Branch("ttt2trkjetPt", &m_ttt2trkjetPt); 
  m_collectionTree->Branch("ttt2trkjetPx", &m_ttt2trkjetPx); 
  m_collectionTree->Branch("ttt2trkjetPy", &m_ttt2trkjetPy); 
  m_collectionTree->Branch("ttt2trkjetPz", &m_ttt2trkjetPz); 
  
  m_collectionTree->Branch("std4PV0trkjetEta",	&m_std4PV0trkjetEta);
  m_collectionTree->Branch("std4PV0trkjetPhi",	&m_std4PV0trkjetPhi);
  m_collectionTree->Branch("std4PV0trkjetE",  	&m_std4PV0trkjetE);
  m_collectionTree->Branch("std4PV0trkjetM",  	&m_std4PV0trkjetM);
  m_collectionTree->Branch("std4PV0trkjetPt", 	&m_std4PV0trkjetPt);
  m_collectionTree->Branch("std4PV0trkjetPx", 	&m_std4PV0trkjetPx);
  m_collectionTree->Branch("std4PV0trkjetPy", 	&m_std4PV0trkjetPy);
  m_collectionTree->Branch("std4PV0trkjetPz", 	&m_std4PV0trkjetPz);
                                                            
  m_collectionTree->Branch("std2PV0trkjetEta",	&m_std2PV0trkjetEta);
  m_collectionTree->Branch("std2PV0trkjetPhi",	&m_std2PV0trkjetPhi);
  m_collectionTree->Branch("std2PV0trkjetE",  	&m_std2PV0trkjetE);
  m_collectionTree->Branch("std2PV0trkjetM",  	&m_std2PV0trkjetM);
  m_collectionTree->Branch("std2PV0trkjetPt", 	&m_std2PV0trkjetPt);
  m_collectionTree->Branch("std2PV0trkjetPx", 	&m_std2PV0trkjetPx);
  m_collectionTree->Branch("std2PV0trkjetPy", 	&m_std2PV0trkjetPy);
  m_collectionTree->Branch("std2PV0trkjetPz", 	&m_std2PV0trkjetPz);
                                                            
  m_collectionTree->Branch("ttt4PV0trkjetEta",	&m_ttt4PV0trkjetEta);
  m_collectionTree->Branch("ttt4PV0trkjetPhi",	&m_ttt4PV0trkjetPhi);
  m_collectionTree->Branch("ttt4PV0trkjetE",  	&m_ttt4PV0trkjetE);
  m_collectionTree->Branch("ttt4PV0trkjetM",  	&m_ttt4PV0trkjetM);
  m_collectionTree->Branch("ttt4PV0trkjetPt", 	&m_ttt4PV0trkjetPt);
  m_collectionTree->Branch("ttt4PV0trkjetPx", 	&m_ttt4PV0trkjetPx);
  m_collectionTree->Branch("ttt4PV0trkjetPy", 	&m_ttt4PV0trkjetPy);
  m_collectionTree->Branch("ttt4PV0trkjetPz", 	&m_ttt4PV0trkjetPz);
                                                            
  m_collectionTree->Branch("ttt2PV0trkjetEta",	&m_ttt2PV0trkjetEta);
  m_collectionTree->Branch("ttt2PV0trkjetPhi",	&m_ttt2PV0trkjetPhi);
  m_collectionTree->Branch("ttt2PV0trkjetE",  	&m_ttt2PV0trkjetE);
  m_collectionTree->Branch("ttt2PV0trkjetM",  	&m_ttt2PV0trkjetM);
  m_collectionTree->Branch("ttt2PV0trkjetPt", 	&m_ttt2PV0trkjetPt);
  m_collectionTree->Branch("ttt2PV0trkjetPx", 	&m_ttt2PV0trkjetPx);
  m_collectionTree->Branch("ttt2PV0trkjetPy", 	&m_ttt2PV0trkjetPy);
  m_collectionTree->Branch("ttt2PV0trkjetPz", 	&m_ttt2PV0trkjetPz);
  return StatusCode::SUCCESS;
}

/******************************************************
 * Execute method:
 ******************************************************/
StatusCode MyAnalysis::execute()
{
  // Print where you are
  ATH_MSG_INFO ("executing MyAnalysis");

  //clear data
  m_event=0; 
  m_weight = 1;

  m_StdPVx = 0;
  m_StdPVy = 0;
  m_StdPVz = 0;
  m_TTTPVz = 0;

  m_truthM.clear();
  m_truthPt.clear();
  m_truthEta.clear();
  m_truthPhi.clear();
  m_truthPdg.clear();
  m_truthStatus.clear();
  m_truthBarcode.clear();

  m_truthjetEta.clear();
  m_truthjetPhi.clear();
  m_truthjetE.clear();
  m_truthjetM.clear();
  m_truthjetPt.clear();
  m_truthjetPx.clear();
  m_truthjetPy.clear();
  m_truthjetPz.clear();

  m_InDetd0.clear();
  m_InDetz0.clear();
  m_InDetphi0.clear();
  m_InDettheta.clear();
  m_InDetqOverP.clear();
  m_InDetTBarcode.clear();
  m_InDetTPt.clear();
  m_InDetTEta.clear();
  m_InDetTPhi.clear();

  m_TTTd0.clear();
  m_TTTz0.clear();
  m_TTTphi0.clear();
  m_TTTtheta.clear();
  m_TTTqOverP.clear();
  m_TTTPt.clear();
  m_TTTTBarcode.clear();
  m_TTTTPt.clear();
  m_TTTTEta.clear();
  m_TTTTPhi.clear();
                 
  m_calojetEta.clear();
  m_calojetPhi.clear();
  m_calojetE.clear();
  m_calojetM.clear();
  m_calojetPt.clear();
  m_calojetPx.clear();
  m_calojetPy.clear();
  m_calojetPz.clear();
  m_calojetJVF.clear();
  m_calojetJVT.clear();

  m_caloStdjetEta.clear();
  m_caloStdjetPhi.clear();
  m_caloStdjetE.clear();
  m_caloStdjetM.clear();
  m_caloStdjetPt.clear();
  m_caloStdjetPx.clear();
  m_caloStdjetPy.clear();
  m_caloStdjetPz.clear();
  m_caloStdjetJVF.clear();
  m_caloStdjetJVT.clear();

  m_caloTTTjetEta.clear();
  m_caloTTTjetPhi.clear();
  m_caloTTTjetE.clear();
  m_caloTTTjetM.clear();
  m_caloTTTjetPt.clear();
  m_caloTTTjetPx.clear();
  m_caloTTTjetPy.clear();
  m_caloTTTjetPz.clear();
  m_caloTTTjetJVF.clear();
  m_caloTTTjetJVT.clear();
                 
  m_std4trkjetEta.clear();
  m_std4trkjetPhi.clear();
  m_std4trkjetE.clear();
  m_std4trkjetM.clear();
  m_std4trkjetPt.clear();
  m_std4trkjetPx.clear();
  m_std4trkjetPy.clear();
  m_std4trkjetPz.clear();
                 
  m_std2trkjetEta.clear();
  m_std2trkjetPhi.clear();
  m_std2trkjetE.clear();
  m_std2trkjetM.clear();
  m_std2trkjetPt.clear();
  m_std2trkjetPx.clear();
  m_std2trkjetPy.clear();
  m_std2trkjetPz.clear();
                 
  m_ttt4trkjetEta.clear();
  m_ttt4trkjetPhi.clear();
  m_ttt4trkjetE.clear();
  m_ttt4trkjetM.clear();
  m_ttt4trkjetPt.clear();
  m_ttt4trkjetPx.clear();
  m_ttt4trkjetPy.clear();
  m_ttt4trkjetPz.clear();
                 
  m_ttt2trkjetEta.clear();
  m_ttt2trkjetPhi.clear();
  m_ttt2trkjetE.clear();
  m_ttt2trkjetM.clear();
  m_ttt2trkjetPt.clear();
  m_ttt2trkjetPx.clear();
  m_ttt2trkjetPy.clear();
  m_ttt2trkjetPz.clear();

  m_std4PV0trkjetEta.clear();
  m_std4PV0trkjetPhi.clear();
  m_std4PV0trkjetE.clear();
  m_std4PV0trkjetM.clear();
  m_std4PV0trkjetPt.clear();
  m_std4PV0trkjetPx.clear();
  m_std4PV0trkjetPy.clear();
  m_std4PV0trkjetPz.clear();

  m_std2PV0trkjetEta.clear();
  m_std2PV0trkjetPhi.clear();
  m_std2PV0trkjetE.clear();
  m_std2PV0trkjetM.clear();
  m_std2PV0trkjetPt.clear();
  m_std2PV0trkjetPx.clear();
  m_std2PV0trkjetPy.clear();
  m_std2PV0trkjetPz.clear();

  m_ttt4PV0trkjetEta.clear();
  m_ttt4PV0trkjetPhi.clear();
  m_ttt4PV0trkjetE.clear();
  m_ttt4PV0trkjetM.clear();
  m_ttt4PV0trkjetPt.clear();
  m_ttt4PV0trkjetPx.clear();
  m_ttt4PV0trkjetPy.clear();
  m_ttt4PV0trkjetPz.clear();

  m_ttt2PV0trkjetEta.clear();
  m_ttt2PV0trkjetPhi.clear();
  m_ttt2PV0trkjetE.clear();
  m_ttt2PV0trkjetM.clear();
  m_ttt2PV0trkjetPt.clear();
  m_ttt2PV0trkjetPx.clear();
  m_ttt2PV0trkjetPy.clear();
  m_ttt2PV0trkjetPz.clear();
  //! Get EventInfo object
  //! Load event info from EventInfo
  const xAOD::EventInfo *eventInfo = nullptr;
  if ( m_sgSvc->retrieve(eventInfo, m_infokey).isFailure() ) {
    ATH_MSG_ERROR( "Could not retrieve EventInfo" );
    return StatusCode::FAILURE;
  } else{
    m_event = eventInfo->eventNumber();
    m_weight = 1.0;
    const std::vector<float> &weights = eventInfo->mcEventWeights();
    if (weights.size() != 0) m_weight = weights[0];
 
    ATH_MSG_INFO( " event: " << m_event );
  }
  
  //! Load THE Truth
  const xAOD::TruthParticleContainer *theTruth = nullptr;
  if ( m_sgSvc->retrieve(theTruth, m_truthkey).isFailure() ) 
  {
    ATH_MSG_ERROR( "Could not retrieve TruthParticleContainer!! I will panic!" );
    return StatusCode::FAILURE;
  }
  std::vector<const xAOD::TruthParticle *> bquark;
  std::vector<const xAOD::TruthParticle *> SMHiggs;
  std::vector<const xAOD::TruthParticle *> BSMHiggs;
  std::vector<const xAOD::TruthParticle *> charged;
  charged.reserve(theTruth->size());
  for (xAOD::TruthParticleContainer::const_iterator itr = theTruth->begin(); itr != theTruth->end(); ++itr) 
  {
 	const xAOD::TruthParticle *part = *itr;
	if (abs(part->pdgId()) == 35)
	{
  		std::vector<const xAOD::TruthParticle *> tmpSMHiggs = findMyBaby(part, 35, 25);
		for (size_t iSMHiggs = 0; iSMHiggs < tmpSMHiggs.size(); ++iSMHiggs)
		{
			std::vector<const xAOD::TruthParticle *> tmpBquark = findMyBaby(tmpSMHiggs[iSMHiggs], 25, 5);
			for (size_t iB = 0; iB < tmpBquark.size(); ++iB) bquark.push_back(tmpBquark[iB]);
		}
		for (size_t iH = 0; iH < tmpSMHiggs.size(); ++iH) SMHiggs.push_back(tmpSMHiggs[iH]);
		BSMHiggs.push_back(part);
		break;
	}
  }
  for (size_t i = 0; i < bquark.size(); ++i)
  {
  	m_truthM.push_back(bquark[i]->p4().M());
  	m_truthPt.push_back(bquark[i]->p4().Perp());
  	m_truthEta.push_back(bquark[i]->p4().Eta());
  	m_truthPhi.push_back(bquark[i]->p4().Phi());
  	m_truthPdg.push_back(bquark[i]->pdgId());
  	m_truthStatus.push_back(bquark[i]->status());
  	m_truthBarcode.push_back(bquark[i]->barcode());
  }
  for (size_t i = 0; i < SMHiggs.size(); ++i)
  {
  	m_truthM.push_back(SMHiggs[i]->p4().M());
  	m_truthPt.push_back(SMHiggs[i]->p4().Perp());
  	m_truthEta.push_back(SMHiggs[i]->p4().Eta());
  	m_truthPhi.push_back(SMHiggs[i]->p4().Phi());
  	m_truthPdg.push_back(SMHiggs[i]->pdgId());
  	m_truthStatus.push_back(SMHiggs[i]->status());
  	m_truthBarcode.push_back(SMHiggs[i]->barcode());
  }
  for (size_t i = 0; i < BSMHiggs.size(); ++i)
  {
  	m_truthM.push_back(BSMHiggs[i]->p4().M());
  	m_truthPt.push_back(BSMHiggs[i]->p4().Perp());
  	m_truthEta.push_back(BSMHiggs[i]->p4().Eta());
  	m_truthPhi.push_back(BSMHiggs[i]->p4().Phi());
  	m_truthPdg.push_back(BSMHiggs[i]->pdgId());
  	m_truthStatus.push_back(BSMHiggs[i]->status());
  	m_truthBarcode.push_back(BSMHiggs[i]->barcode());
  }
  for (xAOD::TruthParticleContainer::const_iterator itr = theTruth->begin(); itr != theTruth->end(); ++itr) 
  {
 	const xAOD::TruthParticle *part = *itr;
	if (part->status() == 1 && part->charge() != 0)
	{
  		m_truthM.push_back(part->p4().M());
  		m_truthPt.push_back(part->p4().Perp());
  		m_truthEta.push_back(part->p4().Eta());
  		m_truthPhi.push_back(part->p4().Phi());
  		m_truthPdg.push_back(part->pdgId());
  		m_truthStatus.push_back(part->status());
  		m_truthBarcode.push_back(part->barcode());
		charged.push_back(part);
	}
  }

  //! Load the standard track particle container
  const xAOD::TrackParticleContainer* tracks = nullptr;
  if(evtStore()->contains<xAOD::TrackParticleContainer>(m_tpContainer))
  {
	ATH_CHECK (evtStore()->retrieve(tracks, m_tpContainer));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::TrackParticleContainer not available (" << m_tpContainer << "). Skipping although requested.");
      tracks = nullptr;
  }
  //! loop over the retrieved track particle conatiner and fill the TTree branches
  xAOD::TrackParticleContainer::const_iterator nextTrk(tracks->begin());
  xAOD::TrackParticleContainer::const_iterator lastTrk(tracks->end());
  const std::vector<xAOD::IParticle*> tracksCont = tracks->stdcont();
  m_associator->match(tracksCont, charged);
  for (; nextTrk!=lastTrk; nextTrk++) 
  {
	const xAOD::TrackParticle* particle = *nextTrk;
	const xAOD::IParticle* iparticle = particle;

	m_InDetd0.push_back(particle->d0());
	m_InDetz0.push_back(particle->z0());
	m_InDetphi0.push_back(particle->phi0());
	m_InDettheta.push_back(particle->theta());
	m_InDetqOverP.push_back(particle->qOverP());
	const xAOD::TruthParticle *truth = m_associator->matched(const_cast<xAOD::IParticle *>(iparticle));
	int truthBarcode = -999;
	float truthEta = -999;
	float truthPhi = -999;
	float truthPt = -999;
	if (truth)
	{
		truthBarcode = truth->barcode();
		truthPt = truth->p4().Perp();
		truthEta = truth->p4().Eta();
		truthPhi = truth->p4().Phi();
	}
	m_InDetTBarcode.push_back(truthBarcode);
	m_InDetTPt.push_back(truthPt);
	m_InDetTEta.push_back(truthEta);
	m_InDetTPhi.push_back(truthPhi);
	//! print track particles
	//ATH_MSG_INFO("printing InDet track particles... ");
	if (m_debug) printTrackPcle( *particle );

  }

  const xAOD::TrackParticleContainer* TTTtracks = nullptr;
  if(evtStore()->contains<xAOD::TrackParticleContainer>(m_tttContainer))
  {
	ATH_CHECK (evtStore()->retrieve(TTTtracks, m_tttContainer));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::TrackParticleContainer not available (" << m_tttContainer << "). Skipping although requested.");
      TTTtracks = nullptr;
  }
  //! loop over the retrieved track particle conatiner and fill the TTree branches
  xAOD::TrackParticleContainer::const_iterator nextTrk1(TTTtracks->begin());
  xAOD::TrackParticleContainer::const_iterator lastTrk1(TTTtracks->end());
  const std::vector<xAOD::IParticle*> TTTCont = TTTtracks->stdcont();
  m_associator->match(TTTCont, charged);
  for (; nextTrk1!=lastTrk1; nextTrk1++) 
  {
	const xAOD::TrackParticle* particle1 = *nextTrk1;
	const xAOD::IParticle* iparticle1 = particle1;
	m_TTTd0.push_back(particle1->d0());
	m_TTTz0.push_back(particle1->z0());
	m_TTTphi0.push_back(particle1->phi0());
	m_TTTtheta.push_back(particle1->theta());
	m_TTTqOverP.push_back(particle1->qOverP());
	m_TTTPt.push_back(particle1->pt());

	const xAOD::TruthParticle *truth = m_associator->matched(const_cast<xAOD::IParticle *>(iparticle1));
	int truthBarcode = -999;
	float truthEta = -999;
	float truthPhi = -999;
	float truthPt = -999;
	if (truth)
	{
		truthBarcode = truth->barcode();
		truthPt = truth->p4().Perp();
		truthEta = truth->p4().Eta();
		truthPhi = truth->p4().Phi();
	}
	m_TTTTBarcode.push_back(truthBarcode);
	m_TTTTPt.push_back(truthPt);
	m_TTTTEta.push_back(truthEta);
	m_TTTTPhi.push_back(truthPhi);
	//! print track particles
	//ATH_MSG_INFO("printing TTT track particles... ");
	if (m_debug) printTrackPcle( *particle1 );

  }

  //! Load AntiKt4 EMTopo calo jets
  const xAOD::JetContainer* jets = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_jetSGkey))
  {
	ATH_CHECK (evtStore()->retrieve(jets, m_jetSGkey));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_jetSGkey << "). Skipping although requested.");
      jets = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet : *jets) 
  {
	GetJetParameters(*jet, 0);
	m_calojetJVF.push_back(vec_jetPars[8]);
	m_calojetJVT.push_back(vec_jetPars[9]);
	m_calojetEta.push_back(vec_jetPars[0]);
	m_calojetPhi.push_back(vec_jetPars[1]);
	m_calojetE.push_back(vec_jetPars[2]);
	m_calojetM.push_back(vec_jetPars[3]);
	m_calojetPt.push_back(vec_jetPars[4]);
	m_calojetPx.push_back(vec_jetPars[5]);
	m_calojetPy.push_back(vec_jetPars[6]);
	m_calojetPz.push_back(vec_jetPars[7]);
	
	if(m_debug) printJet(*jet);
  }
  jets = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_jetStdSGkey))
  {
	ATH_CHECK (evtStore()->retrieve(jets, m_jetStdSGkey));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_jetStdSGkey << "). Skipping although requested.");
      jets = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet : *jets) 
  {
	GetJetParameters(*jet, 1);
	m_caloStdjetJVF.push_back(vec_jetPars[8]);
	m_caloStdjetJVT.push_back(vec_jetPars[9]);
	m_caloStdjetEta.push_back(vec_jetPars[0]);
	m_caloStdjetPhi.push_back(vec_jetPars[1]);
	m_caloStdjetE.push_back(vec_jetPars[2]);
	m_caloStdjetM.push_back(vec_jetPars[3]);
	m_caloStdjetPt.push_back(vec_jetPars[4]);
	m_caloStdjetPx.push_back(vec_jetPars[5]);
	m_caloStdjetPy.push_back(vec_jetPars[6]);
	m_caloStdjetPz.push_back(vec_jetPars[7]);
	
	if(m_debug) printJet(*jet);
  }
  jets = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_jetTTTSGkey))
  {
	ATH_CHECK (evtStore()->retrieve(jets, m_jetTTTSGkey));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_jetTTTSGkey << "). Skipping although requested.");
      jets = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet : *jets) 
  {
	GetJetParameters(*jet, 2);
	m_caloTTTjetJVF.push_back(vec_jetPars[8]);
	m_caloTTTjetJVT.push_back(vec_jetPars[9]);
	m_caloTTTjetEta.push_back(vec_jetPars[0]);
	m_caloTTTjetPhi.push_back(vec_jetPars[1]);
	m_caloTTTjetE.push_back(vec_jetPars[2]);
	m_caloTTTjetM.push_back(vec_jetPars[3]);
	m_caloTTTjetPt.push_back(vec_jetPars[4]);
	m_caloTTTjetPx.push_back(vec_jetPars[5]);
	m_caloTTTjetPy.push_back(vec_jetPars[6]);
	m_caloTTTjetPz.push_back(vec_jetPars[7]);
	
	if(m_debug) printJet(*jet);
  }

  // truth jets
  jets = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_truthjetkey))
  {
	ATH_CHECK (evtStore()->retrieve(jets, m_truthjetkey));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_truthjetkey << "). Skipping although requested.");
      jets = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet : *jets) 
  {
	GetJetParameters(*jet, -1);
	m_truthjetEta.push_back(vec_jetPars[0]);
	m_truthjetPhi.push_back(vec_jetPars[1]);
	m_truthjetE.push_back(vec_jetPars[2]);
	m_truthjetM.push_back(vec_jetPars[3]);
	m_truthjetPt.push_back(vec_jetPars[4]);
	m_truthjetPx.push_back(vec_jetPars[5]);
	m_truthjetPy.push_back(vec_jetPars[6]);
	m_truthjetPz.push_back(vec_jetPars[7]);
	
	if(m_debug) printJet(*jet);
  }

  //! Load AntiKt4 standard track jets
  const xAOD::JetContainer* jets1 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_trkjet4key))
  {
	ATH_CHECK (evtStore()->retrieve(jets1, m_trkjet4key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_trkjet4key << "). Skipping although requested.");
      jets1 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet1 : *jets1) 
  {
	GetJetParameters(*jet1, -1);
	m_std4trkjetEta.push_back(vec_jetPars[0]);
	m_std4trkjetPhi.push_back(vec_jetPars[1]);
	m_std4trkjetE.push_back(vec_jetPars[2]);  
	m_std4trkjetM.push_back(vec_jetPars[3]);  
	m_std4trkjetPt.push_back(vec_jetPars[4]); 
	m_std4trkjetPx.push_back(vec_jetPars[5]); 
	m_std4trkjetPy.push_back(vec_jetPars[6]); 
	m_std4trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet1);
  }
  //! Load AntiKt2 standard track jets
  const xAOD::JetContainer* jets2 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_trkjet2key))
  {
	ATH_CHECK (evtStore()->retrieve(jets2, m_trkjet2key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_trkjet2key << "). Skipping although requested.");
      jets2 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet2 : *jets2) 
  {
	GetJetParameters(*jet2, -1);
	m_std2trkjetEta.push_back(vec_jetPars[0]);
	m_std2trkjetPhi.push_back(vec_jetPars[1]);
	m_std2trkjetE.push_back(vec_jetPars[2]);  
	m_std2trkjetM.push_back(vec_jetPars[3]);  
	m_std2trkjetPt.push_back(vec_jetPars[4]); 
	m_std2trkjetPx.push_back(vec_jetPars[5]); 
	m_std2trkjetPy.push_back(vec_jetPars[6]); 
	m_std2trkjetPz.push_back(vec_jetPars[7]); 

	if(m_debug) printJet(*jet2);
  }

  //! Load AntiKt4 TTT track jets
  const xAOD::JetContainer* jets3 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_ttttrkjet4key))
  {
	ATH_CHECK (evtStore()->retrieve(jets3, m_ttttrkjet4key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_ttttrkjet4key << "). Skipping although requested.");
      jets3 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet3 : *jets3) 
  {
	GetJetParameters(*jet3, -1);
	m_ttt4trkjetEta.push_back(vec_jetPars[0]);
	m_ttt4trkjetPhi.push_back(vec_jetPars[1]);
	m_ttt4trkjetE.push_back(vec_jetPars[2]);  
	m_ttt4trkjetM.push_back(vec_jetPars[3]);  
	m_ttt4trkjetPt.push_back(vec_jetPars[4]); 
	m_ttt4trkjetPx.push_back(vec_jetPars[5]); 
	m_ttt4trkjetPy.push_back(vec_jetPars[6]); 
	m_ttt4trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet3);
  }
  //! Load AntiKt2 standard track jets
  const xAOD::JetContainer* jets4 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_ttttrkjet2key))
  {
	ATH_CHECK (evtStore()->retrieve(jets4, m_ttttrkjet2key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_ttttrkjet2key << "). Skipping although requested.");
      jets4 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet4 : *jets4) 
  {
	GetJetParameters(*jet4, -1);
	m_ttt2trkjetEta.push_back(vec_jetPars[0]);
	m_ttt2trkjetPhi.push_back(vec_jetPars[1]);
	m_ttt2trkjetE.push_back(vec_jetPars[2]);  
	m_ttt2trkjetM.push_back(vec_jetPars[3]);  
	m_ttt2trkjetPt.push_back(vec_jetPars[4]); 
	m_ttt2trkjetPx.push_back(vec_jetPars[5]); 
	m_ttt2trkjetPy.push_back(vec_jetPars[6]); 
	m_ttt2trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet4);
  } 
  //! Load AntiKt4 standard track jets associated to primary vertex
  const xAOD::JetContainer* jets5 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_stdPV0trkjet4key))
  {
	ATH_CHECK (evtStore()->retrieve(jets5, m_stdPV0trkjet4key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_stdPV0trkjet4key << "). Skipping although requested.");
      jets5 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet5 : *jets5) 
  {
	GetJetParameters(*jet5, -1);
	m_std4PV0trkjetEta.push_back(vec_jetPars[0]);
	m_std4PV0trkjetPhi.push_back(vec_jetPars[1]);
	m_std4PV0trkjetE.push_back(vec_jetPars[2]);  
	m_std4PV0trkjetM.push_back(vec_jetPars[3]);  
	m_std4PV0trkjetPt.push_back(vec_jetPars[4]); 
	m_std4PV0trkjetPx.push_back(vec_jetPars[5]); 
	m_std4PV0trkjetPy.push_back(vec_jetPars[6]); 
	m_std4PV0trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet5);
  }

  //! Load AntiKt2 standard track jets associated to primary vertex
  const xAOD::JetContainer* jets6 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_stdPV0trkjet2key))
  {
	ATH_CHECK (evtStore()->retrieve(jets6, m_stdPV0trkjet2key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_stdPV0trkjet2key << "). Skipping although requested.");
      jets6 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet6 : *jets6) 
  {
	GetJetParameters(*jet6, -1);
	m_std2PV0trkjetEta.push_back(vec_jetPars[0]);
	m_std2PV0trkjetPhi.push_back(vec_jetPars[1]);
	m_std2PV0trkjetE.push_back(vec_jetPars[2]);  
	m_std2PV0trkjetM.push_back(vec_jetPars[3]);  
	m_std2PV0trkjetPt.push_back(vec_jetPars[4]); 
	m_std2PV0trkjetPx.push_back(vec_jetPars[5]); 
	m_std2PV0trkjetPy.push_back(vec_jetPars[6]); 
	m_std2PV0trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet6);
  }
 
  //! Load AntiKt4 TTT track jets associated to primary vertex
  const xAOD::JetContainer* jets7 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_tttPV0trkjet4key))
  {
	ATH_CHECK (evtStore()->retrieve(jets7, m_tttPV0trkjet4key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_tttPV0trkjet4key << "). Skipping although requested.");
      jets7 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet7 : *jets7) 
  {
	GetJetParameters(*jet7, -1);
	m_ttt4PV0trkjetEta.push_back(vec_jetPars[0]);
	m_ttt4PV0trkjetPhi.push_back(vec_jetPars[1]);
	m_ttt4PV0trkjetE.push_back(vec_jetPars[2]);  
	m_ttt4PV0trkjetM.push_back(vec_jetPars[3]);  
	m_ttt4PV0trkjetPt.push_back(vec_jetPars[4]); 
	m_ttt4PV0trkjetPx.push_back(vec_jetPars[5]); 
	m_ttt4PV0trkjetPy.push_back(vec_jetPars[6]); 
	m_ttt4PV0trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet7);
  }

  //! Load AntiKt2 TTT track jets associated to primary vertex
  const xAOD::JetContainer* jets8 = nullptr;
  if(evtStore()->contains<xAOD::JetContainer>(m_tttPV0trkjet2key))
  {
	ATH_CHECK (evtStore()->retrieve(jets8, m_tttPV0trkjet2key));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::JetContainer not available (" << m_tttPV0trkjet2key << "). Skipping although requested.");
      jets8 = nullptr;
  }
  //! loop over the retrieved jet conatiner and fill the TTree branches
  for (const xAOD::Jet* jet8 : *jets8) 
  {
	GetJetParameters(*jet8, -1);
	m_ttt2PV0trkjetEta.push_back(vec_jetPars[0]);
	m_ttt2PV0trkjetPhi.push_back(vec_jetPars[1]);
	m_ttt2PV0trkjetE.push_back(vec_jetPars[2]);  
	m_ttt2PV0trkjetM.push_back(vec_jetPars[3]);  
	m_ttt2PV0trkjetPt.push_back(vec_jetPars[4]); 
	m_ttt2PV0trkjetPx.push_back(vec_jetPars[5]); 
	m_ttt2PV0trkjetPy.push_back(vec_jetPars[6]); 
	m_ttt2PV0trkjetPz.push_back(vec_jetPars[7]); 
	
	if(m_debug) printJet(*jet8);
  }

//! Retrieve Primary Vertices (the standard ones) 
  const xAOD::VertexContainer* vx = nullptr;
  if(evtStore()->contains<xAOD::VertexContainer>("PrimaryVertices"))
  {
	ATH_CHECK (evtStore()->retrieve(vx, "PrimaryVertices"));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::VertexContainer not available (" << "PrimaryVertices" << "). Skipping although requested.");
      vx = nullptr;
  }
  const xAOD::Vertex *pv = nullptr;
  for (const xAOD::Vertex* i : *vx) 
  {
  	if (i->vertexType() == xAOD::VxType::PriVtx)
	{
		pv = i;
		break;
	}
  }
  if (pv)
  {
  	m_StdPVx = pv->x();
  	m_StdPVy = pv->y();
  	m_StdPVz = pv->z();
  }
  //! from MyPVAnalysis - Primary bins
  vx = nullptr;
  if(evtStore()->contains<xAOD::VertexContainer>("MyPrimaryVertices"))
  {
	ATH_CHECK (evtStore()->retrieve(vx, "MyPrimaryVertices"));
  }
  else 
  {
      ATH_MSG_WARNING("xAOD::VertexContainer not available (" << "MyPrimaryVertices" << "). Skipping although requested.");
      vx = nullptr;
  }
  pv = nullptr;
  if (vx)
  {
  	if (vx->size() >= 1)
	{
		pv = vx->at(0);
	}
  }
  if (pv)
  {
  	m_TTTPVz = pv->z();
  }


	//! fill n-tuple
	if (m_collectionTree->Fill() == -1) 
	{
	   ATH_MSG_WARNING("Error writing truth Tree");
	}

  return StatusCode::SUCCESS;
}

/******************************************************
 * Finalize method:
 ******************************************************/
StatusCode MyAnalysis::finalize()
{
  // Print where you are
  ATH_MSG_INFO ("finalize()");
  return StatusCode::SUCCESS;
}

/*****************************************************
 * Find the children particles of a parent-particle,
 * which can decay in a chain of the same particle
 * due to radiation.
 ****************************************************/
std::vector<const xAOD::TruthParticle *> MyAnalysis::findMyBaby(const xAOD::TruthParticle *part, const int myMommy, const int myBaby) {
	std::vector<const xAOD::TruthParticle *> babies;
	for (size_t iChild = 0; iChild < part->nChildren(); ++iChild)
	{
		const xAOD::TruthParticle *aParticle = part->child(iChild);
		if (!aParticle) continue;
		if (abs(aParticle->pdgId()) == myMommy)
		{
			babies = findMyBaby(aParticle, myMommy, myBaby);
			break;
		}
		if (abs(aParticle->pdgId()) == myBaby)
		{
			babies.push_back(aParticle);
		}

	}
	return babies;
}
