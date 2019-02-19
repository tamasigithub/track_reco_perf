# echo "cleanup RecExCommon RecExCommon-00-14-47-09 in /nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/CMT/v1r25p20160527; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtRecExCommontempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtRecExCommontempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=RecExCommon -version=RecExCommon-00-14-47-09 -path=/nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample  -quiet -without_version_directory $* >${cmtRecExCommontempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=RecExCommon -version=RecExCommon-00-14-47-09 -path=/nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample  -quiet -without_version_directory $* >${cmtRecExCommontempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtRecExCommontempfile}
  unset cmtRecExCommontempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtRecExCommontempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtRecExCommontempfile}
unset cmtRecExCommontempfile
return $cmtcleanupstatus

