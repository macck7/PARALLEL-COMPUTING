#!/bin/bash
g++ luserial.cpp -o luserial
g++ -fopenmp luomp.cpp -o luomp
g++ -pthread luthread.cpp -o luthread


x=100
while [ $x -le 2000 ]
do
  ./luserial $x

  x=$(( $x + 100 ))
done


y=100
while [ $y -le 2000 ]
do
  ./luomp $y 4

  y=$(( $y + 100 ))
done



z=100
while [ $z -le 2000 ]
do
  ./luthread $z 4

  z=$(( $z + 100 ))
done

sleep 5

python3 2.py
python3 1.py
