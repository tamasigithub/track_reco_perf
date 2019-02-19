#-- start of make_header -----------------

#====================================
#  Document check_install_runtime
#
#   Generated Mon Feb  4 11:40:46 2019  by tkar
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_check_install_runtime

RecExCommon_tag = $(tag)

#cmt_local_tagfile_check_install_runtime = $(RecExCommon_tag)_check_install_runtime.make
cmt_local_tagfile_check_install_runtime = $(bin)$(RecExCommon_tag)_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

RecExCommon_tag = $(tag)

#cmt_local_tagfile_check_install_runtime = $(RecExCommon_tag).make
cmt_local_tagfile_check_install_runtime = $(bin)$(RecExCommon_tag).make

endif

include $(cmt_local_tagfile_check_install_runtime)
#-include $(cmt_local_tagfile_check_install_runtime)

ifdef cmt_check_install_runtime_has_target_tag

cmt_final_setup_check_install_runtime = $(bin)setup_check_install_runtime.make
cmt_dependencies_in_check_install_runtime = $(bin)dependencies_check_install_runtime.in
#cmt_final_setup_check_install_runtime = $(bin)RecExCommon_check_install_runtimesetup.make
cmt_local_check_install_runtime_makefile = $(bin)check_install_runtime.make

else

cmt_final_setup_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_check_install_runtime = $(bin)RecExCommonsetup.make
cmt_local_check_install_runtime_makefile = $(bin)check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)RecExCommonsetup.make

#check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = check_install_runtime/
#check_install_runtime::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of cmt_action_runner_header ---------------

ifdef ONCE
check_install_runtime_once = 1
endif

ifdef check_install_runtime_once

check_install_runtimeactionstamp = $(bin)check_install_runtime.actionstamp
#check_install_runtimeactionstamp = check_install_runtime.actionstamp

check_install_runtime :: $(check_install_runtimeactionstamp)
	$(echo) "check_install_runtime ok"
#	@echo check_install_runtime ok

#$(check_install_runtimeactionstamp) :: $(check_install_runtime_dependencies)
$(check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/cmt/atlas_check_installations.sh -files=' -s=../share ../data/*.ascii.gz  ' -installdir=/nfs/dust/atlas/user/tkar/derivations/InstallArea/share -level=
	$(silent) cat /dev/null > $(check_install_runtimeactionstamp)
#	@echo ok > $(check_install_runtimeactionstamp)

check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(check_install_runtimeactionstamp)

else

#check_install_runtime :: $(check_install_runtime_dependencies)
check_install_runtime ::
	$(silent) /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/cmt/atlas_check_installations.sh -files=' -s=../share ../data/*.ascii.gz  ' -installdir=/nfs/dust/atlas/user/tkar/derivations/InstallArea/share -level=

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

check_install_runtimeclean ::
#-- end of cleanup_header ---------------
