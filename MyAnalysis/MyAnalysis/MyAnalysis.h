///////////////////////////////////////////////////
// MyAnalysis.h
///////////////////////////////////////////////////
#ifndef MYANALYSIS_MyAnalysis_H_
#define MYANALYSIS_MyAnalysis_H_

//! Gaudi includes
#include "GaudiKernel/ToolHandle.h"
#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/ITHistSvc.h"

#include "TH1.h"
#include "TTree.h"
#include <string>

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthVertexContainer.h"
#include "xAODTruth/TruthVertex.h"

#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/TrackParticleAuxContainer.h"

#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"

#include <set>
//#include "TrigInDetAnalysis/TIDAAssociator.h"


template<typename T, typename S=T> 
class Associator {

public:

  typedef std::map<T*, S*> map_type; 
  typedef std::map<S*, T*> rev_map_type; 

public:

  Associator(const std::string& name)
    :  mname(name) 
  { } 
  
  virtual ~Associator() { } 
  
  virtual void match(const std::vector<T*>& s1, 
		     const std::vector<S*>& s2 ) = 0;
  
  // get matched track from map
  virtual const S* matched( T* t) { 
     typename map_type::const_iterator titr = mmatched.find(t);
     if ( titr != mmatched.end() ) return titr->second;
     else                          return 0;
  } 

  // get matched track from reverse map
  virtual const T* revmatched( S* t) { 
     typename rev_map_type::const_iterator titr = mrevmatched.find(t);
     if ( titr != mrevmatched.end() ) return titr->second;
     else                             return 0;
  } 

  // get the lookup tables
  const map_type&    matched() const { return mmatched; }
  const rev_map_type& revmatched() const { return mrevmatched; }

  // clear the match lookup tables
  void clear() { mmatched.clear(); mrevmatched.clear(); } 

  // how many items were matched
  unsigned size() const { return mmatched.size(); }

protected:

  std::string mname;
  
  map_type mmatched;
  rev_map_type mrevmatched;

};



template<typename T, typename S>
class BestMatcher : public Associator<T,S>  {

protected:

  /// internal class to store the matching paramter for a pair, 
  /// and in the indices of the pair

  class matched_ { 
    
  public:
    
    matched_(double d, int i, int j) : m_d(d), m_match(std::pair<int,int>(i,j)) { } 
    
    double d() const { return m_d; } 
    
    std::pair<int, int> pair() const { return m_match; }
    
    int first()  const { return m_match.first; } 
    int second() const { return m_match.second; } 
    
    bool  operator<(const matched_& a) const { return d()<a.d(); }
    bool  operator>(const matched_& a) const { return d()>a.d(); }
    bool operator==(const matched_& a) const { return  d()==a.d(); } 
    bool operator!=(const matched_& a) const { return  d()!=a.d(); } 
    
  private:
    double              m_d;
    std::pair<int, int> m_match; 
  };

public:

  BestMatcher(const std::string& name, double d) : 
    Associator<T,S>(name), m_d(d) 
  {   } 
  
  virtual ~BestMatcher() { } 
  
  
  virtual void match(const std::vector<T*>& ref, const std::vector<S*>& test ) 
  {
    this->clear();
    
    std::map<int,int> matched = matcher( ref, test);

    std::map<int,int>::iterator  mitr = matched.begin();
    while ( mitr!=matched.end() ) {
      this->mmatched.insert(    typename Associator<T,S>::map_type::value_type( ref[mitr->first],   test[mitr->second]) );
      this->mrevmatched.insert( typename Associator<T,S>::rev_map_type::value_type( test[mitr->second], ref[mitr->first] ) );
      mitr++;
    }  

  }
 
  virtual double distance( const T* t0,  const S* t1 ) const {
      double deta = t0->eta()-t1->eta();
      double dphi = t0->phi()-t1->phi();  
      if ( dphi> M_PI ) dphi-=2*M_PI; 
      if ( dphi<-M_PI ) dphi+=2*M_PI;
      //std::cout<<"deta, dphi, dR : " << deta << ", " << dphi << ", " << std::sqrt( deta*deta + dphi*dphi ) <<std::endl;
      return std::sqrt( deta*deta + dphi*dphi );
    }


protected:


