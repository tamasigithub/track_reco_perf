#-- start of make_header -----------------

#====================================
#  Library MyAnalysis
#
#   Generated Tue Feb 19 13:02:43 2019  by tkar
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyAnalysis_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyAnalysis_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyAnalysis

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysis = $(MyAnalysis_tag)_MyAnalysis.make
cmt_local_tagfile_MyAnalysis = $(bin)$(MyAnalysis_tag)_MyAnalysis.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile_MyAnalysis = $(MyAnalysis_tag).make
cmt_local_tagfile_MyAnalysis = $(bin)$(MyAnalysis_tag).make

endif

include $(cmt_local_tagfile_MyAnalysis)
#-include $(cmt_local_tagfile_MyAnalysis)

ifdef cmt_MyAnalysis_has_target_tag

cmt_final_setup_MyAnalysis = $(bin)setup_MyAnalysis.make
cmt_dependencies_in_MyAnalysis = $(bin)dependencies_MyAnalysis.in
#cmt_final_setup_MyAnalysis = $(bin)MyAnalysis_MyAnalysissetup.make
cmt_local_MyAnalysis_makefile = $(bin)MyAnalysis.make

else

cmt_final_setup_MyAnalysis = $(bin)setup.make
cmt_dependencies_in_MyAnalysis = $(bin)dependencies.in
#cmt_final_setup_MyAnalysis = $(bin)MyAnalysissetup.make
cmt_local_MyAnalysis_makefile = $(bin)MyAnalysis.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MyAnalysissetup.make

#MyAnalysis :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MyAnalysis'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyAnalysis/
#MyAnalysis::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

MyAnalysislibname   = $(bin)$(library_prefix)MyAnalysis$(library_suffix)
MyAnalysislib       = $(MyAnalysislibname).a
MyAnalysisstamp     = $(bin)MyAnalysis.stamp
MyAnalysisshstamp   = $(bin)MyAnalysis.shstamp

MyAnalysis :: dirs  MyAnalysisLIB
	$(echo) "MyAnalysis ok"

#-- end of libary_header ----------------
#-- start of library_no_static ------

#MyAnalysisLIB :: $(MyAnalysislib) $(MyAnalysisshstamp)
MyAnalysisLIB :: $(MyAnalysisshstamp)
	$(echo) "MyAnalysis : library ok"

