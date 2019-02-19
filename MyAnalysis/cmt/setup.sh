# echo "setup MyAnalysis MyAnalysis-00-00-01 in /nfs/dust/atlas/user/tkar/derivations"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/CMT/v1r25p20160527; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtMyAnalysistempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtMyAnalysistempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=MyAnalysis -version=MyAnalysis-00-00-01 -path=/nfs/dust/atlas/user/tkar/derivations  -no_cleanup $* >${cmtMyAnalysistempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=MyAnalysis -version=MyAnalysis-00-00-01 -path=/nfs/dust/atlas/user/tkar/derivations  -no_cleanup $* >${cmtMyAnalysistempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtMyAnalysistempfile}
  unset cmtMyAnalysistempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtMyAnalysistempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtMyAnalysistempfile}
unset cmtMyAnalysistempfile
return $cmtsetupstatus

