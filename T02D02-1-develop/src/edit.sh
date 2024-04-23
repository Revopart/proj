#!/bin/bash
if (($# != 3));
then
	echo "must be 3 arguments"
	exit
fi
PATH_FILE=$1
FIND_TEXT=$2
REPLACE_TEXT=$3
if (($FIND_TEXT == $REPLACE_TEXT));
then
        echo "result constant"
        exit
fi
cd ..
if [ ! -f "$PATH_FILE" ];
then
	echo "file doesn't exist or can't be open"
	exit
fi
if ! grep -q "$FIND_TEXT" "$PATH_FILE";
then
	echo "Text for replace doent't find in file"
	exit
fi
sed -i '' "s/$FIND_TEXT/$REPLACE_TEXT/g" "$PATH_FILE"
if [ ! -f src/files.log ];
then
	echo "files.log file doesnt't exist. it will be created"
	touch src/files.log
fi
TIME_EDIT=$(stat -f "%Sm %N" -t "%H:%M" "$PATH_FILE" | awk '{print $1}')
DATE_EDIT=$(stat -f "%Sm %N" -t "%Y-%m-%d" "$PATH_FILE" | awk '{print $1}')
VOLUME=$(wc -c $PATH_FILE | awk '{print $1}')
SHA=$(shasum -a 256 "$PATH_FILE" | awk '{print $1}') 
echo "$PATH_FILE - $VOLUME - $DATE_EDIT $TIME_EDIT - $SHA - sha256" >> "src/files.log"
