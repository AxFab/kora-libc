#!/bin/bash
#      This file is part of the KoraOS project.
#  Copyright (C) 2015-2021  <Fabien Bavent>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
set -e

SCRIPT_NAME="$BASH_SOURCE"
SCRIPT_DIR=`dirname "$BASH_SOURCE"`
SCRIPT_HOME=`readlink -f "${SCRIPT_DIR}/.."`

PATCHES_DIR=`readlink -f "${SCRIPT_DIR}/patches"`

# ------------------------------
# Configuration

source "${SCRIPT_DIR}/utils.sh"

VERSION_autoconf='2.64'
VERSION_automake='1.11.6'
VERSION_nasm='2.14.02'
VERSION_binutils='2.30' # '2.33.1'
VERSION_gcc='7.3.0' # '10.1.0'


SRCDIR=$(readlink -f `pwd`/sources)
GENDIR=''
PREFIX=''
TARGET=i386-kora
WGETFLAGS=
MAKETHRDS=4
DEV_MODE='n'
CLEAN_MODE='n'
BUILD_MODE='y'
AUTOTOOLS_MODE='y'
INFO_MODE='n'

# ------------------------------
# Building scripts

function make_generic {
    DIRECTORY="$1"

    ${DIRECTORY}/configure --target=$TARGET --prefix=$PREFIX
    make -j "$MAKETHRDS"
    make install
}

function make_binutils {
    DIRECTORY="$1"

    pushd "${DIRECTORY}/ld"
    automake
    autoconf
    popd

    ${DIRECTORY}/configure \
        --target=$TARGET \
        --prefix=$PREFIX \
        --with-sysroot=$PREFIX \
        --disable-nls \
        --disable-werror \
        --enable-shared
    make -j "$MAKETHRDS"
    make install
}

function make_gcc {
    DIRECTORY="$1"

    pushd "${DIRECTORY}/libstdc++-v3"
    automake
    autoconf
    popd

    pushd "${DIRECTORY}/gcc"
    autoconf
    popd

    pushd "${DIRECTORY}"
    ./contrib/download_prerequisites
    autoconf
    popd

    ${DIRECTORY}/configure \
        --target=$TARGET \
        --prefix=$PREFIX \
        --with-sysroot=$PREFIX \
        --disable-nls \
        --enable-shared \
        -enable-languages=c,c++

    make -j "$MAKETHRDS" all-gcc
    make -j "$MAKETHRDS" all-target-libgcc
    # make -j "$MAKETHRDS" all-target-libstdc++-v3
    make install-gcc
    make install-target-libgcc
    # make install-target-libstdc++-v3
}

function info {
    NAME="$1"
    K="VERSION_${NAME}"
    VERSION="${!K}"
    echo_important "Need package ${NAME} ${VERSION}"
}

function build {
    # Build some variables
    NAME="$1"
    K="VERSION_${NAME}"
    VERSION="${!K}"
    DIRECTORY=${NAME}-${VERSION}
    FILENAME=${DIRECTORY}.tar.xz
    URL="http://ftp.gnu.org/gnu/${NAME}/${FILENAME}"
    MAKE='make_generic'

    if [ "${NAME}" == 'gcc' ]; then
        URL="http://ftp.gnu.org/gnu/${NAME}/${DIRECTORY}/${FILENAME}"
    fi
    if [ "${NAME}" == 'nasm' ]; then
        URL="https://www.nasm.us/pub/nasm/releasebuilds/${VERSION}/${FILENAME}"
    fi
    if [ "${NAME}" == 'gcc' ] || [ "${NAME}" == 'binutils' ]; then
        MAKE="make_${NAME}"
    fi

    echo_important "Package ${NAME} ${VERSION}"

    cd "${SRCDIR}"

    # Download tarball
    if [ ! -e "${FILENAME}" ]; then
        echo_info "Dowloading ${NAME}"
        wget $WGETFLAGS "${URL}"
    else
        echo_info "Skipped dowloading ${NAME}"
    fi

    # Extract sources
    if [ "${CLEAN_MODE}" = 'y' ]; then
        rm -rf "${DIRECTORY}"
    fi
    if [ ! -d "${DIRECTORY}" ]; then
        echo_info "Extracting ${NAME}..."
        tar -xf "${FILENAME}"

        pushd "${DIRECTORY}"
        if [ "${DEV_MODE}" = 'y' ]; then
            git init
            git add .
            git commit -m "Saving ${NAME} ${VERSION}"
            git tag "v${VERSION}"
        fi
        if [ -e "${PATCHES_DIR}/${NAME}-${VERSION}.patch" ]; then
            echo_info "Patching ${NAME} ${VERSION}"
            patch -u -p 1 -i "${PATCHES_DIR}/${NAME}-${VERSION}.patch"
        elif [ -e "${PATCHES_DIR}/${NAME}.patch" ]; then
            echo_info "Patching ${NAME}"
            echo_warning "Using generic patch for ${NAME}, the version ${VERSION} is probably untested"
            patch -u -p 1 -i "${PATCHES_DIR}/${NAME}.patch"
        fi
        popd
    else
        echo_info "Using existing sources at ${DIRECTORY}"
    fi

    cd "${GENDIR}"

    # Building
    if [ "${CLEAN_MODE}" = 'y' ]; then
        rm -rf "${DIRECTORY}"
    fi
    mkdir -p "${DIRECTORY}"
    pushd "${DIRECTORY}"
    echo_info "Building ${NAME} ${VERSION}..."
    if [ "${BUILD_MODE}" = 'y' ]; then
        unset PKG_CONFIG_LIBDIR
        ${MAKE} "${SRCDIR}/${DIRECTORY}"
    fi
    popd

    echo_important "Build completed ${NAME} ${VERSION}"
}


