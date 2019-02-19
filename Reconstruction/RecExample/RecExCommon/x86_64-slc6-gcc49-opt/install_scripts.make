#-- start of make_header -----------------

#====================================
#  Document install_scripts
#
#   Generated Mon Feb  4 11:40:47 2019  by tkar
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_install_scripts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_install_scripts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_install_scripts

RecExCommon_tag = $(tag)

#cmt_local_tagfile_install_scripts = $(RecExCommon_tag)_install_scripts.make
cmt_local_tagfile_install_scripts = $(bin)$(RecExCommon_tag)_install_scripts.make

else

tags      = $(tag),$(CMTEXTRATAGS)

RecExCommon_tag = $(tag)

#cmt_local_tagfile_install_scripts = $(RecExCommon_tag).make
cmt_local_tagfile_install_scripts = $(bin)$(RecExCommon_tag).make

endif

include $(cmt_local_tagfile_install_scripts)
#-include $(cmt_local_tagfile_install_scripts)

ifdef cmt_install_scripts_has_target_tag

cmt_final_setup_install_scripts = $(bin)setup_install_scripts.make
cmt_dependencies_in_install_scripts = $(bin)dependencies_install_scripts.in
#cmt_final_setup_install_scripts = $(bin)RecExCommon_install_scriptssetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make

else

cmt_final_setup_install_scripts = $(bin)setup.make
cmt_dependencies_in_install_scripts = $(bin)dependencies.in
#cmt_final_setup_install_scripts = $(bin)RecExCommonsetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)RecExCommonsetup.make

#install_scripts :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'install_scripts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = install_scripts/
#install_scripts::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------


ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/share/bin

install_scripts :: install_scriptsinstall ;

install :: install_scriptsinstall ;

install_scriptsclean :: install_scriptsuninstall

uninstall :: install_scriptsuninstall


# This is to avoid error in case there are no files to install
# Ideally, the fragment should not be used without files to install,
# and this line should be dropped then
install_scriptsinstall :: ;

RecExCommon_links_zc_sh_dependencies = ../share/RecExCommon_links_zc.sh
RecExCommon_links_cern_zc_sh_dependencies = ../share/RecExCommon_links_cern_zc.sh
RecExCommon_links_sh_dependencies = ../share/RecExCommon_links.sh
RecExCommon_links_csh_dependencies = ../share/RecExCommon_links.csh
RecExCommon_runTimeFiles_zc_sh_dependencies = ../share/RecExCommon_runTimeFiles_zc.sh
RecExCommon_dump_C_dependencies = ../share/RecExCommon_dump.C
manyrecotests_sh_dependencies = ../Testing/manyrecotests.sh
recexcommon-links_py_dependencies = ../share/recexcommon-links.py
qtest_run1_sh_dependencies = ../share/qtest_run1.sh
qtest_run2_sh_dependencies = ../share/qtest_run2.sh


install_scriptsinstall :: ${install_dir}/RecExCommon_links_zc.sh ;

${install_dir}/RecExCommon_links_zc.sh :: ../share/RecExCommon_links_zc.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_links_zc.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_links_zc.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_links_zc.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/RecExCommon_links_cern_zc.sh ;

${install_dir}/RecExCommon_links_cern_zc.sh :: ../share/RecExCommon_links_cern_zc.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links_cern_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_links_cern_zc.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_links_cern_zc.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links_cern_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_links_cern_zc.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/RecExCommon_links.sh ;

${install_dir}/RecExCommon_links.sh :: ../share/RecExCommon_links.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_links.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_links.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_links.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/RecExCommon_links.csh ;

${install_dir}/RecExCommon_links.csh :: ../share/RecExCommon_links.csh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links.csh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_links.csh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_links.csh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_links.csh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_links.csh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/RecExCommon_runTimeFiles_zc.sh ;

${install_dir}/RecExCommon_runTimeFiles_zc.sh :: ../share/RecExCommon_runTimeFiles_zc.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_runTimeFiles_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_runTimeFiles_zc.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_runTimeFiles_zc.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_runTimeFiles_zc.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_runTimeFiles_zc.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/RecExCommon_dump.C ;

${install_dir}/RecExCommon_dump.C :: ../share/RecExCommon_dump.C
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_dump.C`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "RecExCommon_dump.C" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/RecExCommon_dump.C : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/RecExCommon_dump.C`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "RecExCommon_dump.C" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/manyrecotests.sh ;

${install_dir}/manyrecotests.sh :: ../Testing/manyrecotests.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../Testing/manyrecotests.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "manyrecotests.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../Testing/manyrecotests.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../Testing/manyrecotests.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "manyrecotests.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/recexcommon-links.py ;

${install_dir}/recexcommon-links.py :: ../share/recexcommon-links.py
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/recexcommon-links.py`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "recexcommon-links.py" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/recexcommon-links.py : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/recexcommon-links.py`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "recexcommon-links.py" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/qtest_run1.sh ;

${install_dir}/qtest_run1.sh :: ../share/qtest_run1.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/qtest_run1.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "qtest_run1.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/qtest_run1.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/qtest_run1.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "qtest_run1.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi


install_scriptsinstall :: ${install_dir}/qtest_run2.sh ;

${install_dir}/qtest_run2.sh :: ../share/qtest_run2.sh
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/qtest_run2.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "qtest_run2.sh" "$(install_dir)" "/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc49-opt/20.20.10/AtlasCore/20.20.10/External/ExternalPolicy/src/symlink.sh" "$($(package)_cmtpath)"; \
	fi

../share/qtest_run2.sh : ;

install_scriptsuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/qtest_run2.sh`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "qtest_run2.sh" "$(install_dir)" "$($(package)_cmtpath)"; \
	fi
#-- start of cleanup_header --------------

clean :: install_scriptsclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(install_scripts.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

install_scriptsclean ::
#-- end of cleanup_header ---------------
