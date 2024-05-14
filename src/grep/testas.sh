#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
EXE=cat.c
PATTERN=int
PATTERN_1=int
PATTERN_FILE=pattern.txt
FILE=test.txt
printf "${GREEN}====TEST RUNNING=====${NC}\n"

k=0
cnt=0
test() 
{
    if [[ $i == f || $j == f ]]
    then
        PATTERN=$PATTERN_FILE
    else
        PATTERN=$PATTERN_1
    fi
    grep -$i$j $PATTERN $FILE > y.txt &> error.txt
    make s21_grep && ./s21_grep -$i$j $PATTERN $FILE > y1.txt &> error1.txt
    leaks -quiet -atExit -- ./s21_grep -$i$j $PATTERN $FILE > m1.txt 
    leak=$(grep -a -e "0 leaks for 0 total leaked bytes" m1.txt)
    if [[ $(diff y.txt y1.txt) -eq 0 && $leak == *"0 leaks for 0 total leaked bytes"* && $(diff error.txt error1.txt) -eq 0 ]]
    then
        printf "TEST #$k ${GREEN}OK${NC} -$i$j \n"
        ((cnt++))
    else
        printf "TEST #$k ${RED}FAILED${NC} -$i$j \n"
        if [[ $(diff y.txt y1.txt) -eq 1 ]]
        then
            printf "$(diff y.txt y1.txt)"
        fi
        if [[ $leak != *"0 leaks for 0 total leaked bytes"*  ]]
        then
            printf "$(grep -a -e "0 leaks for 0 total leaked bytes" m1.txt)"
        fi
        if [[ $(diff error.txt error1.txt) -eq 1 ]]
        then
            printf "$(diff error.txt error1.txt)"
        fi
    fi
    rm y.txt y1.txt m1.txt error.txt error1.txt
    ((k++))
}

for i in e i v c l n h s o f
do
    test $i
done

for i in i v c l n h s o
do
    for j in e i v c l n h s o f
    do
        if [[ $i != $j ]]
        then
            test $i $j
        fi
    done
done

r=$((k-cnt))
printf "RESULT\n"
printf "ALL: $k\n"
printf "${GREEN}OK${NC}: $cnt\n"
printf "${RED}FAIL${NC}: $r\n"
