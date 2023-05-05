#! /bin/bash

EXEC_N=philo

# tests correction
#  1 800 200 200	(no eat - die)
#  5 800 200 200	(no die)
#  5 800 200 200 7	(no die - stop after 7 eat)
#  4 410 200 200	(no die)
#  4 310 200 100	(1 die)

# const
ITA="\033[3m"
UNDERL="\033[4m"
GREEN="\033[32m"
RED="\033[31m"
YEL="\033[33m"
END="\033[m"
BLU_BG="\033[44m"
YEL_BG="\033[43;1m"
RED_BG="\033[41;1m"

# machine spec
uname -s | grep -qi darwin && os=mac
uname -s | grep -qi linux && os=linux

[[ $os != "linux" ]] && echo -e "${ITA}No valgrind testing (uncompatible os)${END}"

# -------------------------------------------------------------------------------------------------------------------------------------
#  NORMINETTE
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test norminette:${END} \t\t\t\t\t\t-->"
norm=$(find . | egrep ".*(\.c|\.h)$" | norminette)
if [[ $(echo $norm | egrep -v "OK\!$") ]] ;
then
	echo -e "${RED} norme errors:${END}"
	echo -e $norm | egrep -v "OK\!$"
else
	echo -e "${GREEN} norm ok${END}"
fi

# -------------------------------------------------------------------------------------------------------------------------------------
#  MAKEFILE
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test Makefile:${END} \t\t\t\t\t\t\t-->"
make re 1>/dev/null 2> stderrmake.txt
make > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED} make wrote on std err${END}" || echo -ne "${GREEN} no make error${END}" 
echo -n " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relink?${END}" || echo -ne "${GREEN}no relink${END}"
echo -n " -- "
[[ -f $EXEC_N && -x $EXEC_N ]] && echo -e "${GREEN}exec == ${EXEC_N}${END}" || echo -e "${RED}no exec file found named ${EXEC_N}${END}"
rm -rf stderrmake.txt stdoutmakebis.txt

[[ ! -f ${EXEC_N} ]] && { echo -e "${RED_BG}No exec 'philo'. Tester exiting.${END}" ; make fclean >/dev/null 2>&1 ; exit ; }
[[ ! -x ${EXEC_N} ]] && { echo -e "${RED_BG}No exec rights on 'philo'. Tester exiting.${END}" ; make fclean >/dev/null 2>&1 ; exit ; }

# -------------------------------------------------------------------------------------------------------------------------------------
#  ARGUMENTS NUMBER BAD
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test arg nb (<4 && >5):${END} \t\t\t\t\t\t-->"
./${EXEC_N} > no_arg.txt 2> no_arg_err.txt
./${EXEC_N} 1 > one_arg.txt 2> one_arg_err.txt
./${EXEC_N} 1 800 > two_arg.txt 2> two_arg_err.txt
./${EXEC_N} 1 800 200 > three_arg.txt 2> three_arg_err.txt
./${EXEC_N} 5 800 200 200 7 56 > six_arg.txt 2> six_arg_err.txt
if [[ -s no_arg.txt || -s one_arg.txt || -s two_arg.txt || -s three_arg.txt || -s six_arg_.txt ]] ; then
	echo -ne "${YEL} ${EXEC_N} wrote on std out (fd 1)${END} "
fi
if [[ -s no_arg_err.txt || -s one_arg_err.txt || -s two_arg_err.txt || -s three_arg_err.txt || six_arg_err.txt ]] ; then
	echo -e "${GREEN} ${EXEC_N} wrote on std err (fd 2)${END} "
fi
rm -rf *arg*.txt
