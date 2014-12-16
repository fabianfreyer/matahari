#!/bin/sh
usage() {
  echo $0 `options`
}

option() {
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

BASE_DIR=$(readlink -f $(dirname $0)/../)
mkdir -p $BASE_DIR

echo "Retrieving ct-ng..."
wget -N http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-${CT_VERSION}.tar.bz2

echo "Unpacking ct-ng..."
tar xjf crosstool-ng-${CT_VERSION}.tar.bz2
cd crosstool-ng-${CT_VERSION}

echo "Building..."
./configure --prefix=${BASE_DIR}
make
make install

echo "Adjusting PATH..."
export PATH="${PATH}:${BASE_DIR}"

echo "Done."
