# echo "cleanup MyAnalysis MyAnalysis-00-00-01 in /nfs/dust/atlas/user/tkar/derivations"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/CMT/v1r25p20160527
endif
source ${CMTROOT}/mgr/setup.csh
set cmtMyAnalysistempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtMyAnalysistempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=MyAnalysis -version=MyAnalysis-00-00-01 -path=/nfs/dust/atlas/user/tkar/derivations  $* >${cmtMyAnalysistempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=MyAnalysis -version=MyAnalysis-00-00-01 -path=/nfs/dust/atlas/user/tkar/derivations  $* >${cmtMyAnalysistempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtMyAnalysistempfile}
  unset cmtMyAnalysistempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtMyAnalysistempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtMyAnalysistempfile}
unset cmtMyAnalysistempfile
exit $cmtcleanupstatus

