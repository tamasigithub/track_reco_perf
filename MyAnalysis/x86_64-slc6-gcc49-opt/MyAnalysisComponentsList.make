#-- start of make_header -----------------

#====================================
#  Document MyAnalysisComponentsList
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

cmt_MyAnalysisComponentsList_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysisComponentsList_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysisComponentsList

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisComponentsList = $(MyAnalysis_tag)_MyAnalysisComponentsList.make
cmt_local_tagfile_MyAnalysisComponentsList = $(bin)$(MyAnalysis_tag)_MyAnalysisComponentsList.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisComponentsList = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysisComponentsList = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysisComponentsList)
#-include $(cmt_local_tagfile_MyAnalysisComponentsList)

ifdef cmt_MyAnalysisComponentsList_has_target_tag

cmt_final_setup_MyAnalysisComponentsList = $(bin)setup_MyAnalysisComponentsList.make
cmt_dependencies_in_MyAnalysisComponentsList = $(bin)dependencies_MyAnalysisComponentsList.in
#cmt_final_setup_MyAnalysisComponentsList = $(bin)MyAnalysis_MyAnalysisComponentsListsetup.make
cmt_local_MyAnalysisComponentsList_makefile = $(bin)MyAnalysisComponentsList.make

else

cmt_final_setup_MyAnalysisComponentsList = $(bin)setup.make
cmt_dependencies_in_MyAnalysisComponentsList = $(bin)dependencies.in
#cmt_final_setup_MyAnalysisComponentsList = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysisComponentsList_makefile = $(bin)MyAnalysisComponentsList.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysisComponentsList :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysisComponentsList'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysisComponentsList/
#MyAnalysisComponentsList::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
##
componentslistfile = MyAnalysis.components
COMPONENTSLIST_DIR = ../$(tag)
fulllibname = libMyAnalysis.$(shlibsuffix)

MyAnalysisComponentsList :: ${COMPONENTSLIST_DIR}/$(componentslistfile)
	@:

${COMPONENTSLIST_DIR}/$(componentslistfile) :: $(bin)$(fulllibname)
	@echo 'Generating componentslist file for $(fulllibname)'
	cd ../$(tag);$(listcomponents_cmd) --output ${COMPONENTSLIST_DIR}/$(componentslistfile) $(fulllibname)

install :: MyAnalysisComponentsListinstall
MyAnalysisComponentsListinstall :: MyAnalysisComponentsList

uninstall :: MyAnalysisComponentsListuninstall
MyAnalysisComponentsListuninstall :: MyAnalysisComponentsListclean

MyAnalysisComponentsListclean ::
	@echo 'Deleting $(componentslistfile)'
	@rm -f ${COMPONENTSLIST_DIR}/$(componentslistfile)

#-- start of cleanup_header --------------

clean :: MyAnalysisComponentsListclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysisComponentsList.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisComponentsListclean ::
#-- end of cleanup_header ---------------
