#!/bin/sh
function usage() {
  echo $0 `options`
}

function options() {
  echo "[-h|--help][-u|--options][--mountpoint=./mnt][--device-file=<image>.device][--fs=msdos][<image = \"floppy\">]"
}

#Default parameters
FILENAME=image
MOUNTPOINT=./mnt
DEVICE_FILE=""
FS=msdos

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
    --fs)
      FS=$VALUE
      ;;
    *)
      FILENAME=$PARAM
      ;;
  esac
  shift
done
if [ ! $DEVICE_FILE ]; then
  DEVICE_FILE=$FILENAME.device
fi

# Create mountpoint, if it doesn't exist already.
if [ ! -d $MOUNTPOINT ]; then
  echo "Creating $MOUNTPOINT"
  mkdir $MOUNTPOINT
elif [ "`ls -A $DIR`" ]; then
  echo "Error: $MOUNTPOINT exists and is not empty!"
  exit 126 
fi

hdid -nomount $FILENAME.img > $DEVICE_FILE
mount -t $FS `cat $DEVICE_FILE` $MOUNTPOINT
