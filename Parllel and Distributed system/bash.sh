#!/bin/bash
g++ luserial.cpp -o luserial
g++ -fopenmp luomp.cpp -o luomp
g++ -pthread luthread.cpp -o luthread


x=10
while [ $x -le 1000 ]
do
  ./luserial $x

  x=$(( $x + 50 ))
done


y=10
while [ $y -le 1000 ]
do
  ./luomp $y 2

  y=$(( $y + 50 ))
done



z=10
while [ $z -le 1000 ]
do
  ./luthread $z 4

  z=$(( $z + 50 ))
done

sleep 5

python 2.py
python 1.py
