///////////////////////////////////////////////////
// MyPVAnalysis.h
///////////////////////////////////////////////////
#ifndef MYPVANALYSIS_MyAnalysis_H_
#define MYPVANALYSIS_MyAnalysis_H_

//! Gaudi includes
#include "GaudiKernel/ToolHandle.h"
#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/ITHistSvc.h"

#include "xAODTracking/Vertex.h"
#include "xAODTracking/VertexContainer.h"
#include "xAODTracking/VertexAuxContainer.h"

#include "TH1.h"
#include "TTree.h"
#include <string>

#include <set>

////////////////////////////////////////////////////////////////////////
class StoreGateSvc;
class MyPVAnalysis : public AthAlgorithm
{
public:
  //! Constructor with parameters:
  MyPVAnalysis(const std::string& name, ISvcLocator* pSvcLocator);
  //! Default Destructor
  ~MyPVAnalysis();

  //! Basic algorithm methods:
  StatusCode 	initialize();
  StatusCode 	execute();
  StatusCode 	finalize();
private:
  StoreGateSvc* m_sgSvc;
  bool		m_debug;
  std::string 	m_infokey;
  std::string 	m_tttContainer;
  std::string   m_vertexKey;

  double m_R;
  unsigned int m_nVtxBin;
  double m_zRange;
  double m_ptMinJet;
  unsigned int m_maxNjets;

};
#endif // MYANALYSIS_MyPVAnalysis_H_
