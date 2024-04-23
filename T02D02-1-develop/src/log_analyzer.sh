#!/bin/bash
cd ..
if (($# != 1));
then
        echo "must be only 1 argument"
        exit
fi
PATH_FILE=$1
if [ ! -f "$PATH_FILE" ];
then
        echo "file doesn't exist or can't be open"
        exit
fi
COUNT_LINES=$(wc -l "$PATH_FILE" | awk '{print $1}' | tr -d ' ')
COUNT_UNIQ_NAME=$(cut -d" "  -f1 "$PATH_FILE" | sort | uniq | wc -l | tr -d ' ')
COUNT_UNIQ_HASH=$(cut -d" "  -f8 "$PATH_FILE" | sort | uniq | wc -l | tr -d ' ')
echo "$COUNT_LINES $COUNT_UNIQ_NAME $COUNT_UNIQ_HASH"
