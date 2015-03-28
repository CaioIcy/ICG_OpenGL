#!/bin/bash
pdflatex gdd_dsw_icg.tex
bibtex gdd_dsw_icg
pdflatex gdd_dsw_icg.tex x 2
