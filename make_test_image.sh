#! /bin/bash

./src/MakefileTemp

for nom in $(ls ./images/our_images/*.pgm)
do
    ./a.out $nom ./images/conv_jpeg/$nom.jpeg
done

