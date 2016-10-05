#!/bin/sh

EXTRACTEDPDFMARK=$1
BASENAME=`basename ${EXTRACTEDPDFMARK} | sed -e "s/-round\.ps$//"`

PDF="${BASENAME}.pdf"
PDF2="${BASENAME}-round-test.pdf"
EXTRACTEDPDFMARK2="${BASENAME}-round-test.ps"

if [ ! -e ${PDF} ]; then
    PDF="${srcdir}/${BASENAME}.pdf"
fi

${GS} -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=${PDF2} \
      ${PDF} ${EXTRACTEDPDFMARK}
${top_builddir}/src/extractpdfmark -o ${EXTRACTEDPDFMARK2} ${PDF2}

if test x"$DIFF" = x; then
    # skip
    exit 77
fi

${DIFF} -u ${EXTRACTEDPDFMARK} ${EXTRACTEDPDFMARK2}
