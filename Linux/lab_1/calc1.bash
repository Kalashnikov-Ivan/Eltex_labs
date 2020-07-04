#!/bin/bash

inpt=42;

while [ $inpt -ne 4 ]
do
	
	echo "1. Ввести данные";
	echo "2. Выбрать действие";
	echo "3. Выполнение и вывод результата";
	echo "4. Выход";

	echo;
	
	echo -n "Дейсвтие: ";
	read inpt;
	
	if [[ inpt -eq 1  ]]; then

		echo -n "a = ";
		read a;
		echo -n "b = ";
		read b;

	elif [[ inpt -eq 2 ]]; then
		
		echo;

		echo "1. Сложение (+)";
		echo "2. Вычетание (-)";
		echo "3. Умножение (*)";
		echo "4. Целочисленное деление (//)";
		echo "5. Дробное деление (/)";
		echo "6. Факториал";
		echo "7. Выход";
		
		echo;
		
		echo -n "Операция: "
		read op;
		while [[ ($op -lt 1 || $op -gt 7) ]]
		do
			echo "ERROR: Введите корректный номер операции!";
			read op;
		done

	elif [[ inpt -eq 3 ]]; then
		if [[ $op -eq 1 ]]; then
			out=$(($a + $b));
		elif [[ $op -eq 2 ]]; then
			out=$(($a - $b));
		elif [[ $op -eq 3 ]]; then
			out=$(($a * $b));
		elif [[ $op -eq 4 ]]; then
			out=$(($a / $b));
		elif [[ $op -eq 5 ]]; then
			out=$(awk "BEGIN {printf \"%.2f\",${a}/${b}}");
		elif [[ $op -eq 6 ]]; then
			out=1;
			echo -n "Число: ";
			read fact;
			for((i=1; $i <= $fact; i++)); do
				out=$(($out * $i));
			done
		else
			echo "Вы не выбрали операцию";
			out="None";
		fi
		echo;
		echo;
		echo "Результат: $out";
	fi
	
	echo;
	echo;

done
