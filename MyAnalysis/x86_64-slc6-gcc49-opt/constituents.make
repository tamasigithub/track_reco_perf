
#-- start of constituents_header ------

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

tags      = $(tag),$(CMTEXTRATAGS)

MyAnalysis_tag = $(tag)

#cmt_local_tagfile = $(MyAnalysis_tag).make
cmt_local_tagfile = $(bin)$(MyAnalysis_tag).make

#-include $(cmt_local_tagfile)
include $(cmt_local_tagfile)

#cmt_local_setup = $(bin)setup$$$$.make
#cmt_local_setup = $(bin)$(package)setup$$$$.make
#cmt_final_setup = $(bin)MyAnalysissetup.make
cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)$(package)setup.make

cmt_build_library_linksstamp = $(bin)cmt_build_library_links.stamp
#--------------------------------------------------------

#cmt_lock_setup = /tmp/lock$(cmt_lock_pid).make
#cmt_temp_tag = /tmp/tag$(cmt_lock_pid).make

#first :: $(cmt_local_tagfile)
#	@echo $(cmt_local_tagfile) ok
#ifndef QUICK
#first :: $(cmt_final_setup) ;
#else
#first :: ;
#endif

##	@bin=`$(cmtexe) show macro_value bin`

#$(cmt_local_tagfile) : $(cmt_lock_setup)
#	@echo "#CMT> Error: $@: No such file" >&2; exit 1
#$(cmt_local_tagfile) :
#	@echo "#CMT> Warning: $@: No such file" >&2; exit
#	@echo "#CMT> Info: $@: No need to rebuild file" >&2; exit

#$(cmt_final_setup) : $(cmt_local_tagfile) 
#	$(echo) "(constituents.make) Rebuilding $@"
#	@if test ! -d $(@D); then $(mkdir) -p $(@D); fi; \
#	  if test -f $(cmt_local_setup); then /bin/rm -f $(cmt_local_setup); fi; \
#	  trap '/bin/rm -f $(cmt_local_setup)' 0 1 2 15; \
#	  $(cmtexe) -tag=$(tags) show setup >>$(cmt_local_setup); \
#	  if test ! -f $@; then \
#	    mv $(cmt_local_setup) $@; \
#	  else \
#	    if /usr/bin/diff $(cmt_local_setup) $@ >/dev/null ; then \
#	      : ; \
#	    else \
#	      mv $(cmt_local_setup) $@; \
#	    fi; \
#	  fi

#	@/bin/echo $@ ok   

#config :: checkuses
#	@exit 0
#checkuses : ;

env.make ::
	printenv >env.make.tmp; $(cmtexe) check files env.make.tmp env.make

ifndef QUICK
all :: build_library_links ;
else
all :: $(cmt_build_library_linksstamp) ;
endif

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

dirs :: requirements
	@if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi
#	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
#	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

#requirements :
#	@if test ! -r requirements ; then echo "No requirements file" ; fi

build_library_links : dirs
	$(echo) "(constituents.make) Rebuilding library links"; \
	 $(build_library_links)
#	if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi; \
#	$(build_library_links)

$(cmt_build_library_linksstamp) : $(cmt_final_setup) $(cmt_local_tagfile) $(bin)library_links.in
	$(echo) "(constituents.make) Rebuilding library links"; \
	 $(build_library_links) -f=$(bin)library_links.in -without_cmt
	$(silent) \touch $@

ifndef PEDANTIC
.DEFAULT ::
#.DEFAULT :
	$(echo) "(constituents.make) $@: No rule for such target" >&2
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of constituents_header ------
#-- start of group ------

all_groups :: all

all :: $(all_dependencies)  $(all_pre_constituents) $(all_constituents)  $(all_post_constituents)
	$(echo) "all ok."

#	@/bin/echo " all ok."

clean :: allclean

allclean ::  $(all_constituentsclean)
	$(echo) $(all_constituentsclean)
	$(echo) "allclean ok."

#	@echo $(all_constituentsclean)
#	@/bin/echo " allclean ok."

#-- end of group ------
#-- start of group ------

all_groups :: cmt_actions

cmt_actions :: $(cmt_actions_dependencies)  $(cmt_actions_pre_constituents) $(cmt_actions_constituents)  $(cmt_actions_post_constituents)
	$(echo) "cmt_actions ok."

#	@/bin/echo " cmt_actions ok."

clean :: allclean

cmt_actionsclean ::  $(cmt_actions_constituentsclean)
	$(echo) $(cmt_actions_constituentsclean)
	$(echo) "cmt_actionsclean ok."

#	@echo $(cmt_actions_constituentsclean)
#	@/bin/echo " cmt_actionsclean ok."

#-- end of group ------
#-- start of group ------

all_groups :: rulechecker

rulechecker :: $(rulechecker_dependencies)  $(rulechecker_pre_constituents) $(rulechecker_constituents)  $(rulechecker_post_constituents)
	$(echo) "rulechecker ok."

#	@/bin/echo " rulechecker ok."

clean :: allclean

rulecheckerclean ::  $(rulechecker_constituentsclean)
	$(echo) $(rulechecker_constituentsclean)
	$(echo) "rulecheckerclean ok."

#	@echo $(rulechecker_constituentsclean)
#	@/bin/echo " rulecheckerclean ok."

#-- end of group ------
#-- start of constituent ------

cmt_MyAnalysis_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysis_has_target_tag

cmt_local_tagfile_MyAnalysis = $(bin)$(MyAnalysis_tag)_MyAnalysis.make
cmt_final_setup_MyAnalysis = $(bin)setup_MyAnalysis.make
cmt_local_MyAnalysis_makefile = $(bin)MyAnalysis.make

MyAnalysis_extratags = -tag_add=target_MyAnalysis

else

cmt_local_tagfile_MyAnalysis = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysis = $(bin)setup.make
cmt_local_MyAnalysis_makefile = $(bin)MyAnalysis.make

endif

not_MyAnalysis_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysis_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisdirs :
	@if test ! -d $(bin)MyAnalysis; then $(mkdir) -p $(bin)MyAnalysis; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysis
else
MyAnalysisdirs : ;
endif

ifdef cmt_MyAnalysis_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysis_makefile) : $(MyAnalysis_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_makefile) MyAnalysis
else
$(cmt_local_MyAnalysis_makefile) : $(MyAnalysis_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis) ] || \
	  $(not_MyAnalysis_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_makefile) MyAnalysis; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysis_makefile) : $(MyAnalysis_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis.in -tag=$(tags) $(MyAnalysis_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_makefile) MyAnalysis
else
$(cmt_local_MyAnalysis_makefile) : $(MyAnalysis_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysis.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis) ] || \
	  $(not_MyAnalysis_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis.in -tag=$(tags) $(MyAnalysis_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_makefile) MyAnalysis; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysis_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysis_makefile) MyAnalysis

MyAnalysis :: $(MyAnalysis_dependencies) $(cmt_local_MyAnalysis_makefile) dirs MyAnalysisdirs
	$(echo) "(constituents.make) Starting MyAnalysis"
	@if test -f $(cmt_local_MyAnalysis_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_makefile) MyAnalysis; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_makefile) MyAnalysis
	$(echo) "(constituents.make) MyAnalysis done"

clean :: MyAnalysisclean ;

MyAnalysisclean :: $(MyAnalysisclean_dependencies) ##$(cmt_local_MyAnalysis_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisclean"
	@-if test -f $(cmt_local_MyAnalysis_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_makefile) MyAnalysisclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_makefile) MyAnalysisclean

##	  /bin/rm -f $(cmt_local_MyAnalysis_makefile) $(bin)MyAnalysis_dependencies.make

install :: MyAnalysisinstall ;

