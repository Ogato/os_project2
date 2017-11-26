all: pid_info vminfo tests

pid_info:
	$(MAKE) -f Makefile.info

vminfo:
	$(MAKE) -f Makefile.vminfo

tests:
	$(MAKE) -f Makefile.tests
