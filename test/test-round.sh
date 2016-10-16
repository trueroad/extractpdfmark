#!/bin/sh

EXTRACTEDPDFMARK=$1
BASENAME=`basename ${EXTRACTEDPDFMARK} | sed -e "s/-round\(-.\+\)\?\.ps$//"`
OPTSUFFIX=`echo ${EXTRACTEDPDFMARK} | sed -e "s/^\(.*-round\)\(-.\+\)\?\.ps$/\2/"`

PDF="${BASENAME}.pdf"
PDF2="${BASENAME}-round${OPTSUFFIX}-test.pdf"
EXTRACTEDPDFMARK2="${BASENAME}-round${OPTSUFFIX}-test.ps"

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

if test x"$GHOSTSCRIPT" = x; then
    # skip
    exit 77
fi

${GHOSTSCRIPT} -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=${PDF2} \
    ${PDF} ${EXTRACTEDPDFMARK}
${top_builddir}/src/extractpdfmark ${OPTION} -o ${EXTRACTEDPDFMARK2} ${PDF2}

if test x"$DIFF" = x; then
    # skip
    exit 77
fi

${DIFF} -u ${EXTRACTEDPDFMARK} ${EXTRACTEDPDFMARK2}
