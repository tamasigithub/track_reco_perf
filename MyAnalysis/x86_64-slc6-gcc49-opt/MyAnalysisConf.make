#-- start of make_header -----------------

#====================================
#  Document MyAnalysisConf
#
#   Generated Tue Feb 19 13:03:04 2019  by tkar
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyAnalysisConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysisConf_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysisConf

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisConf = $(MyAnalysis_tag)_MyAnalysisConf.make
cmt_local_tagfile_MyAnalysisConf = $(bin)$(MyAnalysis_tag)_MyAnalysisConf.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisConf = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysisConf = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysisConf)
#-include $(cmt_local_tagfile_MyAnalysisConf)

ifdef cmt_MyAnalysisConf_has_target_tag

cmt_final_setup_MyAnalysisConf = $(bin)setup_MyAnalysisConf.make
cmt_dependencies_in_MyAnalysisConf = $(bin)dependencies_MyAnalysisConf.in
#cmt_final_setup_MyAnalysisConf = $(bin)MyAnalysis_MyAnalysisConfsetup.make
cmt_local_MyAnalysisConf_makefile = $(bin)MyAnalysisConf.make

else

cmt_final_setup_MyAnalysisConf = $(bin)setup.make
cmt_dependencies_in_MyAnalysisConf = $(bin)dependencies.in
#cmt_final_setup_MyAnalysisConf = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysisConf_makefile = $(bin)MyAnalysisConf.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysisConf :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysisConf'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysisConf/
#MyAnalysisConf::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/genconfig_header
# Author: Wim Lavrijsen (WLavrijsen@lbl.gov)

# Use genconf.exe to create configurables python modules, then have the
# normal python install procedure take over.

.PHONY: MyAnalysisConf MyAnalysisConfclean

confpy  := MyAnalysisConf.py
conflib := $(bin)$(library_prefix)MyAnalysis.$(shlibsuffix)
confdb  := MyAnalysis.confdb
instdir := $(CMTINSTALLAREA)$(shared_install_subdir)/python/$(package)
product := $(instdir)/$(confpy)
initpy  := $(instdir)/__init__.py

ifdef GENCONF_ECHO
genconf_silent =
else
genconf_silent = $(silent)
endif

MyAnalysisConf :: MyAnalysisConfinstall

install :: MyAnalysisConfinstall

MyAnalysisConfinstall : /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis/$(confpy)
	@echo "Installing /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis in /nfs/dust/atlas/user/tkar/derivations/InstallArea/python" ; \
	 $(install_command) --exclude="*.py?" --exclude="__init__.py" --exclude="*.confdb" /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis /nfs/dust/atlas/user/tkar/derivations/InstallArea/python ; \

/nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis/$(confpy) : $(conflib) /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis
	$(genconf_silent) $(genconfig_cmd)   -o /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis -p $(package) \
	  --configurable-module=GaudiKernel.Proxy \
	  --configurable-default-name=Configurable.DefaultName \
	  --configurable-algorithm=ConfigurableAlgorithm \
	  --configurable-algtool=ConfigurableAlgTool \
	  --configurable-auditor=ConfigurableAuditor \
          --configurable-service=ConfigurableService \
	  -i ../$(tag)/$(library_prefix)MyAnalysis.$(shlibsuffix)

/nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis:
	@ if [ ! -d /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis ] ; then mkdir -p /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis ; fi ;

MyAnalysisConfclean :: MyAnalysisConfuninstall
	$(cleanup_silent) $(remove_command) /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis/$(confpy) /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis/$(confdb)

uninstall :: MyAnalysisConfuninstall

MyAnalysisConfuninstall ::
	@$(uninstall_command) /nfs/dust/atlas/user/tkar/derivations/InstallArea/python
libMyAnalysis_so_dependencies = ../x86_64-slc6-gcc49-opt/libMyAnalysis.so
#-- start of cleanup_header --------------

clean :: MyAnalysisConfclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysisConf.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisConfclean ::
#-- end of cleanup_header ---------------
