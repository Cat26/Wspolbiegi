#!/bin/bash

server=serwerfifo
#tworzenie fifo oraz nadawanie uprawnien
function createFifo {
	if [[ -e $server ]]; then
	  rm $server
	  mkfifo $server
	  chmod 777 $server
	else
	  mkfifo $server
	  chmod 777 $server
	fi
		}
#sprawdzanie za klientem  i odsylanie wiadomosci
if [[ "$1" ]]; then
	echo "Twoj wynik to: $(expr $2 + 1)" > $1

else
	trap "echo Zamykam Serwer; sleep 1; echo 3; sleep 1; echo 2; sleep 1; echo 1;echo Do Zobaczenia; exit 0" SIGUSR1
	trap "" SIGTERM
	trap "" SIGHUP
	createFifo
#odczytywanie wiadomosci trafiajacej do serwera
	while true
	do
		if read line < $server; then
			$0 $line &
		fi
	done
fi
