all: 6UVME TDC64M
6UVME::
	(cd src/6uvme; make -f Makefile_root; make -f Makefile_root install)
TDC64M::
	(cd src/tdc64m; make -f Makefile_root; make -f Makefile_root install)
clean::
	(cd src/6uvme; make -f Makefile_root clean;)
	(cd src/tdc64m; make -f Makefile_root clean;)
