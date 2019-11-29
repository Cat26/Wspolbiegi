dane=dane.txt
wyniki=wyniki.txt

if [  -e $wyniki ]; then
  rm $wyniki
fi

  echo podaj liczbe
  read liczba
  echo $liczba > $dane

while [ ! -e $wyniki ]; do :
done

    value=$(<wyniki.txt)
    rm wyniki.txt

  echo "Wynik dodawania $liczba "+" $liczba "=" $value"
exit
