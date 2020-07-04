#!/bin/bash

echo -n "Куда:";
read path;

cur_PWD=`pwd`;

cd $cur_PWD/$path;

echo "Шаблон название директорий:"; read dir;
echo "Чисто директорий:"; 			read d;
echo "Шаблон названия файлов:"; 	read file;
echo "Число файлов:"; 				read f;

clear;

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
echo "Успешное завершение программы";