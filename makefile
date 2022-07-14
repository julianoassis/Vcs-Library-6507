
SUBDIRS = src-00_compile_test

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
	mv $@/game.a26 bin/$(subst src-,"",$@).a26

.PHONY: cleanall
cleanall:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	rm -f bin/*.a26
