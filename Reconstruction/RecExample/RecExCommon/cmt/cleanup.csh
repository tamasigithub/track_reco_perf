# echo "cleanup RecExCommon RecExCommon-00-14-47-09 in /nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/CMT/v1r25p20160527
endif
source ${CMTROOT}/mgr/setup.csh
set cmtRecExCommontempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtRecExCommontempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=RecExCommon -version=RecExCommon-00-14-47-09 -path=/nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample  -quiet -without_version_directory $* >${cmtRecExCommontempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -csh -pack=RecExCommon -version=RecExCommon-00-14-47-09 -path=/nfs/dust/atlas/user/tkar/derivations/Reconstruction/RecExample  -quiet -without_version_directory $* >${cmtRecExCommontempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtRecExCommontempfile}
  unset cmtRecExCommontempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtRecExCommontempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtRecExCommontempfile}
unset cmtRecExCommontempfile
exit $cmtcleanupstatus