MyAnalysisinstall :: $(MyAnalysis_dependencies) $(cmt_local_MyAnalysis_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysis_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisuninstall

$(foreach d,$(MyAnalysis_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisuninstall))

MyAnalysisuninstall : $(MyAnalysisuninstall_dependencies) ##$(cmt_local_MyAnalysis_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysis_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysis"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysis done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisConf_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisConf_has_target_tag

cmt_local_tagfile_MyAnalysisConf = $(bin)$(MyAnalysis_tag)_MyAnalysisConf.make
cmt_final_setup_MyAnalysisConf = $(bin)setup_MyAnalysisConf.make
cmt_local_MyAnalysisConf_makefile = $(bin)MyAnalysisConf.make

MyAnalysisConf_extratags = -tag_add=target_MyAnalysisConf

else

cmt_local_tagfile_MyAnalysisConf = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisConf = $(bin)setup.make
cmt_local_MyAnalysisConf_makefile = $(bin)MyAnalysisConf.make

endif

not_MyAnalysisConf_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisConf_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisConfdirs :
	@if test ! -d $(bin)MyAnalysisConf; then $(mkdir) -p $(bin)MyAnalysisConf; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisConf
else
MyAnalysisConfdirs : ;
endif

ifdef cmt_MyAnalysisConf_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisConf_makefile) : $(MyAnalysisConf_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisConf.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisConf_extratags) build constituent_config -out=$(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf
else
$(cmt_local_MyAnalysisConf_makefile) : $(MyAnalysisConf_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisConf) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisConf) ] || \
	  $(not_MyAnalysisConf_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisConf.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisConf_extratags) build constituent_config -out=$(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisConf_makefile) : $(MyAnalysisConf_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisConf.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisConf.in -tag=$(tags) $(MyAnalysisConf_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf
else
$(cmt_local_MyAnalysisConf_makefile) : $(MyAnalysisConf_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisConf.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisConf) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisConf) ] || \
	  $(not_MyAnalysisConf_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisConf.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisConf.in -tag=$(tags) $(MyAnalysisConf_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisConf_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf

MyAnalysisConf :: $(MyAnalysisConf_dependencies) $(cmt_local_MyAnalysisConf_makefile) dirs MyAnalysisConfdirs
	$(echo) "(constituents.make) Starting MyAnalysisConf"
	@if test -f $(cmt_local_MyAnalysisConf_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) MyAnalysisConf
	$(echo) "(constituents.make) MyAnalysisConf done"

clean :: MyAnalysisConfclean ;

MyAnalysisConfclean :: $(MyAnalysisConfclean_dependencies) ##$(cmt_local_MyAnalysisConf_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisConfclean"
	@-if test -f $(cmt_local_MyAnalysisConf_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) MyAnalysisConfclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisConfclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) MyAnalysisConfclean

##	  /bin/rm -f $(cmt_local_MyAnalysisConf_makefile) $(bin)MyAnalysisConf_dependencies.make

install :: MyAnalysisConfinstall ;

MyAnalysisConfinstall :: $(MyAnalysisConf_dependencies) $(cmt_local_MyAnalysisConf_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisConf_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisConfuninstall

$(foreach d,$(MyAnalysisConf_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisConfuninstall))

MyAnalysisConfuninstall : $(MyAnalysisConfuninstall_dependencies) ##$(cmt_local_MyAnalysisConf_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisConf_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisConf_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisConfuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisConf"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisConf done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysis_python_init_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysis_python_init_has_target_tag

cmt_local_tagfile_MyAnalysis_python_init = $(bin)$(MyAnalysis_tag)_MyAnalysis_python_init.make
cmt_final_setup_MyAnalysis_python_init = $(bin)setup_MyAnalysis_python_init.make
cmt_local_MyAnalysis_python_init_makefile = $(bin)MyAnalysis_python_init.make

MyAnalysis_python_init_extratags = -tag_add=target_MyAnalysis_python_init

else

cmt_local_tagfile_MyAnalysis_python_init = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysis_python_init = $(bin)setup.make
cmt_local_MyAnalysis_python_init_makefile = $(bin)MyAnalysis_python_init.make

endif

not_MyAnalysis_python_init_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysis_python_init_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysis_python_initdirs :
	@if test ! -d $(bin)MyAnalysis_python_init; then $(mkdir) -p $(bin)MyAnalysis_python_init; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysis_python_init
else
MyAnalysis_python_initdirs : ;
endif

ifdef cmt_MyAnalysis_python_init_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysis_python_init_makefile) : $(MyAnalysis_python_init_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_python_init.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_python_init_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init
else
$(cmt_local_MyAnalysis_python_init_makefile) : $(MyAnalysis_python_init_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_python_init) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_python_init) ] || \
	  $(not_MyAnalysis_python_init_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_python_init.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_python_init_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysis_python_init_makefile) : $(MyAnalysis_python_init_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_python_init.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_python_init.in -tag=$(tags) $(MyAnalysis_python_init_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init
else
$(cmt_local_MyAnalysis_python_init_makefile) : $(MyAnalysis_python_init_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysis_python_init.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_python_init) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_python_init) ] || \
	  $(not_MyAnalysis_python_init_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_python_init.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_python_init.in -tag=$(tags) $(MyAnalysis_python_init_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysis_python_init_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init

MyAnalysis_python_init :: $(MyAnalysis_python_init_dependencies) $(cmt_local_MyAnalysis_python_init_makefile) dirs MyAnalysis_python_initdirs
	$(echo) "(constituents.make) Starting MyAnalysis_python_init"
	@if test -f $(cmt_local_MyAnalysis_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_init
	$(echo) "(constituents.make) MyAnalysis_python_init done"

clean :: MyAnalysis_python_initclean ;

MyAnalysis_python_initclean :: $(MyAnalysis_python_initclean_dependencies) ##$(cmt_local_MyAnalysis_python_init_makefile)
	$(echo) "(constituents.make) Starting MyAnalysis_python_initclean"
	@-if test -f $(cmt_local_MyAnalysis_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_initclean; \
	fi
	$(echo) "(constituents.make) MyAnalysis_python_initclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) MyAnalysis_python_initclean

##	  /bin/rm -f $(cmt_local_MyAnalysis_python_init_makefile) $(bin)MyAnalysis_python_init_dependencies.make

install :: MyAnalysis_python_initinstall ;

MyAnalysis_python_initinstall :: $(MyAnalysis_python_init_dependencies) $(cmt_local_MyAnalysis_python_init_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysis_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysis_python_inituninstall

$(foreach d,$(MyAnalysis_python_init_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysis_python_inituninstall))

MyAnalysis_python_inituninstall : $(MyAnalysis_python_inituninstall_dependencies) ##$(cmt_local_MyAnalysis_python_init_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysis_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_python_init_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysis_python_inituninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysis_python_init"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysis_python_init done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisConfDbMerge_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisConfDbMerge_has_target_tag

cmt_local_tagfile_MyAnalysisConfDbMerge = $(bin)$(MyAnalysis_tag)_MyAnalysisConfDbMerge.make
cmt_final_setup_MyAnalysisConfDbMerge = $(bin)setup_MyAnalysisConfDbMerge.make
cmt_local_MyAnalysisConfDbMerge_makefile = $(bin)MyAnalysisConfDbMerge.make

MyAnalysisConfDbMerge_extratags = -tag_add=target_MyAnalysisConfDbMerge

else

cmt_local_tagfile_MyAnalysisConfDbMerge = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisConfDbMerge = $(bin)setup.make
cmt_local_MyAnalysisConfDbMerge_makefile = $(bin)MyAnalysisConfDbMerge.make

endif

not_MyAnalysisConfDbMerge_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisConfDbMerge_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisConfDbMergedirs :
	@if test ! -d $(bin)MyAnalysisConfDbMerge; then $(mkdir) -p $(bin)MyAnalysisConfDbMerge; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisConfDbMerge
else
MyAnalysisConfDbMergedirs : ;
endif

ifdef cmt_MyAnalysisConfDbMerge_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisConfDbMerge_makefile) : $(MyAnalysisConfDbMerge_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisConfDbMerge.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisConfDbMerge_extratags) build constituent_config -out=$(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge
else
$(cmt_local_MyAnalysisConfDbMerge_makefile) : $(MyAnalysisConfDbMerge_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisConfDbMerge) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisConfDbMerge) ] || \
	  $(not_MyAnalysisConfDbMerge_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisConfDbMerge.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisConfDbMerge_extratags) build constituent_config -out=$(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisConfDbMerge_makefile) : $(MyAnalysisConfDbMerge_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisConfDbMerge.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisConfDbMerge.in -tag=$(tags) $(MyAnalysisConfDbMerge_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge
else
$(cmt_local_MyAnalysisConfDbMerge_makefile) : $(MyAnalysisConfDbMerge_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisConfDbMerge.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisConfDbMerge) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisConfDbMerge) ] || \
	  $(not_MyAnalysisConfDbMerge_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisConfDbMerge.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisConfDbMerge.in -tag=$(tags) $(MyAnalysisConfDbMerge_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisConfDbMerge_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge

MyAnalysisConfDbMerge :: $(MyAnalysisConfDbMerge_dependencies) $(cmt_local_MyAnalysisConfDbMerge_makefile) dirs MyAnalysisConfDbMergedirs
	$(echo) "(constituents.make) Starting MyAnalysisConfDbMerge"
	@if test -f $(cmt_local_MyAnalysisConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMerge
	$(echo) "(constituents.make) MyAnalysisConfDbMerge done"

clean :: MyAnalysisConfDbMergeclean ;

MyAnalysisConfDbMergeclean :: $(MyAnalysisConfDbMergeclean_dependencies) ##$(cmt_local_MyAnalysisConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisConfDbMergeclean"
	@-if test -f $(cmt_local_MyAnalysisConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMergeclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisConfDbMergeclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) MyAnalysisConfDbMergeclean

##	  /bin/rm -f $(cmt_local_MyAnalysisConfDbMerge_makefile) $(bin)MyAnalysisConfDbMerge_dependencies.make

install :: MyAnalysisConfDbMergeinstall ;

MyAnalysisConfDbMergeinstall :: $(MyAnalysisConfDbMerge_dependencies) $(cmt_local_MyAnalysisConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisConfDbMergeuninstall

$(foreach d,$(MyAnalysisConfDbMerge_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisConfDbMergeuninstall))

MyAnalysisConfDbMergeuninstall : $(MyAnalysisConfDbMergeuninstall_dependencies) ##$(cmt_local_MyAnalysisConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisConfDbMerge_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisConfDbMergeuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisConfDbMerge"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisConfDbMerge done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisComponentsList_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisComponentsList_has_target_tag

cmt_local_tagfile_MyAnalysisComponentsList = $(bin)$(MyAnalysis_tag)_MyAnalysisComponentsList.make
cmt_final_setup_MyAnalysisComponentsList = $(bin)setup_MyAnalysisComponentsList.make
cmt_local_MyAnalysisComponentsList_makefile = $(bin)MyAnalysisComponentsList.make

MyAnalysisComponentsList_extratags = -tag_add=target_MyAnalysisComponentsList

else

cmt_local_tagfile_MyAnalysisComponentsList = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisComponentsList = $(bin)setup.make
cmt_local_MyAnalysisComponentsList_makefile = $(bin)MyAnalysisComponentsList.make

endif

not_MyAnalysisComponentsList_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisComponentsList_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisComponentsListdirs :
	@if test ! -d $(bin)MyAnalysisComponentsList; then $(mkdir) -p $(bin)MyAnalysisComponentsList; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisComponentsList
else
MyAnalysisComponentsListdirs : ;
endif

ifdef cmt_MyAnalysisComponentsList_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisComponentsList_makefile) : $(MyAnalysisComponentsList_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisComponentsList.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisComponentsList_extratags) build constituent_config -out=$(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList
else
$(cmt_local_MyAnalysisComponentsList_makefile) : $(MyAnalysisComponentsList_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisComponentsList) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisComponentsList) ] || \
	  $(not_MyAnalysisComponentsList_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisComponentsList.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisComponentsList_extratags) build constituent_config -out=$(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisComponentsList_makefile) : $(MyAnalysisComponentsList_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisComponentsList.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisComponentsList.in -tag=$(tags) $(MyAnalysisComponentsList_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList
else
$(cmt_local_MyAnalysisComponentsList_makefile) : $(MyAnalysisComponentsList_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisComponentsList.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisComponentsList) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisComponentsList) ] || \
	  $(not_MyAnalysisComponentsList_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisComponentsList.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisComponentsList.in -tag=$(tags) $(MyAnalysisComponentsList_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisComponentsList_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList

MyAnalysisComponentsList :: $(MyAnalysisComponentsList_dependencies) $(cmt_local_MyAnalysisComponentsList_makefile) dirs MyAnalysisComponentsListdirs
	$(echo) "(constituents.make) Starting MyAnalysisComponentsList"
	@if test -f $(cmt_local_MyAnalysisComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsList
	$(echo) "(constituents.make) MyAnalysisComponentsList done"

clean :: MyAnalysisComponentsListclean ;

MyAnalysisComponentsListclean :: $(MyAnalysisComponentsListclean_dependencies) ##$(cmt_local_MyAnalysisComponentsList_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisComponentsListclean"
	@-if test -f $(cmt_local_MyAnalysisComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsListclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisComponentsListclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) MyAnalysisComponentsListclean

##	  /bin/rm -f $(cmt_local_MyAnalysisComponentsList_makefile) $(bin)MyAnalysisComponentsList_dependencies.make

install :: MyAnalysisComponentsListinstall ;

MyAnalysisComponentsListinstall :: $(MyAnalysisComponentsList_dependencies) $(cmt_local_MyAnalysisComponentsList_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisComponentsListuninstall

$(foreach d,$(MyAnalysisComponentsList_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisComponentsListuninstall))

MyAnalysisComponentsListuninstall : $(MyAnalysisComponentsListuninstall_dependencies) ##$(cmt_local_MyAnalysisComponentsList_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisComponentsList_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisComponentsListuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisComponentsList"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisComponentsList done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisMergeComponentsList_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisMergeComponentsList_has_target_tag

cmt_local_tagfile_MyAnalysisMergeComponentsList = $(bin)$(MyAnalysis_tag)_MyAnalysisMergeComponentsList.make
cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)setup_MyAnalysisMergeComponentsList.make
cmt_local_MyAnalysisMergeComponentsList_makefile = $(bin)MyAnalysisMergeComponentsList.make

MyAnalysisMergeComponentsList_extratags = -tag_add=target_MyAnalysisMergeComponentsList

else

cmt_local_tagfile_MyAnalysisMergeComponentsList = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisMergeComponentsList = $(bin)setup.make
cmt_local_MyAnalysisMergeComponentsList_makefile = $(bin)MyAnalysisMergeComponentsList.make

endif

not_MyAnalysisMergeComponentsList_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisMergeComponentsList_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisMergeComponentsListdirs :
	@if test ! -d $(bin)MyAnalysisMergeComponentsList; then $(mkdir) -p $(bin)MyAnalysisMergeComponentsList; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisMergeComponentsList
else
MyAnalysisMergeComponentsListdirs : ;
endif

ifdef cmt_MyAnalysisMergeComponentsList_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisMergeComponentsList_makefile) : $(MyAnalysisMergeComponentsList_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisMergeComponentsList.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisMergeComponentsList_extratags) build constituent_config -out=$(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList
else
$(cmt_local_MyAnalysisMergeComponentsList_makefile) : $(MyAnalysisMergeComponentsList_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisMergeComponentsList) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisMergeComponentsList) ] || \
	  $(not_MyAnalysisMergeComponentsList_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisMergeComponentsList.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisMergeComponentsList_extratags) build constituent_config -out=$(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisMergeComponentsList_makefile) : $(MyAnalysisMergeComponentsList_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisMergeComponentsList.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisMergeComponentsList.in -tag=$(tags) $(MyAnalysisMergeComponentsList_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList
else
$(cmt_local_MyAnalysisMergeComponentsList_makefile) : $(MyAnalysisMergeComponentsList_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisMergeComponentsList.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisMergeComponentsList) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisMergeComponentsList) ] || \
	  $(not_MyAnalysisMergeComponentsList_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisMergeComponentsList.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisMergeComponentsList.in -tag=$(tags) $(MyAnalysisMergeComponentsList_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisMergeComponentsList_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList

MyAnalysisMergeComponentsList :: $(MyAnalysisMergeComponentsList_dependencies) $(cmt_local_MyAnalysisMergeComponentsList_makefile) dirs MyAnalysisMergeComponentsListdirs
	$(echo) "(constituents.make) Starting MyAnalysisMergeComponentsList"
	@if test -f $(cmt_local_MyAnalysisMergeComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsList
	$(echo) "(constituents.make) MyAnalysisMergeComponentsList done"

clean :: MyAnalysisMergeComponentsListclean ;

MyAnalysisMergeComponentsListclean :: $(MyAnalysisMergeComponentsListclean_dependencies) ##$(cmt_local_MyAnalysisMergeComponentsList_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisMergeComponentsListclean"
	@-if test -f $(cmt_local_MyAnalysisMergeComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsListclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisMergeComponentsListclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) MyAnalysisMergeComponentsListclean

##	  /bin/rm -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) $(bin)MyAnalysisMergeComponentsList_dependencies.make

install :: MyAnalysisMergeComponentsListinstall ;

MyAnalysisMergeComponentsListinstall :: $(MyAnalysisMergeComponentsList_dependencies) $(cmt_local_MyAnalysisMergeComponentsList_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisMergeComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisMergeComponentsListuninstall

$(foreach d,$(MyAnalysisMergeComponentsList_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisMergeComponentsListuninstall))

MyAnalysisMergeComponentsListuninstall : $(MyAnalysisMergeComponentsListuninstall_dependencies) ##$(cmt_local_MyAnalysisMergeComponentsList_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisMergeComponentsList_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisMergeComponentsList_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisMergeComponentsListuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisMergeComponentsList"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisMergeComponentsList done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysis_optdebug_library_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysis_optdebug_library_has_target_tag

cmt_local_tagfile_MyAnalysis_optdebug_library = $(bin)$(MyAnalysis_tag)_MyAnalysis_optdebug_library.make
cmt_final_setup_MyAnalysis_optdebug_library = $(bin)setup_MyAnalysis_optdebug_library.make
cmt_local_MyAnalysis_optdebug_library_makefile = $(bin)MyAnalysis_optdebug_library.make

MyAnalysis_optdebug_library_extratags = -tag_add=target_MyAnalysis_optdebug_library

else

cmt_local_tagfile_MyAnalysis_optdebug_library = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysis_optdebug_library = $(bin)setup.make
cmt_local_MyAnalysis_optdebug_library_makefile = $(bin)MyAnalysis_optdebug_library.make

endif

not_MyAnalysis_optdebug_library_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysis_optdebug_library_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysis_optdebug_librarydirs :
	@if test ! -d $(bin)MyAnalysis_optdebug_library; then $(mkdir) -p $(bin)MyAnalysis_optdebug_library; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysis_optdebug_library
else
MyAnalysis_optdebug_librarydirs : ;
endif

ifdef cmt_MyAnalysis_optdebug_library_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysis_optdebug_library_makefile) : $(MyAnalysis_optdebug_library_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_optdebug_library.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_optdebug_library_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library
else
$(cmt_local_MyAnalysis_optdebug_library_makefile) : $(MyAnalysis_optdebug_library_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_optdebug_library) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_optdebug_library) ] || \
	  $(not_MyAnalysis_optdebug_library_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_optdebug_library.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_optdebug_library_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysis_optdebug_library_makefile) : $(MyAnalysis_optdebug_library_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_optdebug_library.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_optdebug_library.in -tag=$(tags) $(MyAnalysis_optdebug_library_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library
else
$(cmt_local_MyAnalysis_optdebug_library_makefile) : $(MyAnalysis_optdebug_library_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysis_optdebug_library.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_optdebug_library) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_optdebug_library) ] || \
	  $(not_MyAnalysis_optdebug_library_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_optdebug_library.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_optdebug_library.in -tag=$(tags) $(MyAnalysis_optdebug_library_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysis_optdebug_library_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library

MyAnalysis_optdebug_library :: $(MyAnalysis_optdebug_library_dependencies) $(cmt_local_MyAnalysis_optdebug_library_makefile) dirs MyAnalysis_optdebug_librarydirs
	$(echo) "(constituents.make) Starting MyAnalysis_optdebug_library"
	@if test -f $(cmt_local_MyAnalysis_optdebug_library_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_library
	$(echo) "(constituents.make) MyAnalysis_optdebug_library done"

clean :: MyAnalysis_optdebug_libraryclean ;

MyAnalysis_optdebug_libraryclean :: $(MyAnalysis_optdebug_libraryclean_dependencies) ##$(cmt_local_MyAnalysis_optdebug_library_makefile)
	$(echo) "(constituents.make) Starting MyAnalysis_optdebug_libraryclean"
	@-if test -f $(cmt_local_MyAnalysis_optdebug_library_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_libraryclean; \
	fi
	$(echo) "(constituents.make) MyAnalysis_optdebug_libraryclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) MyAnalysis_optdebug_libraryclean

##	  /bin/rm -f $(cmt_local_MyAnalysis_optdebug_library_makefile) $(bin)MyAnalysis_optdebug_library_dependencies.make

install :: MyAnalysis_optdebug_libraryinstall ;

MyAnalysis_optdebug_libraryinstall :: $(MyAnalysis_optdebug_library_dependencies) $(cmt_local_MyAnalysis_optdebug_library_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysis_optdebug_library_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysis_optdebug_libraryuninstall

$(foreach d,$(MyAnalysis_optdebug_library_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysis_optdebug_libraryuninstall))

MyAnalysis_optdebug_libraryuninstall : $(MyAnalysis_optdebug_libraryuninstall_dependencies) ##$(cmt_local_MyAnalysis_optdebug_library_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysis_optdebug_library_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_optdebug_library_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysis_optdebug_libraryuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysis_optdebug_library"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysis_optdebug_library done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisCLIDDB_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisCLIDDB_has_target_tag

cmt_local_tagfile_MyAnalysisCLIDDB = $(bin)$(MyAnalysis_tag)_MyAnalysisCLIDDB.make
cmt_final_setup_MyAnalysisCLIDDB = $(bin)setup_MyAnalysisCLIDDB.make
cmt_local_MyAnalysisCLIDDB_makefile = $(bin)MyAnalysisCLIDDB.make

MyAnalysisCLIDDB_extratags = -tag_add=target_MyAnalysisCLIDDB

else

cmt_local_tagfile_MyAnalysisCLIDDB = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisCLIDDB = $(bin)setup.make
cmt_local_MyAnalysisCLIDDB_makefile = $(bin)MyAnalysisCLIDDB.make

endif

not_MyAnalysisCLIDDB_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisCLIDDB_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisCLIDDBdirs :
	@if test ! -d $(bin)MyAnalysisCLIDDB; then $(mkdir) -p $(bin)MyAnalysisCLIDDB; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisCLIDDB
else
MyAnalysisCLIDDBdirs : ;
endif

ifdef cmt_MyAnalysisCLIDDB_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisCLIDDB_makefile) : $(MyAnalysisCLIDDB_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisCLIDDB.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisCLIDDB_extratags) build constituent_config -out=$(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB
else
$(cmt_local_MyAnalysisCLIDDB_makefile) : $(MyAnalysisCLIDDB_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisCLIDDB) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisCLIDDB) ] || \
	  $(not_MyAnalysisCLIDDB_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisCLIDDB.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisCLIDDB_extratags) build constituent_config -out=$(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisCLIDDB_makefile) : $(MyAnalysisCLIDDB_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisCLIDDB.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisCLIDDB.in -tag=$(tags) $(MyAnalysisCLIDDB_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB
else
$(cmt_local_MyAnalysisCLIDDB_makefile) : $(MyAnalysisCLIDDB_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisCLIDDB.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisCLIDDB) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisCLIDDB) ] || \
	  $(not_MyAnalysisCLIDDB_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisCLIDDB.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisCLIDDB.in -tag=$(tags) $(MyAnalysisCLIDDB_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisCLIDDB_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB

MyAnalysisCLIDDB :: $(MyAnalysisCLIDDB_dependencies) $(cmt_local_MyAnalysisCLIDDB_makefile) dirs MyAnalysisCLIDDBdirs
	$(echo) "(constituents.make) Starting MyAnalysisCLIDDB"
	@if test -f $(cmt_local_MyAnalysisCLIDDB_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDB
	$(echo) "(constituents.make) MyAnalysisCLIDDB done"

clean :: MyAnalysisCLIDDBclean ;

MyAnalysisCLIDDBclean :: $(MyAnalysisCLIDDBclean_dependencies) ##$(cmt_local_MyAnalysisCLIDDB_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisCLIDDBclean"
	@-if test -f $(cmt_local_MyAnalysisCLIDDB_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDBclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisCLIDDBclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) MyAnalysisCLIDDBclean

##	  /bin/rm -f $(cmt_local_MyAnalysisCLIDDB_makefile) $(bin)MyAnalysisCLIDDB_dependencies.make

install :: MyAnalysisCLIDDBinstall ;

MyAnalysisCLIDDBinstall :: $(MyAnalysisCLIDDB_dependencies) $(cmt_local_MyAnalysisCLIDDB_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisCLIDDB_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisCLIDDBuninstall

$(foreach d,$(MyAnalysisCLIDDB_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisCLIDDBuninstall))

MyAnalysisCLIDDBuninstall : $(MyAnalysisCLIDDBuninstall_dependencies) ##$(cmt_local_MyAnalysisCLIDDB_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisCLIDDB_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisCLIDDB_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisCLIDDBuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisCLIDDB"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisCLIDDB done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysisrchk_has_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysisrchk_has_target_tag

cmt_local_tagfile_MyAnalysisrchk = $(bin)$(MyAnalysis_tag)_MyAnalysisrchk.make
cmt_final_setup_MyAnalysisrchk = $(bin)setup_MyAnalysisrchk.make
cmt_local_MyAnalysisrchk_makefile = $(bin)MyAnalysisrchk.make

MyAnalysisrchk_extratags = -tag_add=target_MyAnalysisrchk

else

cmt_local_tagfile_MyAnalysisrchk = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysisrchk = $(bin)setup.make
cmt_local_MyAnalysisrchk_makefile = $(bin)MyAnalysisrchk.make

endif

not_MyAnalysisrchk_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysisrchk_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysisrchkdirs :
	@if test ! -d $(bin)MyAnalysisrchk; then $(mkdir) -p $(bin)MyAnalysisrchk; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysisrchk
else
MyAnalysisrchkdirs : ;
endif

ifdef cmt_MyAnalysisrchk_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysisrchk_makefile) : $(MyAnalysisrchk_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisrchk.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisrchk_extratags) build constituent_config -out=$(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk
else
$(cmt_local_MyAnalysisrchk_makefile) : $(MyAnalysisrchk_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisrchk) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisrchk) ] || \
	  $(not_MyAnalysisrchk_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisrchk.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysisrchk_extratags) build constituent_config -out=$(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysisrchk_makefile) : $(MyAnalysisrchk_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysisrchk.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisrchk.in -tag=$(tags) $(MyAnalysisrchk_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk
else
$(cmt_local_MyAnalysisrchk_makefile) : $(MyAnalysisrchk_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysisrchk.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysisrchk) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysisrchk) ] || \
	  $(not_MyAnalysisrchk_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysisrchk.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysisrchk.in -tag=$(tags) $(MyAnalysisrchk_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysisrchk_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk

MyAnalysisrchk :: $(MyAnalysisrchk_dependencies) $(cmt_local_MyAnalysisrchk_makefile) dirs MyAnalysisrchkdirs
	$(echo) "(constituents.make) Starting MyAnalysisrchk"
	@if test -f $(cmt_local_MyAnalysisrchk_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchk
	$(echo) "(constituents.make) MyAnalysisrchk done"

clean :: MyAnalysisrchkclean ;

MyAnalysisrchkclean :: $(MyAnalysisrchkclean_dependencies) ##$(cmt_local_MyAnalysisrchk_makefile)
	$(echo) "(constituents.make) Starting MyAnalysisrchkclean"
	@-if test -f $(cmt_local_MyAnalysisrchk_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchkclean; \
	fi
	$(echo) "(constituents.make) MyAnalysisrchkclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) MyAnalysisrchkclean

##	  /bin/rm -f $(cmt_local_MyAnalysisrchk_makefile) $(bin)MyAnalysisrchk_dependencies.make

install :: MyAnalysisrchkinstall ;

MyAnalysisrchkinstall :: $(MyAnalysisrchk_dependencies) $(cmt_local_MyAnalysisrchk_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysisrchk_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysisrchkuninstall

$(foreach d,$(MyAnalysisrchk_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysisrchkuninstall))

MyAnalysisrchkuninstall : $(MyAnalysisrchkuninstall_dependencies) ##$(cmt_local_MyAnalysisrchk_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysisrchk_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysisrchk_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysisrchkuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysisrchk"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysisrchk done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_install_root_include_path_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_install_root_include_path_has_target_tag

cmt_local_tagfile_install_root_include_path = $(bin)$(MyAnalysis_tag)_install_root_include_path.make
cmt_final_setup_install_root_include_path = $(bin)setup_install_root_include_path.make
cmt_local_install_root_include_path_makefile = $(bin)install_root_include_path.make

install_root_include_path_extratags = -tag_add=target_install_root_include_path

else

cmt_local_tagfile_install_root_include_path = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_install_root_include_path = $(bin)setup.make
cmt_local_install_root_include_path_makefile = $(bin)install_root_include_path.make

endif

not_install_root_include_path_dependencies = { n=0; for p in $?; do m=0; for d in $(install_root_include_path_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
install_root_include_pathdirs :
	@if test ! -d $(bin)install_root_include_path; then $(mkdir) -p $(bin)install_root_include_path; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)install_root_include_path
else
install_root_include_pathdirs : ;
endif

ifdef cmt_install_root_include_path_has_target_tag

ifndef QUICK
$(cmt_local_install_root_include_path_makefile) : $(install_root_include_path_dependencies) build_library_links
	$(echo) "(constituents.make) Building install_root_include_path.make"; \
	  $(cmtexe) -tag=$(tags) $(install_root_include_path_extratags) build constituent_config -out=$(cmt_local_install_root_include_path_makefile) install_root_include_path
else
$(cmt_local_install_root_include_path_makefile) : $(install_root_include_path_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_install_root_include_path) ] || \
	  [ ! -f $(cmt_final_setup_install_root_include_path) ] || \
	  $(not_install_root_include_path_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building install_root_include_path.make"; \
	  $(cmtexe) -tag=$(tags) $(install_root_include_path_extratags) build constituent_config -out=$(cmt_local_install_root_include_path_makefile) install_root_include_path; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_install_root_include_path_makefile) : $(install_root_include_path_dependencies) build_library_links
	$(echo) "(constituents.make) Building install_root_include_path.make"; \
	  $(cmtexe) -f=$(bin)install_root_include_path.in -tag=$(tags) $(install_root_include_path_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_install_root_include_path_makefile) install_root_include_path
else
$(cmt_local_install_root_include_path_makefile) : $(install_root_include_path_dependencies) $(cmt_build_library_linksstamp) $(bin)install_root_include_path.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_install_root_include_path) ] || \
	  [ ! -f $(cmt_final_setup_install_root_include_path) ] || \
	  $(not_install_root_include_path_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building install_root_include_path.make"; \
	  $(cmtexe) -f=$(bin)install_root_include_path.in -tag=$(tags) $(install_root_include_path_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_install_root_include_path_makefile) install_root_include_path; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(install_root_include_path_extratags) build constituent_makefile -out=$(cmt_local_install_root_include_path_makefile) install_root_include_path

install_root_include_path :: $(install_root_include_path_dependencies) $(cmt_local_install_root_include_path_makefile) dirs install_root_include_pathdirs
	$(echo) "(constituents.make) Starting install_root_include_path"
	@if test -f $(cmt_local_install_root_include_path_makefile); then \
	  $(MAKE) -f $(cmt_local_install_root_include_path_makefile) install_root_include_path; \
	  fi
#	@$(MAKE) -f $(cmt_local_install_root_include_path_makefile) install_root_include_path
	$(echo) "(constituents.make) install_root_include_path done"

clean :: install_root_include_pathclean ;

install_root_include_pathclean :: $(install_root_include_pathclean_dependencies) ##$(cmt_local_install_root_include_path_makefile)
	$(echo) "(constituents.make) Starting install_root_include_pathclean"
	@-if test -f $(cmt_local_install_root_include_path_makefile); then \
	  $(MAKE) -f $(cmt_local_install_root_include_path_makefile) install_root_include_pathclean; \
	fi
	$(echo) "(constituents.make) install_root_include_pathclean done"
#	@-$(MAKE) -f $(cmt_local_install_root_include_path_makefile) install_root_include_pathclean

##	  /bin/rm -f $(cmt_local_install_root_include_path_makefile) $(bin)install_root_include_path_dependencies.make

install :: install_root_include_pathinstall ;

install_root_include_pathinstall :: $(install_root_include_path_dependencies) $(cmt_local_install_root_include_path_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_install_root_include_path_makefile); then \
	  $(MAKE) -f $(cmt_local_install_root_include_path_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_install_root_include_path_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : install_root_include_pathuninstall

$(foreach d,$(install_root_include_path_dependencies),$(eval $(d)uninstall_dependencies += install_root_include_pathuninstall))

install_root_include_pathuninstall : $(install_root_include_pathuninstall_dependencies) ##$(cmt_local_install_root_include_path_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_install_root_include_path_makefile); then \
	  $(MAKE) -f $(cmt_local_install_root_include_path_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_install_root_include_path_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: install_root_include_pathuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ install_root_include_path"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ install_root_include_path done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_install_includes_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_install_includes_has_target_tag

cmt_local_tagfile_install_includes = $(bin)$(MyAnalysis_tag)_install_includes.make
cmt_final_setup_install_includes = $(bin)setup_install_includes.make
cmt_local_install_includes_makefile = $(bin)install_includes.make

install_includes_extratags = -tag_add=target_install_includes

else

cmt_local_tagfile_install_includes = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_install_includes = $(bin)setup.make
cmt_local_install_includes_makefile = $(bin)install_includes.make

endif

not_install_includes_dependencies = { n=0; for p in $?; do m=0; for d in $(install_includes_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
install_includesdirs :
	@if test ! -d $(bin)install_includes; then $(mkdir) -p $(bin)install_includes; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)install_includes
else
install_includesdirs : ;
endif

ifdef cmt_install_includes_has_target_tag

ifndef QUICK
$(cmt_local_install_includes_makefile) : $(install_includes_dependencies) build_library_links
	$(echo) "(constituents.make) Building install_includes.make"; \
	  $(cmtexe) -tag=$(tags) $(install_includes_extratags) build constituent_config -out=$(cmt_local_install_includes_makefile) install_includes
else
$(cmt_local_install_includes_makefile) : $(install_includes_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_install_includes) ] || \
	  [ ! -f $(cmt_final_setup_install_includes) ] || \
	  $(not_install_includes_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building install_includes.make"; \
	  $(cmtexe) -tag=$(tags) $(install_includes_extratags) build constituent_config -out=$(cmt_local_install_includes_makefile) install_includes; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_install_includes_makefile) : $(install_includes_dependencies) build_library_links
	$(echo) "(constituents.make) Building install_includes.make"; \
	  $(cmtexe) -f=$(bin)install_includes.in -tag=$(tags) $(install_includes_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_install_includes_makefile) install_includes
else
$(cmt_local_install_includes_makefile) : $(install_includes_dependencies) $(cmt_build_library_linksstamp) $(bin)install_includes.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_install_includes) ] || \
	  [ ! -f $(cmt_final_setup_install_includes) ] || \
	  $(not_install_includes_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building install_includes.make"; \
	  $(cmtexe) -f=$(bin)install_includes.in -tag=$(tags) $(install_includes_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_install_includes_makefile) install_includes; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(install_includes_extratags) build constituent_makefile -out=$(cmt_local_install_includes_makefile) install_includes

install_includes :: $(install_includes_dependencies) $(cmt_local_install_includes_makefile) dirs install_includesdirs
	$(echo) "(constituents.make) Starting install_includes"
	@if test -f $(cmt_local_install_includes_makefile); then \
	  $(MAKE) -f $(cmt_local_install_includes_makefile) install_includes; \
	  fi
#	@$(MAKE) -f $(cmt_local_install_includes_makefile) install_includes
	$(echo) "(constituents.make) install_includes done"

clean :: install_includesclean ;

install_includesclean :: $(install_includesclean_dependencies) ##$(cmt_local_install_includes_makefile)
	$(echo) "(constituents.make) Starting install_includesclean"
	@-if test -f $(cmt_local_install_includes_makefile); then \
	  $(MAKE) -f $(cmt_local_install_includes_makefile) install_includesclean; \
	fi
	$(echo) "(constituents.make) install_includesclean done"
#	@-$(MAKE) -f $(cmt_local_install_includes_makefile) install_includesclean

##	  /bin/rm -f $(cmt_local_install_includes_makefile) $(bin)install_includes_dependencies.make

install :: install_includesinstall ;

install_includesinstall :: $(install_includes_dependencies) $(cmt_local_install_includes_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_install_includes_makefile); then \
	  $(MAKE) -f $(cmt_local_install_includes_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_install_includes_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : install_includesuninstall

$(foreach d,$(install_includes_dependencies),$(eval $(d)uninstall_dependencies += install_includesuninstall))

install_includesuninstall : $(install_includesuninstall_dependencies) ##$(cmt_local_install_includes_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_install_includes_makefile); then \
	  $(MAKE) -f $(cmt_local_install_includes_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_install_includes_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: install_includesuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ install_includes"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ install_includes done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_make_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_make_has_target_tag

cmt_local_tagfile_make = $(bin)$(MyAnalysis_tag)_make.make
cmt_final_setup_make = $(bin)setup_make.make
cmt_local_make_makefile = $(bin)make.make

make_extratags = -tag_add=target_make

else

cmt_local_tagfile_make = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_make = $(bin)setup.make
cmt_local_make_makefile = $(bin)make.make

endif

not_make_dependencies = { n=0; for p in $?; do m=0; for d in $(make_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
makedirs :
	@if test ! -d $(bin)make; then $(mkdir) -p $(bin)make; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)make
else
makedirs : ;
endif

ifdef cmt_make_has_target_tag

ifndef QUICK
$(cmt_local_make_makefile) : $(make_dependencies) build_library_links
	$(echo) "(constituents.make) Building make.make"; \
	  $(cmtexe) -tag=$(tags) $(make_extratags) build constituent_config -out=$(cmt_local_make_makefile) make
else
$(cmt_local_make_makefile) : $(make_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_make) ] || \
	  [ ! -f $(cmt_final_setup_make) ] || \
	  $(not_make_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building make.make"; \
	  $(cmtexe) -tag=$(tags) $(make_extratags) build constituent_config -out=$(cmt_local_make_makefile) make; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_make_makefile) : $(make_dependencies) build_library_links
	$(echo) "(constituents.make) Building make.make"; \
	  $(cmtexe) -f=$(bin)make.in -tag=$(tags) $(make_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_make_makefile) make
else
$(cmt_local_make_makefile) : $(make_dependencies) $(cmt_build_library_linksstamp) $(bin)make.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_make) ] || \
	  [ ! -f $(cmt_final_setup_make) ] || \
	  $(not_make_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building make.make"; \
	  $(cmtexe) -f=$(bin)make.in -tag=$(tags) $(make_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_make_makefile) make; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(make_extratags) build constituent_makefile -out=$(cmt_local_make_makefile) make

make :: $(make_dependencies) $(cmt_local_make_makefile) dirs makedirs
	$(echo) "(constituents.make) Starting make"
	@if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) make; \
	  fi
#	@$(MAKE) -f $(cmt_local_make_makefile) make
	$(echo) "(constituents.make) make done"

clean :: makeclean ;

makeclean :: $(makeclean_dependencies) ##$(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting makeclean"
	@-if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) makeclean; \
	fi
	$(echo) "(constituents.make) makeclean done"
#	@-$(MAKE) -f $(cmt_local_make_makefile) makeclean

##	  /bin/rm -f $(cmt_local_make_makefile) $(bin)make_dependencies.make

install :: makeinstall ;

makeinstall :: $(make_dependencies) $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_make_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : makeuninstall

$(foreach d,$(make_dependencies),$(eval $(d)uninstall_dependencies += makeuninstall))

makeuninstall : $(makeuninstall_dependencies) ##$(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_make_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: makeuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ make"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ make done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_CompilePython_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_CompilePython_has_target_tag

cmt_local_tagfile_CompilePython = $(bin)$(MyAnalysis_tag)_CompilePython.make
cmt_final_setup_CompilePython = $(bin)setup_CompilePython.make
cmt_local_CompilePython_makefile = $(bin)CompilePython.make

CompilePython_extratags = -tag_add=target_CompilePython

else

cmt_local_tagfile_CompilePython = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_CompilePython = $(bin)setup.make
cmt_local_CompilePython_makefile = $(bin)CompilePython.make

endif

not_CompilePython_dependencies = { n=0; for p in $?; do m=0; for d in $(CompilePython_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
CompilePythondirs :
	@if test ! -d $(bin)CompilePython; then $(mkdir) -p $(bin)CompilePython; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)CompilePython
else
CompilePythondirs : ;
endif

ifdef cmt_CompilePython_has_target_tag

ifndef QUICK
$(cmt_local_CompilePython_makefile) : $(CompilePython_dependencies) build_library_links
	$(echo) "(constituents.make) Building CompilePython.make"; \
	  $(cmtexe) -tag=$(tags) $(CompilePython_extratags) build constituent_config -out=$(cmt_local_CompilePython_makefile) CompilePython
else
$(cmt_local_CompilePython_makefile) : $(CompilePython_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_CompilePython) ] || \
	  [ ! -f $(cmt_final_setup_CompilePython) ] || \
	  $(not_CompilePython_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building CompilePython.make"; \
	  $(cmtexe) -tag=$(tags) $(CompilePython_extratags) build constituent_config -out=$(cmt_local_CompilePython_makefile) CompilePython; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_CompilePython_makefile) : $(CompilePython_dependencies) build_library_links
	$(echo) "(constituents.make) Building CompilePython.make"; \
	  $(cmtexe) -f=$(bin)CompilePython.in -tag=$(tags) $(CompilePython_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_CompilePython_makefile) CompilePython
else
$(cmt_local_CompilePython_makefile) : $(CompilePython_dependencies) $(cmt_build_library_linksstamp) $(bin)CompilePython.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_CompilePython) ] || \
	  [ ! -f $(cmt_final_setup_CompilePython) ] || \
	  $(not_CompilePython_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building CompilePython.make"; \
	  $(cmtexe) -f=$(bin)CompilePython.in -tag=$(tags) $(CompilePython_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_CompilePython_makefile) CompilePython; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(CompilePython_extratags) build constituent_makefile -out=$(cmt_local_CompilePython_makefile) CompilePython

CompilePython :: $(CompilePython_dependencies) $(cmt_local_CompilePython_makefile) dirs CompilePythondirs
	$(echo) "(constituents.make) Starting CompilePython"
	@if test -f $(cmt_local_CompilePython_makefile); then \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) CompilePython; \
	  fi
#	@$(MAKE) -f $(cmt_local_CompilePython_makefile) CompilePython
	$(echo) "(constituents.make) CompilePython done"

clean :: CompilePythonclean ;

CompilePythonclean :: $(CompilePythonclean_dependencies) ##$(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting CompilePythonclean"
	@-if test -f $(cmt_local_CompilePython_makefile); then \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) CompilePythonclean; \
	fi
	$(echo) "(constituents.make) CompilePythonclean done"
#	@-$(MAKE) -f $(cmt_local_CompilePython_makefile) CompilePythonclean

##	  /bin/rm -f $(cmt_local_CompilePython_makefile) $(bin)CompilePython_dependencies.make

install :: CompilePythoninstall ;

CompilePythoninstall :: $(CompilePython_dependencies) $(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_CompilePython_makefile); then \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_CompilePython_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : CompilePythonuninstall

$(foreach d,$(CompilePython_dependencies),$(eval $(d)uninstall_dependencies += CompilePythonuninstall))

CompilePythonuninstall : $(CompilePythonuninstall_dependencies) ##$(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_CompilePython_makefile); then \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_CompilePython_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: CompilePythonuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ CompilePython"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ CompilePython done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_qmtest_run_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_qmtest_run_has_target_tag

cmt_local_tagfile_qmtest_run = $(bin)$(MyAnalysis_tag)_qmtest_run.make
cmt_final_setup_qmtest_run = $(bin)setup_qmtest_run.make
cmt_local_qmtest_run_makefile = $(bin)qmtest_run.make

qmtest_run_extratags = -tag_add=target_qmtest_run

else

cmt_local_tagfile_qmtest_run = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_qmtest_run = $(bin)setup.make
cmt_local_qmtest_run_makefile = $(bin)qmtest_run.make

endif

not_qmtest_run_dependencies = { n=0; for p in $?; do m=0; for d in $(qmtest_run_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
qmtest_rundirs :
	@if test ! -d $(bin)qmtest_run; then $(mkdir) -p $(bin)qmtest_run; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)qmtest_run
else
qmtest_rundirs : ;
endif

ifdef cmt_qmtest_run_has_target_tag

ifndef QUICK
$(cmt_local_qmtest_run_makefile) : $(qmtest_run_dependencies) build_library_links
	$(echo) "(constituents.make) Building qmtest_run.make"; \
	  $(cmtexe) -tag=$(tags) $(qmtest_run_extratags) build constituent_config -out=$(cmt_local_qmtest_run_makefile) qmtest_run
else
$(cmt_local_qmtest_run_makefile) : $(qmtest_run_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_qmtest_run) ] || \
	  [ ! -f $(cmt_final_setup_qmtest_run) ] || \
	  $(not_qmtest_run_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building qmtest_run.make"; \
	  $(cmtexe) -tag=$(tags) $(qmtest_run_extratags) build constituent_config -out=$(cmt_local_qmtest_run_makefile) qmtest_run; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_qmtest_run_makefile) : $(qmtest_run_dependencies) build_library_links
	$(echo) "(constituents.make) Building qmtest_run.make"; \
	  $(cmtexe) -f=$(bin)qmtest_run.in -tag=$(tags) $(qmtest_run_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_qmtest_run_makefile) qmtest_run
else
$(cmt_local_qmtest_run_makefile) : $(qmtest_run_dependencies) $(cmt_build_library_linksstamp) $(bin)qmtest_run.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_qmtest_run) ] || \
	  [ ! -f $(cmt_final_setup_qmtest_run) ] || \
	  $(not_qmtest_run_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building qmtest_run.make"; \
	  $(cmtexe) -f=$(bin)qmtest_run.in -tag=$(tags) $(qmtest_run_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_qmtest_run_makefile) qmtest_run; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(qmtest_run_extratags) build constituent_makefile -out=$(cmt_local_qmtest_run_makefile) qmtest_run

qmtest_run :: $(qmtest_run_dependencies) $(cmt_local_qmtest_run_makefile) dirs qmtest_rundirs
	$(echo) "(constituents.make) Starting qmtest_run"
	@if test -f $(cmt_local_qmtest_run_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) qmtest_run; \
	  fi
#	@$(MAKE) -f $(cmt_local_qmtest_run_makefile) qmtest_run
	$(echo) "(constituents.make) qmtest_run done"

clean :: qmtest_runclean ;

qmtest_runclean :: $(qmtest_runclean_dependencies) ##$(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting qmtest_runclean"
	@-if test -f $(cmt_local_qmtest_run_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) qmtest_runclean; \
	fi
	$(echo) "(constituents.make) qmtest_runclean done"
#	@-$(MAKE) -f $(cmt_local_qmtest_run_makefile) qmtest_runclean

##	  /bin/rm -f $(cmt_local_qmtest_run_makefile) $(bin)qmtest_run_dependencies.make

install :: qmtest_runinstall ;

qmtest_runinstall :: $(qmtest_run_dependencies) $(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_qmtest_run_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_qmtest_run_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : qmtest_rununinstall

$(foreach d,$(qmtest_run_dependencies),$(eval $(d)uninstall_dependencies += qmtest_rununinstall))

qmtest_rununinstall : $(qmtest_rununinstall_dependencies) ##$(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_qmtest_run_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_qmtest_run_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: qmtest_rununinstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ qmtest_run"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ qmtest_run done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_qmtest_summarize_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_qmtest_summarize_has_target_tag

cmt_local_tagfile_qmtest_summarize = $(bin)$(MyAnalysis_tag)_qmtest_summarize.make
cmt_final_setup_qmtest_summarize = $(bin)setup_qmtest_summarize.make
cmt_local_qmtest_summarize_makefile = $(bin)qmtest_summarize.make

qmtest_summarize_extratags = -tag_add=target_qmtest_summarize

else

cmt_local_tagfile_qmtest_summarize = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_qmtest_summarize = $(bin)setup.make
cmt_local_qmtest_summarize_makefile = $(bin)qmtest_summarize.make

endif

not_qmtest_summarize_dependencies = { n=0; for p in $?; do m=0; for d in $(qmtest_summarize_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
qmtest_summarizedirs :
	@if test ! -d $(bin)qmtest_summarize; then $(mkdir) -p $(bin)qmtest_summarize; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)qmtest_summarize
else
qmtest_summarizedirs : ;
endif

ifdef cmt_qmtest_summarize_has_target_tag

ifndef QUICK
$(cmt_local_qmtest_summarize_makefile) : $(qmtest_summarize_dependencies) build_library_links
	$(echo) "(constituents.make) Building qmtest_summarize.make"; \
	  $(cmtexe) -tag=$(tags) $(qmtest_summarize_extratags) build constituent_config -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize
else
$(cmt_local_qmtest_summarize_makefile) : $(qmtest_summarize_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_qmtest_summarize) ] || \
	  [ ! -f $(cmt_final_setup_qmtest_summarize) ] || \
	  $(not_qmtest_summarize_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building qmtest_summarize.make"; \
	  $(cmtexe) -tag=$(tags) $(qmtest_summarize_extratags) build constituent_config -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_qmtest_summarize_makefile) : $(qmtest_summarize_dependencies) build_library_links
	$(echo) "(constituents.make) Building qmtest_summarize.make"; \
	  $(cmtexe) -f=$(bin)qmtest_summarize.in -tag=$(tags) $(qmtest_summarize_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize
else
$(cmt_local_qmtest_summarize_makefile) : $(qmtest_summarize_dependencies) $(cmt_build_library_linksstamp) $(bin)qmtest_summarize.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_qmtest_summarize) ] || \
	  [ ! -f $(cmt_final_setup_qmtest_summarize) ] || \
	  $(not_qmtest_summarize_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building qmtest_summarize.make"; \
	  $(cmtexe) -f=$(bin)qmtest_summarize.in -tag=$(tags) $(qmtest_summarize_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(qmtest_summarize_extratags) build constituent_makefile -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize

qmtest_summarize :: $(qmtest_summarize_dependencies) $(cmt_local_qmtest_summarize_makefile) dirs qmtest_summarizedirs
	$(echo) "(constituents.make) Starting qmtest_summarize"
	@if test -f $(cmt_local_qmtest_summarize_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) qmtest_summarize; \
	  fi
#	@$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) qmtest_summarize
	$(echo) "(constituents.make) qmtest_summarize done"

clean :: qmtest_summarizeclean ;

qmtest_summarizeclean :: $(qmtest_summarizeclean_dependencies) ##$(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting qmtest_summarizeclean"
	@-if test -f $(cmt_local_qmtest_summarize_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) qmtest_summarizeclean; \
	fi
	$(echo) "(constituents.make) qmtest_summarizeclean done"
#	@-$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) qmtest_summarizeclean

##	  /bin/rm -f $(cmt_local_qmtest_summarize_makefile) $(bin)qmtest_summarize_dependencies.make

install :: qmtest_summarizeinstall ;

qmtest_summarizeinstall :: $(qmtest_summarize_dependencies) $(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_qmtest_summarize_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : qmtest_summarizeuninstall

$(foreach d,$(qmtest_summarize_dependencies),$(eval $(d)uninstall_dependencies += qmtest_summarizeuninstall))

qmtest_summarizeuninstall : $(qmtest_summarizeuninstall_dependencies) ##$(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_qmtest_summarize_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: qmtest_summarizeuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ qmtest_summarize"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ qmtest_summarize done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_TestPackage_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_TestPackage_has_target_tag

cmt_local_tagfile_TestPackage = $(bin)$(MyAnalysis_tag)_TestPackage.make
cmt_final_setup_TestPackage = $(bin)setup_TestPackage.make
cmt_local_TestPackage_makefile = $(bin)TestPackage.make

TestPackage_extratags = -tag_add=target_TestPackage

else

cmt_local_tagfile_TestPackage = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_TestPackage = $(bin)setup.make
cmt_local_TestPackage_makefile = $(bin)TestPackage.make

endif

not_TestPackage_dependencies = { n=0; for p in $?; do m=0; for d in $(TestPackage_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
TestPackagedirs :
	@if test ! -d $(bin)TestPackage; then $(mkdir) -p $(bin)TestPackage; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)TestPackage
else
TestPackagedirs : ;
endif

ifdef cmt_TestPackage_has_target_tag

ifndef QUICK
$(cmt_local_TestPackage_makefile) : $(TestPackage_dependencies) build_library_links
	$(echo) "(constituents.make) Building TestPackage.make"; \
	  $(cmtexe) -tag=$(tags) $(TestPackage_extratags) build constituent_config -out=$(cmt_local_TestPackage_makefile) TestPackage
else
$(cmt_local_TestPackage_makefile) : $(TestPackage_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_TestPackage) ] || \
	  [ ! -f $(cmt_final_setup_TestPackage) ] || \
	  $(not_TestPackage_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building TestPackage.make"; \
	  $(cmtexe) -tag=$(tags) $(TestPackage_extratags) build constituent_config -out=$(cmt_local_TestPackage_makefile) TestPackage; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_TestPackage_makefile) : $(TestPackage_dependencies) build_library_links
	$(echo) "(constituents.make) Building TestPackage.make"; \
	  $(cmtexe) -f=$(bin)TestPackage.in -tag=$(tags) $(TestPackage_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_TestPackage_makefile) TestPackage
else
$(cmt_local_TestPackage_makefile) : $(TestPackage_dependencies) $(cmt_build_library_linksstamp) $(bin)TestPackage.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_TestPackage) ] || \
	  [ ! -f $(cmt_final_setup_TestPackage) ] || \
	  $(not_TestPackage_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building TestPackage.make"; \
	  $(cmtexe) -f=$(bin)TestPackage.in -tag=$(tags) $(TestPackage_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_TestPackage_makefile) TestPackage; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(TestPackage_extratags) build constituent_makefile -out=$(cmt_local_TestPackage_makefile) TestPackage

TestPackage :: $(TestPackage_dependencies) $(cmt_local_TestPackage_makefile) dirs TestPackagedirs
	$(echo) "(constituents.make) Starting TestPackage"
	@if test -f $(cmt_local_TestPackage_makefile); then \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) TestPackage; \
	  fi
#	@$(MAKE) -f $(cmt_local_TestPackage_makefile) TestPackage
	$(echo) "(constituents.make) TestPackage done"

clean :: TestPackageclean ;

TestPackageclean :: $(TestPackageclean_dependencies) ##$(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting TestPackageclean"
	@-if test -f $(cmt_local_TestPackage_makefile); then \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) TestPackageclean; \
	fi
	$(echo) "(constituents.make) TestPackageclean done"
#	@-$(MAKE) -f $(cmt_local_TestPackage_makefile) TestPackageclean

##	  /bin/rm -f $(cmt_local_TestPackage_makefile) $(bin)TestPackage_dependencies.make

install :: TestPackageinstall ;

TestPackageinstall :: $(TestPackage_dependencies) $(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_TestPackage_makefile); then \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_TestPackage_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : TestPackageuninstall

$(foreach d,$(TestPackage_dependencies),$(eval $(d)uninstall_dependencies += TestPackageuninstall))

TestPackageuninstall : $(TestPackageuninstall_dependencies) ##$(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_TestPackage_makefile); then \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_TestPackage_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: TestPackageuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ TestPackage"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ TestPackage done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_TestProject_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_TestProject_has_target_tag

cmt_local_tagfile_TestProject = $(bin)$(MyAnalysis_tag)_TestProject.make
cmt_final_setup_TestProject = $(bin)setup_TestProject.make
cmt_local_TestProject_makefile = $(bin)TestProject.make

TestProject_extratags = -tag_add=target_TestProject

else

cmt_local_tagfile_TestProject = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_TestProject = $(bin)setup.make
cmt_local_TestProject_makefile = $(bin)TestProject.make

endif

not_TestProject_dependencies = { n=0; for p in $?; do m=0; for d in $(TestProject_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
TestProjectdirs :
	@if test ! -d $(bin)TestProject; then $(mkdir) -p $(bin)TestProject; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)TestProject
else
TestProjectdirs : ;
endif

ifdef cmt_TestProject_has_target_tag

ifndef QUICK
$(cmt_local_TestProject_makefile) : $(TestProject_dependencies) build_library_links
	$(echo) "(constituents.make) Building TestProject.make"; \
	  $(cmtexe) -tag=$(tags) $(TestProject_extratags) build constituent_config -out=$(cmt_local_TestProject_makefile) TestProject
else
$(cmt_local_TestProject_makefile) : $(TestProject_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_TestProject) ] || \
	  [ ! -f $(cmt_final_setup_TestProject) ] || \
	  $(not_TestProject_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building TestProject.make"; \
	  $(cmtexe) -tag=$(tags) $(TestProject_extratags) build constituent_config -out=$(cmt_local_TestProject_makefile) TestProject; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_TestProject_makefile) : $(TestProject_dependencies) build_library_links
	$(echo) "(constituents.make) Building TestProject.make"; \
	  $(cmtexe) -f=$(bin)TestProject.in -tag=$(tags) $(TestProject_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_TestProject_makefile) TestProject
else
$(cmt_local_TestProject_makefile) : $(TestProject_dependencies) $(cmt_build_library_linksstamp) $(bin)TestProject.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_TestProject) ] || \
	  [ ! -f $(cmt_final_setup_TestProject) ] || \
	  $(not_TestProject_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building TestProject.make"; \
	  $(cmtexe) -f=$(bin)TestProject.in -tag=$(tags) $(TestProject_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_TestProject_makefile) TestProject; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(TestProject_extratags) build constituent_makefile -out=$(cmt_local_TestProject_makefile) TestProject

TestProject :: $(TestProject_dependencies) $(cmt_local_TestProject_makefile) dirs TestProjectdirs
	$(echo) "(constituents.make) Starting TestProject"
	@if test -f $(cmt_local_TestProject_makefile); then \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) TestProject; \
	  fi
#	@$(MAKE) -f $(cmt_local_TestProject_makefile) TestProject
	$(echo) "(constituents.make) TestProject done"

clean :: TestProjectclean ;

TestProjectclean :: $(TestProjectclean_dependencies) ##$(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting TestProjectclean"
	@-if test -f $(cmt_local_TestProject_makefile); then \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) TestProjectclean; \
	fi
	$(echo) "(constituents.make) TestProjectclean done"
#	@-$(MAKE) -f $(cmt_local_TestProject_makefile) TestProjectclean

##	  /bin/rm -f $(cmt_local_TestProject_makefile) $(bin)TestProject_dependencies.make

install :: TestProjectinstall ;

TestProjectinstall :: $(TestProject_dependencies) $(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_TestProject_makefile); then \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_TestProject_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : TestProjectuninstall

$(foreach d,$(TestProject_dependencies),$(eval $(d)uninstall_dependencies += TestProjectuninstall))

TestProjectuninstall : $(TestProjectuninstall_dependencies) ##$(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_TestProject_makefile); then \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_TestProject_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: TestProjectuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ TestProject"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ TestProject done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_rootsys_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_rootsys_has_target_tag

cmt_local_tagfile_new_rootsys = $(bin)$(MyAnalysis_tag)_new_rootsys.make
cmt_final_setup_new_rootsys = $(bin)setup_new_rootsys.make
cmt_local_new_rootsys_makefile = $(bin)new_rootsys.make

new_rootsys_extratags = -tag_add=target_new_rootsys

else

cmt_local_tagfile_new_rootsys = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_rootsys = $(bin)setup.make
cmt_local_new_rootsys_makefile = $(bin)new_rootsys.make

endif

not_new_rootsys_dependencies = { n=0; for p in $?; do m=0; for d in $(new_rootsys_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_rootsysdirs :
	@if test ! -d $(bin)new_rootsys; then $(mkdir) -p $(bin)new_rootsys; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_rootsys
else
new_rootsysdirs : ;
endif

ifdef cmt_new_rootsys_has_target_tag

ifndef QUICK
$(cmt_local_new_rootsys_makefile) : $(new_rootsys_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_rootsys.make"; \
	  $(cmtexe) -tag=$(tags) $(new_rootsys_extratags) build constituent_config -out=$(cmt_local_new_rootsys_makefile) new_rootsys
else
$(cmt_local_new_rootsys_makefile) : $(new_rootsys_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_rootsys) ] || \
	  [ ! -f $(cmt_final_setup_new_rootsys) ] || \
	  $(not_new_rootsys_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_rootsys.make"; \
	  $(cmtexe) -tag=$(tags) $(new_rootsys_extratags) build constituent_config -out=$(cmt_local_new_rootsys_makefile) new_rootsys; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_rootsys_makefile) : $(new_rootsys_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_rootsys.make"; \
	  $(cmtexe) -f=$(bin)new_rootsys.in -tag=$(tags) $(new_rootsys_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_rootsys_makefile) new_rootsys
else
$(cmt_local_new_rootsys_makefile) : $(new_rootsys_dependencies) $(cmt_build_library_linksstamp) $(bin)new_rootsys.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_rootsys) ] || \
	  [ ! -f $(cmt_final_setup_new_rootsys) ] || \
	  $(not_new_rootsys_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_rootsys.make"; \
	  $(cmtexe) -f=$(bin)new_rootsys.in -tag=$(tags) $(new_rootsys_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_rootsys_makefile) new_rootsys; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_rootsys_extratags) build constituent_makefile -out=$(cmt_local_new_rootsys_makefile) new_rootsys

new_rootsys :: $(new_rootsys_dependencies) $(cmt_local_new_rootsys_makefile) dirs new_rootsysdirs
	$(echo) "(constituents.make) Starting new_rootsys"
	@if test -f $(cmt_local_new_rootsys_makefile); then \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) new_rootsys; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_rootsys_makefile) new_rootsys
	$(echo) "(constituents.make) new_rootsys done"

clean :: new_rootsysclean ;

new_rootsysclean :: $(new_rootsysclean_dependencies) ##$(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting new_rootsysclean"
	@-if test -f $(cmt_local_new_rootsys_makefile); then \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) new_rootsysclean; \
	fi
	$(echo) "(constituents.make) new_rootsysclean done"
#	@-$(MAKE) -f $(cmt_local_new_rootsys_makefile) new_rootsysclean

##	  /bin/rm -f $(cmt_local_new_rootsys_makefile) $(bin)new_rootsys_dependencies.make

install :: new_rootsysinstall ;

new_rootsysinstall :: $(new_rootsys_dependencies) $(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_rootsys_makefile); then \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_rootsys_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_rootsysuninstall

$(foreach d,$(new_rootsys_dependencies),$(eval $(d)uninstall_dependencies += new_rootsysuninstall))

new_rootsysuninstall : $(new_rootsysuninstall_dependencies) ##$(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_rootsys_makefile); then \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_rootsys_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_rootsysuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_rootsys"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_rootsys done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_doxygen_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_doxygen_has_target_tag

cmt_local_tagfile_doxygen = $(bin)$(MyAnalysis_tag)_doxygen.make
cmt_final_setup_doxygen = $(bin)setup_doxygen.make
cmt_local_doxygen_makefile = $(bin)doxygen.make

doxygen_extratags = -tag_add=target_doxygen

else

cmt_local_tagfile_doxygen = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_doxygen = $(bin)setup.make
cmt_local_doxygen_makefile = $(bin)doxygen.make

endif

not_doxygen_dependencies = { n=0; for p in $?; do m=0; for d in $(doxygen_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
doxygendirs :
	@if test ! -d $(bin)doxygen; then $(mkdir) -p $(bin)doxygen; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)doxygen
else
doxygendirs : ;
endif

ifdef cmt_doxygen_has_target_tag

ifndef QUICK
$(cmt_local_doxygen_makefile) : $(doxygen_dependencies) build_library_links
	$(echo) "(constituents.make) Building doxygen.make"; \
	  $(cmtexe) -tag=$(tags) $(doxygen_extratags) build constituent_config -out=$(cmt_local_doxygen_makefile) doxygen
else
$(cmt_local_doxygen_makefile) : $(doxygen_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_doxygen) ] || \
	  [ ! -f $(cmt_final_setup_doxygen) ] || \
	  $(not_doxygen_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building doxygen.make"; \
	  $(cmtexe) -tag=$(tags) $(doxygen_extratags) build constituent_config -out=$(cmt_local_doxygen_makefile) doxygen; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_doxygen_makefile) : $(doxygen_dependencies) build_library_links
	$(echo) "(constituents.make) Building doxygen.make"; \
	  $(cmtexe) -f=$(bin)doxygen.in -tag=$(tags) $(doxygen_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_doxygen_makefile) doxygen
else
$(cmt_local_doxygen_makefile) : $(doxygen_dependencies) $(cmt_build_library_linksstamp) $(bin)doxygen.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_doxygen) ] || \
	  [ ! -f $(cmt_final_setup_doxygen) ] || \
	  $(not_doxygen_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building doxygen.make"; \
	  $(cmtexe) -f=$(bin)doxygen.in -tag=$(tags) $(doxygen_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_doxygen_makefile) doxygen; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(doxygen_extratags) build constituent_makefile -out=$(cmt_local_doxygen_makefile) doxygen

doxygen :: $(doxygen_dependencies) $(cmt_local_doxygen_makefile) dirs doxygendirs
	$(echo) "(constituents.make) Starting doxygen"
	@if test -f $(cmt_local_doxygen_makefile); then \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) doxygen; \
	  fi
#	@$(MAKE) -f $(cmt_local_doxygen_makefile) doxygen
	$(echo) "(constituents.make) doxygen done"

clean :: doxygenclean ;

doxygenclean :: $(doxygenclean_dependencies) ##$(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting doxygenclean"
	@-if test -f $(cmt_local_doxygen_makefile); then \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) doxygenclean; \
	fi
	$(echo) "(constituents.make) doxygenclean done"
#	@-$(MAKE) -f $(cmt_local_doxygen_makefile) doxygenclean

##	  /bin/rm -f $(cmt_local_doxygen_makefile) $(bin)doxygen_dependencies.make

install :: doxygeninstall ;

doxygeninstall :: $(doxygen_dependencies) $(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_doxygen_makefile); then \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_doxygen_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : doxygenuninstall

$(foreach d,$(doxygen_dependencies),$(eval $(d)uninstall_dependencies += doxygenuninstall))

doxygenuninstall : $(doxygenuninstall_dependencies) ##$(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_doxygen_makefile); then \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_doxygen_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: doxygenuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ doxygen"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ doxygen done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_post_install_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_post_install_has_target_tag

cmt_local_tagfile_post_install = $(bin)$(MyAnalysis_tag)_post_install.make
cmt_final_setup_post_install = $(bin)setup_post_install.make
cmt_local_post_install_makefile = $(bin)post_install.make

post_install_extratags = -tag_add=target_post_install

else

cmt_local_tagfile_post_install = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_post_install = $(bin)setup.make
cmt_local_post_install_makefile = $(bin)post_install.make

endif

not_post_install_dependencies = { n=0; for p in $?; do m=0; for d in $(post_install_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
post_installdirs :
	@if test ! -d $(bin)post_install; then $(mkdir) -p $(bin)post_install; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)post_install
else
post_installdirs : ;
endif

ifdef cmt_post_install_has_target_tag

ifndef QUICK
$(cmt_local_post_install_makefile) : $(post_install_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_install.make"; \
	  $(cmtexe) -tag=$(tags) $(post_install_extratags) build constituent_config -out=$(cmt_local_post_install_makefile) post_install
else
$(cmt_local_post_install_makefile) : $(post_install_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_install) ] || \
	  [ ! -f $(cmt_final_setup_post_install) ] || \
	  $(not_post_install_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_install.make"; \
	  $(cmtexe) -tag=$(tags) $(post_install_extratags) build constituent_config -out=$(cmt_local_post_install_makefile) post_install; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_post_install_makefile) : $(post_install_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_install.make"; \
	  $(cmtexe) -f=$(bin)post_install.in -tag=$(tags) $(post_install_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_install_makefile) post_install
else
$(cmt_local_post_install_makefile) : $(post_install_dependencies) $(cmt_build_library_linksstamp) $(bin)post_install.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_install) ] || \
	  [ ! -f $(cmt_final_setup_post_install) ] || \
	  $(not_post_install_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_install.make"; \
	  $(cmtexe) -f=$(bin)post_install.in -tag=$(tags) $(post_install_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_install_makefile) post_install; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(post_install_extratags) build constituent_makefile -out=$(cmt_local_post_install_makefile) post_install

post_install :: $(post_install_dependencies) $(cmt_local_post_install_makefile) dirs post_installdirs
	$(echo) "(constituents.make) Starting post_install"
	@if test -f $(cmt_local_post_install_makefile); then \
	  $(MAKE) -f $(cmt_local_post_install_makefile) post_install; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_install_makefile) post_install
	$(echo) "(constituents.make) post_install done"

clean :: post_installclean ;

post_installclean :: $(post_installclean_dependencies) ##$(cmt_local_post_install_makefile)
	$(echo) "(constituents.make) Starting post_installclean"
	@-if test -f $(cmt_local_post_install_makefile); then \
	  $(MAKE) -f $(cmt_local_post_install_makefile) post_installclean; \
	fi
	$(echo) "(constituents.make) post_installclean done"
#	@-$(MAKE) -f $(cmt_local_post_install_makefile) post_installclean

##	  /bin/rm -f $(cmt_local_post_install_makefile) $(bin)post_install_dependencies.make

install :: post_installinstall ;

post_installinstall :: $(post_install_dependencies) $(cmt_local_post_install_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_post_install_makefile); then \
	  $(MAKE) -f $(cmt_local_post_install_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_post_install_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : post_installuninstall

$(foreach d,$(post_install_dependencies),$(eval $(d)uninstall_dependencies += post_installuninstall))

post_installuninstall : $(post_installuninstall_dependencies) ##$(cmt_local_post_install_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_post_install_makefile); then \
	  $(MAKE) -f $(cmt_local_post_install_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_install_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: post_installuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ post_install"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ post_install done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_post_merge_rootmap_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_post_merge_rootmap_has_target_tag

cmt_local_tagfile_post_merge_rootmap = $(bin)$(MyAnalysis_tag)_post_merge_rootmap.make
cmt_final_setup_post_merge_rootmap = $(bin)setup_post_merge_rootmap.make
cmt_local_post_merge_rootmap_makefile = $(bin)post_merge_rootmap.make

post_merge_rootmap_extratags = -tag_add=target_post_merge_rootmap

else

cmt_local_tagfile_post_merge_rootmap = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_post_merge_rootmap = $(bin)setup.make
cmt_local_post_merge_rootmap_makefile = $(bin)post_merge_rootmap.make

endif

not_post_merge_rootmap_dependencies = { n=0; for p in $?; do m=0; for d in $(post_merge_rootmap_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
post_merge_rootmapdirs :
	@if test ! -d $(bin)post_merge_rootmap; then $(mkdir) -p $(bin)post_merge_rootmap; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)post_merge_rootmap
else
post_merge_rootmapdirs : ;
endif

ifdef cmt_post_merge_rootmap_has_target_tag

ifndef QUICK
$(cmt_local_post_merge_rootmap_makefile) : $(post_merge_rootmap_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_merge_rootmap.make"; \
	  $(cmtexe) -tag=$(tags) $(post_merge_rootmap_extratags) build constituent_config -out=$(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap
else
$(cmt_local_post_merge_rootmap_makefile) : $(post_merge_rootmap_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_merge_rootmap) ] || \
	  [ ! -f $(cmt_final_setup_post_merge_rootmap) ] || \
	  $(not_post_merge_rootmap_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_merge_rootmap.make"; \
	  $(cmtexe) -tag=$(tags) $(post_merge_rootmap_extratags) build constituent_config -out=$(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_post_merge_rootmap_makefile) : $(post_merge_rootmap_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_merge_rootmap.make"; \
	  $(cmtexe) -f=$(bin)post_merge_rootmap.in -tag=$(tags) $(post_merge_rootmap_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap
else
$(cmt_local_post_merge_rootmap_makefile) : $(post_merge_rootmap_dependencies) $(cmt_build_library_linksstamp) $(bin)post_merge_rootmap.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_merge_rootmap) ] || \
	  [ ! -f $(cmt_final_setup_post_merge_rootmap) ] || \
	  $(not_post_merge_rootmap_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_merge_rootmap.make"; \
	  $(cmtexe) -f=$(bin)post_merge_rootmap.in -tag=$(tags) $(post_merge_rootmap_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(post_merge_rootmap_extratags) build constituent_makefile -out=$(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap

post_merge_rootmap :: $(post_merge_rootmap_dependencies) $(cmt_local_post_merge_rootmap_makefile) dirs post_merge_rootmapdirs
	$(echo) "(constituents.make) Starting post_merge_rootmap"
	@if test -f $(cmt_local_post_merge_rootmap_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) post_merge_rootmap
	$(echo) "(constituents.make) post_merge_rootmap done"

clean :: post_merge_rootmapclean ;

post_merge_rootmapclean :: $(post_merge_rootmapclean_dependencies) ##$(cmt_local_post_merge_rootmap_makefile)
	$(echo) "(constituents.make) Starting post_merge_rootmapclean"
	@-if test -f $(cmt_local_post_merge_rootmap_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) post_merge_rootmapclean; \
	fi
	$(echo) "(constituents.make) post_merge_rootmapclean done"
#	@-$(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) post_merge_rootmapclean

##	  /bin/rm -f $(cmt_local_post_merge_rootmap_makefile) $(bin)post_merge_rootmap_dependencies.make

install :: post_merge_rootmapinstall ;

post_merge_rootmapinstall :: $(post_merge_rootmap_dependencies) $(cmt_local_post_merge_rootmap_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_post_merge_rootmap_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : post_merge_rootmapuninstall

$(foreach d,$(post_merge_rootmap_dependencies),$(eval $(d)uninstall_dependencies += post_merge_rootmapuninstall))

post_merge_rootmapuninstall : $(post_merge_rootmapuninstall_dependencies) ##$(cmt_local_post_merge_rootmap_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_post_merge_rootmap_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_merge_rootmap_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: post_merge_rootmapuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ post_merge_rootmap"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ post_merge_rootmap done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_post_merge_genconfdb_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_post_merge_genconfdb_has_target_tag

cmt_local_tagfile_post_merge_genconfdb = $(bin)$(MyAnalysis_tag)_post_merge_genconfdb.make
cmt_final_setup_post_merge_genconfdb = $(bin)setup_post_merge_genconfdb.make
cmt_local_post_merge_genconfdb_makefile = $(bin)post_merge_genconfdb.make

post_merge_genconfdb_extratags = -tag_add=target_post_merge_genconfdb

else

cmt_local_tagfile_post_merge_genconfdb = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_post_merge_genconfdb = $(bin)setup.make
cmt_local_post_merge_genconfdb_makefile = $(bin)post_merge_genconfdb.make

endif

not_post_merge_genconfdb_dependencies = { n=0; for p in $?; do m=0; for d in $(post_merge_genconfdb_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
post_merge_genconfdbdirs :
	@if test ! -d $(bin)post_merge_genconfdb; then $(mkdir) -p $(bin)post_merge_genconfdb; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)post_merge_genconfdb
else
post_merge_genconfdbdirs : ;
endif

ifdef cmt_post_merge_genconfdb_has_target_tag

ifndef QUICK
$(cmt_local_post_merge_genconfdb_makefile) : $(post_merge_genconfdb_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_merge_genconfdb.make"; \
	  $(cmtexe) -tag=$(tags) $(post_merge_genconfdb_extratags) build constituent_config -out=$(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb
else
$(cmt_local_post_merge_genconfdb_makefile) : $(post_merge_genconfdb_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_merge_genconfdb) ] || \
	  [ ! -f $(cmt_final_setup_post_merge_genconfdb) ] || \
	  $(not_post_merge_genconfdb_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_merge_genconfdb.make"; \
	  $(cmtexe) -tag=$(tags) $(post_merge_genconfdb_extratags) build constituent_config -out=$(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_post_merge_genconfdb_makefile) : $(post_merge_genconfdb_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_merge_genconfdb.make"; \
	  $(cmtexe) -f=$(bin)post_merge_genconfdb.in -tag=$(tags) $(post_merge_genconfdb_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb
else
$(cmt_local_post_merge_genconfdb_makefile) : $(post_merge_genconfdb_dependencies) $(cmt_build_library_linksstamp) $(bin)post_merge_genconfdb.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_merge_genconfdb) ] || \
	  [ ! -f $(cmt_final_setup_post_merge_genconfdb) ] || \
	  $(not_post_merge_genconfdb_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_merge_genconfdb.make"; \
	  $(cmtexe) -f=$(bin)post_merge_genconfdb.in -tag=$(tags) $(post_merge_genconfdb_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(post_merge_genconfdb_extratags) build constituent_makefile -out=$(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb

post_merge_genconfdb :: $(post_merge_genconfdb_dependencies) $(cmt_local_post_merge_genconfdb_makefile) dirs post_merge_genconfdbdirs
	$(echo) "(constituents.make) Starting post_merge_genconfdb"
	@if test -f $(cmt_local_post_merge_genconfdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdb
	$(echo) "(constituents.make) post_merge_genconfdb done"

clean :: post_merge_genconfdbclean ;

post_merge_genconfdbclean :: $(post_merge_genconfdbclean_dependencies) ##$(cmt_local_post_merge_genconfdb_makefile)
	$(echo) "(constituents.make) Starting post_merge_genconfdbclean"
	@-if test -f $(cmt_local_post_merge_genconfdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdbclean; \
	fi
	$(echo) "(constituents.make) post_merge_genconfdbclean done"
#	@-$(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) post_merge_genconfdbclean

##	  /bin/rm -f $(cmt_local_post_merge_genconfdb_makefile) $(bin)post_merge_genconfdb_dependencies.make

install :: post_merge_genconfdbinstall ;

post_merge_genconfdbinstall :: $(post_merge_genconfdb_dependencies) $(cmt_local_post_merge_genconfdb_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_post_merge_genconfdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : post_merge_genconfdbuninstall

$(foreach d,$(post_merge_genconfdb_dependencies),$(eval $(d)uninstall_dependencies += post_merge_genconfdbuninstall))

post_merge_genconfdbuninstall : $(post_merge_genconfdbuninstall_dependencies) ##$(cmt_local_post_merge_genconfdb_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_post_merge_genconfdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_merge_genconfdb_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: post_merge_genconfdbuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ post_merge_genconfdb"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ post_merge_genconfdb done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_post_build_tpcnvdb_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_post_build_tpcnvdb_has_target_tag

cmt_local_tagfile_post_build_tpcnvdb = $(bin)$(MyAnalysis_tag)_post_build_tpcnvdb.make
cmt_final_setup_post_build_tpcnvdb = $(bin)setup_post_build_tpcnvdb.make
cmt_local_post_build_tpcnvdb_makefile = $(bin)post_build_tpcnvdb.make

post_build_tpcnvdb_extratags = -tag_add=target_post_build_tpcnvdb

else

cmt_local_tagfile_post_build_tpcnvdb = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_post_build_tpcnvdb = $(bin)setup.make
cmt_local_post_build_tpcnvdb_makefile = $(bin)post_build_tpcnvdb.make

endif

not_post_build_tpcnvdb_dependencies = { n=0; for p in $?; do m=0; for d in $(post_build_tpcnvdb_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
post_build_tpcnvdbdirs :
	@if test ! -d $(bin)post_build_tpcnvdb; then $(mkdir) -p $(bin)post_build_tpcnvdb; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)post_build_tpcnvdb
else
post_build_tpcnvdbdirs : ;
endif

ifdef cmt_post_build_tpcnvdb_has_target_tag

ifndef QUICK
$(cmt_local_post_build_tpcnvdb_makefile) : $(post_build_tpcnvdb_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_build_tpcnvdb.make"; \
	  $(cmtexe) -tag=$(tags) $(post_build_tpcnvdb_extratags) build constituent_config -out=$(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb
else
$(cmt_local_post_build_tpcnvdb_makefile) : $(post_build_tpcnvdb_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_build_tpcnvdb) ] || \
	  [ ! -f $(cmt_final_setup_post_build_tpcnvdb) ] || \
	  $(not_post_build_tpcnvdb_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_build_tpcnvdb.make"; \
	  $(cmtexe) -tag=$(tags) $(post_build_tpcnvdb_extratags) build constituent_config -out=$(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_post_build_tpcnvdb_makefile) : $(post_build_tpcnvdb_dependencies) build_library_links
	$(echo) "(constituents.make) Building post_build_tpcnvdb.make"; \
	  $(cmtexe) -f=$(bin)post_build_tpcnvdb.in -tag=$(tags) $(post_build_tpcnvdb_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb
else
$(cmt_local_post_build_tpcnvdb_makefile) : $(post_build_tpcnvdb_dependencies) $(cmt_build_library_linksstamp) $(bin)post_build_tpcnvdb.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_post_build_tpcnvdb) ] || \
	  [ ! -f $(cmt_final_setup_post_build_tpcnvdb) ] || \
	  $(not_post_build_tpcnvdb_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building post_build_tpcnvdb.make"; \
	  $(cmtexe) -f=$(bin)post_build_tpcnvdb.in -tag=$(tags) $(post_build_tpcnvdb_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(post_build_tpcnvdb_extratags) build constituent_makefile -out=$(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb

post_build_tpcnvdb :: $(post_build_tpcnvdb_dependencies) $(cmt_local_post_build_tpcnvdb_makefile) dirs post_build_tpcnvdbdirs
	$(echo) "(constituents.make) Starting post_build_tpcnvdb"
	@if test -f $(cmt_local_post_build_tpcnvdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdb
	$(echo) "(constituents.make) post_build_tpcnvdb done"

clean :: post_build_tpcnvdbclean ;

post_build_tpcnvdbclean :: $(post_build_tpcnvdbclean_dependencies) ##$(cmt_local_post_build_tpcnvdb_makefile)
	$(echo) "(constituents.make) Starting post_build_tpcnvdbclean"
	@-if test -f $(cmt_local_post_build_tpcnvdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdbclean; \
	fi
	$(echo) "(constituents.make) post_build_tpcnvdbclean done"
#	@-$(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) post_build_tpcnvdbclean

##	  /bin/rm -f $(cmt_local_post_build_tpcnvdb_makefile) $(bin)post_build_tpcnvdb_dependencies.make

install :: post_build_tpcnvdbinstall ;

post_build_tpcnvdbinstall :: $(post_build_tpcnvdb_dependencies) $(cmt_local_post_build_tpcnvdb_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_post_build_tpcnvdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : post_build_tpcnvdbuninstall

$(foreach d,$(post_build_tpcnvdb_dependencies),$(eval $(d)uninstall_dependencies += post_build_tpcnvdbuninstall))

post_build_tpcnvdbuninstall : $(post_build_tpcnvdbuninstall_dependencies) ##$(cmt_local_post_build_tpcnvdb_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_post_build_tpcnvdb_makefile); then \
	  $(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_post_build_tpcnvdb_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: post_build_tpcnvdbuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ post_build_tpcnvdb"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ post_build_tpcnvdb done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_all_post_constituents_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_all_post_constituents_has_target_tag

cmt_local_tagfile_all_post_constituents = $(bin)$(MyAnalysis_tag)_all_post_constituents.make
cmt_final_setup_all_post_constituents = $(bin)setup_all_post_constituents.make
cmt_local_all_post_constituents_makefile = $(bin)all_post_constituents.make

all_post_constituents_extratags = -tag_add=target_all_post_constituents

else

cmt_local_tagfile_all_post_constituents = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_all_post_constituents = $(bin)setup.make
cmt_local_all_post_constituents_makefile = $(bin)all_post_constituents.make

endif

not_all_post_constituents_dependencies = { n=0; for p in $?; do m=0; for d in $(all_post_constituents_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
all_post_constituentsdirs :
	@if test ! -d $(bin)all_post_constituents; then $(mkdir) -p $(bin)all_post_constituents; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)all_post_constituents
else
all_post_constituentsdirs : ;
endif

ifdef cmt_all_post_constituents_has_target_tag

ifndef QUICK
$(cmt_local_all_post_constituents_makefile) : $(all_post_constituents_dependencies) build_library_links
	$(echo) "(constituents.make) Building all_post_constituents.make"; \
	  $(cmtexe) -tag=$(tags) $(all_post_constituents_extratags) build constituent_config -out=$(cmt_local_all_post_constituents_makefile) all_post_constituents
else
$(cmt_local_all_post_constituents_makefile) : $(all_post_constituents_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_all_post_constituents) ] || \
	  [ ! -f $(cmt_final_setup_all_post_constituents) ] || \
	  $(not_all_post_constituents_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building all_post_constituents.make"; \
	  $(cmtexe) -tag=$(tags) $(all_post_constituents_extratags) build constituent_config -out=$(cmt_local_all_post_constituents_makefile) all_post_constituents; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_all_post_constituents_makefile) : $(all_post_constituents_dependencies) build_library_links
	$(echo) "(constituents.make) Building all_post_constituents.make"; \
	  $(cmtexe) -f=$(bin)all_post_constituents.in -tag=$(tags) $(all_post_constituents_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_all_post_constituents_makefile) all_post_constituents
else
$(cmt_local_all_post_constituents_makefile) : $(all_post_constituents_dependencies) $(cmt_build_library_linksstamp) $(bin)all_post_constituents.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_all_post_constituents) ] || \
	  [ ! -f $(cmt_final_setup_all_post_constituents) ] || \
	  $(not_all_post_constituents_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building all_post_constituents.make"; \
	  $(cmtexe) -f=$(bin)all_post_constituents.in -tag=$(tags) $(all_post_constituents_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_all_post_constituents_makefile) all_post_constituents; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(all_post_constituents_extratags) build constituent_makefile -out=$(cmt_local_all_post_constituents_makefile) all_post_constituents

all_post_constituents :: $(all_post_constituents_dependencies) $(cmt_local_all_post_constituents_makefile) dirs all_post_constituentsdirs
	$(echo) "(constituents.make) Starting all_post_constituents"
	@if test -f $(cmt_local_all_post_constituents_makefile); then \
	  $(MAKE) -f $(cmt_local_all_post_constituents_makefile) all_post_constituents; \
	  fi
#	@$(MAKE) -f $(cmt_local_all_post_constituents_makefile) all_post_constituents
	$(echo) "(constituents.make) all_post_constituents done"

clean :: all_post_constituentsclean ;

all_post_constituentsclean :: $(all_post_constituentsclean_dependencies) ##$(cmt_local_all_post_constituents_makefile)
	$(echo) "(constituents.make) Starting all_post_constituentsclean"
	@-if test -f $(cmt_local_all_post_constituents_makefile); then \
	  $(MAKE) -f $(cmt_local_all_post_constituents_makefile) all_post_constituentsclean; \
	fi
	$(echo) "(constituents.make) all_post_constituentsclean done"
#	@-$(MAKE) -f $(cmt_local_all_post_constituents_makefile) all_post_constituentsclean

##	  /bin/rm -f $(cmt_local_all_post_constituents_makefile) $(bin)all_post_constituents_dependencies.make

install :: all_post_constituentsinstall ;

all_post_constituentsinstall :: $(all_post_constituents_dependencies) $(cmt_local_all_post_constituents_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_all_post_constituents_makefile); then \
	  $(MAKE) -f $(cmt_local_all_post_constituents_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_all_post_constituents_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : all_post_constituentsuninstall

$(foreach d,$(all_post_constituents_dependencies),$(eval $(d)uninstall_dependencies += all_post_constituentsuninstall))

all_post_constituentsuninstall : $(all_post_constituentsuninstall_dependencies) ##$(cmt_local_all_post_constituents_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_all_post_constituents_makefile); then \
	  $(MAKE) -f $(cmt_local_all_post_constituents_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_all_post_constituents_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: all_post_constituentsuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ all_post_constituents"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ all_post_constituents done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_checkreq_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_checkreq_has_target_tag

cmt_local_tagfile_checkreq = $(bin)$(MyAnalysis_tag)_checkreq.make
cmt_final_setup_checkreq = $(bin)setup_checkreq.make
cmt_local_checkreq_makefile = $(bin)checkreq.make

checkreq_extratags = -tag_add=target_checkreq

else

cmt_local_tagfile_checkreq = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_checkreq = $(bin)setup.make
cmt_local_checkreq_makefile = $(bin)checkreq.make

endif

not_checkreq_dependencies = { n=0; for p in $?; do m=0; for d in $(checkreq_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
checkreqdirs :
	@if test ! -d $(bin)checkreq; then $(mkdir) -p $(bin)checkreq; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)checkreq
else
checkreqdirs : ;
endif

ifdef cmt_checkreq_has_target_tag

ifndef QUICK
$(cmt_local_checkreq_makefile) : $(checkreq_dependencies) build_library_links
	$(echo) "(constituents.make) Building checkreq.make"; \
	  $(cmtexe) -tag=$(tags) $(checkreq_extratags) build constituent_config -out=$(cmt_local_checkreq_makefile) checkreq
else
$(cmt_local_checkreq_makefile) : $(checkreq_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_checkreq) ] || \
	  [ ! -f $(cmt_final_setup_checkreq) ] || \
	  $(not_checkreq_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building checkreq.make"; \
	  $(cmtexe) -tag=$(tags) $(checkreq_extratags) build constituent_config -out=$(cmt_local_checkreq_makefile) checkreq; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_checkreq_makefile) : $(checkreq_dependencies) build_library_links
	$(echo) "(constituents.make) Building checkreq.make"; \
	  $(cmtexe) -f=$(bin)checkreq.in -tag=$(tags) $(checkreq_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_checkreq_makefile) checkreq
else
$(cmt_local_checkreq_makefile) : $(checkreq_dependencies) $(cmt_build_library_linksstamp) $(bin)checkreq.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_checkreq) ] || \
	  [ ! -f $(cmt_final_setup_checkreq) ] || \
	  $(not_checkreq_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building checkreq.make"; \
	  $(cmtexe) -f=$(bin)checkreq.in -tag=$(tags) $(checkreq_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_checkreq_makefile) checkreq; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(checkreq_extratags) build constituent_makefile -out=$(cmt_local_checkreq_makefile) checkreq

checkreq :: $(checkreq_dependencies) $(cmt_local_checkreq_makefile) dirs checkreqdirs
	$(echo) "(constituents.make) Starting checkreq"
	@if test -f $(cmt_local_checkreq_makefile); then \
	  $(MAKE) -f $(cmt_local_checkreq_makefile) checkreq; \
	  fi
#	@$(MAKE) -f $(cmt_local_checkreq_makefile) checkreq
	$(echo) "(constituents.make) checkreq done"

clean :: checkreqclean ;

checkreqclean :: $(checkreqclean_dependencies) ##$(cmt_local_checkreq_makefile)
	$(echo) "(constituents.make) Starting checkreqclean"
	@-if test -f $(cmt_local_checkreq_makefile); then \
	  $(MAKE) -f $(cmt_local_checkreq_makefile) checkreqclean; \
	fi
	$(echo) "(constituents.make) checkreqclean done"
#	@-$(MAKE) -f $(cmt_local_checkreq_makefile) checkreqclean

##	  /bin/rm -f $(cmt_local_checkreq_makefile) $(bin)checkreq_dependencies.make

install :: checkreqinstall ;

checkreqinstall :: $(checkreq_dependencies) $(cmt_local_checkreq_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_checkreq_makefile); then \
	  $(MAKE) -f $(cmt_local_checkreq_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_checkreq_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : checkrequninstall

$(foreach d,$(checkreq_dependencies),$(eval $(d)uninstall_dependencies += checkrequninstall))

checkrequninstall : $(checkrequninstall_dependencies) ##$(cmt_local_checkreq_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_checkreq_makefile); then \
	  $(MAKE) -f $(cmt_local_checkreq_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_checkreq_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: checkrequninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ checkreq"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ checkreq done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_MyAnalysis_NICOS_Fix_debuginfo_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_MyAnalysis_NICOS_Fix_debuginfo_has_target_tag

cmt_local_tagfile_MyAnalysis_NICOS_Fix_debuginfo = $(bin)$(MyAnalysis_tag)_MyAnalysis_NICOS_Fix_debuginfo.make
cmt_final_setup_MyAnalysis_NICOS_Fix_debuginfo = $(bin)setup_MyAnalysis_NICOS_Fix_debuginfo.make
cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile = $(bin)MyAnalysis_NICOS_Fix_debuginfo.make

MyAnalysis_NICOS_Fix_debuginfo_extratags = -tag_add=target_MyAnalysis_NICOS_Fix_debuginfo

else

cmt_local_tagfile_MyAnalysis_NICOS_Fix_debuginfo = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_MyAnalysis_NICOS_Fix_debuginfo = $(bin)setup.make
cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile = $(bin)MyAnalysis_NICOS_Fix_debuginfo.make

endif

not_MyAnalysis_NICOS_Fix_debuginfo_dependencies = { n=0; for p in $?; do m=0; for d in $(MyAnalysis_NICOS_Fix_debuginfo_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
MyAnalysis_NICOS_Fix_debuginfodirs :
	@if test ! -d $(bin)MyAnalysis_NICOS_Fix_debuginfo; then $(mkdir) -p $(bin)MyAnalysis_NICOS_Fix_debuginfo; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)MyAnalysis_NICOS_Fix_debuginfo
else
MyAnalysis_NICOS_Fix_debuginfodirs : ;
endif

ifdef cmt_MyAnalysis_NICOS_Fix_debuginfo_has_target_tag

ifndef QUICK
$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) : $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_NICOS_Fix_debuginfo.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_NICOS_Fix_debuginfo_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo
else
$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) : $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_NICOS_Fix_debuginfo) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_NICOS_Fix_debuginfo) ] || \
	  $(not_MyAnalysis_NICOS_Fix_debuginfo_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_NICOS_Fix_debuginfo.make"; \
	  $(cmtexe) -tag=$(tags) $(MyAnalysis_NICOS_Fix_debuginfo_extratags) build constituent_config -out=$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) : $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) build_library_links
	$(echo) "(constituents.make) Building MyAnalysis_NICOS_Fix_debuginfo.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_NICOS_Fix_debuginfo.in -tag=$(tags) $(MyAnalysis_NICOS_Fix_debuginfo_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo
else
$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) : $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) $(cmt_build_library_linksstamp) $(bin)MyAnalysis_NICOS_Fix_debuginfo.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_MyAnalysis_NICOS_Fix_debuginfo) ] || \
	  [ ! -f $(cmt_final_setup_MyAnalysis_NICOS_Fix_debuginfo) ] || \
	  $(not_MyAnalysis_NICOS_Fix_debuginfo_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building MyAnalysis_NICOS_Fix_debuginfo.make"; \
	  $(cmtexe) -f=$(bin)MyAnalysis_NICOS_Fix_debuginfo.in -tag=$(tags) $(MyAnalysis_NICOS_Fix_debuginfo_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(MyAnalysis_NICOS_Fix_debuginfo_extratags) build constituent_makefile -out=$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo

MyAnalysis_NICOS_Fix_debuginfo :: $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) dirs MyAnalysis_NICOS_Fix_debuginfodirs
	$(echo) "(constituents.make) Starting MyAnalysis_NICOS_Fix_debuginfo"
	@if test -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfo
	$(echo) "(constituents.make) MyAnalysis_NICOS_Fix_debuginfo done"

clean :: MyAnalysis_NICOS_Fix_debuginfoclean ;

MyAnalysis_NICOS_Fix_debuginfoclean :: $(MyAnalysis_NICOS_Fix_debuginfoclean_dependencies) ##$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile)
	$(echo) "(constituents.make) Starting MyAnalysis_NICOS_Fix_debuginfoclean"
	@-if test -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfoclean; \
	fi
	$(echo) "(constituents.make) MyAnalysis_NICOS_Fix_debuginfoclean done"
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) MyAnalysis_NICOS_Fix_debuginfoclean

##	  /bin/rm -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) $(bin)MyAnalysis_NICOS_Fix_debuginfo_dependencies.make

install :: MyAnalysis_NICOS_Fix_debuginfoinstall ;

MyAnalysis_NICOS_Fix_debuginfoinstall :: $(MyAnalysis_NICOS_Fix_debuginfo_dependencies) $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : MyAnalysis_NICOS_Fix_debuginfouninstall

$(foreach d,$(MyAnalysis_NICOS_Fix_debuginfo_dependencies),$(eval $(d)uninstall_dependencies += MyAnalysis_NICOS_Fix_debuginfouninstall))

MyAnalysis_NICOS_Fix_debuginfouninstall : $(MyAnalysis_NICOS_Fix_debuginfouninstall_dependencies) ##$(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile); then \
	  $(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_MyAnalysis_NICOS_Fix_debuginfo_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: MyAnalysis_NICOS_Fix_debuginfouninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyAnalysis_NICOS_Fix_debuginfo"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyAnalysis_NICOS_Fix_debuginfo done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_find_packages_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_find_packages_has_target_tag

cmt_local_tagfile_find_packages = $(bin)$(MyAnalysis_tag)_find_packages.make
cmt_final_setup_find_packages = $(bin)setup_find_packages.make
cmt_local_find_packages_makefile = $(bin)find_packages.make

find_packages_extratags = -tag_add=target_find_packages

else

cmt_local_tagfile_find_packages = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_find_packages = $(bin)setup.make
cmt_local_find_packages_makefile = $(bin)find_packages.make

endif

not_find_packages_dependencies = { n=0; for p in $?; do m=0; for d in $(find_packages_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
find_packagesdirs :
	@if test ! -d $(bin)find_packages; then $(mkdir) -p $(bin)find_packages; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)find_packages
else
find_packagesdirs : ;
endif

ifdef cmt_find_packages_has_target_tag

ifndef QUICK
$(cmt_local_find_packages_makefile) : $(find_packages_dependencies) build_library_links
	$(echo) "(constituents.make) Building find_packages.make"; \
	  $(cmtexe) -tag=$(tags) $(find_packages_extratags) build constituent_config -out=$(cmt_local_find_packages_makefile) find_packages
else
$(cmt_local_find_packages_makefile) : $(find_packages_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_find_packages) ] || \
	  [ ! -f $(cmt_final_setup_find_packages) ] || \
	  $(not_find_packages_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building find_packages.make"; \
	  $(cmtexe) -tag=$(tags) $(find_packages_extratags) build constituent_config -out=$(cmt_local_find_packages_makefile) find_packages; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_find_packages_makefile) : $(find_packages_dependencies) build_library_links
	$(echo) "(constituents.make) Building find_packages.make"; \
	  $(cmtexe) -f=$(bin)find_packages.in -tag=$(tags) $(find_packages_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_find_packages_makefile) find_packages
else
$(cmt_local_find_packages_makefile) : $(find_packages_dependencies) $(cmt_build_library_linksstamp) $(bin)find_packages.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_find_packages) ] || \
	  [ ! -f $(cmt_final_setup_find_packages) ] || \
	  $(not_find_packages_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building find_packages.make"; \
	  $(cmtexe) -f=$(bin)find_packages.in -tag=$(tags) $(find_packages_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_find_packages_makefile) find_packages; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(find_packages_extratags) build constituent_makefile -out=$(cmt_local_find_packages_makefile) find_packages

find_packages :: $(find_packages_dependencies) $(cmt_local_find_packages_makefile) dirs find_packagesdirs
	$(echo) "(constituents.make) Starting find_packages"
	@if test -f $(cmt_local_find_packages_makefile); then \
	  $(MAKE) -f $(cmt_local_find_packages_makefile) find_packages; \
	  fi
#	@$(MAKE) -f $(cmt_local_find_packages_makefile) find_packages
	$(echo) "(constituents.make) find_packages done"

clean :: find_packagesclean ;

find_packagesclean :: $(find_packagesclean_dependencies) ##$(cmt_local_find_packages_makefile)
	$(echo) "(constituents.make) Starting find_packagesclean"
	@-if test -f $(cmt_local_find_packages_makefile); then \
	  $(MAKE) -f $(cmt_local_find_packages_makefile) find_packagesclean; \
	fi
	$(echo) "(constituents.make) find_packagesclean done"
#	@-$(MAKE) -f $(cmt_local_find_packages_makefile) find_packagesclean

##	  /bin/rm -f $(cmt_local_find_packages_makefile) $(bin)find_packages_dependencies.make

install :: find_packagesinstall ;

find_packagesinstall :: $(find_packages_dependencies) $(cmt_local_find_packages_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_find_packages_makefile); then \
	  $(MAKE) -f $(cmt_local_find_packages_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_find_packages_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : find_packagesuninstall

$(foreach d,$(find_packages_dependencies),$(eval $(d)uninstall_dependencies += find_packagesuninstall))

find_packagesuninstall : $(find_packagesuninstall_dependencies) ##$(cmt_local_find_packages_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_find_packages_makefile); then \
	  $(MAKE) -f $(cmt_local_find_packages_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_find_packages_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: find_packagesuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ find_packages"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ find_packages done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_compile_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_compile_has_target_tag

cmt_local_tagfile_compile = $(bin)$(MyAnalysis_tag)_compile.make
cmt_final_setup_compile = $(bin)setup_compile.make
cmt_local_compile_makefile = $(bin)compile.make

compile_extratags = -tag_add=target_compile

else

cmt_local_tagfile_compile = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_compile = $(bin)setup.make
cmt_local_compile_makefile = $(bin)compile.make

endif

not_compile_dependencies = { n=0; for p in $?; do m=0; for d in $(compile_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
compiledirs :
	@if test ! -d $(bin)compile; then $(mkdir) -p $(bin)compile; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)compile
else
compiledirs : ;
endif

ifdef cmt_compile_has_target_tag

ifndef QUICK
$(cmt_local_compile_makefile) : $(compile_dependencies) build_library_links
	$(echo) "(constituents.make) Building compile.make"; \
	  $(cmtexe) -tag=$(tags) $(compile_extratags) build constituent_config -out=$(cmt_local_compile_makefile) compile
else
$(cmt_local_compile_makefile) : $(compile_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_compile) ] || \
	  [ ! -f $(cmt_final_setup_compile) ] || \
	  $(not_compile_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building compile.make"; \
	  $(cmtexe) -tag=$(tags) $(compile_extratags) build constituent_config -out=$(cmt_local_compile_makefile) compile; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_compile_makefile) : $(compile_dependencies) build_library_links
	$(echo) "(constituents.make) Building compile.make"; \
	  $(cmtexe) -f=$(bin)compile.in -tag=$(tags) $(compile_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_compile_makefile) compile
else
$(cmt_local_compile_makefile) : $(compile_dependencies) $(cmt_build_library_linksstamp) $(bin)compile.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_compile) ] || \
	  [ ! -f $(cmt_final_setup_compile) ] || \
	  $(not_compile_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building compile.make"; \
	  $(cmtexe) -f=$(bin)compile.in -tag=$(tags) $(compile_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_compile_makefile) compile; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(compile_extratags) build constituent_makefile -out=$(cmt_local_compile_makefile) compile

compile :: $(compile_dependencies) $(cmt_local_compile_makefile) dirs compiledirs
	$(echo) "(constituents.make) Starting compile"
	@if test -f $(cmt_local_compile_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_makefile) compile; \
	  fi
#	@$(MAKE) -f $(cmt_local_compile_makefile) compile
	$(echo) "(constituents.make) compile done"

clean :: compileclean ;

compileclean :: $(compileclean_dependencies) ##$(cmt_local_compile_makefile)
	$(echo) "(constituents.make) Starting compileclean"
	@-if test -f $(cmt_local_compile_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_makefile) compileclean; \
	fi
	$(echo) "(constituents.make) compileclean done"
#	@-$(MAKE) -f $(cmt_local_compile_makefile) compileclean

##	  /bin/rm -f $(cmt_local_compile_makefile) $(bin)compile_dependencies.make

install :: compileinstall ;

compileinstall :: $(compile_dependencies) $(cmt_local_compile_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_compile_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_compile_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : compileuninstall

$(foreach d,$(compile_dependencies),$(eval $(d)uninstall_dependencies += compileuninstall))

compileuninstall : $(compileuninstall_dependencies) ##$(cmt_local_compile_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_compile_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_compile_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: compileuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ compile"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ compile done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_compile_pkg_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_compile_pkg_has_target_tag

cmt_local_tagfile_compile_pkg = $(bin)$(MyAnalysis_tag)_compile_pkg.make
cmt_final_setup_compile_pkg = $(bin)setup_compile_pkg.make
cmt_local_compile_pkg_makefile = $(bin)compile_pkg.make

compile_pkg_extratags = -tag_add=target_compile_pkg

else

cmt_local_tagfile_compile_pkg = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_compile_pkg = $(bin)setup.make
cmt_local_compile_pkg_makefile = $(bin)compile_pkg.make

endif

not_compile_pkg_dependencies = { n=0; for p in $?; do m=0; for d in $(compile_pkg_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
compile_pkgdirs :
	@if test ! -d $(bin)compile_pkg; then $(mkdir) -p $(bin)compile_pkg; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)compile_pkg
else
compile_pkgdirs : ;
endif

ifdef cmt_compile_pkg_has_target_tag

ifndef QUICK
$(cmt_local_compile_pkg_makefile) : $(compile_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building compile_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(compile_pkg_extratags) build constituent_config -out=$(cmt_local_compile_pkg_makefile) compile_pkg
else
$(cmt_local_compile_pkg_makefile) : $(compile_pkg_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_compile_pkg) ] || \
	  [ ! -f $(cmt_final_setup_compile_pkg) ] || \
	  $(not_compile_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building compile_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(compile_pkg_extratags) build constituent_config -out=$(cmt_local_compile_pkg_makefile) compile_pkg; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_compile_pkg_makefile) : $(compile_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building compile_pkg.make"; \
	  $(cmtexe) -f=$(bin)compile_pkg.in -tag=$(tags) $(compile_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_compile_pkg_makefile) compile_pkg
else
$(cmt_local_compile_pkg_makefile) : $(compile_pkg_dependencies) $(cmt_build_library_linksstamp) $(bin)compile_pkg.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_compile_pkg) ] || \
	  [ ! -f $(cmt_final_setup_compile_pkg) ] || \
	  $(not_compile_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building compile_pkg.make"; \
	  $(cmtexe) -f=$(bin)compile_pkg.in -tag=$(tags) $(compile_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_compile_pkg_makefile) compile_pkg; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(compile_pkg_extratags) build constituent_makefile -out=$(cmt_local_compile_pkg_makefile) compile_pkg

compile_pkg :: $(compile_pkg_dependencies) $(cmt_local_compile_pkg_makefile) dirs compile_pkgdirs
	$(echo) "(constituents.make) Starting compile_pkg"
	@if test -f $(cmt_local_compile_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_pkg_makefile) compile_pkg; \
	  fi
#	@$(MAKE) -f $(cmt_local_compile_pkg_makefile) compile_pkg
	$(echo) "(constituents.make) compile_pkg done"

clean :: compile_pkgclean ;

compile_pkgclean :: $(compile_pkgclean_dependencies) ##$(cmt_local_compile_pkg_makefile)
	$(echo) "(constituents.make) Starting compile_pkgclean"
	@-if test -f $(cmt_local_compile_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_pkg_makefile) compile_pkgclean; \
	fi
	$(echo) "(constituents.make) compile_pkgclean done"
#	@-$(MAKE) -f $(cmt_local_compile_pkg_makefile) compile_pkgclean

##	  /bin/rm -f $(cmt_local_compile_pkg_makefile) $(bin)compile_pkg_dependencies.make

install :: compile_pkginstall ;

compile_pkginstall :: $(compile_pkg_dependencies) $(cmt_local_compile_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_compile_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_pkg_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_compile_pkg_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : compile_pkguninstall

$(foreach d,$(compile_pkg_dependencies),$(eval $(d)uninstall_dependencies += compile_pkguninstall))

compile_pkguninstall : $(compile_pkguninstall_dependencies) ##$(cmt_local_compile_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_compile_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_compile_pkg_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_compile_pkg_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: compile_pkguninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ compile_pkg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ compile_pkg done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_analysisapp_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_analysisapp_has_target_tag

cmt_local_tagfile_new_analysisapp = $(bin)$(MyAnalysis_tag)_new_analysisapp.make
cmt_final_setup_new_analysisapp = $(bin)setup_new_analysisapp.make
cmt_local_new_analysisapp_makefile = $(bin)new_analysisapp.make

new_analysisapp_extratags = -tag_add=target_new_analysisapp

else

cmt_local_tagfile_new_analysisapp = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_analysisapp = $(bin)setup.make
cmt_local_new_analysisapp_makefile = $(bin)new_analysisapp.make

endif

not_new_analysisapp_dependencies = { n=0; for p in $?; do m=0; for d in $(new_analysisapp_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_analysisappdirs :
	@if test ! -d $(bin)new_analysisapp; then $(mkdir) -p $(bin)new_analysisapp; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_analysisapp
else
new_analysisappdirs : ;
endif

ifdef cmt_new_analysisapp_has_target_tag

ifndef QUICK
$(cmt_local_new_analysisapp_makefile) : $(new_analysisapp_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_analysisapp.make"; \
	  $(cmtexe) -tag=$(tags) $(new_analysisapp_extratags) build constituent_config -out=$(cmt_local_new_analysisapp_makefile) new_analysisapp
else
$(cmt_local_new_analysisapp_makefile) : $(new_analysisapp_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_analysisapp) ] || \
	  [ ! -f $(cmt_final_setup_new_analysisapp) ] || \
	  $(not_new_analysisapp_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_analysisapp.make"; \
	  $(cmtexe) -tag=$(tags) $(new_analysisapp_extratags) build constituent_config -out=$(cmt_local_new_analysisapp_makefile) new_analysisapp; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_analysisapp_makefile) : $(new_analysisapp_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_analysisapp.make"; \
	  $(cmtexe) -f=$(bin)new_analysisapp.in -tag=$(tags) $(new_analysisapp_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_analysisapp_makefile) new_analysisapp
else
$(cmt_local_new_analysisapp_makefile) : $(new_analysisapp_dependencies) $(cmt_build_library_linksstamp) $(bin)new_analysisapp.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_analysisapp) ] || \
	  [ ! -f $(cmt_final_setup_new_analysisapp) ] || \
	  $(not_new_analysisapp_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_analysisapp.make"; \
	  $(cmtexe) -f=$(bin)new_analysisapp.in -tag=$(tags) $(new_analysisapp_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_analysisapp_makefile) new_analysisapp; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_analysisapp_extratags) build constituent_makefile -out=$(cmt_local_new_analysisapp_makefile) new_analysisapp

new_analysisapp :: $(new_analysisapp_dependencies) $(cmt_local_new_analysisapp_makefile) dirs new_analysisappdirs
	$(echo) "(constituents.make) Starting new_analysisapp"
	@if test -f $(cmt_local_new_analysisapp_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisapp_makefile) new_analysisapp; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_analysisapp_makefile) new_analysisapp
	$(echo) "(constituents.make) new_analysisapp done"

clean :: new_analysisappclean ;

new_analysisappclean :: $(new_analysisappclean_dependencies) ##$(cmt_local_new_analysisapp_makefile)
	$(echo) "(constituents.make) Starting new_analysisappclean"
	@-if test -f $(cmt_local_new_analysisapp_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisapp_makefile) new_analysisappclean; \
	fi
	$(echo) "(constituents.make) new_analysisappclean done"
#	@-$(MAKE) -f $(cmt_local_new_analysisapp_makefile) new_analysisappclean

##	  /bin/rm -f $(cmt_local_new_analysisapp_makefile) $(bin)new_analysisapp_dependencies.make

install :: new_analysisappinstall ;

new_analysisappinstall :: $(new_analysisapp_dependencies) $(cmt_local_new_analysisapp_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_analysisapp_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisapp_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_analysisapp_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_analysisappuninstall

$(foreach d,$(new_analysisapp_dependencies),$(eval $(d)uninstall_dependencies += new_analysisappuninstall))

new_analysisappuninstall : $(new_analysisappuninstall_dependencies) ##$(cmt_local_new_analysisapp_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_analysisapp_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisapp_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_analysisapp_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_analysisappuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_analysisapp"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_analysisapp done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_pkg_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_pkg_has_target_tag

cmt_local_tagfile_new_pkg = $(bin)$(MyAnalysis_tag)_new_pkg.make
cmt_final_setup_new_pkg = $(bin)setup_new_pkg.make
cmt_local_new_pkg_makefile = $(bin)new_pkg.make

new_pkg_extratags = -tag_add=target_new_pkg

else

cmt_local_tagfile_new_pkg = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_pkg = $(bin)setup.make
cmt_local_new_pkg_makefile = $(bin)new_pkg.make

endif

not_new_pkg_dependencies = { n=0; for p in $?; do m=0; for d in $(new_pkg_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_pkgdirs :
	@if test ! -d $(bin)new_pkg; then $(mkdir) -p $(bin)new_pkg; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_pkg
else
new_pkgdirs : ;
endif

ifdef cmt_new_pkg_has_target_tag

ifndef QUICK
$(cmt_local_new_pkg_makefile) : $(new_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_pkg_extratags) build constituent_config -out=$(cmt_local_new_pkg_makefile) new_pkg
else
$(cmt_local_new_pkg_makefile) : $(new_pkg_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_pkg) ] || \
	  [ ! -f $(cmt_final_setup_new_pkg) ] || \
	  $(not_new_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_pkg_extratags) build constituent_config -out=$(cmt_local_new_pkg_makefile) new_pkg; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_pkg_makefile) : $(new_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_pkg.make"; \
	  $(cmtexe) -f=$(bin)new_pkg.in -tag=$(tags) $(new_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_pkg_makefile) new_pkg
else
$(cmt_local_new_pkg_makefile) : $(new_pkg_dependencies) $(cmt_build_library_linksstamp) $(bin)new_pkg.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_pkg) ] || \
	  [ ! -f $(cmt_final_setup_new_pkg) ] || \
	  $(not_new_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_pkg.make"; \
	  $(cmtexe) -f=$(bin)new_pkg.in -tag=$(tags) $(new_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_pkg_makefile) new_pkg; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_pkg_extratags) build constituent_makefile -out=$(cmt_local_new_pkg_makefile) new_pkg

new_pkg :: $(new_pkg_dependencies) $(cmt_local_new_pkg_makefile) dirs new_pkgdirs
	$(echo) "(constituents.make) Starting new_pkg"
	@if test -f $(cmt_local_new_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_pkg_makefile) new_pkg; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_pkg_makefile) new_pkg
	$(echo) "(constituents.make) new_pkg done"

clean :: new_pkgclean ;

new_pkgclean :: $(new_pkgclean_dependencies) ##$(cmt_local_new_pkg_makefile)
	$(echo) "(constituents.make) Starting new_pkgclean"
	@-if test -f $(cmt_local_new_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_pkg_makefile) new_pkgclean; \
	fi
	$(echo) "(constituents.make) new_pkgclean done"
#	@-$(MAKE) -f $(cmt_local_new_pkg_makefile) new_pkgclean

##	  /bin/rm -f $(cmt_local_new_pkg_makefile) $(bin)new_pkg_dependencies.make

install :: new_pkginstall ;

new_pkginstall :: $(new_pkg_dependencies) $(cmt_local_new_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_pkg_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_pkg_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_pkguninstall

$(foreach d,$(new_pkg_dependencies),$(eval $(d)uninstall_dependencies += new_pkguninstall))

new_pkguninstall : $(new_pkguninstall_dependencies) ##$(cmt_local_new_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_pkg_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_pkg_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_pkguninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_pkg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_pkg done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_alg_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_alg_has_target_tag

cmt_local_tagfile_new_alg = $(bin)$(MyAnalysis_tag)_new_alg.make
cmt_final_setup_new_alg = $(bin)setup_new_alg.make
cmt_local_new_alg_makefile = $(bin)new_alg.make

new_alg_extratags = -tag_add=target_new_alg

else

cmt_local_tagfile_new_alg = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_alg = $(bin)setup.make
cmt_local_new_alg_makefile = $(bin)new_alg.make

endif

not_new_alg_dependencies = { n=0; for p in $?; do m=0; for d in $(new_alg_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_algdirs :
	@if test ! -d $(bin)new_alg; then $(mkdir) -p $(bin)new_alg; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_alg
else
new_algdirs : ;
endif

ifdef cmt_new_alg_has_target_tag

ifndef QUICK
$(cmt_local_new_alg_makefile) : $(new_alg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_alg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_alg_extratags) build constituent_config -out=$(cmt_local_new_alg_makefile) new_alg
else
$(cmt_local_new_alg_makefile) : $(new_alg_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_alg) ] || \
	  [ ! -f $(cmt_final_setup_new_alg) ] || \
	  $(not_new_alg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_alg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_alg_extratags) build constituent_config -out=$(cmt_local_new_alg_makefile) new_alg; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_alg_makefile) : $(new_alg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_alg.make"; \
	  $(cmtexe) -f=$(bin)new_alg.in -tag=$(tags) $(new_alg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_alg_makefile) new_alg
else
$(cmt_local_new_alg_makefile) : $(new_alg_dependencies) $(cmt_build_library_linksstamp) $(bin)new_alg.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_alg) ] || \
	  [ ! -f $(cmt_final_setup_new_alg) ] || \
	  $(not_new_alg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_alg.make"; \
	  $(cmtexe) -f=$(bin)new_alg.in -tag=$(tags) $(new_alg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_alg_makefile) new_alg; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_alg_extratags) build constituent_makefile -out=$(cmt_local_new_alg_makefile) new_alg

new_alg :: $(new_alg_dependencies) $(cmt_local_new_alg_makefile) dirs new_algdirs
	$(echo) "(constituents.make) Starting new_alg"
	@if test -f $(cmt_local_new_alg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_alg_makefile) new_alg; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_alg_makefile) new_alg
	$(echo) "(constituents.make) new_alg done"

clean :: new_algclean ;

new_algclean :: $(new_algclean_dependencies) ##$(cmt_local_new_alg_makefile)
	$(echo) "(constituents.make) Starting new_algclean"
	@-if test -f $(cmt_local_new_alg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_alg_makefile) new_algclean; \
	fi
	$(echo) "(constituents.make) new_algclean done"
#	@-$(MAKE) -f $(cmt_local_new_alg_makefile) new_algclean

##	  /bin/rm -f $(cmt_local_new_alg_makefile) $(bin)new_alg_dependencies.make

install :: new_alginstall ;

new_alginstall :: $(new_alg_dependencies) $(cmt_local_new_alg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_alg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_alg_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_alg_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_alguninstall

$(foreach d,$(new_alg_dependencies),$(eval $(d)uninstall_dependencies += new_alguninstall))

new_alguninstall : $(new_alguninstall_dependencies) ##$(cmt_local_new_alg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_alg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_alg_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_alg_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_alguninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_alg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_alg done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_analysisalg_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_analysisalg_has_target_tag

cmt_local_tagfile_new_analysisalg = $(bin)$(MyAnalysis_tag)_new_analysisalg.make
cmt_final_setup_new_analysisalg = $(bin)setup_new_analysisalg.make
cmt_local_new_analysisalg_makefile = $(bin)new_analysisalg.make

new_analysisalg_extratags = -tag_add=target_new_analysisalg

else

cmt_local_tagfile_new_analysisalg = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_analysisalg = $(bin)setup.make
cmt_local_new_analysisalg_makefile = $(bin)new_analysisalg.make

endif

not_new_analysisalg_dependencies = { n=0; for p in $?; do m=0; for d in $(new_analysisalg_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_analysisalgdirs :
	@if test ! -d $(bin)new_analysisalg; then $(mkdir) -p $(bin)new_analysisalg; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_analysisalg
else
new_analysisalgdirs : ;
endif

ifdef cmt_new_analysisalg_has_target_tag

ifndef QUICK
$(cmt_local_new_analysisalg_makefile) : $(new_analysisalg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_analysisalg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_analysisalg_extratags) build constituent_config -out=$(cmt_local_new_analysisalg_makefile) new_analysisalg
else
$(cmt_local_new_analysisalg_makefile) : $(new_analysisalg_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_analysisalg) ] || \
	  [ ! -f $(cmt_final_setup_new_analysisalg) ] || \
	  $(not_new_analysisalg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_analysisalg.make"; \
	  $(cmtexe) -tag=$(tags) $(new_analysisalg_extratags) build constituent_config -out=$(cmt_local_new_analysisalg_makefile) new_analysisalg; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_analysisalg_makefile) : $(new_analysisalg_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_analysisalg.make"; \
	  $(cmtexe) -f=$(bin)new_analysisalg.in -tag=$(tags) $(new_analysisalg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_analysisalg_makefile) new_analysisalg
else
$(cmt_local_new_analysisalg_makefile) : $(new_analysisalg_dependencies) $(cmt_build_library_linksstamp) $(bin)new_analysisalg.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_analysisalg) ] || \
	  [ ! -f $(cmt_final_setup_new_analysisalg) ] || \
	  $(not_new_analysisalg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_analysisalg.make"; \
	  $(cmtexe) -f=$(bin)new_analysisalg.in -tag=$(tags) $(new_analysisalg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_analysisalg_makefile) new_analysisalg; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_analysisalg_extratags) build constituent_makefile -out=$(cmt_local_new_analysisalg_makefile) new_analysisalg

new_analysisalg :: $(new_analysisalg_dependencies) $(cmt_local_new_analysisalg_makefile) dirs new_analysisalgdirs
	$(echo) "(constituents.make) Starting new_analysisalg"
	@if test -f $(cmt_local_new_analysisalg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisalg_makefile) new_analysisalg; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_analysisalg_makefile) new_analysisalg
	$(echo) "(constituents.make) new_analysisalg done"

clean :: new_analysisalgclean ;

new_analysisalgclean :: $(new_analysisalgclean_dependencies) ##$(cmt_local_new_analysisalg_makefile)
	$(echo) "(constituents.make) Starting new_analysisalgclean"
	@-if test -f $(cmt_local_new_analysisalg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisalg_makefile) new_analysisalgclean; \
	fi
	$(echo) "(constituents.make) new_analysisalgclean done"
#	@-$(MAKE) -f $(cmt_local_new_analysisalg_makefile) new_analysisalgclean

##	  /bin/rm -f $(cmt_local_new_analysisalg_makefile) $(bin)new_analysisalg_dependencies.make

install :: new_analysisalginstall ;

new_analysisalginstall :: $(new_analysisalg_dependencies) $(cmt_local_new_analysisalg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_analysisalg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisalg_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_analysisalg_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_analysisalguninstall

$(foreach d,$(new_analysisalg_dependencies),$(eval $(d)uninstall_dependencies += new_analysisalguninstall))

new_analysisalguninstall : $(new_analysisalguninstall_dependencies) ##$(cmt_local_new_analysisalg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_analysisalg_makefile); then \
	  $(MAKE) -f $(cmt_local_new_analysisalg_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_analysisalg_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_analysisalguninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_analysisalg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_analysisalg done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_asgtool_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_asgtool_has_target_tag

cmt_local_tagfile_new_asgtool = $(bin)$(MyAnalysis_tag)_new_asgtool.make
cmt_final_setup_new_asgtool = $(bin)setup_new_asgtool.make
cmt_local_new_asgtool_makefile = $(bin)new_asgtool.make

new_asgtool_extratags = -tag_add=target_new_asgtool

else

cmt_local_tagfile_new_asgtool = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_asgtool = $(bin)setup.make
cmt_local_new_asgtool_makefile = $(bin)new_asgtool.make

endif

not_new_asgtool_dependencies = { n=0; for p in $?; do m=0; for d in $(new_asgtool_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_asgtooldirs :
	@if test ! -d $(bin)new_asgtool; then $(mkdir) -p $(bin)new_asgtool; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_asgtool
else
new_asgtooldirs : ;
endif

ifdef cmt_new_asgtool_has_target_tag

ifndef QUICK
$(cmt_local_new_asgtool_makefile) : $(new_asgtool_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_asgtool.make"; \
	  $(cmtexe) -tag=$(tags) $(new_asgtool_extratags) build constituent_config -out=$(cmt_local_new_asgtool_makefile) new_asgtool
else
$(cmt_local_new_asgtool_makefile) : $(new_asgtool_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_asgtool) ] || \
	  [ ! -f $(cmt_final_setup_new_asgtool) ] || \
	  $(not_new_asgtool_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_asgtool.make"; \
	  $(cmtexe) -tag=$(tags) $(new_asgtool_extratags) build constituent_config -out=$(cmt_local_new_asgtool_makefile) new_asgtool; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_asgtool_makefile) : $(new_asgtool_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_asgtool.make"; \
	  $(cmtexe) -f=$(bin)new_asgtool.in -tag=$(tags) $(new_asgtool_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_asgtool_makefile) new_asgtool
else
$(cmt_local_new_asgtool_makefile) : $(new_asgtool_dependencies) $(cmt_build_library_linksstamp) $(bin)new_asgtool.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_asgtool) ] || \
	  [ ! -f $(cmt_final_setup_new_asgtool) ] || \
	  $(not_new_asgtool_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_asgtool.make"; \
	  $(cmtexe) -f=$(bin)new_asgtool.in -tag=$(tags) $(new_asgtool_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_asgtool_makefile) new_asgtool; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_asgtool_extratags) build constituent_makefile -out=$(cmt_local_new_asgtool_makefile) new_asgtool

new_asgtool :: $(new_asgtool_dependencies) $(cmt_local_new_asgtool_makefile) dirs new_asgtooldirs
	$(echo) "(constituents.make) Starting new_asgtool"
	@if test -f $(cmt_local_new_asgtool_makefile); then \
	  $(MAKE) -f $(cmt_local_new_asgtool_makefile) new_asgtool; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_asgtool_makefile) new_asgtool
	$(echo) "(constituents.make) new_asgtool done"

clean :: new_asgtoolclean ;

new_asgtoolclean :: $(new_asgtoolclean_dependencies) ##$(cmt_local_new_asgtool_makefile)
	$(echo) "(constituents.make) Starting new_asgtoolclean"
	@-if test -f $(cmt_local_new_asgtool_makefile); then \
	  $(MAKE) -f $(cmt_local_new_asgtool_makefile) new_asgtoolclean; \
	fi
	$(echo) "(constituents.make) new_asgtoolclean done"
#	@-$(MAKE) -f $(cmt_local_new_asgtool_makefile) new_asgtoolclean

##	  /bin/rm -f $(cmt_local_new_asgtool_makefile) $(bin)new_asgtool_dependencies.make

install :: new_asgtoolinstall ;

new_asgtoolinstall :: $(new_asgtool_dependencies) $(cmt_local_new_asgtool_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_asgtool_makefile); then \
	  $(MAKE) -f $(cmt_local_new_asgtool_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_asgtool_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_asgtooluninstall

$(foreach d,$(new_asgtool_dependencies),$(eval $(d)uninstall_dependencies += new_asgtooluninstall))

new_asgtooluninstall : $(new_asgtooluninstall_dependencies) ##$(cmt_local_new_asgtool_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_asgtool_makefile); then \
	  $(MAKE) -f $(cmt_local_new_asgtool_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_asgtool_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_asgtooluninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_asgtool"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_asgtool done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_jobo_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_jobo_has_target_tag

cmt_local_tagfile_new_jobo = $(bin)$(MyAnalysis_tag)_new_jobo.make
cmt_final_setup_new_jobo = $(bin)setup_new_jobo.make
cmt_local_new_jobo_makefile = $(bin)new_jobo.make

new_jobo_extratags = -tag_add=target_new_jobo

else

cmt_local_tagfile_new_jobo = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_jobo = $(bin)setup.make
cmt_local_new_jobo_makefile = $(bin)new_jobo.make

endif

not_new_jobo_dependencies = { n=0; for p in $?; do m=0; for d in $(new_jobo_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_jobodirs :
	@if test ! -d $(bin)new_jobo; then $(mkdir) -p $(bin)new_jobo; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_jobo
else
new_jobodirs : ;
endif

ifdef cmt_new_jobo_has_target_tag

ifndef QUICK
$(cmt_local_new_jobo_makefile) : $(new_jobo_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_jobo.make"; \
	  $(cmtexe) -tag=$(tags) $(new_jobo_extratags) build constituent_config -out=$(cmt_local_new_jobo_makefile) new_jobo
else
$(cmt_local_new_jobo_makefile) : $(new_jobo_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_jobo) ] || \
	  [ ! -f $(cmt_final_setup_new_jobo) ] || \
	  $(not_new_jobo_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_jobo.make"; \
	  $(cmtexe) -tag=$(tags) $(new_jobo_extratags) build constituent_config -out=$(cmt_local_new_jobo_makefile) new_jobo; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_jobo_makefile) : $(new_jobo_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_jobo.make"; \
	  $(cmtexe) -f=$(bin)new_jobo.in -tag=$(tags) $(new_jobo_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_jobo_makefile) new_jobo
else
$(cmt_local_new_jobo_makefile) : $(new_jobo_dependencies) $(cmt_build_library_linksstamp) $(bin)new_jobo.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_jobo) ] || \
	  [ ! -f $(cmt_final_setup_new_jobo) ] || \
	  $(not_new_jobo_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_jobo.make"; \
	  $(cmtexe) -f=$(bin)new_jobo.in -tag=$(tags) $(new_jobo_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_jobo_makefile) new_jobo; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_jobo_extratags) build constituent_makefile -out=$(cmt_local_new_jobo_makefile) new_jobo

new_jobo :: $(new_jobo_dependencies) $(cmt_local_new_jobo_makefile) dirs new_jobodirs
	$(echo) "(constituents.make) Starting new_jobo"
	@if test -f $(cmt_local_new_jobo_makefile); then \
	  $(MAKE) -f $(cmt_local_new_jobo_makefile) new_jobo; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_jobo_makefile) new_jobo
	$(echo) "(constituents.make) new_jobo done"

clean :: new_joboclean ;

new_joboclean :: $(new_joboclean_dependencies) ##$(cmt_local_new_jobo_makefile)
	$(echo) "(constituents.make) Starting new_joboclean"
	@-if test -f $(cmt_local_new_jobo_makefile); then \
	  $(MAKE) -f $(cmt_local_new_jobo_makefile) new_joboclean; \
	fi
	$(echo) "(constituents.make) new_joboclean done"
#	@-$(MAKE) -f $(cmt_local_new_jobo_makefile) new_joboclean

##	  /bin/rm -f $(cmt_local_new_jobo_makefile) $(bin)new_jobo_dependencies.make

install :: new_joboinstall ;

new_joboinstall :: $(new_jobo_dependencies) $(cmt_local_new_jobo_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_jobo_makefile); then \
	  $(MAKE) -f $(cmt_local_new_jobo_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_jobo_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_jobouninstall

$(foreach d,$(new_jobo_dependencies),$(eval $(d)uninstall_dependencies += new_jobouninstall))

new_jobouninstall : $(new_jobouninstall_dependencies) ##$(cmt_local_new_jobo_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_jobo_makefile); then \
	  $(MAKE) -f $(cmt_local_new_jobo_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_jobo_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_jobouninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_jobo"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_jobo done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_new_skeleton_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_new_skeleton_has_target_tag

cmt_local_tagfile_new_skeleton = $(bin)$(MyAnalysis_tag)_new_skeleton.make
cmt_final_setup_new_skeleton = $(bin)setup_new_skeleton.make
cmt_local_new_skeleton_makefile = $(bin)new_skeleton.make

new_skeleton_extratags = -tag_add=target_new_skeleton

else

cmt_local_tagfile_new_skeleton = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_new_skeleton = $(bin)setup.make
cmt_local_new_skeleton_makefile = $(bin)new_skeleton.make

endif

not_new_skeleton_dependencies = { n=0; for p in $?; do m=0; for d in $(new_skeleton_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
new_skeletondirs :
	@if test ! -d $(bin)new_skeleton; then $(mkdir) -p $(bin)new_skeleton; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)new_skeleton
else
new_skeletondirs : ;
endif

ifdef cmt_new_skeleton_has_target_tag

ifndef QUICK
$(cmt_local_new_skeleton_makefile) : $(new_skeleton_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_skeleton.make"; \
	  $(cmtexe) -tag=$(tags) $(new_skeleton_extratags) build constituent_config -out=$(cmt_local_new_skeleton_makefile) new_skeleton
else
$(cmt_local_new_skeleton_makefile) : $(new_skeleton_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_skeleton) ] || \
	  [ ! -f $(cmt_final_setup_new_skeleton) ] || \
	  $(not_new_skeleton_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_skeleton.make"; \
	  $(cmtexe) -tag=$(tags) $(new_skeleton_extratags) build constituent_config -out=$(cmt_local_new_skeleton_makefile) new_skeleton; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_new_skeleton_makefile) : $(new_skeleton_dependencies) build_library_links
	$(echo) "(constituents.make) Building new_skeleton.make"; \
	  $(cmtexe) -f=$(bin)new_skeleton.in -tag=$(tags) $(new_skeleton_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_skeleton_makefile) new_skeleton
else
$(cmt_local_new_skeleton_makefile) : $(new_skeleton_dependencies) $(cmt_build_library_linksstamp) $(bin)new_skeleton.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_new_skeleton) ] || \
	  [ ! -f $(cmt_final_setup_new_skeleton) ] || \
	  $(not_new_skeleton_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building new_skeleton.make"; \
	  $(cmtexe) -f=$(bin)new_skeleton.in -tag=$(tags) $(new_skeleton_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_new_skeleton_makefile) new_skeleton; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(new_skeleton_extratags) build constituent_makefile -out=$(cmt_local_new_skeleton_makefile) new_skeleton

new_skeleton :: $(new_skeleton_dependencies) $(cmt_local_new_skeleton_makefile) dirs new_skeletondirs
	$(echo) "(constituents.make) Starting new_skeleton"
	@if test -f $(cmt_local_new_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_new_skeleton_makefile) new_skeleton; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_skeleton_makefile) new_skeleton
	$(echo) "(constituents.make) new_skeleton done"

clean :: new_skeletonclean ;

new_skeletonclean :: $(new_skeletonclean_dependencies) ##$(cmt_local_new_skeleton_makefile)
	$(echo) "(constituents.make) Starting new_skeletonclean"
	@-if test -f $(cmt_local_new_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_new_skeleton_makefile) new_skeletonclean; \
	fi
	$(echo) "(constituents.make) new_skeletonclean done"
#	@-$(MAKE) -f $(cmt_local_new_skeleton_makefile) new_skeletonclean

##	  /bin/rm -f $(cmt_local_new_skeleton_makefile) $(bin)new_skeleton_dependencies.make

install :: new_skeletoninstall ;

new_skeletoninstall :: $(new_skeleton_dependencies) $(cmt_local_new_skeleton_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_new_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_new_skeleton_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_new_skeleton_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : new_skeletonuninstall

$(foreach d,$(new_skeleton_dependencies),$(eval $(d)uninstall_dependencies += new_skeletonuninstall))

new_skeletonuninstall : $(new_skeletonuninstall_dependencies) ##$(cmt_local_new_skeleton_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_new_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_new_skeleton_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_new_skeleton_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: new_skeletonuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_skeleton"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_skeleton done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_make_skeleton_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_make_skeleton_has_target_tag

cmt_local_tagfile_make_skeleton = $(bin)$(MyAnalysis_tag)_make_skeleton.make
cmt_final_setup_make_skeleton = $(bin)setup_make_skeleton.make
cmt_local_make_skeleton_makefile = $(bin)make_skeleton.make

make_skeleton_extratags = -tag_add=target_make_skeleton

else

cmt_local_tagfile_make_skeleton = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_make_skeleton = $(bin)setup.make
cmt_local_make_skeleton_makefile = $(bin)make_skeleton.make

endif

not_make_skeleton_dependencies = { n=0; for p in $?; do m=0; for d in $(make_skeleton_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
make_skeletondirs :
	@if test ! -d $(bin)make_skeleton; then $(mkdir) -p $(bin)make_skeleton; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)make_skeleton
else
make_skeletondirs : ;
endif

ifdef cmt_make_skeleton_has_target_tag

ifndef QUICK
$(cmt_local_make_skeleton_makefile) : $(make_skeleton_dependencies) build_library_links
	$(echo) "(constituents.make) Building make_skeleton.make"; \
	  $(cmtexe) -tag=$(tags) $(make_skeleton_extratags) build constituent_config -out=$(cmt_local_make_skeleton_makefile) make_skeleton
else
$(cmt_local_make_skeleton_makefile) : $(make_skeleton_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_make_skeleton) ] || \
	  [ ! -f $(cmt_final_setup_make_skeleton) ] || \
	  $(not_make_skeleton_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building make_skeleton.make"; \
	  $(cmtexe) -tag=$(tags) $(make_skeleton_extratags) build constituent_config -out=$(cmt_local_make_skeleton_makefile) make_skeleton; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_make_skeleton_makefile) : $(make_skeleton_dependencies) build_library_links
	$(echo) "(constituents.make) Building make_skeleton.make"; \
	  $(cmtexe) -f=$(bin)make_skeleton.in -tag=$(tags) $(make_skeleton_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_make_skeleton_makefile) make_skeleton
else
$(cmt_local_make_skeleton_makefile) : $(make_skeleton_dependencies) $(cmt_build_library_linksstamp) $(bin)make_skeleton.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_make_skeleton) ] || \
	  [ ! -f $(cmt_final_setup_make_skeleton) ] || \
	  $(not_make_skeleton_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building make_skeleton.make"; \
	  $(cmtexe) -f=$(bin)make_skeleton.in -tag=$(tags) $(make_skeleton_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_make_skeleton_makefile) make_skeleton; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(make_skeleton_extratags) build constituent_makefile -out=$(cmt_local_make_skeleton_makefile) make_skeleton

make_skeleton :: $(make_skeleton_dependencies) $(cmt_local_make_skeleton_makefile) dirs make_skeletondirs
	$(echo) "(constituents.make) Starting make_skeleton"
	@if test -f $(cmt_local_make_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_make_skeleton_makefile) make_skeleton; \
	  fi
#	@$(MAKE) -f $(cmt_local_make_skeleton_makefile) make_skeleton
	$(echo) "(constituents.make) make_skeleton done"

clean :: make_skeletonclean ;

make_skeletonclean :: $(make_skeletonclean_dependencies) ##$(cmt_local_make_skeleton_makefile)
	$(echo) "(constituents.make) Starting make_skeletonclean"
	@-if test -f $(cmt_local_make_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_make_skeleton_makefile) make_skeletonclean; \
	fi
	$(echo) "(constituents.make) make_skeletonclean done"
#	@-$(MAKE) -f $(cmt_local_make_skeleton_makefile) make_skeletonclean

##	  /bin/rm -f $(cmt_local_make_skeleton_makefile) $(bin)make_skeleton_dependencies.make

install :: make_skeletoninstall ;

make_skeletoninstall :: $(make_skeleton_dependencies) $(cmt_local_make_skeleton_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_make_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_make_skeleton_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_make_skeleton_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : make_skeletonuninstall

$(foreach d,$(make_skeleton_dependencies),$(eval $(d)uninstall_dependencies += make_skeletonuninstall))

make_skeletonuninstall : $(make_skeletonuninstall_dependencies) ##$(cmt_local_make_skeleton_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_make_skeleton_makefile); then \
	  $(MAKE) -f $(cmt_local_make_skeleton_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_make_skeleton_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: make_skeletonuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ make_skeleton"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ make_skeleton done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_checkout_pkg_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_checkout_pkg_has_target_tag

cmt_local_tagfile_checkout_pkg = $(bin)$(MyAnalysis_tag)_checkout_pkg.make
cmt_final_setup_checkout_pkg = $(bin)setup_checkout_pkg.make
cmt_local_checkout_pkg_makefile = $(bin)checkout_pkg.make

checkout_pkg_extratags = -tag_add=target_checkout_pkg

else

cmt_local_tagfile_checkout_pkg = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_checkout_pkg = $(bin)setup.make
cmt_local_checkout_pkg_makefile = $(bin)checkout_pkg.make

endif

not_checkout_pkg_dependencies = { n=0; for p in $?; do m=0; for d in $(checkout_pkg_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
checkout_pkgdirs :
	@if test ! -d $(bin)checkout_pkg; then $(mkdir) -p $(bin)checkout_pkg; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)checkout_pkg
else
checkout_pkgdirs : ;
endif

ifdef cmt_checkout_pkg_has_target_tag

ifndef QUICK
$(cmt_local_checkout_pkg_makefile) : $(checkout_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building checkout_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(checkout_pkg_extratags) build constituent_config -out=$(cmt_local_checkout_pkg_makefile) checkout_pkg
else
$(cmt_local_checkout_pkg_makefile) : $(checkout_pkg_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_checkout_pkg) ] || \
	  [ ! -f $(cmt_final_setup_checkout_pkg) ] || \
	  $(not_checkout_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building checkout_pkg.make"; \
	  $(cmtexe) -tag=$(tags) $(checkout_pkg_extratags) build constituent_config -out=$(cmt_local_checkout_pkg_makefile) checkout_pkg; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_checkout_pkg_makefile) : $(checkout_pkg_dependencies) build_library_links
	$(echo) "(constituents.make) Building checkout_pkg.make"; \
	  $(cmtexe) -f=$(bin)checkout_pkg.in -tag=$(tags) $(checkout_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_checkout_pkg_makefile) checkout_pkg
else
$(cmt_local_checkout_pkg_makefile) : $(checkout_pkg_dependencies) $(cmt_build_library_linksstamp) $(bin)checkout_pkg.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_checkout_pkg) ] || \
	  [ ! -f $(cmt_final_setup_checkout_pkg) ] || \
	  $(not_checkout_pkg_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building checkout_pkg.make"; \
	  $(cmtexe) -f=$(bin)checkout_pkg.in -tag=$(tags) $(checkout_pkg_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_checkout_pkg_makefile) checkout_pkg; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(checkout_pkg_extratags) build constituent_makefile -out=$(cmt_local_checkout_pkg_makefile) checkout_pkg

checkout_pkg :: $(checkout_pkg_dependencies) $(cmt_local_checkout_pkg_makefile) dirs checkout_pkgdirs
	$(echo) "(constituents.make) Starting checkout_pkg"
	@if test -f $(cmt_local_checkout_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_checkout_pkg_makefile) checkout_pkg; \
	  fi
#	@$(MAKE) -f $(cmt_local_checkout_pkg_makefile) checkout_pkg
	$(echo) "(constituents.make) checkout_pkg done"

clean :: checkout_pkgclean ;

checkout_pkgclean :: $(checkout_pkgclean_dependencies) ##$(cmt_local_checkout_pkg_makefile)
	$(echo) "(constituents.make) Starting checkout_pkgclean"
	@-if test -f $(cmt_local_checkout_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_checkout_pkg_makefile) checkout_pkgclean; \
	fi
	$(echo) "(constituents.make) checkout_pkgclean done"
#	@-$(MAKE) -f $(cmt_local_checkout_pkg_makefile) checkout_pkgclean

##	  /bin/rm -f $(cmt_local_checkout_pkg_makefile) $(bin)checkout_pkg_dependencies.make

install :: checkout_pkginstall ;

checkout_pkginstall :: $(checkout_pkg_dependencies) $(cmt_local_checkout_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_checkout_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_checkout_pkg_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_checkout_pkg_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : checkout_pkguninstall

$(foreach d,$(checkout_pkg_dependencies),$(eval $(d)uninstall_dependencies += checkout_pkguninstall))

checkout_pkguninstall : $(checkout_pkguninstall_dependencies) ##$(cmt_local_checkout_pkg_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_checkout_pkg_makefile); then \
	  $(MAKE) -f $(cmt_local_checkout_pkg_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_checkout_pkg_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: checkout_pkguninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ checkout_pkg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ checkout_pkg done"
endif

#-- end of constituent ------
#-- start of constituent ------

cmt_cppcheck_has_no_target_tag = 1

#--------------------------------------

ifdef cmt_cppcheck_has_target_tag

cmt_local_tagfile_cppcheck = $(bin)$(MyAnalysis_tag)_cppcheck.make
cmt_final_setup_cppcheck = $(bin)setup_cppcheck.make
cmt_local_cppcheck_makefile = $(bin)cppcheck.make

cppcheck_extratags = -tag_add=target_cppcheck

else

cmt_local_tagfile_cppcheck = $(bin)$(MyAnalysis_tag).make
cmt_final_setup_cppcheck = $(bin)setup.make
cmt_local_cppcheck_makefile = $(bin)cppcheck.make

endif

not_cppcheck_dependencies = { n=0; for p in $?; do m=0; for d in $(cppcheck_dependencies); do if [ $$p = $$d ]; then m=1; break; fi; done; if [ $$m -eq 0 ]; then n=1; break; fi; done; [ $$n -eq 1 ]; }

ifdef STRUCTURED_OUTPUT
cppcheckdirs :
	@if test ! -d $(bin)cppcheck; then $(mkdir) -p $(bin)cppcheck; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)cppcheck
else
cppcheckdirs : ;
endif

ifdef cmt_cppcheck_has_target_tag

ifndef QUICK
$(cmt_local_cppcheck_makefile) : $(cppcheck_dependencies) build_library_links
	$(echo) "(constituents.make) Building cppcheck.make"; \
	  $(cmtexe) -tag=$(tags) $(cppcheck_extratags) build constituent_config -out=$(cmt_local_cppcheck_makefile) cppcheck
else
$(cmt_local_cppcheck_makefile) : $(cppcheck_dependencies) $(cmt_build_library_linksstamp) $(use_requirements)
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_cppcheck) ] || \
	  [ ! -f $(cmt_final_setup_cppcheck) ] || \
	  $(not_cppcheck_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building cppcheck.make"; \
	  $(cmtexe) -tag=$(tags) $(cppcheck_extratags) build constituent_config -out=$(cmt_local_cppcheck_makefile) cppcheck; \
	  fi
endif

else

ifndef QUICK
$(cmt_local_cppcheck_makefile) : $(cppcheck_dependencies) build_library_links
	$(echo) "(constituents.make) Building cppcheck.make"; \
	  $(cmtexe) -f=$(bin)cppcheck.in -tag=$(tags) $(cppcheck_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_cppcheck_makefile) cppcheck
else
$(cmt_local_cppcheck_makefile) : $(cppcheck_dependencies) $(cmt_build_library_linksstamp) $(bin)cppcheck.in
	@if [ ! -f $@ ] || [ ! -f $(cmt_local_tagfile_cppcheck) ] || \
	  [ ! -f $(cmt_final_setup_cppcheck) ] || \
	  $(not_cppcheck_dependencies) ; then \
	  test -z "$(cmtmsg)" || \
	  echo "$(CMTMSGPREFIX)" "(constituents.make) Building cppcheck.make"; \
	  $(cmtexe) -f=$(bin)cppcheck.in -tag=$(tags) $(cppcheck_extratags) build constituent_makefile -without_cmt -out=$(cmt_local_cppcheck_makefile) cppcheck; \
	  fi
endif

endif

#	  $(cmtexe) -tag=$(tags) $(cppcheck_extratags) build constituent_makefile -out=$(cmt_local_cppcheck_makefile) cppcheck

cppcheck :: $(cppcheck_dependencies) $(cmt_local_cppcheck_makefile) dirs cppcheckdirs
	$(echo) "(constituents.make) Starting cppcheck"
	@if test -f $(cmt_local_cppcheck_makefile); then \
	  $(MAKE) -f $(cmt_local_cppcheck_makefile) cppcheck; \
	  fi
#	@$(MAKE) -f $(cmt_local_cppcheck_makefile) cppcheck
	$(echo) "(constituents.make) cppcheck done"

clean :: cppcheckclean ;

cppcheckclean :: $(cppcheckclean_dependencies) ##$(cmt_local_cppcheck_makefile)
	$(echo) "(constituents.make) Starting cppcheckclean"
	@-if test -f $(cmt_local_cppcheck_makefile); then \
	  $(MAKE) -f $(cmt_local_cppcheck_makefile) cppcheckclean; \
	fi
	$(echo) "(constituents.make) cppcheckclean done"
#	@-$(MAKE) -f $(cmt_local_cppcheck_makefile) cppcheckclean

##	  /bin/rm -f $(cmt_local_cppcheck_makefile) $(bin)cppcheck_dependencies.make

install :: cppcheckinstall ;

cppcheckinstall :: $(cppcheck_dependencies) $(cmt_local_cppcheck_makefile)
	$(echo) "(constituents.make) Starting $@"
	@if test -f $(cmt_local_cppcheck_makefile); then \
	  $(MAKE) -f $(cmt_local_cppcheck_makefile) install; \
	  fi
#	@-$(MAKE) -f $(cmt_local_cppcheck_makefile) install
	$(echo) "(constituents.make) $@ done"

uninstall : cppcheckuninstall

$(foreach d,$(cppcheck_dependencies),$(eval $(d)uninstall_dependencies += cppcheckuninstall))

cppcheckuninstall : $(cppcheckuninstall_dependencies) ##$(cmt_local_cppcheck_makefile)
	$(echo) "(constituents.make) Starting $@"
	@-if test -f $(cmt_local_cppcheck_makefile); then \
	  $(MAKE) -f $(cmt_local_cppcheck_makefile) uninstall; \
	  fi
#	@$(MAKE) -f $(cmt_local_cppcheck_makefile) uninstall
	$(echo) "(constituents.make) $@ done"

remove_library_links :: cppcheckuninstall ;

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ cppcheck"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ cppcheck done"
endif

#-- end of constituent ------
#-- start of constituents_trailer ------

uninstall : remove_library_links ;
clean ::
	$(cleanup_echo) $(cmt_build_library_linksstamp)
	-$(cleanup_silent) \rm -f $(cmt_build_library_linksstamp)
#clean :: remove_library_links

remove_library_links ::
ifndef QUICK
	$(echo) "(constituents.make) Removing library links"; \
	  $(remove_library_links)
else
	$(echo) "(constituents.make) Removing library links"; \
	  $(remove_library_links) -f=$(bin)library_links.in -without_cmt
endif

#-- end of constituents_trailer ------
