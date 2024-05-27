#! /bin/sh
./ppm2jpeg --outfile=./images/invader.jpg ./images/invader.pgm
test -f ./images/invader.jpg

./ppm2jpeg --outfile=./images/gris.jpg ./images/gris.pgm
test -f ./images/gris.jpg

./ppm2jpeg --outfile=./images/complexite.jpg ./images/complexite.pgm
test -f ./images/complexite.jpg

./ppm2jpeg --outfile=./images/bisou.jpg ./images/bisou.pgm
test -f ./images/bisou.jpg

./ppm2jpeg --sample=1x1,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x1,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_1x2,1x1,1x2.jpg

./ppm2jpeg --sample=1x2,1x2,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x2,1x2,1x1.jpg

./ppm2jpeg --sample=1x2,1x2,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_1x2,1x2,1x2.jpg

./ppm2jpeg --sample=1x3,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x3,1x1,1x1.jpg

./ppm2jpeg --sample=1x3,1x1,1x3 ./images/vertical.ppm --st
test -f ./images/vertical_1x3,1x1,1x3.jpg

./ppm2jpeg --sample=1x3,1x3,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x3,1x3,1x1.jpg

./ppm2jpeg --sample=1x3,1x3,1x3 ./images/vertical.ppm --st
test -f ./images/vertical_1x3,1x3,1x3.jpg

./ppm2jpeg --sample=1x4,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x1,1x1.jpg

./ppm2jpeg --sample=1x4,1x1,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x1,1x2.jpg

./ppm2jpeg --sample=1x4,1x1,1x4 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x1,1x4.jpg

./ppm2jpeg --sample=1x4,1x2,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x2,1x1.jpg

./ppm2jpeg --sample=1x4,1x2,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x2,1x2.jpg

./ppm2jpeg --sample=1x4,1x2,1x4 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x2,1x4.jpg

./ppm2jpeg --sample=1x4,1x4,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x4,1x1.jpg

./ppm2jpeg --sample=1x4,1x4,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_1x4,1x4,1x2.jpg

./ppm2jpeg --sample=2x1,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x1,1x1,1x1.jpg

./ppm2jpeg --sample=2x1,1x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x1,1x1,2x1.jpg

./ppm2jpeg --sample=2x1,2x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x1,2x1,1x1.jpg

./ppm2jpeg --sample=2x1,2x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x1,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x1,1x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x1,1x2.jpg

./ppm2jpeg --sample=2x2,1x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,2x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x1,2x2.jpg

./ppm2jpeg --sample=2x2,1x2,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x2,1x1.jpg

./ppm2jpeg --sample=2x2,1x2,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x2,1x2.jpg

./ppm2jpeg --sample=2x2,1x2,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x2,2x1.jpg

./ppm2jpeg --sample=2x2,1x2,2x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,1x2,2x2.jpg

./ppm2jpeg --sample=2x2,2x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x1,1x1.jpg

./ppm2jpeg --sample=2x2,2x1,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x1,1x2.jpg

./ppm2jpeg --sample=2x2,2x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,2x1,2x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x1,2x2.jpg

./ppm2jpeg --sample=2x2,2x2,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x2,1x1.jpg

./ppm2jpeg --sample=2x2,2x2,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x2,1x2.jpg

./ppm2jpeg --sample=2x2,2x2,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x2,2x2,2x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,1x1,1x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x3 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,1x1,1x3.jpg

./ppm2jpeg --sample=2x3,1x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,1x1,2x1.jpg

./ppm2jpeg --sample=2x3,1x3,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,1x3,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,2x1,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x3,2x1,2x1.jpg

./ppm2jpeg --sample=2x4,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_2x4,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x1,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,3x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x1,1x1,3x1.jpg

./ppm2jpeg --sample=3x1,3x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x1,3x1,1x1.jpg

./ppm2jpeg --sample=3x1,3x1,3x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x1,3x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,1x1,1x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,1x1,1x2.jpg

./ppm2jpeg --sample=3x2,1x1,3x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,1x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,1x2,1x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x2 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,1x2,1x2.jpg

./ppm2jpeg --sample=3x2,3x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_3x2,3x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,1x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,1x1,2x1.jpg

./ppm2jpeg --sample=4x1,1x1,4x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,1x1,4x1.jpg

./ppm2jpeg --sample=4x1,2x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,2x1,1x1.jpg

./ppm2jpeg --sample=4x1,2x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,2x1,2x1.jpg

./ppm2jpeg --sample=4x1,2x1,4x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,2x1,4x1.jpg

