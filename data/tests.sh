#!/bin/bash
for f in *.pov
do 
	echo "Processing $f file.."
	echo "../src/protracer.exe --output=$f.ppm $f"
	../src/protracer --output="$f.ppm" "./$f"
done