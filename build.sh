#!/data/data/com.termux/files/usr/bin/bash

SRC="$1"
OUT="${SRC%.*}"
LIB_FLAGS=""

# Read each line in libs.txt and append pkg-config flags
while IFS= read -r lib; do
  LIB_FLAGS+=" $(pkg-config --cflags --libs $lib)"
done < "${PWD}/libs.txt"

# Compile and run
clang -march=native "$SRC" -o "$OUT" $LIB_FLAGS && "$OUT"

