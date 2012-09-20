#!/bin/bash
for f in ../data/*.pov
do 
	echo "Processing $f file.."
	filename=$(basename "$f")
	extension="${filename##*.}"
	filename="${filename%.*}"
	echo "../src/protracer.exe --output=$filename.ppm $f"
	../src/protracer --output="$filename.ppm" "../data/$f"
done