#!/bin/bash

declare -i FCOUNT
FCOUNT=0
CHILDREN=
TEMP=

if [ "$#" -lt 2 ]; then
	echo "There is not enought arguments, enter ./search.sh [where] [what]"
	exit
else
	if [ ! -d "$1" ]; then
		echo "'$1' is not a directory"
		exit
	fi
fi

for item in $1/*; do
	if [ -d "$item" ]; then
		"$0" "$item" "$2" "$$" &
		CHILDREN+=("$!")
	elif [ -f "$item" ] && [[ "$item" != *.LNK ]] && [[ "$item" != *.DeskLink ]] && [[ "$item" != *.ZFSendToTarget ]]; then
		TEMP=$(basename -- $item)
		if [ "$TEMP"  == "$2" ]; then
			echo "There is '$2' in directory '$1'"
			FCOUNT=$((FCOUNT+1))
		fi
	fi
done

for i in "${CHILDREN[@]}"; do
	if [ "$i" ]; then
		wait "$i"
		FCOUNT=$((FCOUNT+$?))
	fi
done

if [ -z "$3" ]; then
	if [ "$FCOUNT" -eq 0 ]; then
		echo "File not found"
	else
		echo "File exist $FCOUNT times"
	fi
fi

exit "$FCOUNT"
