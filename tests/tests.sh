#!/bin/bash
for f in ../data/*.pov
do 
	echo "Processing $f file.."
	filename=$(basename "$f")
	extension="${filename##*.}"
	filename="${filename%.*}"
	echo "../src/protracer --output=$filename.png $f"
	../src/protracer -o $filename.png "$f"
done