./ppm2jpeg --sample=4x1,4x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,4x1,1x1.jpg

./ppm2jpeg --sample=4x1,4x1,2x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x1,4x1,2x1.jpg

./ppm2jpeg --sample=4x2,1x1,1x1 ./images/vertical.ppm --st
test -f ./images/vertical_4x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x1,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x1,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x2,1x1,1x2.jpg

./ppm2jpeg --sample=1x2,1x2,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x2,1x2,1x1.jpg

./ppm2jpeg --sample=1x2,1x2,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x2,1x2,1x2.jpg

./ppm2jpeg --sample=1x3,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x3,1x1,1x1.jpg

./ppm2jpeg --sample=1x3,1x1,1x3 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x3,1x1,1x3.jpg

./ppm2jpeg --sample=1x3,1x3,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x3,1x3,1x1.jpg

./ppm2jpeg --sample=1x3,1x3,1x3 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x3,1x3,1x3.jpg

./ppm2jpeg --sample=1x4,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x1,1x1.jpg

./ppm2jpeg --sample=1x4,1x1,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x1,1x2.jpg

./ppm2jpeg --sample=1x4,1x1,1x4 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x1,1x4.jpg

./ppm2jpeg --sample=1x4,1x2,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x2,1x1.jpg

./ppm2jpeg --sample=1x4,1x2,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x2,1x2.jpg

./ppm2jpeg --sample=1x4,1x2,1x4 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x2,1x4.jpg

./ppm2jpeg --sample=1x4,1x4,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x4,1x1.jpg

./ppm2jpeg --sample=1x4,1x4,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_1x4,1x4,1x2.jpg

./ppm2jpeg --sample=2x1,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x1,1x1,1x1.jpg

./ppm2jpeg --sample=2x1,1x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x1,1x1,2x1.jpg

./ppm2jpeg --sample=2x1,2x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x1,2x1,1x1.jpg

./ppm2jpeg --sample=2x1,2x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x1,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x1,1x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x1,1x2.jpg

./ppm2jpeg --sample=2x2,1x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,2x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x1,2x2.jpg

./ppm2jpeg --sample=2x2,1x2,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x2,1x1.jpg

./ppm2jpeg --sample=2x2,1x2,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x2,1x2.jpg

./ppm2jpeg --sample=2x2,1x2,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x2,2x1.jpg

./ppm2jpeg --sample=2x2,1x2,2x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,1x2,2x2.jpg

./ppm2jpeg --sample=2x2,2x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x1,1x1.jpg

./ppm2jpeg --sample=2x2,2x1,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x1,1x2.jpg

./ppm2jpeg --sample=2x2,2x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,2x1,2x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x1,2x2.jpg

./ppm2jpeg --sample=2x2,2x2,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x2,1x1.jpg

./ppm2jpeg --sample=2x2,2x2,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x2,1x2.jpg

./ppm2jpeg --sample=2x2,2x2,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x2,2x2,2x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,1x1,1x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x3 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,1x1,1x3.jpg

./ppm2jpeg --sample=2x3,1x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,1x1,2x1.jpg

./ppm2jpeg --sample=2x3,1x3,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,1x3,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,2x1,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x3,2x1,2x1.jpg

./ppm2jpeg --sample=2x4,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_2x4,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x1,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,3x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x1,1x1,3x1.jpg

./ppm2jpeg --sample=3x1,3x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x1,3x1,1x1.jpg

./ppm2jpeg --sample=3x1,3x1,3x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x1,3x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,1x1,1x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,1x1,1x2.jpg

./ppm2jpeg --sample=3x2,1x1,3x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,1x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,1x2,1x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x2 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,1x2,1x2.jpg

./ppm2jpeg --sample=3x2,3x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_3x2,3x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,1x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,1x1,2x1.jpg

./ppm2jpeg --sample=4x1,1x1,4x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,1x1,4x1.jpg

./ppm2jpeg --sample=4x1,2x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,2x1,1x1.jpg

./ppm2jpeg --sample=4x1,2x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,2x1,2x1.jpg

./ppm2jpeg --sample=4x1,2x1,4x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,2x1,4x1.jpg

./ppm2jpeg --sample=4x1,4x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,4x1,1x1.jpg

./ppm2jpeg --sample=4x1,4x1,2x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x1,4x1,2x1.jpg

./ppm2jpeg --sample=4x2,1x1,1x1 ./images/horizontal.ppm --st
test -f ./images/horizontal_4x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x1,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x1,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x2,1x1,1x2.jpg

