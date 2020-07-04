#!/usr/bin/env bash

DEFAULT_PATH="$PWD/"
tag="Archivator"

print_menu() {

    echo "Меню:";
    echo "1. Создать задачу";
    echo "2. Редактировать задачу";
    echo "3. Просмотреть задачи";
    echo "4. Удалить задачу";
    echo "5. Выход из программы";
    echo "------------------------"
}

set_task() {

#----------------SET TIME------------------
	d=''
	h=''
	m=''

	echo -n "В какой день недели? (0-7): "
	read d

	echo -n "В какой час? (чч): "
	read h

	echo -n "Во сколько минут? (мм): "
	read m


	echo "1. Архивировать";
	echo "2. Извлечь из архива";
	echo "------------------------"
	read answ

	case $answ in
		#Архивация
		"1"	)
		echo "Введите абсолютный путь к файлу/директории/блочному устройству: " 
        read input

        #For files
		if [[ -f $input  ]]
        then
			echo -n "Введите название архива: "; read name_arh

			echo "1. Выполнить архивацию в директории запуска скрипта"
			echo "2. Указать абсолютный путь для помещения архива"
			
            echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	) 
					crontab -l | { cat; echo "$m $h * * $d tar -czf $DEFAULT_PATH$name_arh.tar $DEFAULT_PATH/$input #$tag"; } | crontab -
				;;
				"2"	) 
					echo -n "Путь: " read path
					crontab -l | { cat; echo "$m $h * * $d tar -czf $path$name_arh.tar $input #$tag"; } | crontab -
				;;
				*	) echo "Ошибка" ;;
			esac	

        #For catalogs
		elif [[ -d $input  ]]
        then
			echo -n "Введите название архива: "; read name_arh

			echo "1. Выполнить архивацию в директории запуска скрипта"
			echo "2. Указать абсолютный путь для помещения архива"
			
			echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	) 
					crontab -l | { cat; echo "$m $h * * $d tar -czf $DEFAULT_PATH$name_arh.tar $input #$tag"; } | crontab -
				;;
				"2"	) 
					echo -n "Путь: " read path
					crontab -l | { cat; echo "$m $h * * $d tar -czf $path$name_arh.tar $input #$tag"; } | crontab -
				;;

				*	) echo "Ошибка" ;;
			esac

        #For block devices
		elif [[ -b $input ]]
        then
			echo -n "Введите название архива: "; read name_arh

			echo "1. Выполнить архивацию в директории запуска скрипта"
			echo "2. Указать абсолютный путь для помещения архива"
			
			echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	) 
					sudo crontab -l | { cat; echo "$m $h * * $d dd if=/$input of=$DEFAULT_PATH$name_arh #$tag"; } | sudo crontab -
				;;
				"2"	) 
					echo -n "Путь: " read path
					sudo crontab -l | { cat; echo "$m $h * * $d dd if=/$input of=/$path$name_arh #$tag"; } | sudo crontab -
				;;

				*	) echo "Ошибка" ;;
			esac
		fi
		;;
        #End of 1 case

		#Деархивация
		"2"	) 
		echo "Введите название архива с указанием абсолютного пути: "; read input
		if [[ $input == *"*.iso"*  ]]
        then
			echo "Это образ"
			echo "1. Выполнить извлечение в dev/"
			echo "2. Указать абсолютный путь для извлечения архива"
			
			echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	) 
					sudo crontab -l | { cat; echo "$m $h * * $d dd if=$DEFAULT_PATH$input of=dev/sdb1 #$tag"; } | sudo crontab -
				;;
				"2"	) 
					echo -n "Директория: "; read path
					sudo crontab -l | { cat; echo "$m $h * * $d dd if=$DEFAULT_PATH$input of=$path/sdb1 #$tag"; } | sudo crontab -
				;;

				*	) echo "Ошибка" ;;
			esac
		else
        	echo "1. Выполнить извлечение в директории запуска скрипта"
			echo "2. Указать абсолютный путь для извлечения архива"

			echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	)
                	crontab -l | { cat; echo "$m $h * * $d tar -xzf $input -C $DEFAULT_PATH #$tag"; } | crontab -
				;;
				"2"	) 
					echo -n "Путь: "; read path
					crontab -l | { cat; echo "$m $h * * $d tar -xzf $input -C $path #$tag"; } | crontab -
				;;
				*	) echo "Ошибка" ;;
			esac
		fi
		;;
        #End of 2 case

		*	) echo "Ошибка" ;;
	esac

	echo "Задача установлена в расписание"
}

delete_task() {
	echo -n "Выберите номер задачи, с которой нужно взаимодействовать: "; read answ
	crontab -l | grep -v "$tag" | {
		cat
		crontab -l | grep "$tag" | sed "$answ d"
	} | crontab -
}

show_tasks() {
	crontab -l | grep Archivator | grep -n ".*" | sed s/" \* \* "/"  "/g | sed s/"[~][/].*[/].*[/]"/"  "/
}


#--------------MAIN LOOP------------------
clear
echo -e "\n----FleX Arhiver v1.0----\n";
print_menu;
echo -n "Дейсвтие: "; read choose;

while [ $choose != "5" ]
do

    case $choose in
        "1"	) 
            set_task
        ;;
        "2"	) 
            show_tasks
            delete_task
            set_task
        ;;
        "3" )
            show_tasks
        ;;
        "4" )
            show_tasks
            delete_task
        ;;
        "5" )
            exit
        ;;
        *	) echo "Ошибка" ;;
	esac

    echo; print_menu
	echo -n "Дейсвтие: "; read choose;
done