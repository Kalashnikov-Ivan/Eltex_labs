#!/usr/bin/env bash

SET_COLOR_GREEN_F="echo -en \\033[1;32m"
SET_COLOR_RED_F="echo -en \\033[1;31m"
SET_COLOR_YELLOW_F="echo -en \\033[1;33m"
SET_COLOR_CYAN="echo -en \\033[0;36m"
SET_COLOR_BROWN="echo -en \\033[0;33m"
SET_COLOR_NORMAL="echo -en \\033[0;39m"

IP="";
mask="";

IFS=/ read -r IP mask <<< "$1";

echo $mask;

#Devision variable IFS
IFS=. read -r n1 n2 n3 n4 <<< "$IP";

#echo "Enter the mask of subnet: ";
#read mask;
if [[ $mask == *"."* ]]
then
	#Devision variable IFS
	IFS=. read -r m1 m2 m3 m4 <<< "$mask";

	if [[ $m1 == "255" ]]
	then
		bits=8;
	fi
	if [[ $m2 == "255" ]]
	then
		bits=16;
	fi
	if [[ $m3 == "255" ]]
	then
		bits=24;
	fi
	if [[ $m4 == "255" ]]
	then
		bits=32;
	fi

    ${SET_COLOR_CYAN}
    echo -n "IP:        $IP";

	nb1=`echo "obase=2; $n1" | bc`;
	nb2=`echo "obase=2; $n2" | bc`; 
	nb3=`echo "obase=2; $n3" | bc`;
	nb4=`echo "obase=2; $n4" | bc`;
	${SET_COLOR_BROWN}
	printf '            %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

	${SET_COLOR_CYAN}
    echo -n "Mask       $mask = $bits";

	mb1=`echo "obase=2; $m1" | bc`;
	mb2=`echo "obase=2; $m2" | bc`; 
	mb3=`echo "obase=2; $m3" | bc`;
	mb4=`echo "obase=2; $m4" | bc`;
	${SET_COLOR_BROWN}
	printf '           %08d.%08d.%08d.%08d\n\n' $mb1 $mb2 $mb3 $mb4


    ${SET_COLOR_GREEN_F}
    echo -n "Network:   $((n1 & m1)).$((n2 & m2)).$((n3 & m3)).$((n4 & m4))"

	nb1=`echo "obase=2; $((n1 & m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3))" | bc`;
	nb4=`echo "obase=2; $((n4 & m4))" | bc`;
	${SET_COLOR_BROWN}
	printf '              %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_RED_F}
    echo -n "Min IP:    $((n1 & m1)).$((n2 & m2)).$((n3 & m3)).$(((n4 & m4)+1))"

	nb1=`echo "obase=2; $((n1 & m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3))" | bc`;
	nb4=`echo "obase=2; $(((n4 & m4)+1))" | bc`;
	${SET_COLOR_BROWN}
	printf '              %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_YELLOW_F}
    echo -n "Max IP:    $((n1 & m1 | 255-m1)).$((n2 & m2 | 255-m2)).$((n3 & m3 | 255-m3)).$(((n4 & m4 | 255-m4)-1))"

	nb1=`echo "obase=2;  $((n1 & m1 | 255-m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2 | 255-m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3 | 255-m3))" | bc`;
	nb4=`echo "obase=2; $(((n4 & m4 | 255-m4)-1))" | bc`;
	${SET_COLOR_BROWN}
	printf '        %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_NORMAL}
    echo -n "Broadcast: $((n1 & m1 | 255-m1)).$((n2 & m2 | 255-m2)).$((n3 & m3 | 255-m3)).$((n4 & m4 | 255-m4))"

	nb1=`echo "obase=2;  $((n1 & m1 | 255-m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2 | 255-m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3 | 255-m3))" | bc`;
	nb4=`echo "obase=2; $((n4 & m4 | 255-m4))" | bc`;
	${SET_COLOR_BROWN}
	printf '        %08d.%08d.%08d.%08d\n\n' $nb1 $nb2 $nb3 $nb4
else
	if [[ $mask == *"8"*  ]]
	then
		m1=255; m2=0; m3=0; m4=0;
	fi

	if [[ $mask == *"16"*  ]]
	then
		m1=255; m2=255; m3=0; m4=0; 
	fi

	if [[ $mask == *"24"*  ]]
	then
		m1=255; m2=255; m3=255; m4=0;
	fi

	if [[ $mask == *"32"*  ]]
	then
		m1=255; m2=255; m3=255; m4=255;
	fi

	${SET_COLOR_CYAN}
    echo -n "IP:        $IP";

	nb1=`echo "obase=2; $n1" | bc`;
	nb2=`echo "obase=2; $n2" | bc`; 
	nb3=`echo "obase=2; $n3" | bc`;
	nb4=`echo "obase=2; $n4" | bc`;
	${SET_COLOR_BROWN}
	printf '            %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

	${SET_COLOR_CYAN}
    echo -n "Mask       $m1.$m2.$m3.$m4 = $mask";

	mb1=`echo "obase=2; $m1" | bc`;
	mb2=`echo "obase=2; $m2" | bc`; 
	mb3=`echo "obase=2; $m3" | bc`;
	mb4=`echo "obase=2; $m4" | bc`;
	${SET_COLOR_BROWN}
	printf '          %08d.%08d.%08d.%08d\n\n' $mb1 $mb2 $mb3 $mb4


    ${SET_COLOR_GREEN_F}
    echo -n "Network:   $((n1 & m1)).$((n2 & m2)).$((n3 & m3)).$((n4 & m4))"

	nb1=`echo "obase=2; $((n1 & m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3))" | bc`;
	nb4=`echo "obase=2; $((n4 & m4))" | bc`;
	${SET_COLOR_BROWN}
	printf '              %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_RED_F}
    echo -n "Min IP:    $((n1 & m1)).$((n2 & m2)).$((n3 & m3)).$(((n4 & m4)+1))"

	nb1=`echo "obase=2; $((n1 & m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3))" | bc`;
	nb4=`echo "obase=2; $(((n4 & m4)+1))" | bc`;
	${SET_COLOR_BROWN}
	printf '              %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_YELLOW_F}
    echo -n "Max IP:    $((n1 & m1 | 255-m1)).$((n2 & m2 | 255-m2)).$((n3 & m3 | 255-m3)).$(((n4 & m4 | 255-m4)-1))"

	nb1=`echo "obase=2;  $((n1 & m1 | 255-m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2 | 255-m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3 | 255-m3))" | bc`;
	nb4=`echo "obase=2; $(((n4 & m4 | 255-m4)-1))" | bc`;
	${SET_COLOR_BROWN}
	printf '        %08d.%08d.%08d.%08d\n' $nb1 $nb2 $nb3 $nb4

    ${SET_COLOR_NORMAL}
    echo -n "Broadcast: $((n1 & m1 | 255-m1)).$((n2 & m2 | 255-m2)).$((n3 & m3 | 255-m3)).$((n4 & m4 | 255-m4))"

	nb1=`echo "obase=2;  $((n1 & m1 | 255-m1))" | bc`;
	nb2=`echo "obase=2; $((n2 & m2 | 255-m2))" | bc`;
	nb3=`echo "obase=2; $((n3 & m3 | 255-m3))" | bc`;
	nb4=`echo "obase=2; $((n4 & m4 | 255-m4))" | bc`;
	${SET_COLOR_BROWN}
	printf '        %08d.%08d.%08d.%08d\n\n' $nb1 $nb2 $nb3 $nb4
fi