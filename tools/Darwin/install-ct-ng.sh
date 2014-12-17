#!/bin/sh
usage() {
  echo $0 `options`
}

options() {
  echo "[-h|--help][-u|--options][--option=value]"
}

#Default parameters
CT_VERSION=1.19.0

while [ "$1" != "" ]; do
  PARAM=`echo $1 | awk -F= '{print $1}'`
  VALUE=`echo $1 | awk -F= '{print $2}'`
  case $PARAM in
    -h | --help)
      usage
      exit
      ;;
    -u | --options)
      options
      exit
      ;;
    -v | --version)
      CT_VERSION=$VALUE
      ;;
    *)
      usage
      exit
      ;;
  esac
  shift
done

BASE_DIR=$(python -c 'import os,sys;print os.path.realpath(sys.argv[1])' $(dirname $0)/../)
echo $BASE_DIR
mkdir -p $BASE_DIR

echo "Retrieving ct-ng..."
wget -N http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-${CT_VERSION}.tar.bz2

echo "Unpacking ct-ng..."
tar xjf crosstool-ng-${CT_VERSION}.tar.bz2
cd crosstool-ng-${CT_VERSION}

echo "Checking for GNU tools"
require() {
    command -v $1 >/dev/null 2>&1 || {
        echo "$1 is required but not installed."
	exit 1
    }
}
for tool in gobjcopy gobjdump granlib greadelf glibtool glibtoolize gsed gawk automake bash
do
	require ${tool} && echo "${tool} found."
done

echo "Patching..."
patch -p1 << PATCH
diff --git a/kconfig/zconf.gperf b/kconfig/zconf.gperf
index c9e690e..21e79e4 100644
--- a/kconfig/zconf.gperf
+++ b/kconfig/zconf.gperf
@@ -7,6 +7,10 @@
 %pic
 %struct-type

+%{
+#include <stddef.h>
+%}
+
 struct kconf_id;

 static struct kconf_id *kconf_id_lookup(register const char *str, register unsigned int len);
PATCH

echo "Building..."
./configure \
	--prefix=${BASE_DIR} \
	--exec-prefix=${BASE_DIR} \
	--with-objcopy=$(command -v gobjcopy) \
	--with-objdump=$(command -v gobjdump) \
	--with-ranlib=$(command -v granlib) \
	--with-readelf=$(command -v greadelf) \
	--with-libtool=$(command -v glibtool) \
	--with-libtoolize=$(command -v glibtoolize) \
        --with-sed=$(command -v gsed) \
	--with-awk=$(command -v gawk) \
	CFLAGS=-std=gnu89
make
make install

echo "Adjusting PATH..."
export PATH="${PATH}:${BASE_DIR}"

echo "Done."