  template<typename Tp, typename Tq>
  std::map<int, int>  matcher( const std::vector<Tp*>& ref, const std::vector<Tq*>& test) { 
    
    /// inserting into a multimatch sorts them into order 
    /// as they are added so you get the list of best 
    /// matches imediately 
    /// NB: probably quicker to add them to a vector and then 
    ///     sort them afterward
    
    std::multiset<matched_> m;
    
    for (unsigned int i=0 ; i<ref.size() ; i++ ) { 
      
      for (unsigned int j=0 ; j<test.size() ; j++ ) { 
	double d = distance(ref[i], test[j]);   
	if ( d<m_d ){  
	  m.insert( matched_(d, i, j) ); 
	}
      }
    }
    
    /// now go through from best to worst, adding to another
    /// sorted set only the matches that do not use tracks
    /// already used by a better matching pair already found
    
    std::vector<bool>  refused(  ref.size(), false ); 
    std::vector<bool> testused( test.size(), false ); 

    /// set of unique track pairings
    /// NB: for some reason, using the multiset is faster 
    ///     than using a vector, even though we are only
    ///     iterating through it later
    std::multiset<matched_> unique;

    typename std::multiset<matched_>::iterator mitr = m.begin();
    
    double  chi2 = 0;
    
    for ( ; mitr!=m.end() ; mitr++ ) { 

      int rind = mitr->first();
      int tind = mitr->second();

      if (  refused[rind] ) continue;
      if ( testused[tind] ) continue;

      refused[rind]  = true;
      testused[tind] = true;

      unique.insert( *mitr );

      chi2 += (mitr->d()*mitr->d());

    }
    
    
    //std::cout << "chi2 of matches " << chi2 << std::endl;
   
    /// hooray!! now print out the answer, make a map etc
    /// this isn't technically needed, could just use the 
    /// set of "matched" objects, but hey ho 
    
    //std::cout << "\nmatched" << std::endl; 
    
    std::map<int, int> matches;


    mitr = unique.begin();
    while ( mitr!=unique.end() ) {
      matches.insert( std::map<int, int>::value_type( mitr->first(), mitr->second() ) );
      //std::cout << "\tbest match " << *mitr << "\t" <<  ref[mitr->first()] << "\t" << test[mitr->second()] << std::endl;
      mitr++;
    }  
 
    return matches;
    
  }


protected:

  double m_d;

};


typedef BestMatcher<xAOD::IParticle, const xAOD::TruthParticle> DeltaRAssociator;
typedef BestMatcher<xAOD::IParticle, xAOD::IParticle> DeltaRAssociatorII;


////////////////////////////////////////////////////////////////////////
class StoreGateSvc;
class MyAnalysis : public AthAlgorithm
{
public:
  //! Constructor with parameters:
  MyAnalysis(const std::string& name, ISvcLocator* pSvcLocator);
  //! Default Destructor
  ~MyAnalysis();
  //! Function printing the properties of a TrackParticle
  void printTrackPcle( const xAOD::TrackParticle& tp );
  //! Function printing the properties of a Jet
  void printJet( const xAOD::Jet &tj );
  //! Function getting the properties of a jet
  std::vector<float> GetJetParameters( const xAOD::Jet &tj, int isStd = -1 );
  //! Return angle in the range [0,2*pi)
  static double angle_positive(double angle){ return angle -(2*M_PI) * std::floor(angle/(2*M_PI));}
  //! Return angle in the range [-pi,pi)
  static double angle_symmetric(double angle){return angle - (2*M_PI) * std::floor((angle + M_PI)/(2*M_PI));}

  //! Basic algorithm methods:
  StatusCode 	initialize();
  StatusCode 	execute();
  StatusCode 	finalize();
private:
  StoreGateSvc* m_sgSvc;
  bool		m_debug;
  std::string 	m_infokey;
  std::string 	m_truthkey;
  std::string 	m_tpContainer;
  std::string 	m_tttContainer;
  std::string 	m_ttttruthContainer;
  std::string 	m_jetSGkey;
  std::string 	m_jetTTTSGkey;
  std::string 	m_jetStdSGkey;
  std::string	m_trkjet4key;
  std::string	m_trkjet2key;
  std::string	m_ttttrkjet4key;
  std::string	m_ttttrkjet2key;
  std::string	m_truthjetkey;
  std::string	m_stdPV0trkjet4key;
  std::string  	m_stdPV0trkjet2key;
  std::string  	m_tttPV0trkjet4key;
  std::string  	m_tttPV0trkjet2key;
  std::vector<const xAOD::TruthParticle *> findMyBaby(const xAOD::TruthParticle *part, const int myMommy, const int myBaby);

  DeltaRAssociator* m_associator;
  DeltaRAssociatorII* m_associatorII;

