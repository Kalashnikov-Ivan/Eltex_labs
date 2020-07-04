#!/usr/bin/env bash

tag="Alarm"

print_menu() {

    echo "Меню:";
    echo "1. Создать будильник";
    echo "2. Редактировать будильник";
    echo "3. Просмотреть будильники";
    echo "4. Удалить будильник";
    echo "5. Выход из программы";
    echo "------------------------"
}

set_alarm() {

    #isGoodFormat="true"

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

#----------------SET PLAYER------------------
	echo "1. Вывести список установленных плееров"
	echo "2. Установка плеера"
	echo "3. Плеер по умолчанию"

    echo -n "Дейсвтие: "; read answ

	case $answ in
		"1"	) 
            apt list --installed | grep "^rhythmbox/\|^mpg123/\|^mplayer/\|^amarok/\|^clementina/"
			echo "Выберите плеер из установленных: 1, 2, 3..."
			echo "------------------------"
			echo -n "Дейсвтие: "; read answ
			case $answ in
				"1"	) player=mpg123    ;;
				"2"	) player=mplayer   ;;
        		"3"	) player=rhythmbox ;;
				*	) echo "Ошибка"    ;;
			esac
		;;
		"2"	) 
            echo "Введите желаемый плеер для установки"
            read player
            sudo apt install $player
		;;
		"3" ) 
            player=rhythmbox 
        ;;
		*	) echo "Ошибка" ;;
	esac

#----------------SET MUSIC------------------
    echo "1. Установить свою мелодию на будильник"
	echo "2. Мелодия по умолчанию"

    echo -n "Дейсвтие: "; read answ

    case $answ in
        "1"	)
            echo -n "Путь до файла с мелодией: "; read music
            crontab -l | { cat; echo "$m $h * * $d $player $music #$tag"; } | crontab -
        ;;
        "2"	) 
            music="/home/st/work/eltex/linux_Networks/lab_3/default_music.mp3"
            crontab -l | { cat; echo "$m $h * * $d $player $music #$tag"; } | crontab -
        ;;
        *	) echo "Ошибка" ;;
	esac

	echo "Будильник готов"
}

delete_alarm() {
	echo -n "Выберите номер задачи, с которой нужно взаимодействовать: "; read answ
	crontab -l | grep -v "$tag" | {
		cat
		crontab -l | grep "$tag" | sed "$answ d"
	} | crontab -
}

show_alarm() {
    echo "Формат: "
    echo -e "<номер>:минуты часы   день недели плеер мелодия #метка\n"
    echo -e "Установленные будильники: \n"
	crontab -l | grep Alarm | grep -n ".*" | sed s/" \* \* "/"  "/g | sed s/"[~][/].*[/].*[/]"/"  "/
}


#--------------MAIN LOOP------------------
clear
echo -e "\n----FleX alarm v1.0----\n";
print_menu
echo -n "Дейсвтие: "; read choose;

while [ $choose != "5" ]
do

    case $choose in
        "1"	) 
            set_alarm
        ;;
        "2"	) 
            show_alarm
            delete_alarm
            set_alarm
        ;;
        "3" )
            show_alarm
        ;;
        "4" )
            show_alarm
            delete_alarm
        ;;
        "5" )
            exit
        ;;
        *	) echo "Ошибка" ;;
	esac

    echo; print_menu
	echo -n "Дейсвтие: "; read choose;
done