#!/bin/bash
shopt -s nullglob

if [ $# -ne 1 ]; then
    echo "please input exact one argument, problem number"
    exit 1
fi

problem_number=$1

mkdir -p ./output/$problem_number

cp ./test-data/$problem_number/*.in ./output/$problem_number/

mkdir -p ./temp

clang++ ./code/$problem_number.cpp -o ./temp/$problem_number -O2 -fsanitize=integer


for generator in ./test-data/$problem_number/*.cpp; do
test_data_number=`echo $generator | sed -r "s/.*([0-9]+)\.cpp/\1/"` 

clang++ $generator -o ./temp/$problem_number-$test_data_number-g -O2 -fsanitize=integer

./temp/$problem_number-$test_data_number-g > ./output/$problem_number/$test_data_number.in
done

for test_data in ./output/$problem_number/*.in; do
out_file=`echo $test_data | sed "s/\.in/.out/"`
./temp/$problem_number < $test_data | tee > $out_file
done
