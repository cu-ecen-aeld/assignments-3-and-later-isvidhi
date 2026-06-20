#!/bin/sh

if[$# -ne 2 ]; then
    echo "Error: Two arguments required: <writefile> <writecontent>"
    exit 1
fi

writefile=$1
writecontent=$2

dir=$(dirname "$writefile")
if [ ! -d "$dir" ]; then
    echo "Error: Directory does not exist: $dir"
    mkdir -p "$dir"
    if[$? -ne 0 ]; then
        echo "Error: Failed to create directory: $dir"
        exit 1
    fi
fi

echo "$writecontent" > "$writefile"