# AUTOCONF_URL="ftp://ftp.gnu.org/pub/gnu/autoconf/$AUTOCONF.tar.xz"
# AUTOMAKE_URL="http://ftp.gnu.org/gnu/automake/$AUTOMAKE.tar.xz"
# NASM_URL="https://www.nasm.us/pub/nasm/releasebuilds/2.14.02/$NASM.tar.xz"
# BUTILS_URL="https://ftp.gnu.org/gnu/binutils/$BUTILS.tar.xz"
# GCC_URL="https://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.xz"


# ------------------------------
# Reading scrits parameters

function HELP {
    cat << EOF
Usage: ${SCRIPT_NAME} [OPTIONS]
with options:
    --srcdir=SRCDIR     Change the directory to put sources (default \$pwd/sources)
    --gendir=GENDIR     Change the building directory (default \$pwd/build-\$TARGET)
    --prefix=PREFIX     Change the installation directory (default \$pwd/tools-\$TARGET)
    --target=TARGET     Triplet of the destination platform
    --wgetflags=FLAGS   Setup some flags for 'wget' tool
    --makethrds=FLAGS   Setup the number of threads for 'make' tool
    --develop           Setup the environment for package hacking
    --cleaning          Clean up the sources and build environment first
    --no-build          Dry-run, won't build any packages
    --no-autotools      Don't recompile automake and autoconf, use the host ones
    --info              Don't do anything, just print basic configuration
    --help              Display this helper
EOF
}


while (( $# > 0 )); do
    case $1 in
        --srcdir=*) SRCDIR=`readlink -f ${1:9}` ;;
        --gendir=*) GENDIR=`readlink -f ${1:9}` ;;
        --prefix=*) PREFIX=`readlink -f ${1:9}` ;;
        --target=*) TARGET=${1:9} ;;
        --wgetflags=*) WGETFLAGS=${1:12} ;;
        --makethrds=*) MAKETHRDS=${1:12} ;;
        --develop) DEV_MODE='y' ;;
        --cleaning) CLEAN_MODE='y' ;;
        --no-build) BUILD_MODE='n' ;;
        --no-autotools) AUTOTOOLS_MODE='n' ;;
        --info) INFO_MODE=y ;;
        --help) HELP; exit 0 ;;
        *) HELP; exit 1 ;;
    esac
    shift
done

if [ -z "${GENDIR}" ]; then
    GENDIR=$(readlink -f `pwd`/build-${TARGET})
fi
if [ -z "${PREFIX}" ]; then
    PREFIX=$(readlink -f `pwd`/tools-${TARGET})
fi


# ------------------------------
# Build OS-Specific toolchain

echo_important "Setup system directory: $PREFIX"
echo_important "Look for sources at : $SRCDIR"
echo_important "Use building directory : $GENDIR"
export PATH=$PREFIX/bin:$PATH

BUILD=build
if [ "${INFO_MODE}" = 'y' ]; then
    BUILD=info
else
    mkdir -p "$PREFIX" "$SRCDIR" "$GENDIR"
    mkdir -p "$PREFIX/usr/include"
fi

if [ "${AUTOTOOLS_MODE}" = 'y' ]; then
    if [ ! -f "${PREFIX}/bin/autoconf" ]; then $BUILD autoconf; fi
    if [ ! -f "${PREFIX}/bin/automake" ]; then $BUILD automake; fi
fi

if [ ! -f "${PREFIX}/bin/nasm" ]; then $BUILD nasm; fi

if [ ! -f "${PREFIX}/bin/${TARGET}-ld" ]; then $BUILD binutils; fi
if [ ! -f "${PREFIX}/bin/${TARGET}-gcc" ]; then
    cd ${PREFIX}/usr
    rm -rf include
    mkdir -p include
    cp -rpvR ${SCRIPT_HOME}/include .
    cp -rpvR ${SCRIPT_HOME}/src/include/i386/* include/
    cp -rpvR ${SCRIPT_HOME}/src/include/kora/* include/

    $BUILD gcc;
fi

# We do have the tooling !
if [ "${INFO_MODE}" = 'n' ] && [ "${BUILD_MODE}" = 'y' ]; then
    echo_important "OS-Specific toolchain is ready"
    echo_important "Think about updating your PATH, ${PREFIX}/bin"
fi
