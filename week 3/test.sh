#!/bin/sh
for program in ./benchmarkArrayQueue ./benchmarkCircularArrayQueue
do
    echo
    echo "time complexity : $program"
    /usr/bin/time $program > /dev/null
done