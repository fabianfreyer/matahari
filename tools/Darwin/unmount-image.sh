#!/bin/sh
function usage() {
  echo $0 `options`
}

function options() {
  echo "[-h|--help][-u|--options][--mountpoint=./mnt][-k|--keep-device-file][--device-file=<image>.device][<image = \"floppy\">]"
}

#Default parameters
FILENAME=floppy 
MOUNTPOINT=./mnt
DEVICE_FILE=""
DELETE_DEVICE_FILE=1

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
    --mountpoint)
      MOUNTPOINT=$VALUE
      ;;
    --device-file)
      DEVICE_FILE=$VALUE
      ;;
    -k | --keep-device-file)
      DELETE_DEVICE_FILE=0
      ;;
    *)
      FILENAME=$PARAM
      ;;
  esac
  shift
done
if [ "$DEVICE_FILE" -eq "" ]; then
  DEVICE_FILE=$FILENAME.device
fi

umount $MOUNTPOINT
if [ $DELETE_DEVICE_FILE ]; then
  rm ./$1.device
fi
rmdir $MOUNTPOINT
