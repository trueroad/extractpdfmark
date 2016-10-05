#!/bin/sh

EXPECTEDPDFMARK=$1
BASENAME=`basename ${EXPECTEDPDFMARK} | sed -e "s/-expected\.pdfmark$//"`

PDF="${BASENAME}.pdf"
EXTRACTEDPDFMARK="${BASENAME}-expected-test.pdfmark"

if [ ! -e ${EXPECTEDPDFMARK} ]; then
    EXPEXTEDPDFMARK="${srcdir}/${BASENAME}-expected.pdfmark"
fi
if [ ! -e ${PDF} ]; then
    PDF="${srcdir}/${BASENAME}.pdf"
fi

${top_builddir}/src/extractpdfmark ${PDF} | \
    ${GREP} -v "^%\|^$" > ${EXTRACTEDPDFMARK}

if test x"$DIFF" = x; then
    # skip
    exit 77
fi

${DIFF} -ubwBE  ${EXPECTEDPDFMARK} ${EXTRACTEDPDFMARK}
