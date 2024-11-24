#!/bin/bash

# Тестовые файлы
testfile_sets=("test.txt" "test2.txt test3.txt")
# Pattern
pattern=example

# Временные файлы
timestamp=$(date +%Y%m%d%H%M%S)
s21_grep_res="s21_grep_res_$timestamp.txt"
grep_res="grep_res_$timestamp.txt"

# Флаги
options=("" "-i" "-e" "-v" "-c" "-cv" "-cvh" "-h" "-o" "-ov" "-n" "-no" "-l")

# Определение цветов
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
RESET=$(tput sgr0)

for testfile_set in "${testfile_sets[@]}"
do
    echo "TESTING '$testfile_set' files"
    for opt in "${options[@]}"
    do
        # Записываем результаты выполнения утилит во временные файлы
        ../grep/s21_grep $opt $pattern $testfile_set > $s21_grep_res
        grep $opt $pattern $testfile_set > $grep_res

        # Записываем результат теста в переменную
        if cmp --silent $s21_grep_res $grep_res
        then
            RESULT="${GREEN}OK${RESET}"
            rm $s21_grep_res $grep_res
        else
            RESULT="${RED}FAILED${RESET}"
            mv $s21_grep_res "${s21_grep_res%.*}_failed_$opt.txt"
            mv $grep_res "${grep_res%.*}_failed_$opt.txt"
        fi
        echo "  '$opt' $RESULT"
    done
done

# Тесты для опции '-s'
s_testfile_set="test.txt not_existing_file test.txt"
echo "TESTING '$s_testfile_set' files"
s_options=("-s" "-sh" "-shn" "-so" "-sl")
for opt in "${s_options[@]}"
do
    ../grep/s21_grep $opt $pattern $s_testfile_set > $s21_grep_res
    grep $opt $pattern $s_testfile_set > $grep_res

    if cmp --silent $s21_grep_res $grep_res
    then
        RESULT="${GREEN}OK${RESET}"
        rm $s21_grep_res $grep_res
    else
        RESULT="${RED}FAILED${RESET}"
        mv $s21_grep_res "${s21_grep_res%.*}_failed_$opt.txt"
        mv $grep_res "${grep_res%.*}_failed_$opt.txt"
    fi
    echo "  '$opt' $RESULT"
done

# Тесты для опции '-e'
patterns=("-e line -e example" "-e line")
testfile=test.txt
for set_of_patterns in "${patterns[@]}"
do
    echo "TESTING '$set_of_patterns' set of patterns"
    ../grep/s21_grep $set_of_patterns $testfile > $s21_grep_res
    grep $set_of_patterns $testfile > $grep_res

    if cmp --silent $s21_grep_res $grep_res
    then
        RESULT="${GREEN}OK${RESET}"
        rm $s21_grep_res $grep_res
    else
        RESULT="${RED}FAILED${RESET}"
        mv $s21_grep_res "${s21_grep_res%.*}_failed_$opt.txt"
        mv $grep_res "${grep_res%.*}_failed_$opt.txt"
    fi
    echo "  '$opt' $RESULT"
done

# Тесты для опции '-f'
patterns=("-f patterns.txt" "-f patterns.txt -f patterns1.txt" "-f patterns.txt -e word")
testfile=test.txt
echo "TESTING '-f option' files"
s_options=("-s" "-sh" "-shn" "-so" "-sl")
for pattern in "${patterns[@]}"
do
    for opt in "${s_options[@]}"
    do
        ../grep/s21_grep $opt $pattern $testfile > $s21_grep_res
        grep $opt $pattern $testfile > $grep_res

        if cmp --silent $s21_grep_res $grep_res
        then
            RESULT="${GREEN}OK${RESET}"
            rm $s21_grep_res $grep_res
        else
            RESULT="${RED}FAILED${RESET}"
            mv $s21_grep_res "${s21_grep_res%.*}_failed_$opt.txt"
            mv $grep_res "${grep_res%.*}_failed_$opt.txt"
        fi
        echo "  '$opt' $RESULT"
    done
done
