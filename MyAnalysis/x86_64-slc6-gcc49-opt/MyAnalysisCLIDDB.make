#-- start of make_header -----------------

#====================================
#  Document MyAnalysisCLIDDB
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

cmt_MyAnalysisCLIDDB_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysisCLIDDB_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysisCLIDDB

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisCLIDDB = $(MyAnalysis_tag)_MyAnalysisCLIDDB.make
cmt_local_tagfile_MyAnalysisCLIDDB = $(bin)$(MyAnalysis_tag)_MyAnalysisCLIDDB.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysisCLIDDB = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysisCLIDDB = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysisCLIDDB)
#-include $(cmt_local_tagfile_MyAnalysisCLIDDB)

ifdef cmt_MyAnalysisCLIDDB_has_target_tag

cmt_final_setup_MyAnalysisCLIDDB = $(bin)setup_MyAnalysisCLIDDB.make
cmt_dependencies_in_MyAnalysisCLIDDB = $(bin)dependencies_MyAnalysisCLIDDB.in
#cmt_final_setup_MyAnalysisCLIDDB = $(bin)MyAnalysis_MyAnalysisCLIDDBsetup.make
cmt_local_MyAnalysisCLIDDB_makefile = $(bin)MyAnalysisCLIDDB.make

else

cmt_final_setup_MyAnalysisCLIDDB = $(bin)setup.make
cmt_dependencies_in_MyAnalysisCLIDDB = $(bin)dependencies.in
#cmt_final_setup_MyAnalysisCLIDDB = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysisCLIDDB_makefile = $(bin)MyAnalysisCLIDDB.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysisCLIDDB :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysisCLIDDB'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysisCLIDDB/
#MyAnalysisCLIDDB::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
# File: cmt/fragments/genCLIDDB_header
# Author: Paolo Calafiura
# derived from genconf_header

# Use genCLIDDB_cmd to create package clid.db files

.PHONY: MyAnalysisCLIDDB MyAnalysisCLIDDBclean

outname := clid.db
cliddb  := MyAnalysis_$(outname)
instdir := $(CMTINSTALLAREA)/share
result  := $(instdir)/$(cliddb)
product := $(instdir)/$(outname)
conflib := $(bin)$(library_prefix)MyAnalysis.$(shlibsuffix)

MyAnalysisCLIDDB :: $(result)

$(instdir) :
	$(mkdir) -p $(instdir)

$(result) : $(conflib) $(product)
	@$(genCLIDDB_cmd) -p MyAnalysis -i$(product) -o $(result)

$(product) : $(instdir)
	touch $(product)

MyAnalysisCLIDDBclean ::
	$(cleanup_silent) $(uninstall_command) $(product) $(result)
	$(cleanup_silent) $(cmt_uninstallarea_command) $(product) $(result)

#-- start of cleanup_header --------------

clean :: MyAnalysisCLIDDBclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysisCLIDDB.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisCLIDDBclean ::
#-- end of cleanup_header ---------------
