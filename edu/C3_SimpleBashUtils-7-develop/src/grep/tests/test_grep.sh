#!/ bin / bash

#тестовые файлы
testfile_sets=("tests/test.txt" "tests/test.txt tests/test.txt")
#pattern
pattern=example

#временные файлы
grep_res=grep_res.txt
s21_grep_res=s21_grep_res.txt

#флаги
options=("" "-i" "-e" "-v" "-c" "-cv" "-cvh" "-h" "-o" "-ov" "-n" "-no" "-l")

#Define color variables
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
RESET=$(tput sgr0)

for testfile_set in "${testfile_sets[@]}"
do
    echo "TESTING '$testfile_set' files"

    for opt in "${options[@]}"
    do

#записываем результаты выполнения утилит
#во временные файлы
        ./s21_grep $opt $pattern $testfile_set > $s21_grep_res
        grep $opt $pattern $testfile_set > $grep_res

#записываем результат теста в переменную
        if cmp --silent $s21_grep_res $grep_res
        then RESULT="${GREEN}OK${RESET}"
        else RESULT="${RED}FAILED${RESET}"
        fi

        echo "  '$opt' $RESULT"

#удаляем временные файлы
        rm $s21_grep_res $grep_res
    done

done

#-- - Тесты для опции '-s'
s_testfile_set="tests/test.txt not_existing_file tests/test.txt"

echo "TESTING '$s_testfile_set' files"
#флаги
s_options=("-s" "-sh" "-shn" "-so" "-sl")
for opt in "${s_options[@]}"
do

#записываем результаты выполнения утилит
#во временные файлы
    ./s21_grep $opt $pattern $s_testfile_set > $s21_grep_res
    grep $opt $pattern $s_testfile_set > $grep_res

#записываем результат теста в переменную
    if cmp --silent $s21_grep_res $grep_res
    then RESULT="${GREEN}OK${RESET}"
    else RESULT="${RED}FAILED${RESET}"
    fi

    echo "  '$opt' $RESULT"

#удаляем временные файлы
    rm $s21_grep_res $grep_res
done

#-- - Тесты для опции '-e'
patterns=("-e line -e example" "-e line")
testfile=tests/test.txt

for set_of_patterns in "${patterns[@]}"
do
    echo "TESTING '$set_of_patterns' set of patterns"

#записываем результаты выполнения утилит
#во временные файлы
    ./s21_grep $set_of_patterns $testfile > $s21_grep_res
    grep $set_of_patterns $testfile > $grep_res

#записываем результат теста в переменную
    if cmp --silent $s21_grep_res $grep_res
    then RESULT="${GREEN}OK${RESET}"
    else RESULT="${RED}FAILED${RESET}"
    fi

    echo "  '$opt' $RESULT"

#удаляем временные файлы
    rm $s21_grep_res $grep_res
done

#-- - Тесты для опции '-f'
patterns=("-f tests/patterns.txt" "-f tests/patterns.txt -f tests/patterns1.txt" "-f tests/patterns.txt -e word")
testfile=tests/test.txt

echo "TESTING '-f option' files"
#флаги
s_options=("-s" "-sh" "-shn" "-so" "-sl")
for pattern in "${patterns[@]}" 
do
    for opt in "${s_options[@]}"
    do

#записываем результаты выполнения утилит
#во временные файлы
        ./s21_grep $opt $pattern $testfile > $s21_grep_res
        grep $opt $pattern $testfile > $grep_res

#записываем результат теста в переменную
        if cmp --silent $s21_grep_res $grep_res
        then RESULT="${GREEN}OK${RESET}"
        else RESULT="${RED}FAILED${RESET}"
        fi

        echo "  '$opt' $RESULT"

#удаляем временные файлы
        rm $s21_grep_res $grep_res
    done
done
