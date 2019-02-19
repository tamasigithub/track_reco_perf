#include "GaudiKernel/DeclareFactoryEntries.h"
#include "MyAnalysis/MyAnalysis.h"
#include "MyAnalysis/MyPVAnalysis.h"

//enter all the algorithms used in this package
DECLARE_ALGORITHM_FACTORY( MyAnalysis )
DECLARE_ALGORITHM_FACTORY( MyPVAnalysis )

//enter all the algorithms used in this package
DECLARE_FACTORY_ENTRIES(MyAnalysis) {
DECLARE_ALGORITHM( MyAnalysis )
DECLARE_ALGORITHM( MyPVAnalysis )
}
