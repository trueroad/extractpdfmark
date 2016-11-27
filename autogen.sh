#!/bin/sh

CURRENT_DIR=`pwd`
AUTOPOINT_TMP_DIR=`mktemp -d autopoint.tmp.XXXXXXXXXX`

echo "*** Entering temporary directory ${AUTOPOINT_TMP_DIR}"
cd ${AUTOPOINT_TMP_DIR}

echo
echo "*** Creating dummy configure.ac"
{
    cat <<EOF
AM_GNU_GETTEXT_REQUIRE_VERSION([0.19.6])
AM_GNU_GETTEXT([external])
EOF
} > configure.ac

echo
echo "*** Invoking autopoint"

autopoint ||
    {
	echo
	echo "WARNING: autopoint failed."
	echo "WARNING: It is required for getting \`config.rpath'."
	echo "WARNING: Please consider to install autopoint-0.19.6+."
    }

echo
echo "*** Leaving temporary directory ${AUTOPOINT_TMP_DIR}"
cd ${CURRENT_DIR}

echo
echo "*** Copying config.rpath from temporary directory"
cp ${AUTOPOINT_TMP_DIR}/config.rpath . ||
    {
	echo
	echo "WARNING: Copy failed."
	if [ -e config.rpath ]; then
	    echo "WARNING: Using existing \`config.rpath'."
	else
	    echo
	    echo "ERROR: config.rpath does not exist."
	    echo "ERROR: Please consider to install autopoint-0.19.6+"
	    echo "ERROR: or copy \`config.rpath'."
	    exit 1
	fi
    }

echo
echo "*** Deleting temporary directory"
rm -fr ${AUTOPOINT_TMP_DIR}

echo
echo "*** Invoking autoreconf"
autoreconf -v -i
