i=0
j=0
for i in $(seq 8 15);
do
    for j in $(seq 8 15)
    do
        ./make_generation_ppm.sh $i $j 1
    done
done