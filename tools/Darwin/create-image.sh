#!/bin/sh
function usage() {
  echo $0 `options`
}

function options() {
  echo "[-h|--help][-u|--options][--sectors=2880][--fs=FAT12][-L|--label=foobar][<image = \"floppy\">]"
}

#Default parameters
SECTORS=2880
FILENAME=floppy
FS="MS-DOS FAT12"
LABEL="FOOBAR"

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
    -L|--label)
      LABEL=$VALUE
      ;;
    *)
      FILENAME=$PARAM
      ;;
  esac
  shift
done

dd if=/dev/zero of=$FILENAME count=$SECTORS bs=512
DEVICE=`hdid -nomount $FILENAME`
diskutil eraseVolume "$FS" $LABEL $DEVICE
hdiutil detach $DEVICE
