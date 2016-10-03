#!/bin/sh

${top_builddir}/src/extractpdfmark -o desttype.ps desttype.pdf
${GS} -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=desttype-2.pdf desttype.pdf desttype.ps
${top_builddir}/src/extractpdfmark -o desttype-2.ps desttype-2.pdf

diff -u desttype.ps desttype-2.ps