./ppm2jpeg --sample=1x2,1x2,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x2,1x2,1x1.jpg

./ppm2jpeg --sample=1x2,1x2,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x2,1x2,1x2.jpg

./ppm2jpeg --sample=1x3,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x3,1x1,1x1.jpg

./ppm2jpeg --sample=1x3,1x1,1x3 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x3,1x1,1x3.jpg

./ppm2jpeg --sample=1x3,1x3,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x3,1x3,1x1.jpg

./ppm2jpeg --sample=1x3,1x3,1x3 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x3,1x3,1x3.jpg

./ppm2jpeg --sample=1x4,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x1,1x1.jpg

./ppm2jpeg --sample=1x4,1x1,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x1,1x2.jpg

./ppm2jpeg --sample=1x4,1x1,1x4 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x1,1x4.jpg

./ppm2jpeg --sample=1x4,1x2,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x2,1x1.jpg

./ppm2jpeg --sample=1x4,1x2,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x2,1x2.jpg

./ppm2jpeg --sample=1x4,1x2,1x4 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x2,1x4.jpg

./ppm2jpeg --sample=1x4,1x4,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x4,1x1.jpg

./ppm2jpeg --sample=1x4,1x4,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_1x4,1x4,1x2.jpg

./ppm2jpeg --sample=2x1,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x1,1x1,1x1.jpg

./ppm2jpeg --sample=2x1,1x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x1,1x1,2x1.jpg

./ppm2jpeg --sample=2x1,2x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x1,2x1,1x1.jpg

./ppm2jpeg --sample=2x1,2x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x1,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x1,1x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x1,1x2.jpg

./ppm2jpeg --sample=2x2,1x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,2x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x1,2x2.jpg

./ppm2jpeg --sample=2x2,1x2,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x2,1x1.jpg

./ppm2jpeg --sample=2x2,1x2,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x2,1x2.jpg

./ppm2jpeg --sample=2x2,1x2,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x2,2x1.jpg

./ppm2jpeg --sample=2x2,1x2,2x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,1x2,2x2.jpg

./ppm2jpeg --sample=2x2,2x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x1,1x1.jpg

./ppm2jpeg --sample=2x2,2x1,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x1,1x2.jpg

./ppm2jpeg --sample=2x2,2x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,2x1,2x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x1,2x2.jpg

./ppm2jpeg --sample=2x2,2x2,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x2,1x1.jpg

./ppm2jpeg --sample=2x2,2x2,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x2,1x2.jpg

./ppm2jpeg --sample=2x2,2x2,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x2,2x2,2x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,1x1,1x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x3 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,1x1,1x3.jpg

./ppm2jpeg --sample=2x3,1x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,1x1,2x1.jpg

./ppm2jpeg --sample=2x3,1x3,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,1x3,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,2x1,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x3,2x1,2x1.jpg

./ppm2jpeg --sample=2x4,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_2x4,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x1,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,3x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x1,1x1,3x1.jpg

./ppm2jpeg --sample=3x1,3x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x1,3x1,1x1.jpg

./ppm2jpeg --sample=3x1,3x1,3x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x1,3x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,1x1,1x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,1x1,1x2.jpg

./ppm2jpeg --sample=3x2,1x1,3x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,1x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,1x2,1x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x2 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,1x2,1x2.jpg

./ppm2jpeg --sample=3x2,3x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_3x2,3x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,1x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,1x1,2x1.jpg

./ppm2jpeg --sample=4x1,1x1,4x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,1x1,4x1.jpg

./ppm2jpeg --sample=4x1,2x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,2x1,1x1.jpg

./ppm2jpeg --sample=4x1,2x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,2x1,2x1.jpg

./ppm2jpeg --sample=4x1,2x1,4x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,2x1,4x1.jpg

./ppm2jpeg --sample=4x1,4x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,4x1,1x1.jpg

./ppm2jpeg --sample=4x1,4x1,2x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x1,4x1,2x1.jpg

./ppm2jpeg --sample=4x2,1x1,1x1 ./images/thumbs.ppm --st
test -f ./images/thumbs_4x2,1x1,1x1.jpg

./ppm2jpeg --sample=1x1,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x1,1x1,1x1.jpg

./ppm2jpeg --sample=1x2,1x1,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x2,1x1,1x2.jpg

./ppm2jpeg --sample=1x2,1x2,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x2,1x2,1x1.jpg

./ppm2jpeg --sample=1x2,1x2,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x2,1x2,1x2.jpg

./ppm2jpeg --sample=1x3,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x3,1x1,1x1.jpg

