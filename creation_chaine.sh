i=0
j=0
for i in $(seq 8 15);
do
    for j in $(seq 8 15)
    do
        ./make_generation_pgm.sh 1 $i $j
    done
done