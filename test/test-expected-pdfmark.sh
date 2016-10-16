#!/bin/sh

EXPECTEDPDFMARK=$1
BASENAME=`basename ${EXPECTEDPDFMARK} | sed -e "s/-expected\(-.\+\)\?\.pdfmark$//"`
OPTSUFFIX=`echo ${EXPECTEDPDFMARK} | sed -e "s/^\(.*-expected\)\(-.\+\)\?\.pdfmark$/\2/"`

PDF="${BASENAME}.pdf"
EXTRACTEDPDFMARK="${BASENAME}-expected${OPTSUFFIX}-test.pdfmark"

if [ ! -e ${EXPECTEDPDFMARK} ]; then
    EXPEXTEDPDFMARK="${srcdir}/${BASENAME}-expected${OPTSUFFIX}.pdfmark"
fi
if [ ! -e ${PDF} ]; then
    PDF="${srcdir}/${BASENAME}.pdf"
fi
if [ ! -s ${PDF} ]; then
    # skip
    exit 77
fi

case "$OPTSUFFIX" in
    "-literal" )
	OPTION="--style=literal"
	;;
    "-literal-escape" )
	OPTION="--style=literal --escape"
	;;
    "-hex" )
	OPTION="--style=hex"
	;;
    "-name" )
	OPTION="--style=name"
	;;
    "-name-escape" )
	OPTION="--style=name --escape"
	;;
    * )
	OPTION=""
	;;
esac

${top_builddir}/src/extractpdfmark ${OPTION} ${PDF} | \
    ${GREP} -v "^%\|^$" > ${EXTRACTEDPDFMARK}

if test x"$DIFF" = x; then
    # skip
    exit 77
fi

${DIFF} -ubwBE  ${EXPECTEDPDFMARK} ${EXTRACTEDPDFMARK}
