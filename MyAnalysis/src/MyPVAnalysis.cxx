#include "MyAnalysis/MyPVAnalysis.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/ServiceHandle.h"
#include "StoreGate/StoreGateSvc.h"

#include "xAODEventInfo/EventInfo.h"

#include "AthContainers/AuxElement.h"

#include "CxxUtils/make_unique.h"
#include <algorithm>
#include <iterator>

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"

using namespace fastjet;

/////////////////////////////////////////////////////////
/*******************************************************
 * Constructor with parameters
 *******************************************************/
MyPVAnalysis::MyPVAnalysis(const std::string& name, ISvcLocator* pSvcLocator):
AthAlgorithm(name, pSvcLocator)
{
  //add constructor properties
  //Configuration keys
  declareProperty("Debug",			m_debug = false);
  declareProperty("McEventInfoKey", 		m_infokey= "EventInfo");
  declareProperty("TTTPcleContainerKey", 	m_tttContainer= "TTTParticles");
  declareProperty("VertexKey", 			m_vertexKey =  "MyPrimaryVertices");
  declareProperty("R",	 			m_R =  0.4);
  declareProperty("NumberOfVertexBins",		m_nVtxBin =  40);
  declareProperty("RangeOfZVertex",		m_zRange =  200.); // mm
  declareProperty("MinimumPtJet",		m_ptMinJet =  5000.); // MeV
  declareProperty("MaximumNumberJets",		m_maxNjets =  10);
}

//! Destructor
MyPVAnalysis::~MyPVAnalysis()
{
}

/*******************************************************
 * Initialize method :
 *******************************************************/
StatusCode MyPVAnalysis::initialize()
{
  // Print where you are
  ATH_MSG_INFO ("initialize()");

  // Get the Storegate collection
  StatusCode sc = service("StoreGateSvc", m_sgSvc);
  if (sc.isFailure()) {
    ATH_MSG_ERROR( "Could not find StoreGateSvc" );
    return sc;
  }
  return StatusCode::SUCCESS;
}

/******************************************************
 * Execute method:
 ******************************************************/
StatusCode MyPVAnalysis::execute()
{
  // Print where you are
  ATH_MSG_INFO ("executing MyPVAnalysis");

  xAOD::VertexContainer *vertex = new xAOD::VertexContainer();
  xAOD::VertexAuxContainer *vertex_aux = new xAOD::VertexAuxContainer();
  vertex->setStore(vertex_aux);
  
  //! Load the TTT track particle container
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

  JetDefinition jet_def(antikt_algorithm, m_R);

  std::vector<std::vector<double> > vectorof_jetpt(m_nVtxBin, std::vector<double>(m_maxNjets, 0.0));
  std::vector<double> sum_pt(m_nVtxBin, 0.0);

  // [-0.5*m_zRange, 0.5*m_zRange] in m_nVtxBin steps
  double zBinWidth = m_zRange/((double) m_nVtxBin);
  std::vector<double> zvtx(m_nVtxBin, 0.0);

  std::vector< std::vector<const xAOD::TrackParticle *> > tp;
  for (unsigned int ith_bin = 0; ith_bin < m_nVtxBin; ++ith_bin)
  {
  	tp.push_back(std::vector<const xAOD::TrackParticle *>());
  	std::vector<PseudoJet> in_tracks;
	in_tracks.reserve(TTTtracks->size());
  	double zBin = -0.5*m_zRange + zBinWidth*ith_bin;

  	//! loop over the retrieved track particle conatiner and fill the TTree branches
  	xAOD::TrackParticleContainer::const_iterator nextTrk1(TTTtracks->begin());
  	xAOD::TrackParticleContainer::const_iterator lastTrk1(TTTtracks->end());
  	for (; nextTrk1!=lastTrk1; nextTrk1++) 
  	{
		const xAOD::TrackParticle* p = *nextTrk1;
		double zTrack = p->z0();
		bool isInBin = ((zTrack > zBin) && (zTrack < zBin + zBinWidth)) ||
				((zTrack < -0.5*m_zRange) && (ith_bin == 0)) ||
				((zTrack >= 0.5*m_zRange) && (ith_bin == m_nVtxBin-1));
		if (!isInBin) continue;
		PseudoJet trk(p->p4().Px(), p->p4().Py(), p->p4().Pz(), p->p4().E());
		in_tracks.push_back(trk);
		tp[ith_bin].push_back(p);
	}
	ClusterSequence clust_seq(in_tracks, jet_def);
	std::vector<PseudoJet> jets = sorted_by_pt(clust_seq.inclusive_jets(m_ptMinJet));
	unsigned int Njets = m_maxNjets;
	if (jets.size() < Njets) Njets = jets.size();
	for (unsigned int i = 0; i < Njets; ++i)
	{
		if (jets[i].perp() > vectorof_jetpt[ith_bin][i]) vectorof_jetpt[ith_bin][i] = jets[i].perp();
	}
	sum_pt[ith_bin] = std::accumulate( (vectorof_jetpt[ith_bin]).begin(), (vectorof_jetpt[ith_bin]).end(), 0.0);
  }
  std::vector<double>::iterator best_bin_iter = std::max_element(sum_pt.begin(), sum_pt.end());
  unsigned int best_ith_bin = (unsigned int) (best_bin_iter - sum_pt.begin());
  double best_z0 = -0.5*m_zRange + zBinWidth*best_ith_bin;
  xAOD::Vertex *mypv = new xAOD::Vertex();
  vertex->push_back(mypv);
  mypv->setX(0.0);
  mypv->setY(0.0);
  mypv->setZ(best_z0);
  mypv->setVertexType(xAOD::VxType::PriVtx);
  for (size_t i = 0; i < tp[best_ith_bin].size(); ++i) {
  	ElementLink<xAOD::TrackParticleContainer> el;
  	el.setElement(tp[best_ith_bin][i]);
  	mypv->addTrackAtVertex(el);
  }

  if ( m_sgSvc->record(vertex, m_vertexKey, false).isFailure() ) {
    ATH_MSG_ERROR( "Could not record new vertex" );
    return StatusCode::FAILURE;
  }
  if ( m_sgSvc->record(vertex_aux, m_vertexKey+"Aux.", false).isFailure() ) {
    ATH_MSG_ERROR( "Could not record new vertex" );
    return StatusCode::FAILURE;
  }

  return StatusCode::SUCCESS;
}

/******************************************************
 * Finalize method:
 ******************************************************/
StatusCode MyPVAnalysis::finalize()
{
  // Print where you are
  ATH_MSG_INFO ("finalize()");
  return StatusCode::SUCCESS;
}

