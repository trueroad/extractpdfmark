#!/bin/sh

BASENAME="desttype"

PDFFILENAME="${BASENAME}.pdf"
PSFILENAME="${BASENAME}.ps"
PDFFILENAME2="${BASENAME}-2.pdf"
PSFILENAME2="${BASENAME}-2.ps"

if [ ! -e ${PDFFILENAME} ]; then
    PDFFILENAME="${srcdir}/${BASENAME}.pdf"
fi

${top_builddir}/src/extractpdfmark -o ${PSFILENAME} ${PDFFILENAME}
${GS} -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=${PDFFILENAME2} \
      ${PDFFILENAME} ${PSFILENAME}
${top_builddir}/src/extractpdfmark -o ${PSFILENAME2} ${PDFFILENAME2}

diff -u ${PSFILENAME} ${PSFILENAME2}
