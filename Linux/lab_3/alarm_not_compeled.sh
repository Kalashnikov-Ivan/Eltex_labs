#!/usr/bin/env bash

function printMenu
{
	echo "1. Установить новый будильник";
	echo "2. Список установленных";
	echo "3. Дейсвие с будильником";
	echo "4. Выход";
}

inpt=42;

echo "----FleX alarm v0.1----";
echo; echo;

#--------------MAIN LOOP------------------
while [ $inpt -ne 4 ]
do
	
	cronTime=(0, 1, 2, 3);

	printMenu;

	echo;
	
	echo -n "Дейсвтие: ";
	read inpt;
	#--------------Set alarm------------------
	if   [[ inpt -eq 1 ]]; then
		echo;
		echo -e "Установите новый будильник в формате:\n<месяц.день> <час.минута>\n";
		
		#--------------Input------------------
		isGoogFormat=0;
		while [[ isGoogFormat -ne 1 ]]
		do
			echo $isGoogFormat; echo;

			IFS=$"\n";
			echo "Enter 'q' for back";
			echo -n "Time: "; read time;

			if [[ $time = "q" ]]; then
				break;
			fi

			IFS=$".":" ";

			i=3;
			for var in $time
			do
				cronTime[$i]=$var;

				if [[ $i -eq 0 ]]; then
					break;
				fi

				i=$(($i - 1));
			done

			i=-1;
			for var in ${cronTime[@]}
			do
				i=$(($i + 1));

				case $i in
					0)
						if [[ $var -lt 0 || $var -gt 59 ]]; then
							echo "Неверно введённая минута!" 		  >&2;
							echo "Вы ввели: $var. Такой минуты нет."  >&2;
							echo "Введите минуту в диапазоне: 0-59"   >&2;

							isGoogFormat=0;
							#i=-1;
							break;
						else
							isGoogFormat=1;
						fi
					;;
					1)
						if [[  $var -lt 0 || $var -gt 23 ]]; then
							echo "Неверно введённый час!" 		      >&2;
							echo "Вы ввели: $var. Такого часа нет."   >&2;
							echo "Введите час в диапазоне: 0-23" 	  >&2;

							isGoogFormat=0;
							#i=-1;
							break;
						else
							isGoogFormat=1;
						fi
					;;
					2)
						if [[ $var -lt 1 || $var -gt 31 ]]; then
							echo "Неверно введённый день!" 			  >&2;
							echo "Вы ввели: $var. Такого дня нет."    >&2;
							echo "Введите день в диапазоне: 1-31" 	  >&2;

							isGoogFormat=0;
							#i=-1;
							break;
						else
							isGoogFormat=1;
						fi
					;;
					3)
						if [[ $var -lt 1 || $var -gt 12 ]]; then
							echo "Неверно введённый месяц!" 		  >&2;
							echo "Вы ввели: $var. Такого месяца нет." >&2;
							echo "Введите месяц в диапазоне: 1-12" 	  >&2;

							isGoogFormat=0;
							#i=-1;
							break;
						else
							isGoogFormat=1;
						fi
					;;
				esac

				echo $isGoogFormat;

			done
		 done
		#--------------Input------------------

	fi
	#--------------Set alarm------------------
	echo;
	echo;

done
#--------------MAIN LOOP------------------