#!/bin/sh

CURRENT_DIR=`pwd`
AUTOPOINT_TMP_DIR=`mktemp -d autopoint.tmp.XXXXXXXXXX`

echo "*** Entering temporary directory ${AUTOPOINT_TMP_DIR}"
cd ${AUTOPOINT_TMP_DIR}

echo
echo "*** Creating dummy configure.ac"
{
    cat <<EOF
AM_GNU_GETTEXT_REQUIRE_VERSION([0.19.8])
AM_GNU_GETTEXT([external])
EOF
} > configure.ac

echo
echo "*** Invoking autopoint"

autopoint

echo
echo "*** Leaving temporary directory ${AUTOPOINT_TMP_DIR}"
cd ${CURRENT_DIR}

echo
echo "*** Copying config.rpath from temporary directory"
cp ${AUTOPOINT_TMP_DIR}/config.rpath .

echo
echo "*** Deleting temporary directory"
rm -fr ${AUTOPOINT_TMP_DIR}

echo
echo "*** Invoking autoreconf"
autoreconf -v -i