./ppm2jpeg --sample=1x3,1x1,1x3 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x3,1x1,1x3.jpg

./ppm2jpeg --sample=1x3,1x3,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x3,1x3,1x1.jpg

./ppm2jpeg --sample=1x3,1x3,1x3 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x3,1x3,1x3.jpg

./ppm2jpeg --sample=1x4,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x1,1x1.jpg

./ppm2jpeg --sample=1x4,1x1,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x1,1x2.jpg

./ppm2jpeg --sample=1x4,1x1,1x4 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x1,1x4.jpg

./ppm2jpeg --sample=1x4,1x2,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x2,1x1.jpg

./ppm2jpeg --sample=1x4,1x2,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x2,1x2.jpg

./ppm2jpeg --sample=1x4,1x2,1x4 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x2,1x4.jpg

./ppm2jpeg --sample=1x4,1x4,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x4,1x1.jpg

./ppm2jpeg --sample=1x4,1x4,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_1x4,1x4,1x2.jpg

./ppm2jpeg --sample=2x1,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x1,1x1,1x1.jpg

./ppm2jpeg --sample=2x1,1x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x1,1x1,2x1.jpg

./ppm2jpeg --sample=2x1,2x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x1,2x1,1x1.jpg

./ppm2jpeg --sample=2x1,2x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x1,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x1,1x1.jpg

./ppm2jpeg --sample=2x2,1x1,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x1,1x2.jpg

./ppm2jpeg --sample=2x2,1x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x1,2x1.jpg

./ppm2jpeg --sample=2x2,1x1,2x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x1,2x2.jpg

./ppm2jpeg --sample=2x2,1x2,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x2,1x1.jpg

./ppm2jpeg --sample=2x2,1x2,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x2,1x2.jpg

./ppm2jpeg --sample=2x2,1x2,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x2,2x1.jpg

./ppm2jpeg --sample=2x2,1x2,2x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,1x2,2x2.jpg

./ppm2jpeg --sample=2x2,2x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x1,1x1.jpg

./ppm2jpeg --sample=2x2,2x1,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x1,1x2.jpg

./ppm2jpeg --sample=2x2,2x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x1,2x1.jpg

./ppm2jpeg --sample=2x2,2x1,2x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x1,2x2.jpg

./ppm2jpeg --sample=2x2,2x2,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x2,1x1.jpg

./ppm2jpeg --sample=2x2,2x2,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x2,1x2.jpg

./ppm2jpeg --sample=2x2,2x2,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x2,2x2,2x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,1x1,1x1.jpg

./ppm2jpeg --sample=2x3,1x1,1x3 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,1x1,1x3.jpg

./ppm2jpeg --sample=2x3,1x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,1x1,2x1.jpg

./ppm2jpeg --sample=2x3,1x3,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,1x3,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,2x1,1x1.jpg

./ppm2jpeg --sample=2x3,2x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x3,2x1,2x1.jpg

./ppm2jpeg --sample=2x4,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_2x4,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x1,1x1,1x1.jpg

./ppm2jpeg --sample=3x1,1x1,3x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x1,1x1,3x1.jpg

./ppm2jpeg --sample=3x1,3x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x1,3x1,1x1.jpg

./ppm2jpeg --sample=3x1,3x1,3x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x1,3x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,1x1,1x1.jpg

./ppm2jpeg --sample=3x2,1x1,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,1x1,1x2.jpg

./ppm2jpeg --sample=3x2,1x1,3x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,1x1,3x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,1x2,1x1.jpg

./ppm2jpeg --sample=3x2,1x2,1x2 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,1x2,1x2.jpg

./ppm2jpeg --sample=3x2,3x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_3x2,3x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,1x1,1x1.jpg

./ppm2jpeg --sample=4x1,1x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,1x1,2x1.jpg

./ppm2jpeg --sample=4x1,1x1,4x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,1x1,4x1.jpg

./ppm2jpeg --sample=4x1,2x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,2x1,1x1.jpg

./ppm2jpeg --sample=4x1,2x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,2x1,2x1.jpg

./ppm2jpeg --sample=4x1,2x1,4x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,2x1,4x1.jpg

./ppm2jpeg --sample=4x1,4x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,4x1,1x1.jpg

./ppm2jpeg --sample=4x1,4x1,2x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x1,4x1,2x1.jpg

./ppm2jpeg --sample=4x2,1x1,1x1 ./images/zig-zag.ppm --st
test -f ./images/zig-zag_4x2,1x1,1x1.jpg


