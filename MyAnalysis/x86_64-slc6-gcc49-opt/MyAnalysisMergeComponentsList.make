#-- start of make_header -----------------

#====================================
#  Document MyAnalysisMergeComponentsList
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

cmt_MyAnalysisMergeComponentsList_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysisMergeComponentsList_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysisMergeComponentsList

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisMergeComponentsList = $(MyAnalysis_tag)_MyAnalysisMergeComponentsList.make
cmt_local_tagfile_MyAnalysisMergeComponentsList = $(bin)$(MyAnalysis_tag)_MyAnalysisMergeComponentsList.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisMergeComponentsList = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysisMergeComponentsList = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysisMergeComponentsList)
#-include $(cmt_local_tagfile_MyAnalysisMergeComponentsList)

ifdef cmt_MyAnalysisMergeComponentsList_has_target_tag

cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)setup_MyAnalysisMergeComponentsList.make
cmt_dependencies_in_MyAnalysisMergeComponentsList = $(bin)dependencies_MyAnalysisMergeComponentsList.in
#cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)MyAnalysis_MyAnalysisMergeComponentsListsetup.make
cmt_local_MyAnalysisMergeComponentsList_makefile = $(bin)MyAnalysisMergeComponentsList.make

else

cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)setup.make
cmt_dependencies_in_MyAnalysisMergeComponentsList = $(bin)dependencies.in
#cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysisMergeComponentsList_makefile = $(bin)MyAnalysisMergeComponentsList.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysisMergeComponentsList :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysisMergeComponentsList'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysisMergeComponentsList/
#MyAnalysisMergeComponentsList::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/merge_componentslist_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>.components file into a single
# <project>.components file in the (lib) install area
# If no InstallArea is present the fragment is dummy


.PHONY: MyAnalysisMergeComponentsList MyAnalysisMergeComponentsListclean

# default is already '#'
#genmap_comment_char := "'#'"

componentsListRef    := ../$(tag)/MyAnalysis.components

ifdef CMTINSTALLAREA
componentsListDir    := ${CMTINSTALLAREA}/$(tag)/lib
mergedComponentsList := $(componentsListDir)/$(project).components
stampComponentsList  := $(componentsListRef).stamp
else
componentsListDir    := ../$(tag)
mergedComponentsList :=
stampComponentsList  :=
endif

MyAnalysisMergeComponentsList :: $(stampComponentsList) $(mergedComponentsList)
	@:

.NOTPARALLEL : $(stampComponentsList) $(mergedComponentsList)

$(stampComponentsList) $(mergedComponentsList) :: $(componentsListRef)
	@echo "Running merge_componentslist  MyAnalysisMergeComponentsList"
	$(merge_componentslist_cmd) --do-merge \
         --input-file $(componentsListRef) --merged-file $(mergedComponentsList)

MyAnalysisMergeComponentsListclean ::
	$(cleanup_silent) $(merge_componentslist_cmd) --un-merge \
         --input-file $(componentsListRef) --merged-file $(mergedComponentsList) ;
	$(cleanup_silent) $(remove_command) $(stampComponentsList)
libMyAnalysis_so_dependencies = ../x86_64-slc6-gcc49-opt/libMyAnalysis.so
#-- start of cleanup_header --------------

clean :: MyAnalysisMergeComponentsListclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysisMergeComponentsList.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisMergeComponentsListclean ::
#-- end of cleanup_header ---------------
