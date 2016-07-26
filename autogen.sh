#!/bin/sh

autoheader
aclocal
automake --add-missing --copy
autoconf
