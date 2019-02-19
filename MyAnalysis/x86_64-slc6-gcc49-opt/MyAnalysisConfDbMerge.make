#-- start of make_header -----------------

#====================================
#  Document MyAnalysisConfDbMerge
#
#   Generated Tue Feb 19 13:03:05 2019  by tkar
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyAnalysisConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysisConfDbMerge_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysisConfDbMerge

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisConfDbMerge = $(MyAnalysis_tag)_MyAnalysisConfDbMerge.make
cmt_local_tagfile_MyAnalysisConfDbMerge = $(bin)$(MyAnalysis_tag)_MyAnalysisConfDbMerge.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisConfDbMerge = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysisConfDbMerge = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysisConfDbMerge)
#-include $(cmt_local_tagfile_MyAnalysisConfDbMerge)

ifdef cmt_MyAnalysisConfDbMerge_has_target_tag

cmt_final_setup_MyAnalysisConfDbMerge = $(bin)setup_MyAnalysisConfDbMerge.make
cmt_dependencies_in_MyAnalysisConfDbMerge = $(bin)dependencies_MyAnalysisConfDbMerge.in
#cmt_final_setup_MyAnalysisConfDbMerge = $(bin)MyAnalysis_MyAnalysisConfDbMergesetup.make
cmt_local_MyAnalysisConfDbMerge_makefile = $(bin)MyAnalysisConfDbMerge.make

else

cmt_final_setup_MyAnalysisConfDbMerge = $(bin)setup.make
cmt_dependencies_in_MyAnalysisConfDbMerge = $(bin)dependencies.in
#cmt_final_setup_MyAnalysisConfDbMerge = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysisConfDbMerge_makefile = $(bin)MyAnalysisConfDbMerge.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysisConfDbMerge :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysisConfDbMerge'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysisConfDbMerge/
#MyAnalysisConfDbMerge::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/merge_genconfDb_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>.confdb file into a single
# <project>.confdb file in the (lib) install area

.PHONY: MyAnalysisConfDbMerge MyAnalysisConfDbMergeclean

# default is already '#'
#genconfDb_comment_char := "'#'"

instdir      := ${CMTINSTALLAREA}/$(tag)
confDbRef    := /nfs/dust/atlas/user/tkar/derivations/MyAnalysis/genConf/MyAnalysis/MyAnalysis.confdb
stampConfDb  := $(confDbRef).stamp
mergedConfDb := $(instdir)/lib/$(project).confdb

MyAnalysisConfDbMerge :: $(stampConfDb) $(mergedConfDb)
	@:

.NOTPARALLEL : $(stampConfDb) $(mergedConfDb)

$(stampConfDb) $(mergedConfDb) :: $(confDbRef)
	@echo "Running merge_genconfDb  MyAnalysisConfDbMerge"
	$(merge_genconfDb_cmd) \
          --do-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)

MyAnalysisConfDbMergeclean ::
	$(cleanup_silent) $(merge_genconfDb_cmd) \
          --un-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	;
	$(cleanup_silent) $(remove_command) $(stampConfDb)
libMyAnalysis_so_dependencies = ../x86_64-slc6-gcc49-opt/libMyAnalysis.so
#-- start of cleanup_header --------------

clean :: MyAnalysisConfDbMergeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysisConfDbMerge.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisConfDbMergeclean ::
#-- end of cleanup_header ---------------
