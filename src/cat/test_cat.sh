
FUNC_SUCCESS=0
FUNC_FAIL=0
COUNTER=0
DIFF=""

declare -a flags=(
"-b"
"-e"
"-n"
"-s"
"-t"
"-v"
)

declare -a files=(
"s21_cattest1.txt"
"s21_cattest2.txt"
"s21_cattest3.txt"
)

declare -a commline=(
"OPT FILE"
)

declare -a exotic=(
"-b s21_cat.txt -s"
"-benstv nope.txt"
)


function testing()
{
    str=$(echo $@ | sed "s/OPT/$options/")
    str=$(echo $str | sed -e "s/FILE/$file/g")
    ./s21_cat $str > s21_cat_testing.log
    cat $str > system_cat_testing.log
    DIFF="$(diff -s s21_cat_testing.log system_cat_testing.log)"
    (( COUNTER++ ))
    if [ "$DIFF" == "Files s21_cat_testing.log and system_cat_testing.log are identical" ]
    then
        (( FUNC_SUCCESS++ ))
        echo "cat $str FUNCTIONALITY SUCCESS $COUNTER"
    else
        (( FUNC_FAIL++ ))
        echo "cat $str FUNCTIONALITY FAIL $COUNTER"
    fi
    rm s21_cat_testing.log system_cat_testing.log
}



for i in "${exotic[@]}"
do
    testing $i
done

for opt1 in "${flags[@]}"
do
    for opt2 in "${flags[@]}"
    do
        for opt3 in "${flags[@]}"
        do
            for opt4 in "${flags[@]}"
            do
                if [ $opt1 != $opt2 ] && [ $opt1 != $opt3 ] \
                && [ $opt1 != $opt4 ] && [ $opt2 != $opt3 ] \
                && [ $opt2 != $opt4 ] && [ $opt3 != $opt4 ]
                then
                    for file in "${files[@]}"
                    do
                        options="$opt1 $opt2 $opt3 $opt4"
                        testing $commline
                    done
                fi
            done
        done
    done
done

echo "FAIL: $FUNC_FAIL"
echo "SUCCESS: $FUNC_SUCCESS"
echo "ALL: $COUNTER"
