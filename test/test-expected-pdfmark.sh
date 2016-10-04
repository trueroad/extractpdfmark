#!/bin/sh

MARKFILENAME=$1
BASENAME=`basename ${MARKFILENAME} .mark`

PDFFILENAME="${BASENAME}.pdf"
PSFILENAME="${BASENAME}.ps"

if [ ! -e ${MARKFILENAME} ]; then
    MARKFILENAME="${srcdir}/${BASENAME}.mark"
fi
if [ ! -e ${PDFFILENAME} ]; then
    PDFFILENAME="${srcdir}/${BASENAME}.pdf"
fi

${top_builddir}/src/extractpdfmark ${PDFFILENAME} | \
    ${GREP} -v "^%\|^$" > ${PSFILENAME}

diff -ubwBE  ${MARKFILENAME} ${PSFILENAME}
