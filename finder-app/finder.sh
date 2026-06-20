#!/bin/sh

if [ $# -ne 2 ]; then
    echo "Error: Two arguments required: <filedir> <searchpattern>"
    exit 1
fi

filedir=$1
searchpattern=$2

if [ ! -d "$filedir" ]; then
    echo "Error: Directory does not exist: $filedir"
    exit 1
fi

a_num=$(find "$filedir" -type f | wc -l)
b_num=$(grep -r "$searchpattern" "$filedir" | wc -l)

echo "The number of files are $a_num and the number of matching lines are $b_num"