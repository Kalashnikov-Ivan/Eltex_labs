#!/bin/bash

#For processing keys
while getopts ":p:d:f" opt; 
do
	case $opt in
	p)
		k_path="${OPTARG}";
	;;
	d)
		dir="$2";
		shift;
		d="$2";
		shift;
	;;
	f) 
		file="$2";
		shift;
		f="$2";
		shift;
	;;
	*) 
		echo "$1 is not an option" ;;
	esac
done
shift $(($OPTIND - 1))

#Working with path of catalog
#cur_PWD=`pwd`;
path="$PWD/$k_path";

if [ -d $path ]; then
	echo "$path is exists";
else
	echo "$path is not exist";
	mkdir $path;
	echo "$path has been create";
fi

cd $path;


for ((i=0;i<d;i++)) 
do 
	mkdir $dir$i;
	chmod 755 $dir$i;
	cd $dir$i;
	for ((j=0;j<f;j++)) 
	do
		touch $file$j;
		echo "$file$j в $dir$i - done";
	done
	cd ../;
	echo "$dir$i - comleted";
	echo;
done 

echo;
echo "Script comleted";