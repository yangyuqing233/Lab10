for value in {0..2}
do
	echo $value
	gpio mode $value out
	gpio write $value 0
done