  std::vector<float> 	vec_jetPars;// eta,phi,e,m,pt,px,py,pz
  TTree*		m_collectionTree;
  unsigned int 		m_event; 
  float                 m_weight;
  //! all variables below labled as m_truth* have values
  //! = -1 for truth particles reconstructed more than once with triplet reconstruction
  std::vector<float>    m_truthM;
  std::vector<float>    m_truthPt;
  std::vector<float>    m_truthP;
  std::vector<float>    m_truthEta;
  std::vector<float>    m_truthTheta;
  std::vector<float>    m_truthPhi;
  std::vector<float>    m_truthVx; //!99999.0 production vertex does not exist
  std::vector<float>    m_truthVy;//!99999.0 production vertex does not exist
  std::vector<float>    m_truthVz;//!99999.0 production vertex does not exist
  std::vector<int>      m_truthPdg;
  std::vector<int>      m_truthStatus;
  std::vector<int>      m_truthBarcode;



  std::vector<float>	m_truthjetEta;
  std::vector<float>	m_truthjetPhi;
  std::vector<float>	m_truthjetE;
  std::vector<float>	m_truthjetM;
  std::vector<float>	m_truthjetPt;
  std::vector<float>	m_truthjetPx;
  std::vector<float>	m_truthjetPy;
  std::vector<float>	m_truthjetPz;

  float                 m_StdPVx;
  float                 m_StdPVy;
  float                 m_StdPVz;
  float                 m_TTTPVz;

  std::vector<float>	m_InDetd0;
  std::vector<float>	m_InDetz0;
  std::vector<float>	m_InDetphi0;
  std::vector<float>	m_InDettheta;
  std::vector<float>	m_InDetqOverP;
  std::vector<float>	m_InDetPt;
  std::vector<float>	m_InDetEta;
  std::vector<int>	m_InDetTBarcode;
  std::vector<int>	m_InDetTPdg;
  std::vector<float>	m_InDetTPt;
  std::vector<float>	m_InDetTP;
  std::vector<float>	m_InDetTEta;
  std::vector<float>	m_InDetTTheta;
  std::vector<float>	m_InDetTPhi;
  std::vector<float>	m_InDetTZ0;
  std::vector<float>	m_InDetTVx;
  std::vector<float>	m_InDetTVy;
  std::vector<float>	m_TTTd0;
  std::vector<float>	m_TTTz0;
  std::vector<float>	m_TTTphi0;
  std::vector<float>	m_TTTtheta;
  std::vector<float>	m_TTTqOverP;
  std::vector<float>	m_TTTPt;
  std::vector<float>	m_TTTEta;
  std::vector<int>	m_TTTTBarcode;
  std::vector<int>	m_TTTTPdg;
  std::vector<float>	m_TTTTPt;
  std::vector<float>	m_TTTTP;
  std::vector<float>	m_TTTTEta;
  std::vector<float>	m_TTTTTheta;
  std::vector<float>	m_TTTTPhi;
  std::vector<float>	m_TTTTZ0;
  std::vector<float>	m_TTTTVx;
  std::vector<float>	m_TTTTVy;
  //! TTT truth particles
  std::vector<float>	m_TTTtruthd0;
  std::vector<float>	m_TTTtruthz0;
  std::vector<float>	m_TTTtruthphi0;
  std::vector<float>	m_TTTtruththeta;
  std::vector<float>	m_TTTtruthqOverP;
  std::vector<float>	m_TTTtruthPt;
  std::vector<float>	m_TTTtruthEta;
  //! ttt tracks barcode matched to truth particles 
  std::vector<int>	mc_TTTTBarcode;
  std::vector<int>	mc_TTTTStatus;
  std::vector<int>	mc_TTTTPdg;
  std::vector<float>	mc_TTTTPt;
  std::vector<float>	mc_TTTTP;
  std::vector<float>	mc_TTTTEta;
  std::vector<float>	mc_TTTTTheta;
  std::vector<float>	mc_TTTTPhi;
  std::vector<float>	mc_TTTTZ0;
  std::vector<float>	mc_TTTTVx;
  std::vector<float>	mc_TTTTVy;

 std::vector<float>	m_calojetJVF;
  std::vector<float>	m_calojetJVT;
  std::vector<float>	m_calojetEta;
  std::vector<float>	m_calojetPhi;
  std::vector<float>	m_calojetE;
  std::vector<float>	m_calojetM;
  std::vector<float>	m_calojetPt;
  std::vector<float>	m_calojetPx;
  std::vector<float>	m_calojetPy;
  std::vector<float>	m_calojetPz;

  std::vector<float>	m_caloTTTjetJVF;
  std::vector<float>	m_caloTTTjetJVT;
  std::vector<float>	m_caloTTTjetEta;
  std::vector<float>	m_caloTTTjetPhi;
  std::vector<float>	m_caloTTTjetE;
  std::vector<float>	m_caloTTTjetM;
  std::vector<float>	m_caloTTTjetPt;
  std::vector<float>	m_caloTTTjetPx;
  std::vector<float>	m_caloTTTjetPy;
  std::vector<float>	m_caloTTTjetPz;

