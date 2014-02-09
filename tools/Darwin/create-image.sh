#!/bin/sh
function usage() {
  echo $0 `options`
}

function options() {
  echo "[-h|--help][-u|--options][--sectors=2880][--fs=MS-DOS][<image = \"floppy\">]"
}

#Default parameters
SECTORS=2880
FILENAME=floppy 
FS=MS-DOS

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
    --sectors)
      SECTORS=$VALUE
      ;;
    --fs)
      FS=$VALUE
      ;;
    *)
      FILENAME=$PARAM
      ;;
  esac
  shift
done

echo hdiutil create -fs $FS -sectors $SECTORS -layout NONE -ov $FILENAME
