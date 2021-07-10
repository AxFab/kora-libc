#!/bin/bash

SCRIPT_NAME="${BASH_SOURCE}"
SCRIPT_DIRE="`dirname ${SCRIPT_NAME}`"
SCRIPT_HOME="`readlink -f ${SCRIPT_DIRE}/..`"

FILE="${SCRIPT_HOME}/spec/symbols.csv"
if [ -n "$1" ]; then
    FILE=$1
fi

for rec in `cat ${FILE}`; do
    # Parse symbol information
    sym=`echo "${rec}" | cut -f 1 -d ','`
    if [ "$sym" == "Name" ]; then
        continue
    fi
    inc=`echo "${rec}" | cut -f 2 -d ','`
    lib=`echo "${rec}" | cut -f 3 -d ','`
    src=`echo "${rec}" | cut -f 4 -d ','`
    spec=`echo "${rec}" | tr '\r' ',' | cut -f 5 -d ','`
    if [ ! -f "${SCRIPT_HOME}/lib/${lib}.so" ]; then
        continue;
    fi
    if [ -z "${spec}" ]; then
        continue;
    fi
    if [ "${spec}" == "POSIX&UNIX" ]; then
        continue;
    fi
    if [ "${spec}" == "C99" ]; then
        continue;
    fi
    if [ "${spec}" == "UNIX" ]; then
        continue;
    fi
    # echo "Sym: $sym,  Inc: $inc,  Lib: $lib,  Src: $src,  Spec: '$spec'"

    # Check symbol is present
    R=`nm "${SCRIPT_HOME}/lib/${lib}.so" | grep "\b${sym}"`
    if [ -z "${R}" ]; then
        echo "Missing symbol ${sym} (${spec})"
        continue
    fi

    # Check symbol is available through header
    cat > test_check.c << EOF
#include <${inc}>
int main() { void* p = (void*)${sym}; return 0; }
EOF
    gcc -o test_check.x test_check.c -nostdinc \
        "-I${SCRIPT_HOME}/include"  \
        "-I${SCRIPT_HOME}/src/include/blank"  \
        "-I${SCRIPT_HOME}/src/include/i386"  \
        "-I${SCRIPT_HOME}/src/include/kora"  \
        -D_CTYPE_NO_MACROS 2>/dev/null
    if [ $? != 0 ]; then
        echo "Symbol ${sym} unavailable through ${inc}"
        continue
    fi

done

rm -f test_check.c test_check.x

STD=`gcc -o test_include.x ${SCRIPT_HOME}/spec/include.c -nostdinc \
        "-I${SCRIPT_HOME}/include"  \
        "-I${SCRIPT_HOME}/src/include/blank"  \
        "-I${SCRIPT_HOME}/src/include/i386"  \
        "-I${SCRIPT_HOME}/src/include/kora"  \
        -D_CTYPE_NO_MACROS  2>&1`
if [ $? != 0 ]; then
    echo "Error on include files :: ${STD}"
fi

