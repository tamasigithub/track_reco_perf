----------> uses
# use AtlasPolicy AtlasPolicy-01-*  (no_version_directory)
#   use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#     use PlatformPolicy PlatformPolicy-* External (no_version_directory)
#       use GaudiPolicy *  (no_version_directory)
#         use LCG_Settings *  (no_version_directory)
#         use Python * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.9.p1)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#         use tcmalloc * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.4)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#           use libunwind v* LCG_Interfaces (no_version_directory) (native_version=5c2cade)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use Reflex v* LCG_Interfaces (no_auto_imports) (no_version_directory)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#           use ROOT v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=6.04.18)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#             use GCCXML v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=0.9.0_20131026)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.9.p1)
#             use xrootd v* LCG_Interfaces (no_version_directory) (native_version=4.2.3)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#       use AtlasCommonPolicy AtlasCommonPolicy-*  (no_version_directory)
#         use LCG_Platforms *  (no_version_directory)
#         use AtlasDoxygen AtlasDoxygen-* Tools (no_version_directory) (native_version=)
#           use LCG_Settings *  (no_version_directory)
#           use LCG_Configuration *  (no_version_directory)
#             use LCG_Platforms *  (no_version_directory)
#     use Mac105_Compat Mac105_Compat-* External (no_version_directory) (native_version=1.0.0)
#       use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#         use PlatformPolicy PlatformPolicy-* External (no_version_directory)
#       use PlatformPolicy PlatformPolicy-* External (no_version_directory)
#   use AtlasCxxPolicy AtlasCxxPolicy-*  (no_version_directory)
#     use GaudiPolicy v*  (no_auto_imports) (no_version_directory)
#     use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#     use AtlasCompilers AtlasCompilers-* External (no_version_directory)
#       use LCG_Platforms *  (no_version_directory)
#     use CheckerGccPlugins CheckerGccPlugins-* External (no_version_directory) (native_version=CheckerGccPlugins-00-01-84)
#       use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#       use AtlasCompilers AtlasCompilers-* External (no_version_directory)
#   use AtlasCommonPolicy AtlasCommonPolicy-*  (no_version_directory)
#   use GaudiPolicy v*  (no_auto_imports) (no_version_directory)
#   use CodeCheck CodeCheck-* Tools (no_version_directory)
#   use AtlasDoxygen AtlasDoxygen-* Tools (no_version_directory) (native_version=)
# use AtlasReconstructionRunTime *  (no_version_directory)
#   use AtlasEventRunTime AtlasEventRunTime-*  (no_auto_imports) (no_version_directory)
#     use AtlasConditionsRunTime AtlasConditionsRunTime-*  (no_auto_imports) (no_version_directory)
#       use AtlasCoreRunTime AtlasCoreRunTime-*  (no_auto_imports) (no_version_directory)
#         use MinimalRunTime MinimalRunTime-* Control (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_auto_imports) (no_version_directory)
#           use AthenaCommon AthenaCommon-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use AthenaKernel AthenaKernel-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use uuid v* LCG_Interfaces (no_version_directory) (native_version=dummy)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#               use GaudiKernel v*  (no_version_directory)
#                 use GaudiPolicy *  (no_version_directory)
#                 use GaudiPluginService *  (no_version_directory)
#                   use GaudiPolicy *  (no_version_directory)
#                 use Reflex * LCG_Interfaces (no_version_directory)
#                 use Boost * LCG_Interfaces (no_version_directory) (native_version=1.59.0_python2.7)
#                   use LCG_Configuration v*  (no_version_directory)
#                   use LCG_Settings v*  (no_version_directory)
#                   use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.9.p1)
#             use DataModelRoot DataModelRoot-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use AtlasROOT AtlasROOT-* External (no_version_directory)
#                 use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#                 use ROOT v* LCG_Interfaces (no_version_directory) (native_version=6.04.18)
#               use AtlasReflex AtlasReflex-* External (no_version_directory)
#                 use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#                 use AtlasRELAX AtlasRELAX-* External (no_auto_imports) (no_version_directory)
#                   use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#                   use RELAX v* LCG_Interfaces (no_version_directory) (native_version=RELAX-root6)
#                     use LCG_Configuration v*  (no_version_directory)
#                     use LCG_Settings v*  (no_version_directory)
#                 use AtlasROOT AtlasROOT-* External (no_version_directory)
#             use CxxUtils CxxUtils-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use AtlasBoost AtlasBoost-* External (no_version_directory)
#                 use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#                 use Boost v* LCG_Interfaces (no_version_directory) (native_version=1.59.0_python2.7)
#             use AtlasBoost AtlasBoost-* External (no_version_directory)
#             use Scripts Scripts-* Tools (no_auto_imports) (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use AthenaServices AthenaServices-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use CLIDSvc CLIDSvc-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use SGTools SGTools-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use CxxUtils CxxUtils-* Control (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#               use AtlasBoost AtlasBoost-* External (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#             use AtlasPython AtlasPython-* External (no_auto_imports) (no_version_directory)
#               use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#               use Python v* LCG_Interfaces (no_version_directory) (native_version=2.7.9.p1)
#           use DataModel DataModel-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use SGTools SGTools-* Control (no_version_directory)
#             use AthAllocators AthAllocators-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use AtlasBoost AtlasBoost-* External (no_version_directory)
#             use AthLinks AthLinks-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#               use SGTools SGTools-* Control (no_version_directory)
#               use CxxUtils CxxUtils-* Control (no_version_directory)
#               use AtlasBoost AtlasBoost-* External (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use AtlasReflex AtlasReflex-* External (no_version_directory)
#             use AthContainers AthContainers-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#               use SGTools SGTools-* Control (no_version_directory)
#               use CxxUtils CxxUtils-* Control (no_version_directory)
#               use AthContainersInterfaces AthContainersInterfaces-* Control (no_version_directory)
#                 use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#                 use SGTools SGTools-* Control (no_version_directory)
#                 use CxxUtils CxxUtils-* Control (no_version_directory)
#                 use AtlasBoost AtlasBoost-* External (no_version_directory)
#               use AthLinks AthLinks-* Control (no_version_directory)
#               use AtlasBoost AtlasBoost-* External (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#             use CxxUtils CxxUtils-* Control (no_version_directory)
#           use SGTools SGTools-* Control (no_auto_imports) (no_version_directory)
#           use StoreGate StoreGate-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use CxxUtils CxxUtils-* Control (no_version_directory)
#             use AthenaKernel AthenaKernel-* Control (no_version_directory)
#             use SGTools SGTools-* Control (no_version_directory)
#             use AtlasBoost AtlasBoost-* External (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#             use AthAllocators AthAllocators-* Control (no_version_directory)
#             use AthContainersInterfaces AthContainersInterfaces-* Control (no_version_directory)
#           use DetDescrCnvSvc DetDescrCnvSvc-00-* DetectorDescription (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#           use IdDictDetDescrCnv IdDictDetDescrCnv-* DetectorDescription (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use IOVSvc IOVSvc-* Control (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use SGTools SGTools-* Control (no_version_directory)
#             use AthenaKernel AthenaKernel-* Control (no_version_directory)
#             use AthenaBaseComps AthenaBaseComps-* Control (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use AtlasROOT AtlasROOT-* External (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#               use StoreGate StoreGate-* Control (no_version_directory)
#               use SGTools SGTools-* Control (no_version_directory)
#               use CxxUtils CxxUtils-* Control (no_version_directory)
#             use AtlasBoost AtlasBoost-* External (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#           use McEventSelector McEventSelector-* Generators (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AthenaKernel AthenaKernel-* Control (no_version_directory)
#             use AthenaBaseComps AthenaBaseComps-* Control (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#           use GaudiInterface GaudiInterface-* External (no_auto_imports) (no_version_directory)
#           use GaudiAlg v*  (no_auto_imports) (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#             use GaudiUtils *  (no_version_directory)
#               use GaudiKernel *  (no_version_directory)
#               use ROOT * LCG_Interfaces (no_version_directory) (native_version=6.04.18)
#               use AIDA * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.2.1)
#                 use LCG_Configuration v*  (no_version_directory)
#                 use LCG_Settings v*  (no_version_directory)
#               use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.59.0_python2.7)
#               use uuid * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=dummy)
#               use XercesC * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.1.1p1)
#                 use LCG_Configuration v*  (no_version_directory)
#                 use LCG_Settings v*  (no_version_directory)
#             use ROOT * LCG_Interfaces (no_version_directory) (native_version=6.04.18)
#             use AIDA * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.2.1)
#             use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.59.0_python2.7)
#           use GaudiAud v*  (no_auto_imports) (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#           use GaudiKernel v*  (no_auto_imports) (no_version_directory)
#           use GaudiPython v*  (no_auto_imports) (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#             use GaudiAlg *  (no_version_directory)
#             use GaudiUtils *  (no_version_directory)
#             use AIDA * LCG_Interfaces (no_version_directory) (native_version=3.2.1)
#             use CLHEP * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.2.0.4)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use Python * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.9.p1)
#           use GaudiSvc v*  (no_auto_imports) (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#             use CLHEP * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.2.0.4)
#             use Boost * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.59.0_python2.7)
#             use ROOT * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=6.04.18)
#           use PartPropSvc v*  (no_auto_imports) (no_version_directory)
#             use GaudiPolicy *  (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#             use HepPDT * LCG_Interfaces (no_version_directory) (native_version=2.06.01)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#           use RootHistCnv v*  (no_auto_imports) (no_version_directory)
#             use GaudiKernel *  (no_version_directory)
#             use AIDA * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=3.2.1)
#             use ROOT * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=6.04.18)
#           use AtlasReflex AtlasReflex-* External (no_auto_imports) (no_version_directory)
#           use AtlasCOOL AtlasCOOL-* External (no_auto_imports) (no_version_directory)
#             use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#             use COOL v* LCG_Interfaces (no_version_directory) (native_version=3_1_0)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#               use CORAL v* LCG_Interfaces (no_version_directory) (native_version=3_1_0)
#                 use LCG_Configuration v*  (no_version_directory)
#                 use LCG_Settings v*  (no_version_directory)
#                 use Boost v* LCG_Interfaces (no_version_directory) (native_version=1.59.0_python2.7)
#               use Python v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=2.7.9.p1)
#               use ROOT v* LCG_Interfaces (no_version_directory) (native_version=6.04.18)
#             use AtlasReflex AtlasReflex-00-* External (no_auto_imports) (no_version_directory)
#           use AtlasOracle AtlasOracle-* External (no_auto_imports) (no_version_directory) (native_version=11.2.0.3.0)
#             use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#             use oracle v* LCG_Interfaces (no_version_directory) (native_version=11.2.0.3.0)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#             use pytools * LCG_Interfaces (no_version_directory) (native_version=1.9_python2.7)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#               use Python v* LCG_Interfaces (no_version_directory) (native_version=2.7.9.p1)
#               use mysql v* LCG_Interfaces (no_version_directory) (native_version=5.5.27)
#                 use LCG_Configuration v*  (no_version_directory)
#                 use LCG_Settings v*  (no_version_directory)
#           use AtlasRELAX AtlasRELAX-* External (no_auto_imports) (no_version_directory)
#           use AtlasReflex AtlasReflex-* External (no_auto_imports) (no_version_directory)
#           use AtlasCORAL AtlasCORAL-* External (no_auto_imports) (no_version_directory)
#             use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#             use CORAL v* LCG_Interfaces (no_version_directory) (native_version=3_1_0)
#             use AtlasReflex AtlasReflex-00-* External (no_auto_imports) (no_version_directory)
#           use AtlasShift AtlasShift-* External (no_auto_imports) (no_version_directory)
#             use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#             use CASTOR v* LCG_Interfaces (no_version_directory) (native_version=2.1.13-6)
#               use LCG_Configuration v*  (no_version_directory)
#               use LCG_Settings v*  (no_version_directory)
#           use AtlasDCACHE AtlasDCACHE-* External (no_auto_imports) (no_version_directory)
#             use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#           use AtlasDPM AtlasDPM-* External (no_auto_imports) (no_version_directory)
#             use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#           use AtlasAuthentication AtlasAuthentication-* Database/ConnectionManagement (no_auto_imports) (no_version_directory) (native_version=v18)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#         use Ant Ant-* External (no_auto_imports) (no_version_directory) (native_version=1.7.0)
#           use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#             use CERNJavaInstallation CERNJavaInstallation-01-* External (no_version_directory)
#               use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#         use AtlasAIDA AtlasAIDA-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use AIDA v* LCG_Interfaces (no_version_directory) (native_version=3.2.1)
#         use AtlasBoost AtlasBoost-* External (no_auto_imports) (no_version_directory)
#         use AtlasCLHEP AtlasCLHEP-* External (no_auto_imports) (no_version_directory) (native_version=2.2.0.4)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use CLHEP v* LCG_Interfaces (no_version_directory) (native_version=2.2.0.4)
#         use AtlasCOOL AtlasCOOL-* External (no_auto_imports) (no_version_directory)
#         use AtlasCORAL AtlasCORAL-* External (no_auto_imports) (no_version_directory)
#         use AtlasCppUnit AtlasCppUnit-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use CppUnit v* LCG_Interfaces (no_version_directory) (native_version=1.12.1_p1)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use AtlasDBRelease AtlasDBRelease-* External (no_auto_imports) (no_version_directory) (native_version=current)
#           use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#         use AtlasDataArea AtlasDataArea-* External (no_auto_imports) (no_version_directory) (native_version=v20)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#         use AtlasEigen AtlasEigen-* External (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use PyCmt PyCmt-* Tools (no_auto_imports) (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AtlasPython AtlasPython-* External (no_auto_imports) (no_version_directory)
#         use AtlasExpat AtlasExpat-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use Expat v* LCG_Interfaces (no_version_directory) (native_version=2.0.1)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use AtlasExternalArea AtlasExternalArea-* External (no_auto_imports) (no_version_directory)
#         use AtlasGSL AtlasGSL-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use GSL v* LCG_Interfaces (no_version_directory) (native_version=1.10)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use AtlasGPerfTools AtlasGPerfTools-* External (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#           use PyCmt PyCmt-* Tools (no_auto_imports) (no_version_directory)
#           use AtlasLibUnwind * External (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#             use PyCmt PyCmt-* Tools (no_auto_imports) (no_version_directory)
#         use AtlasMagField AtlasMagField-* External (no_auto_imports) (no_version_directory) (native_version=current)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#         use AtlasMatplotlib AtlasMatplotlib-* External (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#         use AtlasMKL AtlasMKL-* External (no_auto_imports) (no_version_directory) (native_version=2013.3.163)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#         use AtlasOracle AtlasOracle-* External (no_auto_imports) (no_version_directory) (native_version=11.2.0.3.0)
#         use AtlasPOOL AtlasPOOL-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#           use mysql v* LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=5.5.27)
#           use POOLCore POOLCore-* Database/APR (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#             use AtlasBoost AtlasBoost-* External (no_version_directory)
#           use CollectionBase CollectionBase-* Database/APR (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#             use FileCatalog FileCatalog-* Database/APR (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#               use POOLCore POOLCore-* Database/APR (no_version_directory)
#           use CollectionUtilities CollectionUtilities-* Database/APR (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#             use PersistentDataModel PersistentDataModel-* Database (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use SGTools SGTools-* Control (no_version_directory)
#             use CollectionBase CollectionBase-* Database/APR (no_version_directory)
#             use TrigCollQuery TrigCollQuery-* Database/APR (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#               use AthenaBaseComps AthenaBaseComps-* Control (no_version_directory)
#           use StorageSvc StorageSvc-* Database/APR (no_version_directory)
#             use uuid * LCG_Interfaces (no_version_directory) (native_version=dummy)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use AtlasReflex AtlasReflex-* External (no_version_directory)
#             use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#             use CxxUtils CxxUtils-* Control (no_version_directory)
#             use PersistentDataModel PersistentDataModel-* Database (no_version_directory)
#             use DataModelRoot DataModelRoot-* Control (no_version_directory)
#           use PersistencySvc PersistencySvc-* Database/APR (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use POOLCore POOLCore-* Database/APR (no_version_directory)
#             use StorageSvc StorageSvc-* Database/APR (no_version_directory)
#             use DataModelRoot DataModelRoot-* Control (no_version_directory)
#         use AtlasPyROOT AtlasPyROOT-* External (no_auto_imports) (no_version_directory)
#           use AtlasROOT AtlasROOT-02-* External (no_auto_imports) (no_version_directory)
#           use AtlasPython AtlasPython-00-* External (no_auto_imports) (no_version_directory)
#         use AtlasPython AtlasPython-* External (no_auto_imports) (no_version_directory)
#         use AtlasRELAX AtlasRELAX-* External (no_auto_imports) (no_version_directory)
#         use AtlasROOT AtlasROOT-* External (no_auto_imports) (no_version_directory)
#         use AtlasReflex AtlasReflex-* External (no_auto_imports) (no_version_directory)
#         use AtlasSQLite AtlasSQLite-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use sqlite v* LCG_Interfaces (no_version_directory) (native_version=3070900)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use AtlasValgrind AtlasValgrind-* External (no_auto_imports) (no_version_directory) (native_version=3.11.0)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#           use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#           use valgrind v* LCG_Interfaces (no_version_directory) (native_version=3.11.0)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#         use yampl yampl-* External (no_auto_imports) (no_version_directory) (native_version=1.0)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#         use PathResolver PathResolver-* Tools (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use GaudiInterface GaudiInterface-* External (no_version_directory)
#           use AsgTools AsgTools-* Control/AthToolSupport (no_version_directory)
#             use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#             use GaudiInterface GaudiInterface-* External (no_version_directory)
#             use AthenaBaseComps AthenaBaseComps-* Control (no_version_directory)
#             use SGTools SGTools-* Control (no_version_directory)
#             use IOVDbDataModel IOVDbDataModel-* Database (no_version_directory)
#               use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#               use GaudiInterface GaudiInterface-* External (no_version_directory)
#               use CLIDSvc CLIDSvc-* Control (no_version_directory)
#               use AthenaPoolUtilities AthenaPoolUtilities-* Database/AthenaPOOL (no_version_directory)
#                 use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#                 use AtlasCORAL AtlasCORAL-* External (no_version_directory)
#                 use AthenaKernel AthenaKernel-* Control (no_version_directory)
#                 use CLIDSvc CLIDSvc-* Control (no_version_directory)
#                 use DataModel DataModel-* Control (no_version_directory)
#                 use DBDataModel DBDataModel-* Database/AthenaPOOL (no_version_directory)
#                   use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#                   use CLIDSvc CLIDSvc-* Control (no_version_directory)
#                   use DataModel DataModel-* Control (no_version_directory)
#               use AthenaKernel AthenaKernel-* Control (no_version_directory)
#         use Axis Axis-* External (no_auto_imports) (no_version_directory) (native_version=1.4)
#           use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#           use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#           use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#         use CERNJavaInstallation CERNJavaInstallation-* External (no_auto_imports) (no_version_directory)
#         use DataCollection DataCollection-* External (no_auto_imports) (no_version_directory)
#           use AtlasCxxPolicy AtlasCxxPolicy-*  (no_version_directory)
#           use TDAQCPolicyExt v* TDAQCPolicy (no_version_directory)
#         use ExternalPolicy ExternalPolicy-* External (no_auto_imports) (no_version_directory)
#         use GaudiInterface GaudiInterface-* External (no_auto_imports) (no_version_directory)
#         use JavaSDK JavaSDK-* External (no_auto_imports) (no_version_directory) (native_version=1.6.0)
#         use MMMySQL MMMySQL-* External (no_auto_imports) (no_version_directory) (native_version=5.0.5)
#           use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#           use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#           use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#         use MySQL MySQL-* External (no_auto_imports) (no_version_directory)
#           use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#           use mysql v* LCG_Interfaces (no_version_directory) (native_version=5.5.27)
#         use pyAMI pyAMI-* External (no_auto_imports) (no_version_directory)
#           use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#           use AtlasPython AtlasPython-* External (no_version_directory)
#           use PyCmt PyCmt-* Tools (no_auto_imports) (no_version_directory)
#         use pytools * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.9_python2.7)
#         use pyanalysis * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.5_python2.7)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#           use Python v* LCG_Interfaces (no_version_directory) (native_version=2.7.9.p1)
#           use blas v* LCG_Interfaces (no_version_directory) (native_version=20110419)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#           use lapack v* LCG_Interfaces (no_version_directory) (native_version=3.5.0)
#             use LCG_Configuration v*  (no_version_directory)
#             use LCG_Settings v*  (no_version_directory)
#             use blas v* LCG_Interfaces (no_version_directory) (native_version=20110419)
#         use pygraphics * LCG_Interfaces (no_auto_imports) (no_version_directory) (native_version=1.5_python2.7)
#           use LCG_Configuration v*  (no_version_directory)
#           use LCG_Settings v*  (no_version_directory)
#           use Python v* LCG_Interfaces (no_version_directory) (native_version=2.7.9.p1)
#       use JACE JACE-* External (no_auto_imports) (no_version_directory) (native_version=1.1.rc1_04.1.5)
#         use JavaJNI JavaJNI-01-* External (no_version_directory) (native_version=_)
#           use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#           use AtlasPolicy AtlasPolicy-01-*  (no_version_directory)
#           use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#         use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#         use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#       use JavaJNI JavaJNI-* External (no_auto_imports) (no_version_directory) (native_version=_)
#       use Log4J Log4J-* External (no_auto_imports) (no_version_directory) (native_version=1.2.14)
#         use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#         use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#         use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#       use XercesJ XercesJ-* External (no_auto_imports) (no_version_directory) (native_version=2.9.0)
#         use JavaSDK JavaSDK-01-* External (no_version_directory) (native_version=1.6.0)
#         use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#         use Ant Ant-00-* External (no_version_directory) (native_version=1.7.0)
#     use AtlasXercesC AtlasXercesC-* External (no_auto_imports) (no_version_directory)
#       use ExternalPolicy ExternalPolicy-00-* External (no_version_directory)
#       use XercesC v* LCG_Interfaces (no_version_directory) (native_version=3.1.1p1)
#     use Pythia Pythia-* External (no_auto_imports) (no_version_directory) (native_version=428.2_lcgcmt81f)
#       use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#       use LCG_Configuration *  (no_version_directory)
#   use AtlasCoinInventor AtlasCoinInventor-* External (no_auto_imports) (no_version_directory) (native_version=3.1.3p2)
#     use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#   use AtlasSoQt AtlasSoQt-* External (no_auto_imports) (no_version_directory) (native_version=1.5.0_qt_coin3d3.1.3p2)
#     use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#     use AtlasCoinInventor AtlasCoinInventor-* External (no_version_directory) (native_version=3.1.3p2)
#     use AtlasQt4 AtlasQt4-* External (no_version_directory) (native_version=4.8.4)
#       use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#       use Qt * LCG_Interfaces (no_version_directory) (native_version=4.8.4)
#         use LCG_Configuration v*  (no_version_directory)
#         use LCG_Settings v*  (no_version_directory)
#   use AtlasFastJet AtlasFastJet-* External (no_auto_imports) (no_version_directory) (native_version=3.2.0)
#     use AtlasExternalArea AtlasExternalArea-00-* External (no_version_directory)
#     use AtlasFortranPolicy AtlasFortranPolicy-*  (no_version_directory) (native_version=gcc-v-4.2.0-20060924)
#       use AtlasExternalArea AtlasExternalArea-* External (no_version_directory)
#       use AtlasCompilers AtlasCompilers-* External (no_version_directory)
#       use GaudiPolicy v*  (no_auto_imports) (no_version_directory)
#     use fastjet * LCG_Interfaces (no_version_directory) (native_version=3.2.0)
#       use LCG_Configuration v*  (no_version_directory)
#       use LCG_Settings v*  (no_version_directory)
# use TestPolicy TestPolicy-*  (no_version_directory)
#   use AtlasPolicy AtlasPolicy-01-*  (no_version_directory)
# use AtlasPyFwdBwdPorts AtlasPyFwdBwdPorts-* External (no_auto_imports) (no_version_directory)
#   use AtlasPolicy AtlasPolicy-*  (no_version_directory)
#   use ExternalPolicy ExternalPolicy-* External (no_version_directory)
#   use AtlasPython AtlasPython-* External (no_version_directory)
#   use PyCmt PyCmt-* Tools (no_auto_imports) (no_version_directory)
#
# Selection :
use CMT v1r25p20160527 (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10)
use TDAQCPolicyExt v* TDAQCPolicy (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/tdaq-common/tdaq-common-01-46-00) (no_auto_imports)
use CodeCheck CodeCheck-01-02-03 Tools (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use LCG_Platforms v1  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f)
use AtlasCompilers AtlasCompilers-00-00-25 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10)
use LCG_Configuration v1  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f)
use LCG_Settings v1  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f)
use fastjet v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use Qt v* LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use blas v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use lapack v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use valgrind v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use sqlite v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use GSL v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use Expat v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use CppUnit v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use CASTOR v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use mysql v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use oracle v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use HepPDT v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use CLHEP CLHEP-00-75-00-02 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10) (no_auto_imports)
use XercesC v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use AIDA v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use RELAX v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use uuid v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use AtlasDoxygen AtlasDoxygen-00-04-10 Tools (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10)
use AtlasCommonPolicy AtlasCommonPolicy-00-00-55  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10)
use xrootd v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use GCCXML v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use libunwind v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use tcmalloc v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use Python v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use pygraphics v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use pyanalysis v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use pytools v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use Boost Boost-00-75-00-01 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10) (no_auto_imports)
use CORAL v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use ROOT v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use COOL v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use Reflex v1 LCG_Interfaces (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f) (no_auto_imports)
use GaudiPolicy GaudiPolicy-15-05-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f)
use GaudiPluginService GaudiPluginService-02-02-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiKernel GaudiKernel-31-05-04  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use RootHistCnv RootHistCnv-12-01-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use PartPropSvc PartPropSvc-06-04-01  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiSvc GaudiSvc-21-06-01  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiAud GaudiAud-10-02-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiUtils GaudiUtils-05-03-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiAlg GaudiAlg-15-02-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use GaudiPython GaudiPython-13-05-00  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f) (no_auto_imports)
use PlatformPolicy PlatformPolicy-00-00-20 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use AtlasExternalArea AtlasExternalArea-00-00-27 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use AtlasFortranPolicy AtlasFortranPolicy-00-00-81  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasFastJet AtlasFastJet-00-00-30 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasEvent/20.20.10) (no_auto_imports)
use AtlasCoinInventor AtlasCoinInventor-00-01-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasReconstruction/20.20.10) (no_auto_imports)
use Pythia Pythia-04-28-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasEvent/20.20.10) (no_auto_imports)
use AtlasDPM AtlasDPM-00-00-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasDCACHE AtlasDCACHE-00-00-03 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasShift AtlasShift-00-00-10 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use Mac105_Compat Mac105_Compat-00-00-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use ExternalPolicy ExternalPolicy-00-01-71 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use AtlasQt4 AtlasQt4-00-00-11 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasSoQt AtlasSoQt-00-05-06 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasReconstruction/20.20.10) (no_auto_imports)
use AtlasXercesC AtlasXercesC-00-00-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use MySQL MySQL-00-02-06 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use yampl yampl-00-00-03 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasSQLite AtlasSQLite-00-00-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasMagField AtlasMagField-00-00-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasGSL AtlasGSL-00-00-10 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasExpat AtlasExpat-00-00-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasDataArea AtlasDataArea-00-00-31 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasDBRelease AtlasDBRelease-01-00-03 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasCppUnit AtlasCppUnit-00-00-06 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasCLHEP AtlasCLHEP-00-00-11-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasAIDA AtlasAIDA-00-01-02 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CERNJavaInstallation CERNJavaInstallation-01-01-00 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use JavaSDK JavaSDK-01-07-03 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use Ant Ant-00-01-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use XercesJ XercesJ-02-07-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10) (no_auto_imports)
use Log4J Log4J-01-03-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10) (no_auto_imports)
use MMMySQL MMMySQL-00-01-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use Axis Axis-00-01-02 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasOracle AtlasOracle-00-01-28 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasPython AtlasPython-00-01-07 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasRELAX AtlasRELAX-00-01-00 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasROOT AtlasROOT-02-03-23 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasPyROOT AtlasPyROOT-00-01-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasReflex AtlasReflex-00-03-10 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasCORAL AtlasCORAL-00-00-10 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasCOOL AtlasCOOL-00-00-11 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use GaudiInterface GaudiInterface-01-03-04 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CheckerGccPlugins CheckerGccPlugins-00-01-85 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use AtlasCxxPolicy AtlasCxxPolicy-00-00-77  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use DataCollection DataCollection-00-18-06 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasPolicy AtlasPolicy-01-08-46-04  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use TestPolicy TestPolicy-00-02-03  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10)
use JavaJNI JavaJNI-01-01-00 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10) (no_auto_imports)
use JACE JACE-00-00-06 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10) (no_auto_imports)
use AtlasValgrind AtlasValgrind-00-01-17 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasMKL AtlasMKL-00-01-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasMatplotlib AtlasMatplotlib-00-03-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use PyCmt PyCmt-00-00-47 Tools (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasPyFwdBwdPorts AtlasPyFwdBwdPorts-00-02-25 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use pyAMI pyAMI-05-00-03-02 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasLibUnwind AtlasLibUnwind-00-00-05 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasGPerfTools AtlasGPerfTools-00-00-07 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasEigen AtlasEigen-00-00-07 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasAuthentication AtlasAuthentication-00-05-06 Database/ConnectionManagement (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use IdDictDetDescrCnv IdDictDetDescrCnv-00-00-45 DetectorDescription (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use DetDescrCnvSvc DetDescrCnvSvc-00-04-11-01 DetectorDescription (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthenaServices AthenaServices-01-59-06-09 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use Scripts Scripts-00-01-88 Tools (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasBoost AtlasBoost-00-00-11 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use POOLCore POOLCore-00-04-03 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use FileCatalog FileCatalog-00-01-06 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CollectionBase CollectionBase-00-02-08 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthAllocators AthAllocators-00-01-06 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CxxUtils CxxUtils-00-01-56 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use DataModelRoot DataModelRoot-00-00-20 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthenaKernel AthenaKernel-00-56-19-03 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use SGTools SGTools-00-24-09-03 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use PersistentDataModel PersistentDataModel-00-00-40 Database (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use StorageSvc StorageSvc-00-04-28 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use PersistencySvc PersistencySvc-00-02-04-01 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthContainersInterfaces AthContainersInterfaces-00-01-33 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use StoreGate StoreGate-02-45-01-13 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthenaBaseComps AthenaBaseComps-00-07-02 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use TrigCollQuery TrigCollQuery-01-00-03 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CollectionUtilities CollectionUtilities-00-02-24 Database/APR (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasPOOL AtlasPOOL-00-02-01 External (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use McEventSelector McEventSelector-02-03-04 Generators (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use IOVSvc IOVSvc-00-07-33 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthLinks AthLinks-00-02-19 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthContainers AthContainers-00-02-51-01 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use DataModel DataModel-00-23-71 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use CLIDSvc CLIDSvc-00-05-02 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use DBDataModel DBDataModel-00-08-02 Database/AthenaPOOL (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthenaPoolUtilities AthenaPoolUtilities-00-07-00 Database/AthenaPOOL (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use IOVDbDataModel IOVDbDataModel-00-00-27 Database (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AsgTools AsgTools-00-00-85 Control/AthToolSupport (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use PathResolver PathResolver-00-02-14 Tools (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AthenaCommon AthenaCommon-03-03-08-01 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use MinimalRunTime MinimalRunTime-00-00-24 Control (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasCoreRunTime AtlasCoreRunTime-00-00-52  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10) (no_auto_imports)
use AtlasConditionsRunTime AtlasConditionsRunTime-00-00-17  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10) (no_auto_imports)
use AtlasEventRunTime AtlasEventRunTime-00-00-12  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasEvent/20.20.10) (no_auto_imports)
use AtlasReconstructionRunTime AtlasReconstructionRunTime-00-00-08  (/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasReconstruction/20.20.10)
use CMTUSERCONTEXT v0 (/cvmfs/atlas.cern.ch/repo/tools/slc6/cmt)
----------> tags
x86_64-slc6-gcc49-opt (from CMTCONFIG) package [LCG_Platforms PlatformPolicy] implies [target-x86_64 target-slc6 target-gcc49 target-opt Linux slc6 64 gcc-4.9 opt x86_64-slc6-gcc49]
ATLAS (from arguments) package [GaudiPolicy] implies [use-shared-dir no-pyzip] applied [ExternalPolicy]
CMTv1 (from CMTVERSION)
CMTr25 (from CMTVERSION)
CMTp20160527 (from CMTVERSION)
Linux (from uname) package [CMT LCG_Platforms AtlasCxxPolicy AtlasPolicy] implies [Unix host-linux cpp_native_dependencies]
STANDALONE (from CMTSITE)
CMTUSERCONTEXT_no_config (from PROJECT) excludes [CMTUSERCONTEXT_config]
CMTUSERCONTEXT_no_root (from PROJECT) excludes [CMTUSERCONTEXT_root]
CMTUSERCONTEXT_cleanup (from PROJECT) excludes [CMTUSERCONTEXT_no_cleanup]
CMTUSERCONTEXT_scripts (from PROJECT) excludes [CMTUSERCONTEXT_no_scripts]
CMTUSERCONTEXT_no_prototypes (from PROJECT) excludes [CMTUSERCONTEXT_prototypes]
CMTUSERCONTEXT_with_installarea (from PROJECT) excludes [CMTUSERCONTEXT_without_installarea]
CMTUSERCONTEXT_without_version_directory (from PROJECT) excludes [CMTUSERCONTEXT_with_version_directory]
tkar_no_config (from PROJECT) excludes [tkar_config]
tkar_no_root (from PROJECT) excludes [tkar_root]
tkar_cleanup (from PROJECT) excludes [tkar_no_cleanup]
tkar_scripts (from PROJECT) excludes [tkar_no_scripts]
tkar_no_prototypes (from PROJECT) excludes [tkar_prototypes]
tkar_with_installarea (from PROJECT) excludes [tkar_without_installarea]
tkar_without_version_directory (from PROJECT) excludes [tkar_with_version_directory]
tkar (from PROJECT)
AtlasProduction_no_config (from PROJECT) excludes [AtlasProduction_config]
AtlasProduction_no_root (from PROJECT) excludes [AtlasProduction_root]
AtlasProduction_cleanup (from PROJECT) excludes [AtlasProduction_no_cleanup]
AtlasProduction_scripts (from PROJECT) excludes [AtlasProduction_no_scripts]
AtlasProduction_no_prototypes (from PROJECT) excludes [AtlasProduction_prototypes]
AtlasProduction_with_installarea (from PROJECT) excludes [AtlasProduction_without_installarea]
AtlasProduction_without_version_directory (from PROJECT) excludes [AtlasProduction_with_version_directory]
AtlasOffline_no_config (from PROJECT) excludes [AtlasOffline_config]
AtlasOffline_no_root (from PROJECT) excludes [AtlasOffline_root]
AtlasOffline_cleanup (from PROJECT) excludes [AtlasOffline_no_cleanup]
AtlasOffline_scripts (from PROJECT) excludes [AtlasOffline_no_scripts]
AtlasOffline_no_prototypes (from PROJECT) excludes [AtlasOffline_prototypes]
AtlasOffline_with_installarea (from PROJECT) excludes [AtlasOffline_without_installarea]
AtlasOffline_without_version_directory (from PROJECT) excludes [AtlasOffline_with_version_directory]
AtlasAnalysis_no_config (from PROJECT) excludes [AtlasAnalysis_config]
AtlasAnalysis_no_root (from PROJECT) excludes [AtlasAnalysis_root]
AtlasAnalysis_cleanup (from PROJECT) excludes [AtlasAnalysis_no_cleanup]
AtlasAnalysis_scripts (from PROJECT) excludes [AtlasAnalysis_no_scripts]
AtlasAnalysis_no_prototypes (from PROJECT) excludes [AtlasAnalysis_prototypes]
AtlasAnalysis_with_installarea (from PROJECT) excludes [AtlasAnalysis_without_installarea]
AtlasAnalysis_without_version_directory (from PROJECT) excludes [AtlasAnalysis_with_version_directory]
AtlasTrigger_no_config (from PROJECT) excludes [AtlasTrigger_config]
AtlasTrigger_no_root (from PROJECT) excludes [AtlasTrigger_root]
AtlasTrigger_cleanup (from PROJECT) excludes [AtlasTrigger_no_cleanup]
AtlasTrigger_scripts (from PROJECT) excludes [AtlasTrigger_no_scripts]
AtlasTrigger_no_prototypes (from PROJECT) excludes [AtlasTrigger_prototypes]
AtlasTrigger_with_installarea (from PROJECT) excludes [AtlasTrigger_without_installarea]
AtlasTrigger_without_version_directory (from PROJECT) excludes [AtlasTrigger_with_version_directory]
AtlasReconstruction_no_config (from PROJECT) excludes [AtlasReconstruction_config]
AtlasReconstruction_no_root (from PROJECT) excludes [AtlasReconstruction_root]
AtlasReconstruction_cleanup (from PROJECT) excludes [AtlasReconstruction_no_cleanup]
AtlasReconstruction_scripts (from PROJECT) excludes [AtlasReconstruction_no_scripts]
AtlasReconstruction_no_prototypes (from PROJECT) excludes [AtlasReconstruction_prototypes]
AtlasReconstruction_with_installarea (from PROJECT) excludes [AtlasReconstruction_without_installarea]
AtlasReconstruction_without_version_directory (from PROJECT) excludes [AtlasReconstruction_with_version_directory]
AtlasEvent_no_config (from PROJECT) excludes [AtlasEvent_config]
AtlasEvent_no_root (from PROJECT) excludes [AtlasEvent_root]
AtlasEvent_cleanup (from PROJECT) excludes [AtlasEvent_no_cleanup]
AtlasEvent_scripts (from PROJECT) excludes [AtlasEvent_no_scripts]
AtlasEvent_no_prototypes (from PROJECT) excludes [AtlasEvent_prototypes]
AtlasEvent_with_installarea (from PROJECT) excludes [AtlasEvent_without_installarea]
AtlasEvent_without_version_directory (from PROJECT) excludes [AtlasEvent_with_version_directory]
AtlasConditions_no_config (from PROJECT) excludes [AtlasConditions_config]
AtlasConditions_no_root (from PROJECT) excludes [AtlasConditions_root]
AtlasConditions_cleanup (from PROJECT) excludes [AtlasConditions_no_cleanup]
AtlasConditions_scripts (from PROJECT) excludes [AtlasConditions_no_scripts]
AtlasConditions_no_prototypes (from PROJECT) excludes [AtlasConditions_prototypes]
AtlasConditions_with_installarea (from PROJECT) excludes [AtlasConditions_without_installarea]
AtlasConditions_without_version_directory (from PROJECT) excludes [AtlasConditions_with_version_directory]
AtlasCore_no_config (from PROJECT) excludes [AtlasCore_config]
AtlasCore_no_root (from PROJECT) excludes [AtlasCore_root]
AtlasCore_cleanup (from PROJECT) excludes [AtlasCore_no_cleanup]
AtlasCore_scripts (from PROJECT) excludes [AtlasCore_no_scripts]
AtlasCore_no_prototypes (from PROJECT) excludes [AtlasCore_prototypes]
AtlasCore_with_installarea (from PROJECT) excludes [AtlasCore_without_installarea]
AtlasCore_without_version_directory (from PROJECT) excludes [AtlasCore_with_version_directory]
DetCommon_no_config (from PROJECT) excludes [DetCommon_config]
DetCommon_no_root (from PROJECT) excludes [DetCommon_root]
DetCommon_cleanup (from PROJECT) excludes [DetCommon_no_cleanup]
DetCommon_scripts (from PROJECT) excludes [DetCommon_no_scripts]
DetCommon_prototypes (from PROJECT) excludes [DetCommon_no_prototypes]
DetCommon_with_installarea (from PROJECT) excludes [DetCommon_without_installarea]
DetCommon_without_version_directory (from PROJECT) excludes [DetCommon_with_version_directory]
tdaq-common_no_config (from PROJECT) excludes [tdaq-common_config]
tdaq-common_no_root (from PROJECT) excludes [tdaq-common_root]
tdaq-common_cleanup (from PROJECT) excludes [tdaq-common_no_cleanup]
tdaq-common_scripts (from PROJECT) excludes [tdaq-common_no_scripts]
tdaq-common_prototypes (from PROJECT) excludes [tdaq-common_no_prototypes]
tdaq-common_without_installarea (from PROJECT) excludes [tdaq-common_with_installarea]
tdaq-common_without_version_directory (from PROJECT) excludes [tdaq-common_with_version_directory]
LCGCMT_no_config (from PROJECT) excludes [LCGCMT_config]
LCGCMT_no_root (from PROJECT) excludes [LCGCMT_root]
LCGCMT_cleanup (from PROJECT) excludes [LCGCMT_no_cleanup]
LCGCMT_scripts (from PROJECT) excludes [LCGCMT_no_scripts]
LCGCMT_prototypes (from PROJECT) excludes [LCGCMT_no_prototypes]
LCGCMT_with_installarea (from PROJECT) excludes [LCGCMT_without_installarea]
LCGCMT_without_version_directory (from PROJECT) excludes [LCGCMT_with_version_directory]
GAUDI_no_config (from PROJECT) excludes [GAUDI_config]
GAUDI_root (from PROJECT) excludes [GAUDI_no_root]
GAUDI_cleanup (from PROJECT) excludes [GAUDI_no_cleanup]
GAUDI_scripts (from PROJECT) excludes [GAUDI_no_scripts]
GAUDI_prototypes (from PROJECT) excludes [GAUDI_no_prototypes]
GAUDI_with_installarea (from PROJECT) excludes [GAUDI_without_installarea]
GAUDI_without_version_directory (from PROJECT) excludes [GAUDI_with_version_directory]
dqm-common_no_config (from PROJECT) excludes [dqm-common_config]
dqm-common_no_root (from PROJECT) excludes [dqm-common_root]
dqm-common_cleanup (from PROJECT) excludes [dqm-common_no_cleanup]
dqm-common_scripts (from PROJECT) excludes [dqm-common_no_scripts]
dqm-common_prototypes (from PROJECT) excludes [dqm-common_no_prototypes]
dqm-common_without_installarea (from PROJECT) excludes [dqm-common_with_installarea]
dqm-common_without_version_directory (from PROJECT) excludes [dqm-common_with_version_directory]
AtlasSimulation_no_config (from PROJECT) excludes [AtlasSimulation_config]
AtlasSimulation_no_root (from PROJECT) excludes [AtlasSimulation_root]
AtlasSimulation_cleanup (from PROJECT) excludes [AtlasSimulation_no_cleanup]
AtlasSimulation_scripts (from PROJECT) excludes [AtlasSimulation_no_scripts]
AtlasSimulation_no_prototypes (from PROJECT) excludes [AtlasSimulation_prototypes]
AtlasSimulation_with_installarea (from PROJECT) excludes [AtlasSimulation_without_installarea]
AtlasSimulation_without_version_directory (from PROJECT) excludes [AtlasSimulation_with_version_directory]
x86_64 (from package CMT) package [LCG_Platforms] implies [host-x86_64] applied [CMT]
sl610 (from package CMT) applied [CMT]
gcc493 (from package CMT) applied [CMT]
Unix (from package CMT) package [LCG_Platforms] implies [host-unix] excludes [WIN32 Win32]
c_native_dependencies (from package CMT) activated GaudiPolicy
cpp_native_dependencies (from package CMT) activated GaudiPolicy
/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10:/cvmfs/atlas.cern.ch/repo/sw/tdaq/tdaqnotProject (from package ExternalPolicy) applied [ExternalPolicy]
target-unix (from package LCG_Settings) activated LCG_Platforms
target-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-gcc49 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc4 target-lcg-compiler lcg-compiler target-c11] activated LCG_Platforms
host-x86_64 (from package LCG_Settings) activated LCG_Platforms
target-slc (from package LCG_Settings) package [LCG_Platforms] implies [target-linux] activated LCG_Platforms
target-gcc (from package LCG_Settings) activated LCG_Platforms
target-gcc4 (from package LCG_Settings) package [LCG_Platforms] implies [target-gcc] activated LCG_Platforms
target-lcg-compiler (from package LCG_Settings) activated LCG_Platforms
host-linux (from package LCG_Platforms) package [LCG_Platforms] implies [host-unix]
host-unix (from package LCG_Platforms)
target-opt (from package LCG_Platforms)
target-slc6 (from package LCG_Platforms) package [LCG_Platforms] implies [target-slc]
target-linux (from package LCG_Platforms) package [LCG_Platforms] implies [target-unix]
lcg-compiler (from package LCG_Platforms)
target-c11 (from package LCG_Platforms)
ROOT_GE_5_15 (from package LCG_Configuration) applied [LCG_Configuration]
ROOT_GE_5_19 (from package LCG_Configuration) applied [LCG_Configuration]
ROOT_GE_6_00 (from package LCG_Configuration) applied [LCG_Configuration]
use-shared-dir (from package GaudiPolicy)
do_genconf (from package GaudiPolicy) applied [AtlasPolicy] activated AtlasPolicy
no-pyzip (from package GaudiPolicy)
separate-debug (from package AtlasCommonPolicy) excludes [no-separate-debug] applied [AtlasCommonPolicy]
NICOS (from package AtlasCommonPolicy) package AtlasCommonPolicy excludes [NICOSrel_nightly] applied [AtlasCommonPolicy]
LCGCMT_INSTALLED (from package PlatformPolicy) applied [PlatformPolicy ExternalPolicy]
block-tdaqc (from package PlatformPolicy) applied [PlatformPolicy ExternalPolicy]
opt (from package PlatformPolicy) package [AtlasPolicy] implies [optimized]
gcc (from package PlatformPolicy)
64 (from package PlatformPolicy) package [PlatformPolicy] implies [target-64]
gcc-4.9 (from package PlatformPolicy) package [PlatformPolicy] implies [gcc49x gcc49 gcc]
gcc49x (from package PlatformPolicy)
gcc49 (from package PlatformPolicy)
slc6 (from package PlatformPolicy)
x86_64-slc6-gcc49 (from package PlatformPolicy)
target-64 (from package PlatformPolicy)
asNeeded (from package PlatformPolicy) applied [PlatformPolicy]
CheckerGccPlugins_project_AtlasCore (from package CheckerGccPlugins) applied [CheckerGccPlugins]
optimized (from package AtlasPolicy) package [AtlasPolicy] implies [opt]
HasAthenaRunTime (from package AtlasPolicy) applied [AtlasPolicy]
SITE_ (from package AtlasPolicy) applied [AtlasPolicy]
HAVE_GAUDI_PLUGINSVC (from package GaudiPluginService) applied [GaudiPluginService]
ROOTBasicLibs (from package AtlasROOT) applied [AtlasROOT]
AthenaServices_Control/AthenaExamples/ToyConversion_nothasPP (from package AthenaServices) applied [AthenaServices]
NEEDS_CORAL_RELATIONAL_ACCESS (from package CORAL) applied [AtlasCORAL] activated AtlasCORAL
NEEDS_CORAL_BASE (from package CORAL) applied [AthenaPoolUtilities] activated AthenaPoolUtilities
NEEDS_PYCOOL (from package COOL) applied [AtlasCOOL] activated AtlasCOOL
NotAtlasP1 (from package PathResolver) applied [PathResolver]
HAS_FORTRAN_RUNTIME (from package AtlasFortranPolicy)
HAS_FORTRAN (from package AtlasFortranPolicy)
HAS_GFO (from package AtlasFortranPolicy) package [AtlasFortranPolicy] implies [HAS_FORTRAN HAS_GFO_RUNTIME] applied [AtlasFortranPolicy]
HAS_GFO_RUNTIME (from package AtlasFortranPolicy) package [AtlasFortranPolicy] implies [HAS_FORTRAN_RUNTIME]
no_pack_dist_check (from package RecExCommon) applied [RecExCommon]
----------> CMTPATH
# Add path /cvmfs/atlas.cern.ch/repo/tools/slc6/cmt from CMTUSERCONTEXT
# Add path /nfs/dust/atlas/user/tkar/derivations from initialization
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasProduction/20.20.10.7 from initialization
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasOffline/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasAnalysis/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasSimulation/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasTrigger/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasReconstruction/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasEvent/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/dqm-common/dqm-common-00-55-00 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasConditions/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/DetCommon/20.20.10 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/tdaq-common/tdaq-common-01-46-00 from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/GAUDI/v26r2p3-lcg81f from ProjectPath
# Add path /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/LCGCMT/LCGCMT_81f from ProjectPath
