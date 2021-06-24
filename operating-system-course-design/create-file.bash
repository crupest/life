
let dir_count=256
let file_count=500;

for dir_iter in `seq $dir_count`; do
    mkdir -p /mnt/fat-test/$dir_iter
    for iter in `seq $file_count`; do
        truncate -s 4KB /mnt/fat-test/$dir_iter/$iter;
    done
    echo "Created 500 files in dir $dir_iter";
done

df

for dir_iter in `seq $dir_count`; do
    mkdir -p /mnt/fat-test/$dir_iter
    for iter in `seq $file_count`; do
        if (($iter % 2 == 0)); then
            rm /mnt/fat-test/$dir_iter/$iter;
        fi
    done
    echo "Deleted 250 files in dir $dir_iter";
done

df

truncate -s 200MB /mnt/fat-test/big;

df
