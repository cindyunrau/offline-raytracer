#!/bin/bash

FILES="./tests/*.txt"

gcc raytracer.c utilities.c vec.c -o raytracer

for f in $FILES
do
    if [ -f "$f" ]
    then
        echo "Processing $f"
        ./raytracer $f 
    else
        echo "Warning: Some problem with \"$f\""
    fi
done