$(MyAnalysislib) :: $(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o
	$(lib_echo) "static library $@"
	$(lib_silent) cd $(bin); \
	  $(ar) $(MyAnalysislib) $?
	$(lib_silent) $(ranlib) $(MyAnalysislib)
	$(lib_silent) cat /dev/null >$(MyAnalysisstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

#
# We add one level of dependency upon the true shared library 
# (rather than simply upon the stamp file)
# this is for cases where the shared library has not been built
# while the stamp was created (error??) 
#

$(MyAnalysislibname).$(shlibsuffix) :: $(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o $(use_requirements) $(MyAnalysisstamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) $(shlibbuilder) $(shlibflags) -o $@ $(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o $(MyAnalysis_shlibflags)
	$(lib_silent) cat /dev/null >$(MyAnalysisstamp) && \
	  cat /dev/null >$(MyAnalysisshstamp)

$(MyAnalysisshstamp) :: $(MyAnalysislibname).$(shlibsuffix)
	$(lib_silent) if test -f $(MyAnalysislibname).$(shlibsuffix) ; then \
	  cat /dev/null >$(MyAnalysisstamp) && \
	  cat /dev/null >$(MyAnalysisshstamp) ; fi

MyAnalysisclean ::
	$(cleanup_echo) objects MyAnalysis
	$(cleanup_silent) /bin/rm -f $(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o
	$(cleanup_silent) /bin/rm -f $(patsubst %.o,%.d,$(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o) $(patsubst %.o,%.dep,$(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o) $(patsubst %.o,%.d.stamp,$(bin)MyAnalysis.o $(bin)MyPVAnalysis.o $(bin)MyAnalysis_load.o $(bin)MyAnalysis_entries.o)
	$(cleanup_silent) cd $(bin); /bin/rm -rf MyAnalysis_deps MyAnalysis_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
MyAnalysisinstallname = $(library_prefix)MyAnalysis$(library_suffix).$(shlibsuffix)

MyAnalysis :: MyAnalysisinstall ;

install :: MyAnalysisinstall ;

MyAnalysisinstall :: $(install_dir)/$(MyAnalysisinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(MyAnalysisinstallname) :: $(bin)$(MyAnalysisinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(MyAnalysisinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##MyAnalysisclean :: MyAnalysisuninstall

uninstall :: MyAnalysisuninstall ;

MyAnalysisuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(MyAnalysisinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of library_no_static ------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),MyAnalysisclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyAnalysis.d

$(bin)$(binobj)MyAnalysis.d :

$(bin)$(binobj)MyAnalysis.o : $(cmt_final_setup_MyAnalysis)

$(bin)$(binobj)MyAnalysis.o : $(src)MyAnalysis.cxx
	$(cpp_echo) $(src)MyAnalysis.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_cppflags) $(MyAnalysis_cxx_cppflags)  $(src)MyAnalysis.cxx
endif
endif

else
$(bin)MyAnalysis_dependencies.make : $(MyAnalysis_cxx_dependencies)

$(bin)MyAnalysis_dependencies.make : $(src)MyAnalysis.cxx

$(bin)$(binobj)MyAnalysis.o : $(MyAnalysis_cxx_dependencies)
	$(cpp_echo) $(src)MyAnalysis.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_cppflags) $(MyAnalysis_cxx_cppflags)  $(src)MyAnalysis.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),MyAnalysisclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyPVAnalysis.d

$(bin)$(binobj)MyPVAnalysis.d :

$(bin)$(binobj)MyPVAnalysis.o : $(cmt_final_setup_MyAnalysis)

$(bin)$(binobj)MyPVAnalysis.o : $(src)MyPVAnalysis.cxx
	$(cpp_echo) $(src)MyPVAnalysis.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyPVAnalysis_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyPVAnalysis_cppflags) $(MyPVAnalysis_cxx_cppflags)  $(src)MyPVAnalysis.cxx
endif
endif

else
$(bin)MyAnalysis_dependencies.make : $(MyPVAnalysis_cxx_dependencies)

$(bin)MyAnalysis_dependencies.make : $(src)MyPVAnalysis.cxx

$(bin)$(binobj)MyPVAnalysis.o : $(MyPVAnalysis_cxx_dependencies)
	$(cpp_echo) $(src)MyPVAnalysis.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyPVAnalysis_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyPVAnalysis_cppflags) $(MyPVAnalysis_cxx_cppflags)  $(src)MyPVAnalysis.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),MyAnalysisclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyAnalysis_load.d

$(bin)$(binobj)MyAnalysis_load.d :

$(bin)$(binobj)MyAnalysis_load.o : $(cmt_final_setup_MyAnalysis)

$(bin)$(binobj)MyAnalysis_load.o : $(src)components/MyAnalysis_load.cxx
	$(cpp_echo) $(src)components/MyAnalysis_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_load_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_load_cppflags) $(MyAnalysis_load_cxx_cppflags) -I../src/components $(src)components/MyAnalysis_load.cxx
endif
endif

else
$(bin)MyAnalysis_dependencies.make : $(MyAnalysis_load_cxx_dependencies)

$(bin)MyAnalysis_dependencies.make : $(src)components/MyAnalysis_load.cxx

$(bin)$(binobj)MyAnalysis_load.o : $(MyAnalysis_load_cxx_dependencies)
	$(cpp_echo) $(src)components/MyAnalysis_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_load_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_load_cppflags) $(MyAnalysis_load_cxx_cppflags) -I../src/components $(src)components/MyAnalysis_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),MyAnalysisclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyAnalysis_entries.d

$(bin)$(binobj)MyAnalysis_entries.d :

$(bin)$(binobj)MyAnalysis_entries.o : $(cmt_final_setup_MyAnalysis)

$(bin)$(binobj)MyAnalysis_entries.o : $(src)components/MyAnalysis_entries.cxx
	$(cpp_echo) $(src)components/MyAnalysis_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_entries_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_entries_cppflags) $(MyAnalysis_entries_cxx_cppflags) -I../src/components $(src)components/MyAnalysis_entries.cxx
endif
endif

else
$(bin)MyAnalysis_dependencies.make : $(MyAnalysis_entries_cxx_dependencies)

$(bin)MyAnalysis_dependencies.make : $(src)components/MyAnalysis_entries.cxx

$(bin)$(binobj)MyAnalysis_entries.o : $(MyAnalysis_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/MyAnalysis_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MyAnalysis_pp_cppflags) $(lib_MyAnalysis_pp_cppflags) $(MyAnalysis_entries_pp_cppflags) $(use_cppflags) $(MyAnalysis_cppflags) $(lib_MyAnalysis_cppflags) $(MyAnalysis_entries_cppflags) $(MyAnalysis_entries_cxx_cppflags) -I../src/components $(src)components/MyAnalysis_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: MyAnalysisclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MyAnalysis.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

MyAnalysisclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library MyAnalysis
	-$(cleanup_silent) cd $(bin) && \rm -f $(library_prefix)MyAnalysis$(library_suffix).a $(library_prefix)MyAnalysis$(library_suffix).$(shlibsuffix) MyAnalysis.stamp MyAnalysis.shstamp
#-- end of cleanup_library ---------------
