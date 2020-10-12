if [ $# -ne 1 ]
then
    echo "please provide exact one argument, problem number"
    exit 1
fi

pushd ./output/$1/
zip ./$1.zip *.in *.out
popd

mv ./output/$1/$1.zip ./output
