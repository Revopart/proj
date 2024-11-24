#!/bin/bash

# директория с тестовыми файлами
tf_dir=tests/testfiles/

# временные файлы
cat_res=tests/cat_res.txt
s21_cat_res=tests/s21_cat_res.txt

# флаги
options=("" "-b" "-e" "-n" "-s" "-t" "-v")

#Define color variables
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
RESET=$(tput sgr0)

for opt in "${options[@]}"
do
    echo "TESTING '$opt' option"
    for testfile in $tf_dir*
    do
        # извлекаем имя тестового файла из пути
        filename=$(basename $testfile)
    
        # записываем результаты выполнения утилит
        # во временные файлы
        cat $opt $testfile > $cat_res
        ./s21_cat $opt $testfile > $s21_cat_res

        if cmp --silent $cat_res $s21_cat_res
        then echo "    $filename ${GREEN}OK${RESET}"
        else echo "    $filename ${RED}FAILED${RESET}"
        fi

        # удаляем временные файлы
        rm $cat_res $s21_cat_res
    done
done