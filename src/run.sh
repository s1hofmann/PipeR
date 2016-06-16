#!/bin/bash

# Create temp folder for downloads
TMP_DIR=`mktemp -d`

# Cleans up after the script is finished
function onExit {
    rm -rf "$TMP_DIR"
    echo "Removed temporary directory $TMP_DIR"
}

# Clean up created directories / files on EXIT signal
trap onExit EXIT

while [[ $# -gt 1 ]]
do
key="$1"

case $key in
    local)
    FILES="$2"
    REMOTE=false
    shift # past argument
    ;;
    remote)
    FILES="$2"
    REMOTE=true
    shift # past argument
    ;;
    -c|--config)
    CONFIG_FILE="$2"
    shift # past argument
    ;;
    --default)
    DEFAULT=YES
    ;;
    *)
            # unknown option
    ;;
esac
shift # past argument or value
done
if [[ ${REMOTE} ]]; then
    echo remote = "${FILES}"
else
    echo local = "${FILES}"
fi
echo config = "${CONFIG_FILE}"
if [[ -n $1 ]]; then
    echo "Last line of file specified as non-opt/last argument:"
    tail -1 $1
fi