  std::vector<float>	m_caloStdjetJVF;
  std::vector<float>	m_caloStdjetJVT;
  std::vector<float>	m_caloStdjetEta;
  std::vector<float>	m_caloStdjetPhi;
  std::vector<float>	m_caloStdjetE;
  std::vector<float>	m_caloStdjetM;
  std::vector<float>	m_caloStdjetPt;
  std::vector<float>	m_caloStdjetPx;
  std::vector<float>	m_caloStdjetPy;
  std::vector<float>	m_caloStdjetPz;

  std::vector<float>	m_std4trkjetEta;
  std::vector<float>	m_std4trkjetPhi;
  std::vector<float>	m_std4trkjetE;
  std::vector<float>	m_std4trkjetM;
  std::vector<float>	m_std4trkjetPt;
  std::vector<float>	m_std4trkjetPx;
  std::vector<float>	m_std4trkjetPy;
  std::vector<float>	m_std4trkjetPz;

  std::vector<float>	m_std2trkjetEta;
  std::vector<float>	m_std2trkjetPhi;
  std::vector<float>	m_std2trkjetE;
  std::vector<float>	m_std2trkjetM;
  std::vector<float>	m_std2trkjetPt;
  std::vector<float>	m_std2trkjetPx;
  std::vector<float>	m_std2trkjetPy;
  std::vector<float>	m_std2trkjetPz;

  std::vector<float>	m_ttt4trkjetEta;
  std::vector<float>	m_ttt4trkjetPhi;
  std::vector<float>	m_ttt4trkjetE;
  std::vector<float>	m_ttt4trkjetM;
  std::vector<float>	m_ttt4trkjetPt;
  std::vector<float>	m_ttt4trkjetPx;
  std::vector<float>	m_ttt4trkjetPy;
  std::vector<float>	m_ttt4trkjetPz;

  std::vector<float>	m_ttt2trkjetEta;
  std::vector<float>	m_ttt2trkjetPhi;
  std::vector<float>	m_ttt2trkjetE;
  std::vector<float>	m_ttt2trkjetM;
  std::vector<float>	m_ttt2trkjetPt;
  std::vector<float>	m_ttt2trkjetPx;
  std::vector<float>	m_ttt2trkjetPy;
  std::vector<float>	m_ttt2trkjetPz; 
 
  std::vector<float>	m_std4PV0trkjetEta;
  std::vector<float>	m_std4PV0trkjetPhi;
  std::vector<float>	m_std4PV0trkjetE;
  std::vector<float>	m_std4PV0trkjetM;
  std::vector<float>	m_std4PV0trkjetPt;
  std::vector<float>	m_std4PV0trkjetPx;
  std::vector<float>	m_std4PV0trkjetPy;
  std::vector<float>	m_std4PV0trkjetPz;

  std::vector<float>	m_std2PV0trkjetEta;
  std::vector<float>	m_std2PV0trkjetPhi;
  std::vector<float>	m_std2PV0trkjetE;
  std::vector<float>	m_std2PV0trkjetM;
  std::vector<float>	m_std2PV0trkjetPt;
  std::vector<float>	m_std2PV0trkjetPx;
  std::vector<float>	m_std2PV0trkjetPy;
  std::vector<float>	m_std2PV0trkjetPz;

  std::vector<float>	m_ttt4PV0trkjetEta;
  std::vector<float>	m_ttt4PV0trkjetPhi;
  std::vector<float>	m_ttt4PV0trkjetE;
  std::vector<float>	m_ttt4PV0trkjetM;
  std::vector<float>	m_ttt4PV0trkjetPt;
  std::vector<float>	m_ttt4PV0trkjetPx;
  std::vector<float>	m_ttt4PV0trkjetPy;
  std::vector<float>	m_ttt4PV0trkjetPz;

  std::vector<float>	m_ttt2PV0trkjetEta;
  std::vector<float>	m_ttt2PV0trkjetPhi;
  std::vector<float>	m_ttt2PV0trkjetE;
  std::vector<float>	m_ttt2PV0trkjetM;
  std::vector<float>	m_ttt2PV0trkjetPt;
  std::vector<float>	m_ttt2PV0trkjetPx;
  std::vector<float>	m_ttt2PV0trkjetPy;
  std::vector<float>	m_ttt2PV0trkjetPz;

};
#endif // MYANALYSIS_MyAnalysis_H_
