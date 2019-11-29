#!/bin/bash

dane=dane.txt
wyniki=wyniki.txt

while [ 1 ]; do
  if [ -e $dane ]; then
      liczba=$(<dane.txt)
      rm $dane
      echo $(expr $liczba + $liczba) > $wyniki
  fi
done
