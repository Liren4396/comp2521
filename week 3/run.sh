#!/bin/sh


num_runs=5

for input_size in 10000 20000 50000 100000 200000 500000 1000000  # TODO: add more input sizes
do
	for order in random sorted reverse # NOTE: feel free to adjust this list
	do
		for program in ./sortIntList "sort -n"
		do
			echo
			echo "Input size: $input_size, Order: $order, Program: $program"
			for i in $(seq 1 $num_runs)
			do
				case $order in
					#random)
					#	seq $input_size | sort -R | /usr/bin/time -f "%U" $program > /dev/null
					#	;;
					sorted)
						seq $input_size | /usr/bin/time -f "%U" $program > /dev/null
						;;
					reverse)
						seq $input_size | sort -nr | /usr/bin/time -f "%U" $program > /dev/null
						;;
				esac
			done
		done
	done
done