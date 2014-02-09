#!/bin/sh
function usage() {
  echo $0 `options`
}

function options() {
  echo "[-h|--help][-u|--options][--option=value]"
}

#Default parameters
OPTION=DEFAULT_VALUE

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
    --option)
      OPTION=$VALUE
      ;;
    *)
      usage
      exit
      ;;
  esac
  shift
done

echo "do something"
