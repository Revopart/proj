#!/bin/bash

tf_dir="testfiles/"

# флаги
options=("" "-b" "-e" "-n" "-s" "-t" "--" "-q" "test" "b")
#options=("" "-b" "-e" "-n" "-s" "-t")
#options=("--" "-q" "test")
#options=("-b")
#options=("-b" "-e" "-be")
#options=("-b")
#options=("-s")
#options=("-be")
#options=("-b" "-e" "-n" "-s" "-t" "-be" "-bn" "-bs" "-bt" "-en" "-es" "-et" "-ns" "-nt" "-st" "-ben" "-bes" "-bet" "-bns" "-bnst" "-bnt" "-ens" "-enst" "-ent" "-est" "-bens" "-benst" "-best" "-bnst")

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
RESET=$(tput sgr0)


for opt in "${options[@]}"
do
    echo "TESTING '$opt' option"
    COUNTER=1
    for testfile in "${tf_dir}"*
    do

        filename=$(basename "$testfile")


        cat_res="cat_res_${opt}_${COUNTER}.txt"
        s21_cat_res="s21_cat_res_${opt}_${COUNTER}.txt"


        cat $opt "$testfile" &> "$cat_res"
        ../cat/s21_cat $opt "$testfile" &> "$s21_cat_res"



        if cmp --silent "$cat_res" "$s21_cat_res"
        then echo "    $filename ${GREEN}OK${RESET}"
        else echo "    $filename ${RED}FAILED${RESET}"
        fi

        rm $cat_res $s21_cat_res


        COUNTER=$((COUNTER + 1))
    done
done

for opt in "${options[@]}"
do
    echo "TESTING '$opt' option"
    for i in {1..10}
    do
        echo "  Run #$i"

        # Генерируем случайное количество файлов от 1 до 5
        num_files=$((RANDOM % 15 + 1))

        # Собираем все имена файлов в массив
        all_files=("${tf_dir}"*)

        # Массив для выбранных файлов
        selected_files=()

        # Заполнение массива выбранными файлами
        for (( j=0; j<num_files; j++ )); do
            index=$((RANDOM % ${#all_files[@]}))
            selected_files+=("${all_files[$index]}")
        done

        # Создаём строку из выбранных файлов для использования в командах
        file_string="${selected_files[@]}"

        cat_res="cat_res_${opt}_run${i}.txt"
        s21_cat_res="s21_cat_res_${opt}_run${i}.txt"

        # Вызываем команды cat с опцией и случайным набором файлов
        cat $opt $file_string &> "$cat_res"
        ../cat/s21_cat $opt $file_string &> "$s21_cat_res"

        # Сравниваем результаты
        if cmp --silent "$cat_res" "$s21_cat_res"
        then echo "    ${num_files} files ${GREEN}OK${RESET}"
        else echo "    ${num_files} files ${RED}FAILED${RESET}"
        fi

        # Удаление временных файлов результатов
        rm $cat_res $s21_cat_res
    done
done

