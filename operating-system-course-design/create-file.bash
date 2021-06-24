let file_count=2*1024*2;

for iter in `seq $file_count`; do
    truncate -s 512KB /mnt/fat-test/$iter;
done

for iter in `seq $file_count`; do
    if (($iter % 2 == 0)); then
        rm /mnt/fat-test/$iter;
    fi
done

truncate -s 500MB /mnt/fat-test/big;
