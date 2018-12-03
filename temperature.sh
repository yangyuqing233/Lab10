#!/bin/bash


for pins in {0..2} #for each of the items in the list do the following
do
		gpio mode $pins out; #here  we set it to out
		gpio write $pins 0; #here  0 is the value we set it to
		
done


initTemp=$(./tempread); #inital temp to compare to

counter=1;
pin=0;

while true #forever loop
do
	temp2=$(./tempread);
	
	diff=$(( $temp2 - $initTemp))
	echo $initTemp, $temp2, $diff ## get the difference
	
	diff=$((diff/1000)) #put the diff in ones form
	echo $diff	
	
	if [ $initTemp -eq 85000 ]
	then
		echo "temperature was not available. Check sensor and sensor power"
	fi

	#if test "$diff" -ge $counter
	#then
	#	gpio write $pin 1; #turn 1st led on
#
#		((counter++ ))
#		((pin ++))
#	fi


        if test "$diff" -lt 1
        then
                gpio write 0 0;
                gpio write 1 0;
                gpio write 2 0;
        fi

	
	if test "$diff" -ge 1 && test "$diff" -lt 2
	then
		gpio write 0 1;
		gpio write 1 0;
		gpio write 2 0;
	fi

    if test "$diff" -ge 2 && test "$diff" -lt 3
        then
                gpio write 0 1;
                gpio write 1 1;
                gpio write 2 0;
        fi

    if test "$diff" -ge 3 && test "$diff" -lt 4
        then
                gpio write 0 1;
                gpio write 1 1;
                gpio write 2 1;
        fi
	
done
