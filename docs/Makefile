# Sphinx documentation Makefile

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = python3 -m sphinx
SOURCEDIR     = .
BUILDDIR      = _build

# Internal variables.
ALLSPHINXOPTS   = -d $(BUILDDIR)/doctrees $(SPHINXOPTS) $(SOURCEDIR)

.PHONY: help clean html doxygen

help:
	@echo "Please use \`make <target>' where <target> is one of"
	@echo "  html       to make standalone HTML files"
	@echo "  clean      to clean build directory"
	@echo "  doxygen    to generate Doxygen XML files"

clean:
	rm -rf $(BUILDDIR)/*
	rm -rf doxygen/

html: doxygen
	$(SPHINXBUILD) -b html $(ALLSPHINXOPTS) $(BUILDDIR)/html
	@echo
	@echo "Build finished. The HTML pages are in $(BUILDDIR)/html."

doxygen:
	@echo "Generating Doxygen XML files..."
	mkdir -p doxygen
	doxygen Doxyfile.xml 